#include QMK_KEYBOARD_H
#include "print.h"

#define NUM_LOCK_BITMASK 0b01
#define CAPS_LOCK_BITMASK 0b10

// World record for fastest index finger tapping is 1092 taps per minute, which
// is 55ms for a single tap.
// https://recordsetter.com/world-record/index-finger-taps-minute/46066
#define LED_CMD_TIMEOUT 200
#define DELTA_X_THRESHOLD 60
#define DELTA_Y_THRESHOLD 15

typedef enum {
    // You could theoretically define 0b00 and send it by having a macro send
    // the second tap after LED_CMD_TIMEOUT has elapsed.
    // CMD_EXTRA = 0b00,
    TG_SCROLL = 0b01,
    CYC_DPI   = 0b10,
    CMD_RESET = 0b11 // CMD_ prefix to avoid clash with QMK macro
} led_cmd_t;

// State
static bool   scroll_enabled  = false;
static bool   num_lock_state  = false;
static bool   caps_lock_state = false;
static bool   in_cmd_window   = false;
static int8_t delta_x         = 0;
static int8_t delta_y         = 0;

typedef struct {
    led_cmd_t led_cmd;
    uint8_t   num_lock_count;
    uint8_t   caps_lock_count;
} cmd_window_state_t;

#ifdef PIMORONI_TRACKBALL_ENABLE
#include "pimoroni_trackball.h"
#endif

#ifdef POINTING_DEVICE_ENABLE
	bool trackball_is_scrolling = true;		//Default mode is scrolling
	bool trackball_is_precision = false;	//Default mode is less precise
	bool was_scrolling = true;	//Remember preferred state of trackball scrolling
#endif

#ifdef VIA_ENABLE
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
      PM_SCROLL,		//Toggle trackball scrolling mode
      PM_PRECISION,		//Toggle trackball precision mode
	};
#else
	enum custom_keycodes { //Use USER 00 instead of SAFE_RANGE for Via. VIA json must include the custom keycode.
      PM_SCROLL,		//Toggle trackball scrolling mode
      PM_PRECISION,		//Toggle trackball precision mode
	};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {};

#ifdef POINTING_DEVICE_ENABLE
	void run_trackball_cleanup(void) {	//Set colour of trackball LED. Does not require RGBLIGHT_ENABLE if colour shorthands are not used.
		#ifdef POINTING_DEVICE_ENABLE
		if (scroll_enabled) {
			pimoroni_trackball_set_rgbw(0, 128, 0, 0x00);       // scrolling colour
		} else if (!trackball_is_precision) {
			pimoroni_trackball_set_rgbw(64, 0, 0, 0x00);       // Default colour
		} else {
			pimoroni_trackball_set_rgbw(217, 165, 33, 0x00);	//RGB_GOLDENROD in number form.
		}
		#endif
	}

	uint8_t pointing_device_handle_buttons(uint8_t buttons, bool pressed, pointing_device_buttons_t button) {
		if (pressed) {
			buttons |= 1 << (button);
			#ifdef HAPTIC_ENABLE	//Haptic feedback when trackball button is pressed
				DRV_pulse(4);		//sharp_click
			#endif
		} else {
			buttons &= ~(1 << (button));
		}
		return buttons;
	}

	report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
		// if (trackball_is_scrolling) {
		// 	mouse_report.h = mouse_report.x;
		// 	#ifndef PIMORONI_TRACKBALL_INVERT_X
		// 		mouse_report.v = 0.35*-mouse_report.y;	//Multiplier to lower scrolling sensitivity
		// 	#else
		// 		mouse_report.v = 0.35*mouse_report.y;	//invert vertical scroll direction
		// 	#endif
		// 	mouse_report.x = mouse_report.y = 0;
		// }

		// if (host_keyboard_led_state().num_lock) {
		// 	trackball_is_scrolling = true;
		// 	was_scrolling=true;
		// 	run_trackball_cleanup();
		// } else {
		// 	trackball_is_scrolling = false;
		// 	was_scrolling=false;
		// 	run_trackball_cleanup();
		// }

    if (scroll_enabled) {
        delta_x += mouse_report.x;
        delta_y += mouse_report.y;

        if (delta_x > DELTA_X_THRESHOLD) {
            mouse_report.h = 1;
            delta_x        = 0;
        } else if (delta_x < -DELTA_X_THRESHOLD) {
            mouse_report.h = -1;
            delta_x        = 0;
        }

        if (delta_y > DELTA_Y_THRESHOLD) {
            mouse_report.v = -1;
            delta_y        = 0;
        } else if (delta_y < -DELTA_Y_THRESHOLD) {
            mouse_report.v = 1;
            delta_y        = 0;
        }
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
		return mouse_report;
	}

	// #if !defined(MOUSEKEY_ENABLE)	//Allows for button clicks on keymap even though mousekeys is not defined.
	// 	static bool mouse_button_one, trackball_button_one;
	// #endif

	void trackball_register_button(bool pressed, enum mouse_buttons button) {
		report_mouse_t currentReport = pointing_device_get_report();
		if (pressed) {
			currentReport.buttons |= button;
		} else {
			currentReport.buttons &= ~button;
		}
		pointing_device_set_report(currentReport);
	}
#endif


// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// 	switch (keycode) { //For keycode overrides
// 		#ifdef POINTING_DEVICE_ENABLE //Allow modes when trackball is enabled.
// 				case PM_SCROLL:
// 					if (record->event.pressed) {
// 						if (trackball_is_scrolling || was_scrolling){ //Enable toggling for trackball scrolling
// 							trackball_is_scrolling=false;
// 							was_scrolling=false; //Tracks status of scrolling setting. Works with holding of layer key for mouse mode.
// 						} else{
// 							trackball_is_scrolling=true;
// 							was_scrolling=true;
// 						}
// 						run_trackball_cleanup();
// 						break;
// 					}
// 				case PM_PRECISION:
// 					if (record->event.pressed) {
// 						if (trackball_is_precision){ //Enable toggling for trackball precision
// 							pimoroni_trackball_set_cpi(1.75);
// 							trackball_is_precision=false;
// 						} else{
// 							pimoroni_trackball_set_cpi(0.8);
// 							trackball_is_precision=true;
// 						}
// 						run_trackball_cleanup();
// 						break;
// 					}
// 			#ifndef MOUSEKEY_ENABLE //Allow for using mouse buttons in the keymap when mouse keys is not enabled.
// 					case KC_MS_BTN1:
// 						mouse_button_one = record->event.pressed;
// 						trackball_register_button(mouse_button_one | trackball_button_one, MOUSE_BTN1);
// 						break;
// 					case KC_MS_BTN2:
// 						trackball_register_button(record->event.pressed, MOUSE_BTN2);
// 						break;
// 					case KC_MS_BTN3:
// 						trackball_register_button(record->event.pressed, MOUSE_BTN3);
// 						break;
// 			#endif
// 		#endif
// 		}
// 	return true;
// }

void keyboard_post_init_user(void)
{
	layer_move(0); 						//Start on layer0 by default to set LED colours. Can remove to save a very small amount of space.
	#ifdef POINTING_DEVICE_ENABLE
	//	pimoroni_trackball_set_cpi(1.75);	//Start trackball with lower precision mode
		run_trackball_cleanup();
	#endif
    num_lock_state  = host_keyboard_led_state().num_lock;
    caps_lock_state = host_keyboard_led_state().caps_lock;
}

uint32_t command_timeout(uint32_t trigger_time, void *cb_arg) {
    cmd_window_state_t *cmd_window_state = (cmd_window_state_t *)cb_arg;
#   ifdef CONSOLE_ENABLE
    uprintf("Received command 0b%02d (", cmd_window_state->led_cmd);
#   endif
    switch (cmd_window_state->led_cmd) {
        case TG_SCROLL:
#           ifdef CONSOLE_ENABLE
            uprint("TG_SCROLL)\n");
#           endif
            scroll_enabled = !scroll_enabled;
            run_trackball_cleanup();
            break;
        case CYC_DPI:
#           ifdef CONSOLE_ENABLE
            uprint("CYC_DPI)\n");
#           endif
            cycle_dpi();
            run_trackball_cleanup();
            break;
        case CMD_RESET:
#           ifdef CONSOLE_ENABLE
            uprint("RESET)\n");
#           endif
            reset_keyboard();
            break;
        default:
#           ifdef CONSOLE_ENABLE
            uprint("unknown)\n");
#           endif
            // Ignore unrecognised commands.
            break;
    }
    cmd_window_state->led_cmd         = 0;
    cmd_window_state->num_lock_count  = 0;
    cmd_window_state->caps_lock_count = 0;
    in_cmd_window                     = false;

    return 0; // Don't repeat
}

bool led_update_user(led_t led_state) {
    static cmd_window_state_t cmd_window_state = {
      .led_cmd = 0b00,
      .num_lock_count = 0,
      .caps_lock_count = 0
    };

    // Start timer to end command window if we are not already in the middle of
    // one.
    if (!in_cmd_window) {
        in_cmd_window = true;
        defer_exec(LED_CMD_TIMEOUT, command_timeout, &cmd_window_state);
    }

    // Set num lock and caps lock bits when each is toggled on and off within
    // the window.
    if (led_state.num_lock != num_lock_state) {
        cmd_window_state.num_lock_count++;

        if (cmd_window_state.num_lock_count == 2) {
            cmd_window_state.led_cmd |= NUM_LOCK_BITMASK;
            cmd_window_state.num_lock_count = 0;
        }
    }

    if (led_state.caps_lock != caps_lock_state) {
        cmd_window_state.caps_lock_count++;

        if (cmd_window_state.caps_lock_count == 2) {
            cmd_window_state.led_cmd |= CAPS_LOCK_BITMASK;
            cmd_window_state.caps_lock_count = 0;
        }
    }

    // Keep our copy of the LED states in sync with the host.
    num_lock_state  = led_state.num_lock;
    caps_lock_state = led_state.caps_lock;
    return true;
}

#ifdef POINTING_DEVICE_ENABLE
	void suspend_power_down_user(void) {	//Code does not work, need to confirm why
			pimoroni_trackball_set_rgbw(0,0,0, 0x00); //Turn off Pimoroni trackball LED when computer is sleeping
	}
#endif

#ifdef POINTING_DEVICE_ENABLE
	void suspend_wakeup_init_user(void) { //turn on Pimoroni LED when awoken
		run_trackball_cleanup();
	}
#endif



#include QMK_KEYBOARD_H
#include "print.h"

#define NUM_LOCK_BITMASK 0b001
#define CAPS_LOCK_BITMASK 0b010
#define SCROLL_LOCK_BITMASK 0b100

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
    TG_SCROLL = 0b001,
    CYC_DPI   = 0b010,
    CMD_RESET = 0b100 // CMD_ prefix to avoid clash with QMK macro
} led_cmd_t;

// State
static bool   scroll_enabled  = false;
static bool   num_lock_state  = false;
static bool   caps_lock_state = false;
static bool   scroll_lock_state = false;
static bool   in_cmd_window   = false;
static int8_t delta_x         = 0;
static int8_t delta_y         = 0;

typedef struct {
    led_cmd_t led_cmd;
    uint8_t   num_lock_count;
    uint8_t   caps_lock_count;
    uint8_t   scroll_lock_count;} cmd_window_state_t;

// #ifdef PIMORONI_TRACKBALL_ENABLE
// #include "pimoroni_trackball.h"
// #endif

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

// const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_5x1( KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, KC_MS_BTN2, KC_MS_BTN1 )
};

#ifdef POINTING_DEVICE_ENABLE
	void run_trackball_cleanup(void) {	//Set colour of trackball LED. Does not require RGBLIGHT_ENABLE if colour shorthands are not used.
		#ifdef POINTING_DEVICE_ENABLE
		if (scroll_enabled) {
			pimoroni_trackball_set_rgbw(255, 255, 77, 0x00);       // scrolling colour
		} else if (!trackball_is_precision) {
			pimoroni_trackball_set_rgbw(119, 92, 36, 0x00);       // Default colour
		} else {
			pimoroni_trackball_set_rgbw(119, 92, 36, 0x00);	//RGB_GOLDENROD in number form.
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

void keyboard_post_init_user(void)
{
	layer_move(0); 						//Start on layer0 by default to set LED colours. Can remove to save a very small amount of space.
	#ifdef POINTING_DEVICE_ENABLE
	//	pimoroni_trackball_set_cpi(1.75);	//Start trackball with lower precision mode
		run_trackball_cleanup();
	#endif
    num_lock_state  = host_keyboard_led_state().num_lock;
    caps_lock_state = host_keyboard_led_state().caps_lock;
    scroll_lock_state = host_keyboard_led_state().scroll_lock;
    #ifdef RGBLIGHT_ENABLE
        rgblight_enable_noeeprom();
        // rgblight_sethsv_noeeprom_blue();
        // rgblight_sethsv_noeeprom(HSV_GOLD);
        rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
        rgblight_setrgb_at(125, 92, 36, 0);
        rgblight_setrgb_at(125, 92, 36, 1);
        rgblight_setrgb_at(125, 92, 36, 2);
        rgblight_setrgb_at(125, 92, 36, 3);
    #endif

}

uint32_t command_timeout(uint32_t trigger_time, void *cb_arg) {
    cmd_window_state_t *cmd_window_state = (cmd_window_state_t *)cb_arg;
#   ifdef CONSOLE_ENABLE
    uprintf("Received command 0b%03x (", cmd_window_state->led_cmd);
#   endif
    switch (cmd_window_state->led_cmd) {
        case TG_SCROLL:
#           ifdef CONSOLE_ENABLE
            uprint("TG_SCROLL)\n");
#           endif
            // rgblight_toggle();
            // rgblight_setrgb_at(255, 128, 64, 0);
            #ifdef RGBLIGHT_ENABLE
                scroll_enabled = !scroll_enabled;
                if (scroll_enabled)
                {
                rgblight_setrgb_at(255, 255, 78, 0);
                rgblight_setrgb_at(255, 255, 78, 1);
                rgblight_setrgb_at(255, 255, 78, 2);
                rgblight_setrgb_at(255, 255, 78, 3);

                }
                if (!scroll_enabled)
                {
                rgblight_setrgb_at(125, 92, 36, 0);
                rgblight_setrgb_at(125, 92, 36, 1);
                rgblight_setrgb_at(125, 92, 36, 2);
                rgblight_setrgb_at(125, 92, 36, 3);
                }
            #endif
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
    cmd_window_state->scroll_lock_count = 0;

    in_cmd_window                     = false;

    return 0; // Don't repeat
}

bool led_update_user(led_t led_state) {
    static cmd_window_state_t cmd_window_state = {
      .led_cmd = 0b000,
      .num_lock_count = 0,
      .caps_lock_count = 0,
      .scroll_lock_count = 0
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

    if (led_state.scroll_lock != scroll_lock_state) {
        cmd_window_state.scroll_lock_count++;

        if (cmd_window_state.scroll_lock_count == 2) {
            cmd_window_state.led_cmd |= SCROLL_LOCK_BITMASK;
            cmd_window_state.scroll_lock_count = 0;
        }
    }


    // Keep our copy of the LED states in sync with the host.
    num_lock_state  = led_state.num_lock;
    caps_lock_state = led_state.caps_lock;
    scroll_lock_state = led_state.scroll_lock;

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

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_MS_WH_UP);
        } else {
            tap_code(KC_MS_WH_DOWN);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif


#ifdef RGB_MATRIX_ENABLE

#define NA NO_LED

/* RGB Positioning */
led_config_t g_led_config = { {

    { 0, 1, 2, 3 }
}, {
    { 0,  0 }, { 85,  0 }, { 170,  0}, { 255, 0 }
}, {
    4, 4, 4, 4
} };

#endif

#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "keymap_nordic.h"
#include "keymap_french.h"
#include "keymap_spanish.h"
#include "keymap_hungarian.h"
#include "keymap_swedish.h"
#include "keymap_br_abnt2.h"
#include "keymap_canadian_multilingual.h"
#include "keymap_german_ch.h"
#include "keymap_jp.h"
#include "keymap_korean.h"
#include "keymap_bepo.h"
#include "keymap_italian.h"
#include "keymap_slovenian.h"
#include "keymap_lithuanian_azerty.h"
#include "keymap_danish.h"
#include "keymap_norwegian.h"
#include "keymap_portuguese.h"
#include "keymap_contributions.h"
#include "keymap_czech.h"
#include "keymap_romanian.h"
#include "keymap_russian.h"
#include "keymap_uk.h"
#include "keymap_estonian.h"
#include "keymap_belgian.h"
#include "keymap_us_international.h"
#include "keymap_croatian.h"
#include "keymap_turkish_q.h"
#include "keymap_slovak.h"

#define KC_MAC_UNDO LGUI(KC_Z)
#define KC_MAC_CUT LGUI(KC_X)
#define KC_MAC_COPY LGUI(KC_C)
#define KC_MAC_PASTE LGUI(KC_V)
#define KC_PC_UNDO LCTL(KC_Z)
#define KC_PC_CUT LCTL(KC_X)
#define KC_PC_COPY LCTL(KC_C)
#define KC_PC_PASTE LCTL(KC_V)
#define ES_LESS_MAC KC_GRAVE
#define ES_GRTR_MAC LSFT(KC_GRAVE)
#define ES_BSLS_MAC ALGR(KC_6)
#define NO_PIPE_ALT KC_GRAVE
#define NO_BSLS_ALT KC_EQUAL
#define LSA_T(kc) MT(MOD_LSFT | MOD_LALT, kc)
#define BP_NDSH_MAC ALGR(KC_8)
#define SE_SECT_MAC ALGR(KC_6)
#define MOON_LED_LEVEL LED_LEVEL

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  ST_MACRO_0,
  ST_MACRO_1,
  ST_MACRO_2,
  ST_MACRO_3,
};


enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
  DANCE_2,
  DANCE_3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_moonlander(
    KC_GRAVE,       KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_NO,                                          KC_MS_BTN3,     KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_BSPACE,      
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_NO,                                          KC_MS_BTN2,     KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_DELETE,      
    KC_ESCAPE,      KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           ST_MACRO_0,                                                                     KC_MS_BTN1,     KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,       
    KC_LSHIFT,      KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       TD(DANCE_1),    
    KC_LCTRL,       KC_LGUI,        TD(DANCE_0),    KC_LALT,        MO(2),          KC_NO,                                                                                                          KC_NO,          MO(3),          KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       
    KC_SPACE,       KC_BSPACE,      KC_MS_BTN1,                     KC_MS_BTN1,     KC_DELETE,      KC_ENTER
  ),
  [1] = LAYOUT_moonlander(
    KC_ESCAPE,      KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_7,           KC_8,           KC_9,           KC_0,           KC_TRANSPARENT, 
    KC_TAB,         KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,           KC_BSLASH,      
    KC_CAPSLOCK,    KC_A,           KC_S,           KC_D,           KC_F,           KC_G,           KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_H,           KC_J,           KC_K,           KC_L,           KC_SCOLON,      KC_QUOTE,       
    KC_LSHIFT,      KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,                                           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,       TD(DANCE_2),    
    KC_LCTRL,       KC_LGUI,        KC_TRANSPARENT, KC_LALT,        MO(2),          KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, MO(3),          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_SPACE,       KC_LALT,        KC_LCTRL,                       KC_BSPACE,      KC_DELETE,      KC_ENTER
  ),
  [2] = LAYOUT_moonlander(
    KC_TILD,        KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_NO,                                          KC_NO,          KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_TRANSPARENT, 
    KC_TILD,        KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_NO,                                          KC_NO,          KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_NO,                                                                          KC_NO,          KC_F6,          KC_UNDS,        KC_PLUS,        KC_LCBR,        KC_RCBR,        KC_PIPE,        
    KC_LSHIFT,      KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,                                         KC_F12,         KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE,
    KC_LCTRL,       KC_LGUI,        KC_TRANSPARENT, KC_LALT,        KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_END,         KC_HOME,        KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_NO,                                          KC_NO,          KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_NO,                                          KC_NO,          KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_INSERT,      
    KC_TRANSPARENT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_NO,                                                                          KC_NO,          KC_F6,          KC_MINUS,       KC_EQUAL,       KC_LBRACKET,    KC_RBRACKET,    KC_BSLASH,      
    KC_TRANSPARENT, KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,                                         KC_F12,         KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, LCTL(KC_PGUP),  KC_PGDOWN,      KC_PGUP,        LCTL(KC_PGDOWN),
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [4] = LAYOUT_moonlander(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_MS_UP,       KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, ST_MACRO_1,     ST_MACRO_2,     ST_MACRO_3,     KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NUMLOCK,     KC_CAPSLOCK,    KC_SCROLLLOCK,  KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_MS_BTN1,     KC_MS_BTN2,     KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_WWW_BACK
  ),
  [5] = LAYOUT_moonlander(
    KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_NO,                                          KC_NO,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_TRANSPARENT, 
    KC_TRANSPARENT, RESET,          KC_TRANSPARENT, KC_TRANSPARENT, EEP_RST,        KC_TRANSPARENT, KC_NO,                                          KC_NO,          KC_TRANSPARENT, KC_CAPSLOCK,    KC_PSCREEN,     KC_SCROLLLOCK,  KC_PAUSE,       KC_NUMLOCK,     
    KC_TRANSPARENT, KC_TRANSPARENT, MU_MOD,         AU_ON,          AU_OFF,         KC_TRANSPARENT, KC_NO,                                                                          KC_NO,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, MU_ON,          MU_OFF,         KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT, RGB_TOG,        RGB_HUI,        RGB_SAI,        RGB_VAI,        
    KC_TRANSPARENT, KC_TRANSPARENT, TD(DANCE_3),    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                                                                                                 KC_TRANSPARENT, KC_TRANSPARENT, RGB_MOD,        RGB_HUD,        RGB_SAD,        RGB_VAD,        
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,                 KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = { {129,49,192}, {129,49,192}, {0,255,255}, {17,255,253}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {172,255,255}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {172,255,119}, {172,255,119}, {172,255,119}, {129,49,192}, {129,49,192}, {0,0,0}, {0,0,0}, {129,49,192}, {129,49,192}, {129,49,192}, {0,255,255}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {17,255,253}, {129,49,192}, {129,49,192}, {129,49,192}, {129,49,192}, {172,255,119}, {172,255,119}, {172,255,119}, {0,255,255}, {129,49,192}, {0,0,0}, {0,0,0} },

    [1] = { {0,255,255}, {68,255,85}, {68,255,85}, {17,255,253}, {68,255,85}, {68,255,85}, {68,255,85}, {17,255,253}, {68,255,85}, {68,255,85}, {68,255,85}, {17,255,253}, {17,255,253}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {17,255,253}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {172,255,255}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {17,255,253}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {17,255,253}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {17,255,253}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {68,255,85}, {0,255,255}, {68,255,85}, {68,255,85}, {68,255,85} },

    [2] = { {172,255,127}, {172,255,127}, {172,255,127}, {172,255,127}, {172,255,127}, {172,255,127}, {172,255,127}, {43,255,255}, {43,255,255}, {172,255,127}, {172,255,127}, {172,255,127}, {43,255,255}, {43,255,255}, {172,255,127}, {172,255,127}, {172,255,127}, {43,255,255}, {43,255,255}, {172,255,127}, {172,255,127}, {172,255,127}, {43,255,255}, {43,255,255}, {172,255,255}, {172,255,127}, {172,255,127}, {43,255,255}, {43,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {172,255,127}, {172,255,127}, {0,0,0}, {172,255,127}, {172,255,127}, {172,255,127}, {172,255,127}, {86,255,255}, {172,255,127}, {172,255,127}, {172,255,127}, {172,255,127}, {86,255,255}, {172,255,255}, {172,255,127}, {172,255,127}, {172,255,127}, {86,255,255}, {172,255,255}, {172,255,127}, {172,255,127}, {172,255,127}, {86,255,255}, {172,255,127}, {172,255,127}, {172,255,127}, {172,255,127}, {86,255,255}, {172,255,127}, {172,255,127}, {172,255,127}, {43,255,255}, {43,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {172,255,127}, {172,255,127}, {0,0,0}, {172,255,127} },

    [3] = { {17,255,126}, {17,255,126}, {17,255,126}, {17,255,126}, {17,255,126}, {17,255,126}, {17,255,126}, {43,255,255}, {43,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {43,255,255}, {43,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {43,255,255}, {43,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {43,255,255}, {43,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {43,255,255}, {43,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {17,255,126}, {17,255,126}, {0,0,0}, {17,255,126}, {17,255,126}, {37,255,255}, {17,255,126}, {86,255,255}, {213,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {86,255,255}, {20,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {86,255,255}, {20,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {86,255,255}, {213,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {86,255,255}, {17,255,253}, {17,255,126}, {17,255,126}, {43,255,255}, {43,255,255}, {17,255,126}, {17,255,126}, {17,255,126}, {17,255,126}, {17,255,126}, {0,0,0}, {17,255,126} },

    [4] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {20,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {20,255,255}, {20,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {20,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {20,255,255}, {20,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {215,218,204}, {172,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {215,218,204}, {172,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {215,218,204}, {172,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [5] = { {43,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {43,255,255}, {0,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {43,255,255}, {0,0,0}, {86,255,255}, {0,0,0}, {0,0,0}, {43,255,255}, {0,0,0}, {86,255,255}, {86,255,255}, {0,0,0}, {43,255,255}, {0,255,255}, {86,255,255}, {86,255,255}, {0,0,0}, {43,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {43,255,255}, {20,255,255}, {0,0,0}, {86,255,255}, {86,255,255}, {43,255,255}, {37,255,255}, {0,0,0}, {86,255,255}, {86,255,255}, {43,255,255}, {20,255,255}, {0,0,0}, {86,255,255}, {86,255,255}, {43,255,255}, {37,255,255}, {0,0,0}, {86,255,255}, {86,255,255}, {43,255,255}, {20,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {43,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 0:
      set_layer_color(0);
      break;
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
    case 4:
      set_layer_color(4);
      break;
    case 5:
      set_layer_color(5);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case ST_MACRO_0:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_NUMLOCK) SS_DELAY(100) SS_TAP(X_NUMLOCK));

    }
    break;
    case ST_MACRO_1:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_NUMLOCK) SS_DELAY(100) SS_TAP(X_NUMLOCK));

    }
    break;
    case ST_MACRO_2:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_CAPSLOCK) SS_DELAY(100) SS_TAP(X_CAPSLOCK));

    }
    break;
    case ST_MACRO_3:
    if (record->event.pressed) {
      SEND_STRING(SS_TAP(X_SCROLLLOCK) SS_DELAY(100) SS_TAP(X_SCROLLLOCK));

    }
    break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
  }
  return true;
}

typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[4];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_HOLD: layer_on(4); break;
        case DOUBLE_TAP: layer_move(5); break;
    }
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_HOLD: layer_off(4); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(KC_ENTER);
        tap_code16(KC_ENTER);
        tap_code16(KC_ENTER);
    }
    if(state->count > 3) {
        tap_code16(KC_ENTER);
    }
}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(KC_ENTER); break;
        case SINGLE_HOLD: register_code16(KC_RSHIFT); break;
        case DOUBLE_TAP: layer_move(1); break;
        case DOUBLE_SINGLE_TAP: tap_code16(KC_ENTER); register_code16(KC_ENTER);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(KC_ENTER); break;
        case SINGLE_HOLD: unregister_code16(KC_RSHIFT); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(KC_ENTER); break;
    }
    dance_state[1].step = 0;
}
void dance_2_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_2_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_2_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[2].step = dance_step(state);
    switch (dance_state[2].step) {
        case SINGLE_HOLD: register_code16(KC_RSHIFT); break;
        case DOUBLE_TAP: layer_move(0); break;
    }
}

void dance_2_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[2].step) {
        case SINGLE_HOLD: unregister_code16(KC_RSHIFT); break;
    }
    dance_state[2].step = 0;
}
void dance_3_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_3_reset(qk_tap_dance_state_t *state, void *user_data);

void dance_3_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[3].step = dance_step(state);
    switch (dance_state[3].step) {
        case DOUBLE_TAP: layer_move(0); break;
    }
}

void dance_3_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[3].step) {
    }
    dance_state[3].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
        [DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_2_finished, dance_2_reset),
        [DANCE_3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_3_finished, dance_3_reset),
};


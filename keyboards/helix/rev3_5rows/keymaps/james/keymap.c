/* Copyright 2020 yushakobo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include <string.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
//   EISU = SAFE_RANGE,
//   KANA,
  ADJUST,
  RGBRST
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST2 MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   [  |   ]  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Esc  | Alt  | GUI  | Lower |Space |Bksp |Del |Enter | Raise | Left | Down |  Up  |Right |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT(
    //   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    //   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
    //   KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    //   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
    //   KC_LCTL, KC_LALT, ADJUST,  KC_LGUI, LOWER,   KC_SPC,  _______, _______, KC_ENT,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT

  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  _______, _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_LCTL, KC_LGUI, ADJUST, KC_LALT, LOWER,   KC_SPC, _______, _______, KC_ENT,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT



    ),
  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |   ^  |   &  |   *  |   (  |   )  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   _  |   +  |   {  |   }  |  |   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | CAPS |  F7  |  F8  |  F9  |  F10 |  F11 |  (   |   )  |  F12 |      |      | Home | End  |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT(
    //   _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
    //   _______, KC_PLUS, KC_MINS, KC_LCBR, KC_RCBR, KC_PIPE,                   _______, _______, _______, _______, _______,  KC_F12,
    //   _______, KC_ASTR, KC_SLSH, KC_LPRN, KC_RPRN, KC_BSLS,                   _______, _______, _______, _______, _______,  _______,
    //   _______, KC_EQL,  _______, KC_LBRC, KC_RBRC, KC_UNDS, _______, _______, KC_MPRV, KC_MSTP, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,
    //   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_END, KC_HOME, _______

  KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                  KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                  KC_CIRC,  KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
  KC_DEL,    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                    KC_F6,  KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11, _______, _______, KC_F12, KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,
  _______, _______, _______, _______, _______, _______, _______, _______,_______, _______, _______,  KC_END, KC_HOME, _______


      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | CAPS |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |  F12 |      |      |PageDn|PageUp|      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT(
    //   AU_TOG,  _______, _______, _______, _______, _______,                   _______, _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_NUM,
    //   MU_TOG,  _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_INS,
    //   MU_MOD,  _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
    //   KC_CAPS, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MSTP, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,
    //   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LCTL(KC_PGUP), KC_PGDN, KC_PGUP, LCTL(KC_PGDN)


  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_INS,
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, KC_F12,  KC_MPRV, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY,
  _______, _______, _______, _______, _______, _______, _______, _______,_______, _______, LCTL(KC_PGUP), KC_PGDN, KC_PGUP, LCTL(KC_PGDN)



      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|EEPRST|      |      |             |      |      |      |      |      |  Del |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      | Mac  |             | Win  |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT(
    //   _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
    //   _______, QK_BOOT,  RGBRST, EEP_RST, _______, _______,                   _______, _______, _______, _______, _______,  KC_F12,
    //   _______, _______, _______, _______, _______, AG_NORM,                   AG_SWAP, _______, _______, _______, _______, _______,
    //   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
    //   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD

  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, QK_BOOT, DB_TOGG, _______, _______, _______,                    _______, _______, _______,_______, _______, KC_DEL,
  _______, _______, _______,  AU_ON,   AU_OFF,  AG_NORM,                    AG_SWAP, _______,  _______, _______,  _______, _______,
  _______, _______, _______,  MU_ON,   MU_OFF,  MI_ON,    _______, _______, MI_OFF,  _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD



      )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left side encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Right side encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // case EISU:
    //   if (record->event.pressed) {
    //     if (is_mac_mode()) {
    //       register_code(KC_LANG2);
    //     }else{
    //       tap_code16(LALT(KC_GRAVE));
    //     }
    //   } else {
    //     unregister_code(KC_LANG2);
    //   }
    //   return false;
    //   break;
    // case KANA:
    //   if (record->event.pressed) {
    //     if (is_mac_mode()) {
    //       register_code(KC_LANG1);
    //     }else{
    //       tap_code16(LALT(KC_GRAVE));
    //     }
    //   } else {
    //     unregister_code(KC_LANG1);
    //   }
    //   return false;
    //   break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_LOWER);
        layer_on(_RAISE);
      } else {
        layer_off(_LOWER);
        layer_off(_RAISE);
      }
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}

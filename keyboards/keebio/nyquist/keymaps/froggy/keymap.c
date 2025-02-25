#include QMK_KEYBOARD_H
#include <string.h>

#ifndef MAX
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif
#ifndef MIN
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// 遅延入力処理用定数と変数
// レイヤーキーとの同時打鍵を実現するために一時的な入力内容を静的変数に保持する
// DELAY_TIME以内であればレイヤーキーの押下が後でも反映される
#define DELAY_TIME  75 // 遅延入力有効時間 (ms)
static uint16_t key_timer; // 遅延入力用タイマー
static uint16_t tap_timer; // タップ用タイマー
static uint16_t delay_registered_code; // 遅延入力されたキーコード
static uint8_t delay_mat_row; // 遅延入力された行
static uint8_t delay_mat_col; // 遅延入力された列
static bool delay_key_stat; // 遅延入力キーがあるときにtrue
static bool delay_key_pressing; // 延入力キーが押されている間はtrue
static bool tapping_key;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _OPT 1
#define _FUNC 2
#define _SYM 3
#define _NUM 4
#define _WASD 5

bool RGBAnimation = false; //Flag for LED Layer color Refresh.

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  EISU,
  KANA,
  RGBRST,
  RGBOFF,
  RGB1,
  RGB2,
  RGB3,
  OPT_TAP_SP,
  SYM_TAP_ENT,
  DESKTOP,
  MAC,
  WIN,
  WASD,
};


bool is_mac_mode(void) {
    return keymap_config.swap_lalt_lgui == false;
}


#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  C+z |   ;  |   [  |   (  |   <  |   {  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | KANA |   P  |   K  |   R  |   A  |   F  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  BS  |   D  |   T  |   H  |   E  |   O  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Y  |   S  |   N  |   I  |   U  |Space |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Alt  | Gui  | Sym  | Num  | OPT  | Ent  |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_BASE] = LAYOUT( \
      LCTL(KC_Z),    KC_SCLN,       KC_LBRC,       KC_LPRN,      KC_LT,     KC_LCBR,                                _______,  _______,  _______,  _______,  _______,  _______, \
      KANA,          KC_P,          KC_K,          KC_R,         KC_A,      KC_F,                                   _______,  _______,  _______,  _______,  _______,  _______, \
      KC_BSPC,       KC_D,          KC_T,          KC_H,         KC_E,      KC_O,                                   _______,  _______,  _______,  _______,  _______,  _______, \
      OSM(MOD_LSFT), KC_Y,          KC_S,          KC_N,         KC_I,      KC_U,          _______,  _______,  _______,  _______,  _______,  _______, \
      OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), SYM_TAP_ENT,  MO(_NUM),  OPT_TAP_SP,    _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Opt
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  Esc |  :   |  ]   |  )   |  >   |  }   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  EISU|   J  |   M  |   B  |   '  |  Tab |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   .  |   V  |   C  |   L  |   Z  |  Q   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |   X  |   G  |   W  |   -  |  Del | Esc  |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |   ,  | DTOP |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_OPT] = LAYOUT( \
      KC_ESC,  KC_COLN,KC_RBRC, KC_RPRN,KC_GT,     KC_RCBR,                   _______,  _______,  _______,  _______,  _______,  _______, \
      EISU,    KC_J,   KC_M,    KC_B,   KC_QUOT,   KC_TAB,                    _______,  _______,  _______,  _______,  _______,  _______, \
      KC_DOT,  KC_V,   KC_C,    KC_L,   KC_Z,      KC_Q,                      _______,  _______,  _______,  _______,  _______,  _______, \
      _______, KC_X,   KC_G,    KC_W,   KC_MINUS,  KC_DEL,     _______,  _______,  _______,  _______,  _______,  _______, \
      _______, _______,_______, KC_COMM,DESKTOP,   _______,   _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Func
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |RGBRST|  Hue |      |  RST |  Mac |  Win |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | RGB1 | VAL+ |  F7  |  F8  |  F9  |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | RGB2 | VAL- |  F4  |  F5  |  F6  | F12  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | RGB3 |  F10 |  F1  |  F2  |  F3  | F11  |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |RGBOFF|      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_FUNC] = LAYOUT( \
      RGBRST,RGB_HUI, _______, QK_RBT,   MAC,     WIN,                         _______,  _______,  _______,  _______,  _______,  _______, \
      RGB1,  RGB_VAI, KC_F7,   KC_F8,   KC_F9,   _______,                     _______,  _______,  _______,  _______,  _______,  _______, \
      RGB2,  RGB_VAD, KC_F4,   KC_F5,   KC_F6,   KC_F12,                      _______,  _______,  _______,  _______,  _______,  _______, \
      RGB3,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,      _______,  _______,  _______,  _______,  _______,  _______, \
      RGBOFF,_______, _______, _______, _______, _______,     _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Sym
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  Ins |  GRV |      |  PU  |  PD  |   ^  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   \  |   #  |   =  |   ?  |   %  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   $  |  upA |   @  |   !  |   |  |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  CL  |  <-  |  dwA |  ->  |   _  |   &  |      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |  PS  |      |   ~  |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_SYM] = LAYOUT( \
      KC_INS,  KC_GRV,  _______, KC_PGUP, KC_PGDN, KC_CIRC,                   _______,  _______,  _______,  _______,  _______,  _______, \
      _______, KC_BSLS, KC_HASH, KC_EQL,  KC_QUES, KC_PERC,                   _______,  _______,  _______,  _______,  _______,  _______, \
      _______, KC_DLR,  KC_UP,   KC_AT,   KC_EXLM, KC_PIPE,                   _______,  _______,  _______,  _______,  _______,  _______, \
      KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_UNDS, KC_AMPR,   _______,  _______,  _______,  _______,  _______,  _______, \
      _______, _______, KC_PSCR, _______, KC_TILD, _______,   _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      | Func | home |  End |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   *  |  7   |  8   |  9   |  -   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |  .   |   /  |  4   |  5   |  6   |  +   |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |  LN  |  0   |  1   |  2   |  3   |C+S+F1|      |      |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |  ,   |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NUM] = LAYOUT( \
      _______,  _______, OSL(_FUNC), KC_HOME, KC_END,  _______,                          _______,  _______,  _______,  _______,  _______,  _______, \
      _______,  KC_ASTR, KC_P7,      KC_P8,   KC_P9,   KC_MINS,                          _______,  _______,  _______,  _______,  _______,  _______, \
      KC_PDOT,  KC_SLSH, KC_P4,      KC_P5,   KC_P6,   KC_PLUS,                          _______,  _______,  _______,  _______,  _______,  _______, \
      KC_NUM,  KC_P0,   KC_P1,      KC_P2,   KC_P3,   LCTL(S(KC_F1)),   _______,  _______,  _______,  _______,  _______,  _______, \
      _______,  _______, KC_PDOT,    KC_COMM, _______, _______,          _______,  _______,  _______,  _______,  _______,  _______ \
      ),

  [_WASD] = LAYOUT( \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
        OSL(_FUNC),  KC_LCTL, KC_LALT, KC_LGUI, MO(_SYM),   KC_SPC,  KC_SPC,  MO(_NUM),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
      )





};
#else
#error "undefined keymaps"
#endif



// define variables for reactive RGB
//bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool find_mairix(uint16_t keycode, uint8_t *row, uint8_t *col){
  for(uint8_t i=0; i<MATRIX_ROWS; i++){
    for(uint8_t j=0; j<MATRIX_COLS; j++){
      if( pgm_read_word(&(keymaps[_BASE][i][j]))==keycode){
        *row = i;
        *col = j;
        return true;
      }
    }
  }
  return false;
}

void unregister_delay_code(void){
  if(delay_registered_code){
    unregister_code(delay_registered_code);
    if (delay_registered_code & QK_LSFT){
      unregister_code(KC_LSFT);
    }
    if (delay_registered_code & QK_LCTL){
      unregister_code(KC_LCTL);
    }
    if (delay_registered_code & QK_LALT){
      unregister_code(KC_LALT);
    }
    if (delay_registered_code & QK_LGUI){
      unregister_code(KC_LGUI);
    }
    delay_registered_code=0;
  }
}

void register_delay_code(uint8_t layer){
  if(delay_key_stat){
    unregister_delay_code();

    uint16_t code = pgm_read_word(&(keymaps[layer][delay_mat_row][delay_mat_col]));
    if (code & QK_LSFT){
      register_code(KC_LSFT);
    }
    if (code & QK_LCTL){
      register_code(KC_LCTL);
    }
    if (code & QK_LALT){
      register_code(KC_LALT);
    }
    if (code & QK_LGUI){
      register_code(KC_LGUI);
    }
    register_code(code);
    delay_registered_code = code;
    delay_key_stat = false;
    tapping_key = true;
  }
}

#ifdef RGBLIGHT_ENABLE
struct keybuf {
  char col, row;
  char frame;
};
struct keybuf keybufs[256];
unsigned char keybuf_begin, keybuf_end;

int col, row;
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  #ifdef RGBLIGHT_ENABLE
    col = record->event.key.col;
    row = record->event.key.row;
    if (record->event.pressed && ((row < 5 && is_keyboard_master()) || (row >= 5 && !is_keyboard_master()))) {
      int end = keybuf_end;
      keybufs[end].col = col;
      keybufs[end].row = row % 5;
      keybufs[end].frame = 0;
      keybuf_end ++;
    }
  #endif

  if ((tap_timer&&keycode!=OPT_TAP_SP) && (tap_timer&&keycode!=SYM_TAP_ENT)) {
    tapping_key = true;
  }

  if(keycode==delay_registered_code){
      if (!record->event.pressed){
        unregister_delay_code();
      }
  }

void set_mac_mode(bool macmode) {
    /* The result is the same as pressing the AG_NORM(=MAGIC_UNSWAP_ALT_GUI)/AG_SWAP(=MAGIC_SWAP_ALT_GUI) keys.
     * see
     *   https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L123-L124
     *   https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L80-L81
     */
    keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = !macmode;
    eeconfig_update_keymap(keymap_config.raw);
}


  switch (keycode) {
    case KC_SCLN:
    case KC_LBRC:
    case KC_LPRN:
    case KC_LT:
    case KC_LCBR:
    case KC_P:
    case KC_K:
    case KC_R:
    case KC_A:
    case KC_F:
    case KC_BSPC:
    case KC_D:
    case KC_T:
    case KC_H:
    case KC_E:
    case KC_O:
    case KC_Y:
    case KC_S:
    case KC_N:
    case KC_I:
    case KC_U:
    case LCTL(KC_Z):
    case KC_SPC:
      if (record->event.pressed) {
        register_delay_code(_BASE);
        unregister_delay_code();
        if(find_mairix(keycode, &delay_mat_row, &delay_mat_col)){
          key_timer = timer_read();
          delay_key_stat = true;
          delay_key_pressing = true;
        }
      }else{
        delay_key_pressing = false;
      }
      return false;
      break;
    case OPT_TAP_SP:
      if (record->event.pressed) {
        tapping_key = false;
        register_delay_code(_OPT);
        unregister_delay_code();
        layer_on(_OPT);
        tap_timer = timer_read();
      }else{
        layer_off(_OPT);
        if(tapping_key==false && timer_elapsed(tap_timer) < TAPPING_TERM){
          SEND_STRING(" ");
        }
        tap_timer = 0;
      }
      return false;
      break;

    case SYM_TAP_ENT:
      if (record->event.pressed) {
        tapping_key = false;
        register_delay_code(_SYM);
        unregister_delay_code();
        layer_on(_SYM);
        tap_timer = timer_read();
      }else{
        layer_off(_SYM);
        if(tapping_key==false && timer_elapsed(tap_timer) < TAPPING_TERM){
          tap_code16(KC_ENT);
        }
        tap_timer = 0;
      }
      return false;
      break;

   case EISU:
      if (record->event.pressed) {
        if (is_mac_mode()) {
          register_code(KC_LNG2);
        }else{
          tap_code16(LALT(KC_GRAVE));
        }
      } else {
        unregister_code(KC_LNG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if (is_mac_mode()) {
          register_code(KC_LNG1);
        }else{
          tap_code16(LALT(KC_GRAVE));
        }
      } else {
        unregister_code(KC_LNG1);
      }
      return false;
      break;
    case DESKTOP:
      if (record->event.pressed) {
        if (is_mac_mode()) {
          register_code(KC_F11);
        }else{
          SEND_STRING(SS_LGUI("d"));
        }
      } else {
        unregister_code(KC_F11);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
          RGBAnimation = false;
        }
      #endif
      break;
    case RGBOFF:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_disable();
        }
      #endif
      break;
    case RGB1:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_RAINBOW_MOOD);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case RGB2:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_RAINBOW_SWIRL + 1);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case RGB3:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          RGBAnimation = true;
          rgblight_mode(RGBLIGHT_MODE_KNIGHT);
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case MAC:
      if (record->event.pressed) {
        set_mac_mode(true);
      }
      break;
    case WIN:
      if (record->event.pressed) {
        set_mac_mode(false);
      }
      break;
    }
  return true;
}



//keyboard start-up code. Runs once when the firmware starts up.
void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_OPT 2
#define L_FUNC 4
#define L_SYM 8
#define L_NUM 16
#define L_FNLAYER 64
#define L_NUMLAY 128
#define L_NLOWER 136
#define L_NFNLAYER 192
#define L_MOUSECURSOR 256

// LED Effect
#ifdef RGBLIGHT_ENABLE
unsigned char rgb[7][5][3];
void led_ripple_effect(char r, char g, char b) {
    static int scan_count = -10;
    static int keys[] = { 6, 6, 6, 7, 7 };
    static int keys_sum[] = { 0, 6, 12, 18, 25 };

    if (scan_count == -1) {
      rgblight_enable_noeeprom();
      rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    } else if (scan_count >= 0 && scan_count < 5) {
      for (unsigned char c=keybuf_begin; c!=keybuf_end; c++) {
        int i = c;
        // FIXME:

        int y = scan_count;
        int dist_y = abs(y - keybufs[i].row);
        for (int x=0; x<keys[y]; x++) {
          int dist = abs(x - keybufs[i].col) + dist_y;
          if (dist <= keybufs[i].frame) {
            int elevation = MAX(0, (8 + dist - keybufs[i].frame)) << 2;
            if (elevation) {
              if ((rgb[x][y][0] != 255) && r) { rgb[x][y][0] = MIN(255, elevation + rgb[x][y][0]); }
              if ((rgb[x][y][1] != 255) && g) { rgb[x][y][1] = MIN(255, elevation + rgb[x][y][1]); }
              if ((rgb[x][y][2] != 255) && b) { rgb[x][y][2] = MIN(255, elevation + rgb[x][y][2]); }
            }
          }
        }
      }
    } else if (scan_count == 5) {
      for (unsigned char c=keybuf_begin; c!=keybuf_end; c++) {
        int i = c;
        if (keybufs[i].frame < 18) {
          keybufs[i].frame ++;
        } else {
          keybuf_begin ++;
        }
      }
    } else if (scan_count >= 6 && scan_count <= 10) {
      int y = scan_count - 6;
      for (int x=0; x<keys[y]; x++) {
        int at = keys_sum[y] + ((y & 1) ? x : (keys[y] - x - 1));
        led[at].r = rgb[x][y][0];
        led[at].g = rgb[x][y][1];
        led[at].b = rgb[x][y][2];
      }
      rgblight_set();
    } else if (scan_count == 11) {
      memset(rgb, 0, sizeof(rgb));
    }
    scan_count++;
    if (scan_count >= 12) { scan_count = 0; }
}
#endif

uint8_t layer_state_old;

//runs every scan cycle (a lot)
void matrix_scan_user(void) {
  if(delay_key_stat && (timer_elapsed(key_timer) > DELAY_TIME)){
    register_delay_code(_BASE);
    if(!delay_key_pressing){
      unregister_delay_code();
    }
  }

  if(layer_state_old != layer_state){
    switch (layer_state) {
      case L_BASE:
        break;
      case L_OPT:
        register_delay_code(_OPT);
        unregister_delay_code();
        break;
      case L_NUM:
        register_delay_code(_NUM);
        unregister_delay_code();
        break;
      case L_SYM:
        register_delay_code(_SYM);
        unregister_delay_code();
        break;
      case L_FUNC:
        register_delay_code(_FUNC);
        unregister_delay_code();
        break;
    }
    layer_state_old = layer_state;
  }

  #ifdef RGBLIGHT_ENABLE
    if(!RGBAnimation){
      switch (layer_state) {
        case L_BASE:
            // led_ripple_effect(0,112,127);
            rgblight_setrgb(0,112,127);
          break;
        case L_OPT:
            // led_ripple_effect(127,0,100);
            rgblight_setrgb(127,0,100);
          break;
        case L_NUM:
            // led_ripple_effect(127,23,0);
            rgblight_setrgb(127,23,0);
          break;
        case L_SYM:
            // led_ripple_effect(0,127,0);
            rgblight_setrgb(0,127,0);
          break;
        case L_FUNC:
            // led_ripple_effect(127,0,61);
            rgblight_setrgb(127,0,61);
          break;
        }
    }
  #endif
}

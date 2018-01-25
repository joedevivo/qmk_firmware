#include "ergodox_ez.h"
#include "joedevivo.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

enum custom_keycodes {
  PLACEHOLDER = NEW_SAFE_RANGE, // can always be here
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* QWERTY Base Layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   =    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |      |           |      |   Y  |   U  |   I  |   O  |   P  |   \    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |Ctl/Esc |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | LShift |Z/Alt |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Alt | RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | Adj  | Meh  | Alt  | CMD  | LOWER|                                       | RAISE| Left |  Up  | Down | Right|
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |⌘/Esc | Alt  |       | Ctrl | ⌘    |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 |Backsp| Del  |------|       |------|  Enter |Space |
 *                                 |ace   |      | LOWER|       |RAISE |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[_QWERTY] = KEYMAP(
    // left hand
    KC_EQL,   KC_1,        KC_2,    KC_3,    KC_4,   KC_5,   XXXXXX,
    KC_TAB,   KC_Q,        KC_W,    KC_E,    KC_R,   KC_T,   XXXXXX,
    CTL_ESC,  KC_A,        KC_S,    KC_D,    KC_F,   KC_G,
    OSM_LSFT, ALT_T(KC_Z), KC_X,    KC_C,    KC_V,   KC_B,   XXXXXX,
    ADJUST,   KC_MEH,      KC_LALT, KC_LGUI, LOWER,
                                            LGUI_T(KC_ESC), KC_LALT,
                                                              KC_NO,
                                        KC_BSPACE, KC_DELETE, LOWER,
    // right hand
    XXXXXX,  KC_6, KC_7,   KC_8,   KC_9,    KC_0,           KC_MINS,
    XXXXXX,  KC_Y, KC_U,   KC_I,   KC_O,    KC_P,           KC_BSLS,
             KC_H, KC_J,   KC_K,   KC_L,    KC_SCLN,        KC_QUOT,
    XXXXXX,  KC_N, KC_M,   KC_COMM,KC_DOT,  ALT_T(KC_SLSH), OSM_LSFT,
                   RAISE, KC_LEFT, KC_UP,   KC_DOWN,        KC_RGHT,
    KC_LCTL, KC_LGUI,
    KC_NO,
    RAISE  , KC_ENTER, KC_SPACE
  ),

/* Lower
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   ~     |   !  |   @  |   #  |   $  |   %  |      |           |      |   ^  |   &  |   *  |   (  |   )  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Del     |  F1  |  F2  |  F3  |  F4  |  F5  |------|           |------|  F6  |   _  |   +  |   {  |   }  |   |    |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |  F7  |  F8  |  F9  |  F10 |  F11 |      |           |      |  F12 |ISO ~ |ISO | | Home | End  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      | Vol- | Vol+ | Next | Play |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */

[_LOWER] = KEYMAP(
    // left hand
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXX,
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, XXXXXX,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  XXXXXX,
    _______, _______, _______, _______, ______,
                                                _______, _______,
                                                         _______,
                                       _______, _______, _______,
    // right hand
    XXXXXX, KC_F6,   KC_F7,      KC_F8,      KC_F9,   KC_F10,  _______,
    XXXXXX, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, _______,
            KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
    XXXXXX, KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______,
                     XXXXXX,  KC_VOLD,    KC_VOLU,    KC_MNXT, KC_MPLY,
    ______, ______,
    ______,
    ______, ______, _______
),
/* RISE_UP!
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |         |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |        |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |   `     |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Del     |  F1  |  F2  |  F3  |  F4  |  F5  |------|           |------|  F6  |   -  |   =  |   [  |   ]  |  \     |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |  F7  |  F8  |  F9  |  F10 |  F11 |      |           |      |  F12 |ISO # |ISO / |Pg Up |Pg Dn |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |       |      |      |      |      |                                       |      | Vol- | Vol+ | Next | Play |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[_RAISE] = KEYMAP(
    // left hand
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXX,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    XXXXXX,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  XXXXXX,
    _______, _______, _______, _______, ______,
                                                _______, _______,
                                                         _______,
                                       _______, _______, _______,
    // right hand
    XXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
    XXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
            KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    XXXXXX, KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
                     XXXXXX,  KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY,
    ______, ______,
    ______,
    ______, ______, ______
),

/* Adjust
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | VRSN   | Reset|      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *
 *                                        ,-------------.       ,-------------.
 *                                        |Animat|      |       |Toggle|Solid |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |Bright|Bright|      |       |      |Hue-  |Hue+  |
 *                                 |ness- |ness+ |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[_ADJUST] = KEYMAP(
    // left hand
    X,    RGB_M_P,RGB_M_B,RGB_M_R,RGB_M_SW,RGB_M_SN, X,
    VRSN, RESET, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD,
    X,    X,     X,       X,       X,       X,       X,
    X,    X,     X,       X,       X,       X,       X,
    _,    _,     _,       _,       _,
                                             RGB_MOD,_,
                                                     _,
                                     RGB_VAD,RGB_VAI,_,
    // right hand
    X, RGB_M_K, RGB_M_X, RGB_M_G, X,       X,       X,
    X, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, X,
       X,       X,       X,       X,       X,       X,
    X, X,       X,       X,       X,       X,       X,
                X,       X,       X,       X,       X,
    X, X,
    X,
    X, X, X
  ),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  return MACRO_NONE;
};

// Runs boot tasks for keyboard
void matrix_init_keymap(void) {
  rgblight_init();
  ergodox_board_led_off();
  return;
};

// runs frequently to update info
void matrix_scan_keymap(void) {
  uint8_t layer = biton32(layer_state);
  switch (layer) {
    case _QWERTY:
      ergodox_board_led_off();
      ergodox_right_led_1_off();
      ergodox_right_led_2_off();
      ergodox_right_led_3_off();
      break;
    case _LOWER:
      ergodox_board_led_off();
      ergodox_right_led_1_on();
      ergodox_right_led_2_off();
      ergodox_right_led_3_off();
      break;
    case _RAISE:
      ergodox_board_led_off();
      ergodox_right_led_1_off();
      ergodox_right_led_2_off();
      ergodox_right_led_3_on();
      break;
    case _ADJUST:
      ergodox_board_led_off();
      ergodox_right_led_1_on();
      ergodox_right_led_2_on();
      ergodox_right_led_3_on();
      break;
    default:
      ergodox_blink_all_leds();
      ergodox_blink_all_leds();
      break;
  }
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
  }
  return true;
}

#include "iris.h"
#include "joedevivo.h"
#include "action_layer.h"
#include "action_tapping.h"
#include "eeconfig.h"
#include "version.h"

extern keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = KEYMAP( \
  KC_TAB,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
  CTL_ESC, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
  ADJUST,  KC_MEH, KC_LALT, KC_LGUI, LOWER,   KC_BSPC, KC_DEL, KC_ENT, KC_SPC,  RAISE,   KC_LEFT, KC_UP,   KC_DOWN, KC_RIGHT, \
                                     LOWER,   KC_BSPC, KC_DEL, KC_ENT, KC_SPC,  RAISE \
  ),

  [_LOWER] = KEYMAP( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, \
                                      _______, _______, _______, _______, _______, _______ \
  ),

  [_RAISE] = KEYMAP( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,                    KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY, \
                                      _______, _______, _______, _______, _______, _______ \

  ),

  [_ADJUST] =  KEYMAP( \
  _______, RESET,   _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, _______,                   _______, _______,  _______, _______, _______, _______, \
  BL_STEP, DEBUG  , RGB_HUD, RGB_SAD, RGB_VAD, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, RESET,   VRSN,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                                      _______, _______, _______, _______, _______, _______ \
  )
  };

void matrix_init_keymap(void) { // Runs boot tasks for keyboard
};

void matrix_scan_keymap(void) {  // runs frequently to update info
};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

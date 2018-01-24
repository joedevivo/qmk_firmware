#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#include "version.h"

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum userspace_custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  VRSN,
  EPRM,
  NEW_SAFE_RANGE
};

// Fillers to make layering more clear
#define _       KC_TRNS
#define __      KC_TRNS
#define ___     KC_TRNS
#define ____    KC_TRNS
#define _____   KC_TRNS
#define ______  KC_TRNS
#define _______ KC_TRNS
#define X       KC_NO
#define XX      KC_NO
#define XXX     KC_NO
#define XXXX    KC_NO
#define XXXXX   KC_NO
#define XXXXXX  KC_NO
#define XXXXXXX KC_NO

// For Readability
#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define SFT_ENT MT(MOD_LSFT, KC_ENT)
#define SPC_ENT TD(TD_SPC_ENT)

//One Shot Modifiers
#define OSM_LCTL OSM(MOD_LCTL)
#define OSM_LALT OSM(MOD_LALT)
#define OSM_LSFT OSM(MOD_LSFT)

#endif

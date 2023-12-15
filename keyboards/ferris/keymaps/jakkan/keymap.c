#include QMK_KEYBOARD_H
#include "config.h"

enum layer_names {
    // both
    BASE,
    // left
    NUM,
    SYM,
    FUN,
    // right
    NAV,
    MOU,
    // both
    SHF
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT(
    KC_Q,               KC_W,               KC_F,               KC_P,               KC_B,               KC_QUOT,            KC_Y,               KC_U,               KC_L,               KC_J,
    LCTL_T(KC_A),       LALT_T(KC_R),       LGUI_T(KC_S),       LSFT_T(KC_T),       KC_G,               LCTL_T(KC_O),       LALT_T(KC_I),       LGUI_T(KC_E),       LSFT_T(KC_N),       KC_M,
    KC_Z,               RALT_T(KC_X),       KC_C,               KC_D,               KC_V,               KC_SLSH,            RALT_T(KC_DOT),     KC_COMM,            KC_H,               KC_K,
                                                                LT(NAV, KC_SPC),    LT(MOU, KC_TAB),    LT(NUM, KC_BSPC),   LT(SYM, KC_ENT)                                          
  ),
  [NUM] = LAYOUT(
    KC_BSLS,            KC_MINS,            KC_EQL,             KC_LBRC,            KC_RBRC,            KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    KC_6,               KC_7,               KC_8,               KC_9,               KC_0,               KC_LCTL,            KC_LALT,            KC_LGUI,            KC_LSFT,            KC_NO, 
    KC_1,               KC_2,               KC_3,               KC_4,               KC_5,               KC_NO,              KC_RALT,            KC_NO,              KC_NO,              KC_NO,
                                                                KC_SCLN,            KC_GRV,             KC_NO,              MO(SHF)                                   
  ),
  [SYM] = LAYOUT(
    KC_PIPE,            KC_UNDS,            KC_PLUS,            KC_LCBR,            KC_RCBR,            KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    KC_CIRC,            KC_AMPR,            KC_ASTR,            KC_LPRN,            KC_RPRN,            KC_LCTL,            KC_LALT,            KC_LGUI,            KC_LSFT,            KC_NO, 
    KC_EXLM,            KC_AT,              KC_HASH,            KC_DLR,             KC_PERC,            KC_NO,              KC_RALT,            KC_NO,              KC_NO,              KC_NO,
                                                                KC_COLN,            KC_TILDE,           MO(FUN),            KC_NO                                
  ),
  [NAV] = LAYOUT(
    KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    KC_LCTL,            KC_LALT,            KC_LGUI,            KC_LSFT,            KC_NO,              KC_RGHT,            KC_UP,              KC_DOWN,            KC_LEFT,            KC_NO,
    KC_NO,              KC_RALT,            KC_NO,              KC_NO,              KC_NO,              KC_END,             KC_PGUP,            KC_PGDN,            KC_HOME,            KC_NO,                                    
                                                                MO(SHF),            KC_NO,              KC_DEL,             KC_ESC                               
  ),
  [MOU] = LAYOUT(
    KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    KC_LCTL,            KC_LALT,            KC_LGUI,            KC_LSFT,            KC_NO,              KC_MS_R,            KC_MS_U,            KC_MS_D,            KC_MS_L,            KC_NO,
    KC_NO,              KC_RALT,            KC_NO,              KC_NO,              KC_NO,              KC_WH_R,            KC_WH_U,            KC_WH_D,            KC_WH_L,            KC_NO,
                                                                KC_NO,              MO(FUN),            KC_BTN1,            KC_BTN2                                
  ),
  [SHF] = LAYOUT(
    S(KC_Q),            S(KC_W),            S(KC_F),            S(KC_P),            S(KC_B),            S(KC_QUOT),         S(KC_Y),            S(KC_U),            S(KC_L),            S(KC_J),
    S(KC_A),            S(KC_R),            S(KC_S),            S(KC_T),            S(KC_G),            S(KC_O),            S(KC_I),            S(KC_E),            S(KC_N),            S(KC_M),
    S(KC_Z),            S(KC_X),            S(KC_C),            S(KC_D),            S(KC_V),            S(KC_SLSH),         S(KC_DOT),          S(KC_COMM),         S(KC_H),            S(KC_K),
                                                                S(KC_SPC),          S(KC_TAB),          S(KC_BSPC),         S(KC_ENT)                                          
  ),
  [FUN] = LAYOUT(
    KC_F11,             KC_F12,             KC_F13,             KC_F14,             KC_F15,             KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
    KC_F6,              KC_F7,              KC_F8,              KC_F9,              KC_F10,             KC_LCTL,            KC_LALT,            KC_LGUI,            KC_LSFT,            KC_NO, 
    KC_F1,              KC_F2,              KC_F3,              KC_F4,              KC_F5,              KC_NO,              KC_NO,              KC_NO,              KC_NO,              KC_NO,
                                                                KC_NO,              KC_NO,              KC_NO,              KC_NO                                 
  ),
};
#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "quantum_keycodes.h"
#include "action.h"
#include "process_combo.h"
#include "process_key_override.h"
#include "mx8650.h"

enum layers {
    DEFAULT = 0,
    SYM = 1,
    NUM = 2,
    MOUSE = 3
};

enum custom_keycodes {
    CKC_BSPC = SAFE_RANGE,
};

enum unicode_names {
    ae, // ä
    AE, // Ä
    oe, // ö
    OE, // Ö
};


const uint32_t PROGMEM unicode_map[] = {
    [ae] = 0x00E4,
    [AE] = 0x00C4,
    [oe] = 0x00F6,
    [OE] = 0x00D6,
};

#define KC_QUIT (QK_LCTL | QK_LGUI | KC_Q)
#define KC_SHORTCAT MEH(KC_SPACE)
#define KC_MISSION_CTRL MEH(KC_M)
#define KC_OE  UP(oe, OE)
#define KC_AE  UP(ae, AE)
#define KC_SCREENSHOT LSG(KC_4)
#define KC_SCREENCAP  LSG(KC_5)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [DEFAULT] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_ESC,  KC_W,    KC_D,    KC_R,    KC_K,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_Q,    KC_S,    KC_T,    KC_V,    KC_G,                         KC_H,    KC_N,    KC_E,    KC_L,    KC_OE,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_A,    KC_X,    KC_C,    KC_F,    KC_B,                         KC_J,    KC_M,    KC_COMM, KC_DOT,  KC_P, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_Z,                      OSL(NUM), KC_AE,  OSL(SYM),   KC_SPACE, CKC_BSPC, KC_SHORTCAT,             KC_QUOTE
  ),
  [SYM] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_NO,   KC_LT    , KC_GT, KC_GRAVE, KC_NO,                       KC_AMPERSAND, KC_SEMICOLON, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_NO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_CIRCUMFLEX, CW_TOGG, KC_PLUS, KC_EQUAL, KC_HASH,               KC_PIPE, KC_COLON, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_QUESTION,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_EXCLAIM, KC_SLASH, KC_ASTERISK, KC_BACKSLASH, KC_NO,        KC_TILDE, KC_DOLLAR, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_AT,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_NO,                     KC_TRNS, KC_TRNS, KC_TRNS,    G(KC_Z), SGUI(KC_Z), KC_TRNS,               KC_PERCENT
  ),
  [NUM] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_MISSION_CTRL,KC_F1,KC_UP,KC_F2,   KC_NO,                        KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,                      KC_NO,   KC_4,    KC_5,    KC_6,    KC_NO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_NO,   G(KC_X), G(KC_C), G(KC_V), KC_NO,                        KC_0,    KC_1,    KC_2,    KC_3,    KC_NO, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_NO,                     KC_NO,   KC_NO,   KC_NO,      CKC_BSPC, KC_DEL, KC_NO,                     KC_NO
  ),
  [MOUSE] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_NO,   KC_NO,   KC_NO,   KC_SCREENCAP, KC_SCREENSHOT,           MS_BTN3, MS_BTN1, MS_UP  , MS_BTN2, KC_NO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,                        KC_NO,   MS_LEFT, MS_DOWN, MS_RGHT, KC_NO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,                        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_QUIT,                   KC_NO,   KC_NO,  KC_NO,       KC_NO,   KC_NO,   KC_NO,                     QK_BOOT
  )
};

#include "sm_td.h"

// COMBOS
const uint16_t PROGMEM combo_enter[] = {KC_E, KC_L, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_layer_mouse[] = {OSL(SYM), KC_SPACE, COMBO_END};
const uint16_t PROGMEM combo_ms_btn1[] = {KC_C, KC_F, COMBO_END};
const uint16_t PROGMEM combo_ms_btn2[] = {KC_X, KC_C, COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_enter, KC_ENTER),
    COMBO(combo_tab, KC_TAB),
    COMBO(combo_layer_mouse , MO(MOUSE)),
    COMBO(combo_ms_btn1, MS_BTN1),
    COMBO(combo_ms_btn2, MS_BTN2),
};

// KEY OVERRIDES
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t comma_minus = ko_make_basic(MOD_MASK_SHIFT, KC_COMMA, KC_MINUS);
const key_override_t dot_underscore = ko_make_basic(MOD_MASK_SHIFT, KC_DOT, KC_UNDERSCORE);
const key_override_t f1_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_1, KC_F1);
const key_override_t f2_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_2, KC_F2);
const key_override_t f3_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_3, KC_F3);
const key_override_t f4_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_4, KC_F4);
const key_override_t f5_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_5, KC_F5);
const key_override_t f6_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_6, KC_F6);
const key_override_t f7_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_7, KC_F7);
const key_override_t f8_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_8, KC_F8);
const key_override_t f9_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_9, KC_F9);
const key_override_t *key_overrides[] = {
	&delete_key_override,
    &comma_minus,
    &dot_underscore,
    &f1_key_override,
    &f2_key_override,
    &f3_key_override,
    &f4_key_override,
    &f5_key_override,
    &f6_key_override,
    &f7_key_override,
    &f8_key_override,
    &f9_key_override,
};

bool set_scrolling = false;

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 32.0
#define SCROLL_DIVISOR_V 32.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    set_scrolling = record->event.pressed && keycode != MS_BTN1 && keycode != MS_BTN2 && keycode != MS_BTN3;

    // if (record->event.pressed) { mx8650_Log(); }

    if (!process_smtd(keycode, record)) {
        return false;
    }

    return true; // Process all other keycodes normally
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
  uint8_t data = mx8650_getMotionData();

  if (data >= 0x84) {
    int8_t y = mx8650_getDeltaY();
    int8_t x = mx8650_getDeltaX();

    // Check if drag scrolling is active
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = -(int8_t)scroll_accumulated_v;

        printf("dX: %d dY: %d h: %d v: %d\n", x, y, mouse_report.h, mouse_report.v);

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        mouse_report.x = x;
        mouse_report.y = y;
    }
  }

  return mouse_report;
}

// https://github.com/stasmarkin/sm_td/blob/main/docs/070_customization_timeouts.md
// defaults are set in config.h
uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout) {
    switch (keycode) {
        case KC_V:
        case KC_N:
            // all but left and right shift SM_TD keys get short release
            // timeout to avoid accidental triggering of tap dance keys
            if (SMTD_TIMEOUT_RELEASE) return 80;
    }

    return get_smtd_timeout_default(timeout);
}

#define SMTD_TD_HOLD_ON_MKEY(macro_key, tap_key, hold_key, threshold, use_cl) \
    SMTD_DANCE(macro_key,                                        \
        NOTHING,                                                 \
        SMTD_TAP_16(use_cl, tap_key),                            \
        SMTD_LIMIT(threshold,                                    \
            SMTD_TAP_16(use_cl, hold_key),                       \
            SMTD_REGISTER_16(use_cl, tap_key)),                  \
        SMTD_LIMIT(threshold,                                    \
            SMTD_UNREGISTER_16(use_cl, hold_key),                \
            SMTD_UNREGISTER_16(use_cl, tap_key))                 \
    )

smtd_resolution on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        // home row mods
        SMTD_MT(KC_A, KC_LEFT_CTRL)
        SMTD_MT(KC_S, KC_LEFT_ALT)
        SMTD_MT(KC_T, KC_LEFT_GUI)
        SMTD_MT(KC_V, KC_LSFT)
        SMTD_MT(KC_N, KC_RSFT)
        SMTD_MT(KC_E, KC_RIGHT_GUI)
        SMTD_MT(KC_L, KC_RIGHT_ALT)
        SMTD_MT(KC_P, KC_RIGHT_CTRL)

        // tap dance
        SMTD_TD_HOLD_ON_MKEY(CKC_BSPC, KC_BSPC, A(KC_BSPC), 2, true)
    }

    return SMTD_RESOLUTION_UNHANDLED;
}

void pointing_device_driver_init(void) {
  mx8650_init();
}

uint16_t pointing_device_driver_get_cpi(void) {
  return mx8650_getDPI();
}

void pointing_device_driver_set_cpi(uint16_t cpi) {
  mx8650_setDPI(cpi);
}

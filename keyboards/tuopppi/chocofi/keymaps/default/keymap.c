#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "quantum_keycodes.h"
#include "action.h"
#include "process_combo.h"
#include "process_key_override.h"
#include "mx8650.h"
#include "sm_td.h"

enum layers {
    DEFAULT = 0,
    DEFAULT_ANYMAK_END = 4,
    SYM = 1,
    NUM = 2,
    MOUSE = 3
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
      KC_ESC,  KC_W,    KC_D,    KC_R,    KC_K,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_F12,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_Q,    KC_S,    KC_T,    KC_V,    KC_G,                         KC_H,    KC_N,    KC_E,    KC_L,    KC_OE,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_A,    KC_X,    KC_C,    KC_F,    KC_B,                         KC_J,    KC_M,    KC_COMM, KC_DOT,  KC_P, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_Z,                      MO(NUM), KC_AE,  MO(SYM),    KC_SPACE, KC_BSPC, KC_MISSION_CTRL,                KC_QUOTE
  ),
  /* https://keyboard-layout-try-out.pages.dev/?l0r0=q+w+d+r+k++y+u+i+o+%C3%B6&l0r1=a+s+t+v+g++h+n+e+l+p+&l0r2=z+x+c+f+b++j+m+%2C+.+%27&l1r0=f+l+c+d+v++y+u+o+%C3%A4+b&l1r1=s+n+r+t+g++%2C+i+e+a+q&l1r2=j+w+m+k+p++x+.+%C3%B6+z+h&z=z */
  [DEFAULT_ANYMAK_END] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_ESC,  KC_L,    KC_C,    KC_D,    KC_V,                         KC_Y,    KC_U,    KC_O,    KC_AE,   KC_B,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_F,    KC_N,    KC_R,    KC_T,    KC_G,                         KC_COMM, KC_I,    KC_E,    KC_A,    KC_Q,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_S,    KC_W,    KC_M,    KC_K,    KC_P,                         KC_X,    KC_DOT,  KC_OE,   KC_Z,    KC_H, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_J,                      MO(NUM), KC_NO,   MO(SYM),    KC_SPACE,KC_BSPC, KC_NO,                     KC_RSFT
  ),
  [SYM] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_NO,   KC_LT    , KC_GT, KC_GRAVE, KC_NO,                       KC_AMPERSAND, KC_SEMICOLON, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_CIRCUMFLEX,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_NO,   CW_TOGG, KC_PLUS, KC_EQUAL, KC_HASH,               KC_PIPE, KC_COLON, KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_QUESTION,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_EXCLAIM, KC_SLASH, KC_ASTERISK, KC_BACKSLASH, KC_NO,        KC_TILDE, KC_DOLLAR, KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_AT,
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_NO,                     KC_TRNS, KC_TRNS, KC_TRNS,    G(KC_Z), SGUI(KC_Z), KC_TRNS,               KC_PERCENT
  ),
  [NUM] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_NO,   KC_F1,   KC_UP,   KC_F2,   KC_NO,                        KC_NO,   KC_7,    KC_8,    KC_9,    KC_NO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,                      KC_NO,   KC_4,    KC_5,    KC_6,    KC_NO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_NO,   G(KC_X), G(KC_C), G(KC_V), KC_NO,                        KC_0,    KC_1,    KC_2,    KC_3,    KC_NO, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_NO,                     KC_NO,   KC_NO,   KC_NO,      KC_BSPC, KC_DEL, KC_NO,                     KC_NO
  ),
  [MOUSE] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_NO,   KC_NO,   KC_NO,   KC_SCREENCAP, KC_SCREENSHOT,           KC_NO,  KC_NO,   KC_UP,   KC_NO,   KC_NO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,                              KC_NO,  KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,                              KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_QUIT,                   KC_NO,   KC_NO,  KC_NO,       KC_NO,   KC_NO,   KC_NO,                     QK_BOOT
  ),
};

enum combo_events {
  COMBO_ENTER,
  COMBO_TAB,
  COMBO_ML,
  COMBO_MB1,
  COMBO_MB2
};

// COMBOS
// COMBO_ACTION() works with sm_td by default (plain COMBO() doesn't)
const uint16_t PROGMEM combo_enter[] = {KC_E, KC_L, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_layer_mouse[] = {MO(SYM), KC_SPACE, COMBO_END};
const uint16_t PROGMEM combo_ms_btn1[] = {KC_C, KC_F, COMBO_END};
const uint16_t PROGMEM combo_ms_btn2[] = {KC_X, KC_C, COMBO_END};

combo_t key_combos[] = {
    [COMBO_ENTER] = COMBO_ACTION(combo_enter),
    [COMBO_TAB] = COMBO_ACTION(combo_tab),
    [COMBO_ML] = COMBO_ACTION(combo_layer_mouse),
    [COMBO_MB1] = COMBO_ACTION(combo_ms_btn1),
    [COMBO_MB2] = COMBO_ACTION(combo_ms_btn2),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case COMBO_ENTER:
            if (pressed) { tap_code16(KC_ENTER); }
            break;
        case COMBO_TAB:
            if (pressed) { tap_code16(KC_TAB); }
            break;
        case COMBO_ML:
            if (pressed) { layer_on(MOUSE); }
            else { layer_off(MOUSE); }
            break;
        case COMBO_MB1:
            if (pressed) { register_code(MS_BTN1); }
            else { unregister_code(MS_BTN1); }
            break;
        case COMBO_MB2:
            if (pressed) { register_code(MS_BTN2); }
            else { unregister_code(MS_BTN2); }
            break;
    }
}

// https://docs.qmk.fm/features/caps_word#configure-which-keys-are-word-breaking
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case KC_OE:
        case KC_AE:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_DOT:
        case KC_COMM:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

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
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    set_scrolling = record->event.pressed && keycode != MS_BTN1 && keycode != MS_BTN2 && keycode != MS_BTN3;

    if (!process_smtd(keycode, record)) {
        return false;
    }

    // if (record->event.pressed) { mx8650_Log(); }

    return true; // Process all other keycodes normally
}

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)mouse_report.x / 48.0f;
        scroll_accumulated_v += (float)mouse_report.y / 48.0f;

        // Assign integer parts of accumulated scroll values to the mouse report
        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = -(int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        mouse_report.x = 0;
        mouse_report.y = 0;
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
        SMTD_TD_HOLD_ON_MKEY(KC_BSPC, KC_BSPC, A(KC_BSPC), 2, true)
        SMTD_TD_ON_MKEY(KC_B, KC_B, KC_MISSION_CTRL)
        SMTD_TD_ON_MKEY(KC_F, KC_F, MS_BTN1)
    }

    return SMTD_RESOLUTION_UNHANDLED;
}


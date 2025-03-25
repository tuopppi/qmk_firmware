#include QMK_KEYBOARD_H

#include "keycodes.h"
#include "quantum_keycodes.h"
#include "action.h"
#include "process_combo.h"
#include "process_key_override.h"

enum layers {
    DEFAULT = 0,
    SYMBOL = 1,
    NUMNAV = 2,
    MOUSE = 3,
    SPECIAL = 4
};

enum custom_keycodes {
    CKC_A = SAFE_RANGE,
    CKC_S,
    CKC_T,
    CKC_V,
    CKC_N,
    CKC_E,
    CKC_L,
    CKC_P,
    CKC_ESC_Z,
    CKC_BSPC,
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
#define KC_OE  UP(oe, OE)
#define KC_AE  UP(ae, AE)
#define KC_SCREENSHOT LSG(KC_4)
#define KC_SCREENCAP  LSG(KC_5)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEFAULT] = LAYOUT(
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   ,               /* */               XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , XXXXXXX  , KC_W     , KC_D      , KC_R      , KC_K      ,               /* */               KC_Y      , KC_U      , KC_I      , KC_O      , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , KC_Q     , CKC_S    , CKC_T     , CKC_V     , KC_G      ,               /* */               KC_H      , CKC_N     , CKC_E     , CKC_L     , KC_OE      , XXXXXXX  ,
            CKC_ESC_Z   , CKC_A    , KC_X     , KC_C      , KC_F      , KC_B      , XXXXXXX     , /* */ XXXXXXX     , KC_J      , KC_M      , KC_COMMA  , KC_DOT    , CKC_P      , KC_QUOTE ,
                                   XXXXXXX  , XXXXXXX   , OSL(NUMNAV) , KC_AE     , OSL(SYMBOL) , /* */ KC_SPACE    , CKC_BSPC  , OSL(SPECIAL)    , XXXXXXX   , XXXXXXX
    ),
    [SYMBOL] = LAYOUT(
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   ,               /* */               XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , XXXXXXX  , KC_LT    , KC_GT     , KC_GRAVE  , XXXXXXX   ,               /* */               KC_AMPERSAND, KC_SEMICOLON, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, XXXXXXX, XXXXXXX  ,
            XXXXXXX     , KC_CIRCUMFLEX, CW_TOGG, KC_PLUS , KC_EQUAL  , KC_HASH   ,               /* */               KC_PIPE   , KC_COLON  , KC_LEFT_PAREN, KC_RIGHT_PAREN, KC_QUESTION, XXXXXXX  ,
            XXXXXXX     , KC_EXCLAIM, KC_SLASH, KC_ASTERISK, KC_BACKSLASH, XXXXXXX, XXXXXXX     , /* */ XXXXXXX     , KC_TILDE  , KC_DOLLAR , KC_LEFT_CURLY_BRACE, KC_RIGHT_CURLY_BRACE, KC_AT, KC_PERCENT,
                                     XXXXXXX  , XXXXXXX   , KC_TRNS   , KC_TRNS   , KC_TRNS     , /* */ G(KC_Z)     , SGUI(KC_Z), XXXXXXX   , XXXXXXX   , XXXXXXX
    ),
    [NUMNAV] = LAYOUT(
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   ,               /* */               XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , XXXXXXX  , KC_F1    , KC_UP     , KC_F2     , XXXXXXX   ,               /* */               XXXXXXX   , KC_7      , KC_8      , KC_9      , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , KC_HOME  , KC_LEFT  , KC_DOWN   , KC_RIGHT  , KC_END    ,               /* */               XXXXXXX   , KC_4      , KC_5      , KC_6      , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , XXXXXXX  , G(KC_X)  , G(KC_C)   , G(KC_V)   , XXXXXXX   , XXXXXXX     , /* */ XXXXXXX     , KC_0      , KC_1      , KC_2      , KC_3      , XXXXXXX    , XXXXXXX  ,
                                     XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX     , /* */ CKC_BSPC    , KC_DEL    , XXXXXXX   , XXXXXXX   , XXXXXXX
    ),
    [MOUSE] = LAYOUT(
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   ,               /* */               XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , KC_SCREENCAP, KC_SCREENSHOT,          /* */               MS_BTN3   , MS_BTN1   , MS_UP     , MS_BTN2   , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   ,               /* */               XXXXXXX   , MS_LEFT   , MS_DOWN   , MS_RGHT   , XXXXXXX    , XXXXXXX  ,
            KC_QUIT     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX     , /* */ XXXXXXX     , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX    , QK_BOOT  ,
                                     XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX     , /* */ XXXXXXX     , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX
    ),
    [SPECIAL] = LAYOUT(
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   ,               /* */               XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   ,               /* */               XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   ,               /* */               XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX    , XXXXXXX  ,
            XXXXXXX     , XXXXXXX  , XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX     , /* */ XXXXXXX     , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX    , XXXXXXX  ,
                                     XXXXXXX  , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX     , /* */ XXXXXXX     , XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX
    )
};

#include "sm_td.h"

// COMBOS
const uint16_t PROGMEM combo_enter[] = {CKC_E, CKC_L, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_COMMA, KC_DOT, COMBO_END};
const uint16_t PROGMEM combo_layer_mouse[] = {OSL(SYMBOL), KC_SPACE, COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_enter, KC_ENTER),
    COMBO(combo_tab, KC_TAB),
    COMBO(combo_layer_mouse , MO(MOUSE)),
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }

    return true; // Process all other keycodes normally
}

// https://github.com/stasmarkin/sm_td/blob/main/docs/070_customization_timeouts.md
// defaults are set in config.h
uint32_t get_smtd_timeout(uint16_t keycode, smtd_timeout timeout) {
    switch (keycode) {
        case CKC_V:
        case CKC_N:
            // all but left and right shift SM_TD keys get short release
            // timeout to avoid accidental triggering of tap dance keys
            if (SMTD_TIMEOUT_RELEASE) return 90;
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
        SMTD_MTE_ON_MKEY(CKC_A, KC_A, KC_LEFT_CTRL)
        SMTD_MTE_ON_MKEY(CKC_S, KC_S, KC_LEFT_ALT)
        SMTD_MTE_ON_MKEY(CKC_T, KC_T, KC_LEFT_GUI)
        SMTD_MTE_ON_MKEY(CKC_V, KC_V, KC_LSFT)
        SMTD_MTE_ON_MKEY(CKC_N, KC_N, KC_RSFT)
        SMTD_MTE_ON_MKEY(CKC_E, KC_E, KC_RIGHT_GUI)
        SMTD_MTE_ON_MKEY(CKC_L, KC_L, KC_RIGHT_ALT)
        SMTD_MTE_ON_MKEY(CKC_P, KC_P, KC_RIGHT_CTRL)

        // tap dance
        SMTD_TD_ON_MKEY(CKC_ESC_Z, KC_ESC, KC_Z)
        SMTD_TD_HOLD_ON_MKEY(CKC_BSPC, KC_BSPC, A(KC_BSPC), 2, true)
    }

    return SMTD_RESOLUTION_UNHANDLED;
}

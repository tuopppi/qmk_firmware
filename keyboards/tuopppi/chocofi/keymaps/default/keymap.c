#include QMK_KEYBOARD_H

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

#define KC_OE  UP(oe, OE)
#define KC_AE  UP(ae, AE)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_ESC,  KC_W,    KC_D,    KC_R,    KC_K,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_SCLN,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_Q,    KC_S,    KC_T,    KC_V,    KC_G,                         KC_H,    KC_N,    KC_E,    KC_L,    KC_OE,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_A,    KC_X,    KC_C,    KC_F,    KC_B,                         KC_J,    KC_M,    KC_COMM, KC_DOT,  KC_P, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_Z,                      KC_LSFT, KC_AE, XXXXXXX,   KC_SPACE, KC_BSPC, XXXXXXX,                   KC_RSFT
  )
};

const uint16_t PROGMEM combo_enter[] = {KC_E, KC_L, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_COMMA, KC_DOT, COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_enter, KC_ENTER),
    COMBO(combo_tab, KC_TAB),
};

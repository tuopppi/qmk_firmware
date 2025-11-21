#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
  //+--------------------------------------------+                    +---------------------------------------------+
      KC_ESC,  KC_W,    KC_D,    KC_R,    KC_K,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_F12,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_Q,    KC_S,    KC_T,    KC_V,    KC_G,                         KC_H,    KC_N,    KC_E,    KC_L,    KC_O,
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+---------|
      KC_A,    KC_X,    KC_C,    KC_F,    KC_B,                         KC_J,    KC_M,    KC_COMM, KC_DOT,  KC_P, 
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+---------|
      KC_Z,                      KC_1, KC_2,  KC_3,    KC_4, KC_5, KC_6,                KC_QUOTE
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    printf("Keycode: %u, Event: %u\n", keycode, record->event.pressed);

    return true;
}
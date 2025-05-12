#include QMK_KEYBOARD_H
#include "mx8650.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_Q)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   mx8650_Log();

   return true;
}

void keyboard_post_init_user(void) {
  mx8650_init();
}

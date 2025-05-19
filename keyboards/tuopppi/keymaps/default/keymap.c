#include QMK_KEYBOARD_H
#include "mx8650.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(MO(1)),
    [1] = LAYOUT(KC_NO)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    mx8650_Log();
  }

  return true;
}

void pointing_device_driver_init(void) {
  mx8650_init();
}

report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report) {
  uint8_t data = mx8650_getMotionData();

  if (data >= 0x84) {
    int8_t y = mx8650_getDeltaY();
    int8_t x = mx8650_getDeltaX();

    if (layer_state_is(1)) {
      mouse_report.h = x;
      mouse_report.v = y;
    } else {
      mouse_report.x = x;
      mouse_report.y = y;
    }

    printf("dX: %d dY: %d\n", x, y);
  }

  return mouse_report;
}

uint16_t pointing_device_driver_get_cpi(void) {
  return mx8650_getDPI();
}

void pointing_device_driver_set_cpi(uint16_t cpi) {
  mx8650_setDPI(cpi);
}

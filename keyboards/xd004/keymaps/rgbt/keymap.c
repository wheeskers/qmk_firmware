#include QMK_KEYBOARD_H

enum custom_keycodes {
  AC_KEY0 = SAFE_RANGE,
  AC_KEY1,
  AC_KEY2,
  AC_KEY3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // Note: layers should be disabled to save space
  [0] = LAYOUT_all(
    AC_KEY0,  AC_KEY1, AC_KEY2, AC_KEY3
  )
};

// https://beta.docs.qmk.fm/using-qmk/advanced-keycodes/feature_macros
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Initialize timer for key press duration check
  static uint16_t key_timer;

  switch (keycode) {
    case AC_KEY0:
      // Send space keycode (useful for media players)
      if (record->event.pressed) {
        tap_code(KC_SPACE);
      }
      break;

    case AC_KEY1:
      // Send CTRL+SHIFT+M (common alias for Mute)
      if (record->event.pressed) {
        register_code(KC_LCTRL);
        register_code(KC_LSFT);
        tap_code(KC_M);
        unregister_code(KC_LCTRL);
        unregister_code(KC_LSFT);
      }
      break;

    case AC_KEY2:
      if (record->event.pressed) {
        // Start timer on key press
        key_timer = timer_read();
      } else {
        // Determine action on key release depending on timer
        if (timer_elapsed(key_timer) < 200) {
          // Send F20 key
          tap_code(KC_F20);
        } else {
          // Send "Mute" key
          tap_code(KC_MUTE);
        }
      }
      break;


    case AC_KEY3:
      if (record->event.pressed) {
        // Start timer on key press
        key_timer = timer_read();
      } else {
        // Determine action on key release depending on timer
        if (timer_elapsed(key_timer) < 200) {
          rgblight_increase_hue_noeeprom();
        } else if (timer_elapsed(key_timer) < 1000) {
          //rgblight_toggle_noeeprom();
          rgblight_toggle();
        } else {
          rgblight_step_noeeprom();
        }
      }
      break;

  }
  return true;
}

void keyboard_post_init_user(void) {
  // Initialize underglow feature
  // https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md
  //rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(10,200,200);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

void matrix_scan_user(void) {
  // Additional actions may be added here
}

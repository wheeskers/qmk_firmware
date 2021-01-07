#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  ACTION_KEY1 = SAFE_RANGE,
  ACTION_KEY2,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    ACTION_KEY1,  ACTION_KEY2
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {

      // Toggle RGB light
      case ACTION_KEY1:
        rgblight_toggle_noeeprom();
        break;

      // Send Ctrl+Shift+M sequence (common shortcut for "mute" action)
      case ACTION_KEY2:
        rgblight_increase_hue_noeeprom();
        register_code(KC_LCTRL);
        register_code(KC_LSFT);
        tap_code(KC_M);
        unregister_code(KC_LCTRL);
        unregister_code(KC_LSFT);
        break;
    }
  }
  return true;
}

void keyboard_post_init_user(void) {
  // Turn on RGB underglow, set color
  rgblight_enable_noeeprom();
  rgblight_sethsv_noeeprom(10, 200, 200);
  rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

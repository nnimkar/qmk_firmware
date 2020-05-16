#include QMK_KEYBOARD_H

enum alt_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    NN_SLEEP,
};

enum layer_num {
    _BASE,
    _ONE,
    _TWO
};

enum {
  TD_LSFT_CAPS = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for LSFT, twice for Caps Lock
  [TD_LSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS)
};

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_HOME,  \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_END, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGUP, \
        TD(TD_LSFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,          KC_UP,   KC_PGDN, \
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RALT, MO(1),   KC_LEFT, KC_DOWN, KC_RGHT  \
    ),
    [1] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, KC_DEL, KC_MUTE, \
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, KC_PSCR, KC_SLCK, KC_PAUS, _______, KC_MPLY, \
        _______, RGB_RMOD,RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______,          _______, KC_VOLU, \
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_PGUP, KC_VOLD, \
        NN_SLEEP, _______, _______,                            _______,                            MO(2), _______, KC_MRWD, KC_PGDN, KC_MFFD  \
    ),
    [2] = LAYOUT(
        NN_SLEEP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, KC_UP, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, MD_BOOT, NK_TOGG, DBG_TOG, RESET, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    /*
    [X] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, \
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______  \
    ),
    */
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

void keyboard_post_init_user(void){
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

void set_underglow(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = UNDERGLOW_START; i < ISSI3733_LED_COUNT; i++) {
        rgb_matrix_set_color(i, red, green, blue);
    }
};

void rgb_matrix_indicators_user(void) {
    // Caps Lock Colour and Underglow
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        rgb_matrix_set_color(30, 0xFF, 0x00, 0x00);
        set_underglow(0xFF, 0x00, 0x00);
    }

    // Layer Underglow
    switch (biton32(layer_state)) {
        case _ONE:
            rgb_matrix_set_color(0, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(14, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(43, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(57, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(29, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(31, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(33, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(58, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(63, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(64, 0xFF, 0xFF, 0xFF);
            rgb_matrix_set_color(66, 0xFF, 0xFF, 0xFF);
            set_underglow(0xFF, 0xFF, 0xFF);
            break;
        case _TWO:
            rgb_matrix_set_color(63, 0x00, 0x00, 0xFF);
            rgb_matrix_set_color(62, 0x00, 0x00, 0xFF);
            rgb_matrix_set_color(0, 0x00, 0x00, 0xFF);
            rgb_matrix_set_color(17, 0x00, 0x00, 0xFF);
            rgb_matrix_set_color(31, 0x00, 0x00, 0xFF);
            rgb_matrix_set_color(32, 0x00, 0x00, 0xFF);
            rgb_matrix_set_color(33, 0x00, 0x00, 0xFF);
            set_underglow(0x00, 0x00, 0xFF);
            break;
        default:
            break;
    }
};




#define MODS_SHIFT  (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL  (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT  (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        case NN_SLEEP:
            if (record->event.pressed) {
                clear_keyboard();
                SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LGUI) SS_DOWN(X_SLEP));
            }
            else {
                clear_keyboard();
            }
            return false;
        default:
            return true; //Process all other keycodes normally
    }
}

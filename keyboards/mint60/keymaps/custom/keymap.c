/* Copyright 2018 Eucalyn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

enum custom_keycodes {
    RGBRST = SAFE_RANGE
};


const uint16_t PROGMEM
keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] =
LAYOUT( \
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, \
 KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, \
 MO(
1), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, \
 KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RCTL, KC_UP, MO(
1),   \
    KC_LCTL, KC_LGUI, KC_LALT, KC_F7, KC_SPC, KC_SPC, KC_RALT, KC_RGUI, KC_LEFT, KC_DOWN, KC_RGHT \
),
[1] =
LAYOUT( \
    KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, \
 RGB_TOG, XXXXXXX, XXXXXXX, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, KC_UP, XXXXXXX, XXXXXXX, KC_CAPSLOCK, KC_PSCREEN, KC_INSERT, \
 _______, TO(2), XXXXXXX, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX, _______, \
 _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, KC_PGUP, _______, \
 _______, _______, _______, _______, LALT(KC_GRV), KC_DEL, _______, _______, KC_HOME, KC_PGDN, KC_END \

),
[2] =
LAYOUT( \
    KC_ESC, KC_KP_7, KC_KP_8, KC_KP_9, KC_PSLS, KC_DEL, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, \
 KC_TAB, KC_KP_4, KC_KP_5, KC_KP_6, KC_PAST, KC_BSPACE, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, \
 _______, KC_KP_1, KC_KP_2, KC_KP_3, KC_PMNS, KC_NUMLOCK, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, _______, \
 _______, KC_KP_0, KC_KP_DOT, KC_PENT, KC_PPLS, TO(0), KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, _______, KC_UP, _______, \
 _______, _______, _______, _______, KC_SPC, KC_SPC, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT \

)
};

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;


const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    // MACRODOWN only works in this function
    switch (id) {
        case 0:
            if (record->event.pressed) {
                register_code(KC_RSFT);
            } else {
                unregister_code(KC_RSFT);
            }
            break;
    }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
              eeconfig_update_rgblight_default();
              rgblight_enable();
              RGB_current_mode = rgblight_config.mode;
            }
#endif
            break;
    }
    return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

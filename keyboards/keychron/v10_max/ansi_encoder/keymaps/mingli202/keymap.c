/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#include "action.h"
#include "action_layer.h"
#include "process_combo.h"
#include "quantum.h"
#include QMK_KEYBOARD_H
#include "keychron_common.h"

#define FN MO(MAC_FN)
#define VIM_TG TG(VIM_NORMAL)

enum my_keycode {
    W_BACK = SAFE_RANGE,
    W_END,
    N_LINE,
};

enum layers {
    MAC_BASE,
    MAC_FN,
    VIM_NORMAL,
    VIM_LEA,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_89(
        KC_MPLY,    KC_ESC,   KC_BRID,  KC_BRIU,  KC_MCTRL, KC_LNPAD, RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_INS,             KC_DEL,
        MC_1,       KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        MC_2,       KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        MC_3,       KC_LCTL,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        MC_4,       KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        MC_5,       FN,       KC_LOPTN,           KC_LCMMD, KC_SPC,   VIM_TG,                        KC_SPC,             KC_RCMMD,                     KC_LEFT,  KC_DOWN,  KC_RGHT),

    [MAC_FN] = LAYOUT_ansi_89(
        RGB_TOG,    QK_BOOT,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,            _______,
        _______,    _______,  BT_HST1,  BT_HST2,  BT_HST3,  P2P4G,    _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            KC_END,
        _______,    _______,            _______,  _______,  _______,  _______,   BAT_LVL,  BAT_LVL,  NK_TOGG,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [VIM_NORMAL] = LAYOUT_ansi_89(
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  W_END,    _______,  _______,   _______,  _______,  VIM_TG,   N_LINE,   _______,  _______,  _______,  _______,            _______,
        _______,    _______,  VIM_TG,   _______,  _______,  _______,  _______,   KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, _______,  _______,            _______,            _______,
        _______,    _______,            _______,  _______,  _______,  _______,   W_BACK,   W_BACK,   _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  VIM_LEA,  _______,                       VIM_LEA,            _______,                      _______,  _______,  _______),

    [VIM_LEA] = LAYOUT_ansi_89(
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,    _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),


    /*[empty_layer] = LAYOUT_ansi_89(*/
    /*    _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,*/
    /*    _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,*/
    /*    _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,*/
    /*    _______,    _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,*/
    /*    _______,    _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,*/
    /*    _______,    _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),*/
};


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN] = {ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
    [VIM_NORMAL] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [VIM_LEA] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)}
};
#endif // ENCODER_MAP_ENABLE

// clang-format on
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case W_END:
            if (record->event.pressed) {
                tap_code16(LOPT(KC_RIGHT));
            }
            break;
        case W_BACK:
            if (record->event.pressed) {
                tap_code16(LOPT(KC_RIGHT));
            }
            break;
        case N_LINE:
            if (record->event.pressed) {
                register_code(KC_LCMD);
                tap_code(KC_RIGHT);
                unregister_code(KC_LCMD);
                tap_code(KC_ENT);
            }
            break;
    }
    return true;
}

enum combo_events { DEL_LINE };

const uint16_t PROGMEM del_line[] = {KC_LSFT, KC_X, COMBO_END};

combo_t key_combos[] = {
    [DEL_LINE] = COMBO_ACTION(del_line),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case DEL_LINE:
            if (pressed && layer_state_is(VIM_NORMAL)) {
                register_code(KC_LCMD);
                tap_code(KC_LEFT);
                tap_code(KC_BACKSPACE);
                unregister_code(KC_LCMD);
            }
            break;
    }
}

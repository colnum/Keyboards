/* Copyright 2020 Ito
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

#include "Inheritance.h"
#include "pointing_device.h"
#include "i2c.h"
#include "paw3204.h"

#define TB_ADDR 0x4A

enum MOTION_REG_ADDR
{
  MOTION_REG_UP = 0X00,
  MOTION_REG_DOWN,
  MOTION_REG_LEFT,
  MOTION_REG_RIGHT,
  MOTION_REG_CONFIRM,
  MOTION_REG_NUM
};

enum CONFIG_REG_ADDR
{
  CONFIG_REG_VALID = MOTION_REG_NUM,
  CONFIG_REG_I2C_ADDR = CONFIG_REG_VALID + 4,
  CONFIG_REG_I2C_SPEED,
  CONFIG_REG_LED_MODE = CONFIG_REG_I2C_SPEED + 2,
  CONFIG_REG_LED_FLASH_TIME,
  CONFIG_REG_DATA_CLEAR_TIME = CONFIG_REG_LED_FLASH_TIME + 2,  //CONFIG_REG_LED_FLASH_TIME has 2bytes
  CONFIG_REG_DATA_READ_TIME = CONFIG_REG_DATA_CLEAR_TIME + 2,
  CONFIG_REG_NUM = CONFIG_REG_DATA_READ_TIME + 2
};

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LOWER,
    _RAISE
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    BASE = SAFE_RANGE,
    LOWER,
    RAISE,
    USER_NAME,
    PASS_WORD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        /* Left side */
           KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T, \
          KC_LCTL,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G, \
          KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B, \
          XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LGUI,    LOWER,   KC_SPC, \
        /* Right side */
             KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  KC_BSPC, \
             KC_H,     KC_J,     KC_K,     KC_L,  KC_SCLN,  KC_QUOT, \
             KC_N,     KC_M,  KC_COMM,   KC_DOT,  KC_SLSH,  KC_RSFT, \
           KC_ENT,    RAISE,  KC_RALT,  KC_BTN2,  KC_BTN1,  KC_BTN1
    ),
    [_LOWER] = LAYOUT(
        /* Left side */
           KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5, \
          KC_LCTL,   KC_F10,    KC_F2,  KC_COPY,  KC_PSTE,    KC_F5, \
          KC_LSFT,  XXXXXXX,  XXXXXXX,  USER_NAME,  PASS_WORD,  XXXXXXX, \
          XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LGUI,    LOWER,   KC_SPC, \
        /* Right side */
             KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  KC_BSPC, \
          KC_LEFT,  KC_DOWN,    KC_UP, KC_RIGHT,  XXXXXXX,  XXXXXXX, \
          KC_BTN1,  KC_BTN2,  KC_WH_U,  KC_WH_D,  XXXXXXX,  XXXXXXX, \
           KC_ENT,    RAISE,  KC_RALT,  KC_BTN2,  KC_BTN1,  KC_BTN1
    ),
    [_RAISE] = LAYOUT(
        /* Left side */
           KC_ESC,  KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC, \
          KC_LCTL,    KC_F1,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
          KC_LSFT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, \
          XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_LGUI,    LOWER,   KC_SPC, \
        /* Right side */
          KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC, \
          KC_MINS,   KC_EQL,  KC_LCBR,  KC_RCBR,  KC_PIPE,   KC_GRV, \
          KC_UNDS,  KC_PLUS,  KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_TILD, \
           KC_ENT,    RAISE,  KC_RALT,  KC_BTN2,  KC_BTN1,  KC_BTN1
    )
};

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BASE:
            if (record->event.pressed) {
                // when keycode BASE is pressed
                persistent_default_layer_set(1UL<<_BASE);
            } else {
                // when keycode BASE is released
            }
            break;
        case LOWER:
            if (record->event.pressed) {
                // when keycode LOWER is pressed
                layer_on(_LOWER);
            } else {
                // when keycode LOWER is released
                layer_off(_LOWER);
            }
            break;
        case RAISE:
            if (record->event.pressed) {
                // when keycode RAISE is pressed
                layer_on(_RAISE);
            } else {
                // when keycode RAISE is released
                layer_off(_RAISE);
            }
            break;
        case USER_NAME:
            if (record->event.pressed) {
                // when keycode USER_NAME is pressed
                //SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
                SEND_STRING("USERNAME");
            } else {
                // when keycode USER_NAME is released
            }
            break;
        case PASS_WORD:
            if (record->event.pressed) {
                // when keycode PASS_WORD is pressed
                //SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
                SEND_STRING("PASSWORD");
            } else {
                // when keycode PASS_WORD is released
            }
            break;
    }
    /*
    if (record->event.pressed) {
        i2c_start_write(TB_ADDR);
        //i2c_master_write(0x01);     // WriteMode
        //i2c_master_write(CONFIG_REG_LED_MODE);
        //i2c_master_write(led_mode);
        i2c_master_stop();
    }
    */
    return true;
}

/*
void pointing_device_init(void) {
    i2c_master_init();

    // Set Default Value
    i2c_start_write(TB_ADDR);
    i2c_master_write(0x01);     // WriteMode
    i2c_master_write(CONFIG_REG_VALID);
    i2c_master_write(0);
    i2c_master_write(0);
    i2c_master_write(0);
    i2c_master_write(0);
    i2c_master_stop();
}

uint8_t trackball_read(uint8_t reg) {
    if(i2c_start_write(TB_ADDR)) {
        print("i2c_start_write(TB_ADDR): ");
        goto i2c_error;
    }
    if(i2c_master_write(0x00)){
        print("i2c_master_write(0x00): ");
        goto i2c_error;     // ReadMode
    }
    if(i2c_master_write(reg)) {
        print("i2c_master_write(MOTION_REG_UP): ");
        goto i2c_error;
    }
    if(i2c_master_write(0x01)){
        print("i2c_master_write(0x00): ");
        goto i2c_error;     // ReadMode
    }
    //i2c_master_stop();

    if(i2c_start_read(TB_ADDR)) {
        print("i2c_start_read(TB_ADDR): ");
        goto i2c_error;
    }
    uint8_t trackdata = i2c_master_read(I2C_ACK);
    i2c_master_read(I2C_NACK);
    i2c_master_stop();

    return trackdata;

i2c_error:
    println("i2c_error");
    i2c_reset_state();
    return 0;
}

void pointing_device_task() {
    uint8_t up = trackball_read(MOTION_REG_UP);
    uint8_t down = trackball_read(MOTION_REG_DOWN);
    uint8_t left = trackball_read(MOTION_REG_LEFT);
    uint8_t right = trackball_read(MOTION_REG_RIGHT);

    print_hex4(up);   print("-");
    print_hex4(down); print("-");
    print_hex4(left); print("-");
    print_hex4(right); print("-");
    println();

    report_mouse_t currentReport = pointing_device_get_report();
    currentReport.x = (right-left) * 50;
    currentReport.y = (down-up) * 50;
    pointing_device_set_report(currentReport);

    pointing_device_send();

    return;

}
*/

// add paw : start
void matrix_init_user(void) {
    init_paw3204();
}

report_mouse_t mouse_rep;

void keyboard_post_init_user() {
    debug_enable = true;
    debug_mouse = true;
}
void matrix_scan_user(void) {
    static int cnt;
    static bool paw_ready;
    if (cnt++ % 50 == 0) {
        uint8_t pid = read_pid_paw3204();
        if (pid == 0x30) {
            dprint("paw3204 OK\n");
            paw_ready = true;
        } else {
            dprintf("paw3204 NG:%d\n", pid);
            paw_ready = false;
        }
    }

    if(paw_ready) {
        uint8_t stat;
        int8_t x, y;

        read_paw3204(&stat, &x, &y);
        mouse_rep.buttons = 0;
        mouse_rep.h       = 0;
        mouse_rep.v       = 0;
        mouse_rep.x       = y;
        mouse_rep.y       = -x;

        if(cnt % 10 == 0) {
            dprintf("stat:%3d x:%4d y:%4d\n", stat, mouse_rep.x, mouse_rep.y);
        }

        if (stat & 0x80) {
            pointing_device_set_report(mouse_rep);
        }
    }
}
// add paw : end

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    //static uint8_t led_mode = 0;

    if (record->event.pressed) {
        i2c_start_write(TB_ADDR);
        //i2c_master_write(0x01);     // WriteMode
        //i2c_master_write(CONFIG_REG_LED_MODE);
        //i2c_master_write(led_mode);
        i2c_master_stop();
    }
    return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool led_update_user(led_t led_state) {
    return true;
}
*/

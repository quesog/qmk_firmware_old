/*
Copyright 2011,2012,2013 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* key matrix position */
typedef struct {
    uint8_t col;
    uint8_t row;
} keypos_t;

/* key event */
typedef struct {
    keypos_t key;
    uint16_t time;
    bool     pressed : 1;
    bool     valid : 1;
} keyevent_t;

/* equivalent test of keypos_t */
#define KEYEQ(keya, keyb) ((keya).row == (keyb).row && (keya).col == (keyb).col)

static inline bool IS_PRESSED(keyevent_t event) { return event.valid && event.pressed; }
static inline bool IS_RELEASED(keyevent_t event) { return event.valid && !event.pressed; }

/**
 * @brief Constructs a internal tick event that is used to drive the internal QMK state machine.
 */
#define TICK_EVENT \
    (keyevent_t) { .key = (keypos_t){.row = 0, .col = 0}, .pressed = false, .valid = false, .time = timer_read() }

/**
 * @brief Constructs a key event for a pressed or released key.
 */
#define KEY_EVENT(ROW, COL, PRESSED) \
    (keyevent_t) { .key = (keypos_t){.row = ROW, .col = COL}, .pressed = PRESSED, .valid = true, .time = timer_read() }

/* it runs once at early stage of startup before keyboard_init. */
void keyboard_setup(void);
/* it runs once after initializing host side protocol, debug and MCU peripherals. */
void keyboard_init(void);
/* it runs repeatedly in main loop */
void keyboard_task(void);
/* it runs whenever code has to behave differently on a slave */
bool is_keyboard_master(void);
/* it runs whenever code has to behave differently on left vs right split */
bool is_keyboard_left(void);

void keyboard_pre_init_kb(void);
void keyboard_pre_init_user(void);
void keyboard_post_init_kb(void);
void keyboard_post_init_user(void);

void housekeeping_task(void);       // To be executed by the main loop in each backend TMK protocol
void housekeeping_task_kb(void);    // To be overridden by keyboard-level code
void housekeeping_task_user(void);  // To be overridden by user/keymap-level code

uint32_t last_input_activity_time(void);     // Timestamp of the last matrix or encoder activity
uint32_t last_input_activity_elapsed(void);  // Number of milliseconds since the last matrix or encoder activity

uint32_t last_matrix_activity_time(void);     // Timestamp of the last matrix activity
uint32_t last_matrix_activity_elapsed(void);  // Number of milliseconds since the last matrix activity

uint32_t last_encoder_activity_time(void);     // Timestamp of the last encoder activity
uint32_t last_encoder_activity_elapsed(void);  // Number of milliseconds since the last encoder activity

uint32_t get_matrix_scan_rate(void);

#ifdef __cplusplus
}
#endif

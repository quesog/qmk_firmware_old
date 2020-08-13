#pragma once

#include "config_common.h"

#define PRODUCT YAEMK 1.1
#define DESCRIPTION YAEMK 1.1

#define MATRIX_COL_PINS \
    { A8, B15, A9, B13, B12, B2, B1, A3 }
#define MATRIX_ROW_PINS \
    { A10, B14, A6, A4, A5 }
#define MATRIX_COL_PINS_RIGHT \
    { A3, B1, B2, B12, B13, A9, B15, A8 }
#define MATRIX_ROW_PINS_RIGHT \
    { A10, B14, A6, A4, A5 }

#define ENCODERS_PAD_A_RIGHT \
    { A7 }
#define ENCODERS_PAD_B_RIGHT \
    { B0 }
#define ENCODERS_PAD_A \
    { B0 }
#define ENCODERS_PAD_B \
    { A7 }

#define RGBLIGHT_SPLIT
#define RGB_MATRIX_SPLIT RGBLED_SPLIT
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_HAND_PIN B9
//#define I2C_DRIVER I2CD2
//#define I2C1_BANK GPIOB
//#define I2C1_SCL 10  // pin 21
//#define I2C1_SDA 11  // pin 22
//#define OLED_DISPLAY_ADDRESS 0x3C
//#    define OLED_IC OLED_IC_SH1106
#define OLED_DISPLAY_128X64
#ifdef OLED_DRIVER_ENABLE
#endif

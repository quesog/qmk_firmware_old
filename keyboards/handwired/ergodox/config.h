#pragma once

#include "config_common.h"

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x3232
#define DEVICE_VER 0x0001
#define MANUFACTURER QuesoG
#define PRODUCT Handwired Ergodox

// #define MASTER_RIGHT

// Double the actual rows (5 for each half)
#define MATRIX_ROWS 10
#define MATRIX_COLS 9

#define MATRIX_ROW_PINS { GP29, GP28, GP27, GP26, GP18 }
#define MATRIX_COL_PINS { GP1, GP2, GP3, GP4, GP5, GP6, GP7, GP8, GP9 }

#define MATRIX_ROW_PINS_RIGHT { GP28, GP27, GP26, GP22, GP21 }
#define MATRIX_COL_PINS_RIGHT { GP7, GP8, GP9, GP10, GP11, GP12, GP13, GP14, GP15 }

#define DIODE_DIRECTION COL2ROW

// Half duplex operations
#define SERIAL_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the Serial implementation uses the PIO0 peripheral
#define SERIAL_USART_TX_PIN GP19     // USART TX pin
#pragma once

#include "config_common.h"

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x3232
#define DEVICE_VER 0x0001
#define MANUFACTURER QuesoG
#define PRODUCT Handwired Ergodox

#define MATRIX_ROWS 5
#define MATRIX_COLS 9

#define MATRIX_ROW_PINS { GP29, GP28, GP27, GP26, GP18 }
#define MATRIX_COL_PINS { GP1, GP2, GP3, GP4, GP5, GP6, GP7, GP8, GP9 }

// #define MATRIX_ROW_PINS_RIGHT { GP29, GP28, GP27, GP26, GP18 }
// #define MATRIX_COL_PINS_RIGHT { GP1, GP2, GP3, GP4, GP5, GP6, GP7, GP8, GP9 }

#define DIODE_DIRECTION COL2ROW
#include "yaemk.h"

#define X(COL_POSITION) (224 / ((MATRIX_COLS * 2) - 1)) * (COL_POSITION - 1)
#define Y(ROW_POSITION) (64 / ((MATRIX_ROWS / 2) - 1)) * (ROW_POSITION - 1)
#define L(COL, ROW) \
    { X(COL), Y(COL) }
#define XX NO_LED

// clang-format off

#define KEY_2_LED_LEFT \
/*col 1   2   3   4   5   6   7   8    row */\
    {38, 37, 36, 35, 34, 33, 32, XX},/*  1  */\
    {22, 23, 25, 26, 28, 29, 30, XX},/*  2  */\
    {21, 20, 19, 18, 17, 16, 15, XX},/*  3  */\
    { 8,  9, 11, 12, 13, 14,  0,  2},/*  4  */\
    {XX, XX, XX, XX,  6,  5,  4,  3} /*  5 */\

#define POS_LED_LEFT \
L(7.5, 4),\
L(7.7, 4.5),\
L(8.5, 4),\
L(7.5, 5),\
L(7, 5),\
L(6, 5),\
L(5, 5),\
L(4.5, 4.5),\
L(1, 4),\
L(2, 4),\
L(2, 3.5),\
L(3, 4),\
L(4, 4),\
L(5, 4),\
L(6, 4),\
L(7, 3),\
L(6, 3),\
L(5, 3),\
L(4, 3),\
L(3, 3),\
L(2, 3),\
L(1, 3),\
L(1, 2),\
L(2, 2),\
L(2, 1.5),\
L(3, 2),\
L(4, 2),\
L(4, 1.5),\
L(5, 2),\
L(6, 2),\
L(7, 2),\
L(7, 1.5),\
L(7, 1),\
L(6, 1),\
L(5, 1),\
L(4, 1),\
L(3, 1),\
L(2, 1),\
L(1, 1)

#define KEY_2_LED_RIGHT \
/*col 9  10  11  12  13  14  15  16     row */\
    {XX, 71, 72, 73, 74, 75, 76, 77},/*  1  */\
    {XX, 69, 68, 67, 65, 64, 62, 61},/*  2  */\
    {XX, 54, 55, 56, 57, 58, 59, 60},/*  3  */\
    {41, 39, 53, 52, 51, 50, 48, 47},/*  4  */\
    {42, 43, 44, 45, XX, XX, XX, XX} /*  5  */\

#define POS_LED_RIGHT \
L(9.5, 4),/*39*/\
L(9.3, 4.5),\
L(8.5, 4),\
L(9.5, 5),\
L(10, 5),\
L(11, 5),\
L(12, 5),\
L(12.5, 4.5),\
L(16, 4),/*47*/\
L(15, 4),\
L(15, 3.5),\
L(14, 4),/*50*/\
L(13, 4),\
L(12, 4),\
L(11, 4),\
L(10, 3),\
L(11, 3),\
L(12, 3),\
L(13, 3),\
L(14, 3),\
L(15, 3),\
L(16, 3),\
L(16, 2),/*61*/\
L(15, 2),\
L(15, 1.5),\
L(14, 2),\
L(13, 2),\
L(13, 1.5),\
L(12, 2),\
L(11, 2),\
L(10, 2),/*69*/\
L(10, 1.5),\
L(10, 1),/*71*/\
L(11, 1),\
L(12, 1),\
L(13, 1),\
L(14, 1),\
L(15, 1),\
L(16, 1) /*77*/

// clang-format on

#define LED_FLAG 4, 2, 4, 4, 4, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 4, 2, 4, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {{KEY_2_LED_LEFT, KEY_2_LED_RIGHT}, {POS_LED_LEFT, POS_LED_RIGHT}, {LED_FLAG, LED_FLAG}};

#    define RGB_MATRIX_CENTER L(8.5, 3)

#endif

#undef KEY_2_LED_LEFT
#undef KEY_2_LED_RIGHT
#undef POS_LED_LEFT
#undef POS_LED_RIGHT
#undef LED_FLAG
#undef X
#undef Y
#undef L
#undef XX

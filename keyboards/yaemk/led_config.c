#include "yaemk.h"

#define X(COL_POSITION) (224 / ((MATRIX_COLS * 2) - 1)) * COL_POSITION
#define Y(ROW_POSITION) (64 / ((MATRIX_ROWS / 2) - 1)) * ROW_POSITION
#define L(COL, ROW) \
    { X(COL), Y(COL) }
#define XX NO_LED

// clang-format off

#define KEY_2_LED_LEFT \
    {9,  10, 17, 18, 25, 26, 32, XX},\
    {8,  11, 16, 19, 24, 27, 31, XX},\
    {7,  12, 15, 20, 23, 28, 30, XX},\
    {6,  13, 14, 21, 22, 29,  0,  1},\
    {XX, XX, XX, XX,  5,  4,  3,  2}\

#define KEY_2_LED_RIGHT \
    {XX, 65, 59, 58, 51, 50, 43, 42},\
    {XX, 64, 60, 57, 52, 49, 44, 41},\
    {XX, 63, 61, 56, 53, 48, 45, 40},\
    {34, 33, 62, 55, 54, 47, 46, 39},\
    {35, 36, 37, 38, XX, XX, XX, XX}\

#define POS_LED_LEFT L(6,3), L(7,3), L(7,4), L(6,4), L(5,4), L(4,4), L(0,3), L(0,2), L(0,1), L(0,0), L(1,0), L(1,1), L(1,2), L(1,3), L(2,3), L(2,2), L(2,1), L(2,0), L(3,0), L(3,1), L(3,2), L(3,3), L(4,3), L(4,2), L(4,1), L(4,0), L(5,0),L(5,1),L(5,2),L(5,3),L(6,2), L(6,1),L(6,0)

#define POS_LED_RIGHT L(9,3), L(8,3), L(8,4), L(9,4), L(10,4), L(11,4), L(15,3), L(15,2), L(15,1), L(15,0), L(14,0), L(14,1), L(14,2), L(14,3), L(13,3), L(13,2), L(13,1), L(13,0), L(12,0), L(12,1), L(12,2), L(12,3), L(11,3), L(11,2), L(11,1), L(11,0), L(10,0), L(10,1), L(10,2), L(10,3), L(9,2), L(9,1), L(9,0)

#define LED_FLAG \
    4, 4, 4, 4, 4, 4, \
	4, 4, 4, 4, 4, 4, \
	4, 4, 4, 4, 4, 4, \
	4, 4, 4, 4, 4, 4, \
	4, 4, 4, 4, 4, 4, \
	4, 4, 4

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
	KEY_2_LED_LEFT,
	KEY_2_LED_RIGHT
}, {
	POS_LED_LEFT,
	POS_LED_RIGHT
}, {
	LED_FLAG, LED_FLAG
}};

#define RGB_MATRIX_CENTER L(7.5, 2)

#endif

// clang-format on

#undef KEY_2_LED_LEFT
#undef KEY_2_LED_RIGHT
#undef POS_LED_LEFT
#undef POS_LED_RIGHT
#undef LED_FLAG
#undef X
#undef Y
#undef L
#undef XX

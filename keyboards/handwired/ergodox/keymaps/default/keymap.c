#include QMK_KEYBOARD_H

#define ____ KC_TRANSPARENT
#define _____ KC_TRANSPARENT
#define ______ KC_TRANSPARENT

enum layers_enum {
    QWERTY,
    NUMB,
    FUNC
};

#define LAYER_1 MO(NUMB)
#define LAYER_2 MO(FUNC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[QWERTY] = LAYOUT_default(
KC_GRV,	KC_1,	KC_2,	KC_3,	KC_4,	KC_5,	KC_MINS,								KC_EQL,	KC_6,	KC_7,	KC_8,	KC_9,	KC_0,	KC_BSPC,	\
KC_TAB,	KC_Q,	KC_W,	KC_E,	KC_R,	KC_T,	KC_LPRN,								KC_RPRN,	KC_Y,	KC_U,	KC_I,	KC_O,	KC_P,	KC_BSLS,	\
KC_ESC,	KC_A,	KC_S,	KC_D,	KC_F,	KC_G,	KC_LBRC,		KC_BSPC,	KC_DEL,		____,	____,		KC_RBRC,	KC_H,	KC_J,	KC_K,	KC_L,	KC_SCLN,	KC_QUOT,	\
KC_LSFT,	KC_Z,	KC_X,	KC_C,	KC_V,	KC_B,		KC_ENT,	LAYER_1,	KC_HOME,		KC_PGUP,	LAYER_2,	KC_SPC,		KC_N,	KC_M,	KC_COMM,	KC_DOT,	KC_SLASH,	KC_RSFT,	\
KC_LCTL,	KC_LEFT_GUI,	KC_LALT,	KC_LEFT_GUI,	KC_LALT,					KC_END,		KC_PGDN,					KC_LEFT,	KC_DOWN,	KC_UP,	KC_RIGHT,	KC_RCTL	\
),

[NUMB] = LAYOUT_default(
____,  ____,  ____,  ____,  ____,  ____,  ____,                ____,  ____,  ____,  KC_PSLS,  KC_PAST,  KC_PMNS,  ____,  \
____,  ____,  ____,  ____,  ____,  ____,  ____,                ____,  ____,  KC_KP_7,  KC_KP_8,  KC_KP_9,  KC_PPLS,  ____,  \
____,  ____,  ____,  ____,  ____,  ____,  ____,    ____,  ____,    KC_MPLY,  ____,    ____,  ____,  KC_KP_4,  KC_KP_5,  KC_KP_6,  KC_PPLS,  ____,  \
____,  ____,  ____,  ____,  ____,  ____,    ____,  ____,  ____,    KC_VOLU,  ____,  ____,    ____,  KC_KP_1,  KC_KP_2,  KC_KP_3,  KC_PENT,  ____,  \
____,  ____,  ____,  ____,  ____,          ____,    KC_VOLD,          KC_KP_0,  KC_KP_0,  KC_PDOT,  KC_PENT,  ____ \
),


[FUNC] = LAYOUT_default(
____,	____,	____,	____,	____,	____,	____,								____,	____,	KC_F10,	KC_F11,	KC_F12,	____,	LCTL(KC_BRK),	\
____,	____,	____,	____,	____,	____,	____,								____,	____,	KC_F7,	KC_F8,	KC_F9,	____,	____,	\
____,	____,	____,	____,	____,	____,	____,		____,	____,		____,	____,		____,	____,	KC_F4,	KC_F5,	KC_F6,	____,	____,	\
____,	____,	____,	____,	____,	____,		____,	____,	____,		____,	____,	____,		____,	KC_F1,	KC_F2,	KC_F3,	____,	____,	\
____,	____,	____,	____,	____,					____,		____,					____,	____,	____,	____,	____	\
)


};

/* Blank layout for copying

[SYMB] = LAYOUT_default(
____, ____, ____, ____, ____, ____, ____,                                        ____, ____, ____, ____, ____, ____, ____, \
____, ____, ____, ____, ____, ____, ____,                                        ____, ____, ____, ____, ____, ____, ____, \
____, ____, ____, ____, ____, ____, ____,      ____, ____,      ____, ____,      ____, ____, ____, ____, ____, ____, ____, \
____, ____, ____, ____, ____, ____,      ____, ____, ____,      ____, ____, ____,      ____, ____, ____, ____, ____, ____, \
____, ____, ____, ____, ____,                        ____,      ____,                        ____, ____, ____, ____, ____ \
)

*/

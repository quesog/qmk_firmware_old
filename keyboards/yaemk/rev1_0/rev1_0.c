#include "rev1_0.h"

__attribute__((weak)) bool is_keyboard_left(void) {
    // Test pin SPLIT_HAND_PIN for High/Low, if low it's right hand
    setPinInputLow(SPLIT_HAND_PIN);
    bool isleft = readPin(SPLIT_HAND_PIN);
    return isleft;
}

void board_init(void) { AFIO->MAPR |= AFIO_MAPR_USART1_REMAP; }

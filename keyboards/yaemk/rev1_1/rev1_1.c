#include "rev1_1.h"

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_USART1_REMAP;
}

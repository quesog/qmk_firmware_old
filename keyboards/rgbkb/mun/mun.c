#include "mun.h"
#include "touch_encoder.h"

void keyboard_post_init_kb(void)
{
    touch_encoder_init();
    keyboard_post_init_user();
}

void housekeeping_task_kb(void)
{
    touch_encoder_update();
}

#if defined(BUSY_WAIT)
void matrix_output_unselect_delay(void) {
    for (int32_t i = 0; i < BUSY_WAIT_INSTRUCTIONS; i++) {
        __asm__ volatile("nop" ::: "memory");
    }
}
#endif
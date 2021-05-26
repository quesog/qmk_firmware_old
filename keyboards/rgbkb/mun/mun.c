#include "mun.h"
#include "touch_encoder.h"
#include <transactions.h>

void sync_rgb_menu(void)
{
    if (!is_keyboard_master()) return;
}

void keyboard_post_init_kb(void)
{
    touch_encoder_init();
    transaction_register_rpc(TOUCH_ENCODER_SYNC, touch_encoder_slave_sync);
    keyboard_post_init_user();
}

void housekeeping_task_kb(void)
{
    touch_encoder_update(TOUCH_ENCODER_SYNC);
    sync_rgb_menu();
}

#include "yaemk.h"
#include <print.h>

#define MEDIA_KEY_DELAY 10

uint8_t  layer = 0;
uint32_t layer_state_set_kb(uint32_t state) {
    state = layer_state_set_user(state);
    layer = biton32(state);
    return state;
}

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    // debug_enable   = true;
    // debug_matrix   = true;
    // debug_keyboard = true;
    // debug_mouse=true;
}

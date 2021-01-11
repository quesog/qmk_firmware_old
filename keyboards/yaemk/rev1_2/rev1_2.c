#include "rev1_2.h"
#if defined(SPLIT_KEYBOARD)
bool is_keyboard_master(void) {
    static bool determined = false;
    static bool is_master;
    if (!determined) {
        determined = true;
        setPinInputLow(SPLIT_PLUG_DETECT_PIN);
        wait_ms(50);
        is_master = (bool)readPin(SPLIT_PLUG_DETECT_PIN);
        setPinInput(SPLIT_PLUG_DETECT_PIN);
        if (!is_master) {
            usbStop(&USBD1);
        }
    }

    return is_master;
}
#endif  // SPLIT_KEYBOARD

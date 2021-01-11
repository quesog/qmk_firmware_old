#pragma once

/* MATRIX CONFIG */
#define MATRIX_ROWS 10
#define MATRIX_COLS 8
#define DIODE_DIRECTION COL2ROW
#define DEBUG_MATRIX_SCAN_RATE
#define DEBOUNCE 8
#define TAPPING_TOGGLE 2
#define BUSY_WAIT
#define BUSY_WAIT_INSTRUCTIONS 10

// default but used in macros
#define TAPPING_TERM 160

// Prevent normal rollover on alphas from accidentally triggering mods.
#define IGNORE_MOD_TAP_INTERRUPT

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define TAPPING_FORCE_HOLD

// Recommended for heavy chording.
#define QMK_KEYS_PER_SCAN 8

// Mouse key speed and acceleration.
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY 0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 16
#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY 0
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED 6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX 64

/* ENCODER CONFIG */
#define ENCODER_RESOLUTION 2

/* RGB MATRIX DRIVER */
#if defined(RGB_MATRIX_ENABLE)
/* RGB TO HSV CONVERSION WITHOUT LOOKUP TABLE*/
#    undef USE_CIE1931_CURVE
/* EFFECTS */
#    define RGB_DISABLE_WHEN_USB_SUSPENDED false  // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_HUE_STEP 3  // number of steps to cycle through the hue by
#    define RGB_MATRIX_SAT_STEP 6  // number of steps to increment the saturation by
#    define RGB_MATRIX_VAL_STEP 6  // number of steps to increment the brightness by
#    define RGB_MATRIX_SPD_STEP 6
/* HARDWARE CONFIG */

#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS RGBLIGHT_LIMIT_VAL
#    define RGB_MATRIX_LED_PROCESS_LIMIT DRIVER_LED_TOTAL / 10  // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16                       // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(SPLIT_KEYBOARD)
#    define RGBLIGHT_SPLIT
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#endif

/* USB CONFIG */
#define USB_POLLING_INTERVAL_MS 1



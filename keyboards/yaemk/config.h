#pragma once

/* MATRIX CONFIG */
#define MATRIX_ROWS 10
#define MATRIX_COLS 8
#define DIODE_DIRECTION COL2ROW
#define DEBUG_MATRIX_SCAN_RATE
#define DEBOUNCE 5
#define TAPPING_TOGGLE 2

/* ENCODER CONFIG */
#define ENCODER_RESOLUTION 2

/* RGB MATRIX DRIVER */
#if defined(RGB_MATRIX_ENABLE)
/* EFFECTS */
#    define RGB_DISABLE_WHEN_USB_SUSPENDED false  // turn off effects when suspended
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_HUE_STEP 3  // number of steps to cycle through the hue by
#    define RGB_MATRIX_SAT_STEP 6  // number of steps to increment the saturation by
#    define RGB_MATRIX_VAL_STEP 6  // number of steps to increment the brightness by#define RGB_DI_PIN A2
/* HARDWARE CONFIG */
#    define RGB_DI_PIN A2
#    define RGBLED_NUM 66
#    define DRIVER_LED_TOTAL RGBLED_NUM
#    define RGBLED_SPLIT \
        { 33, 33 }
#    define RGBLIGHT_LIMIT_VAL 192
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS RGBLIGHT_LIMIT_VAL
#    define RGB_MATRIX_LED_PROCESS_LIMIT DRIVER_LED_TOTAL / 10  // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16                       // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#endif

#if defined(RGB_MATRIX_ENABLE) && defined(SPLIT_KEYBOARD)
#    define RGBLIGHT_SPLIT
#    define RGB_MATRIX_SPLIT RGBLED_SPLIT
#endif

/* WS2812 DRIVER */
#define WS2812_TRST_US 80
#define WS2812_PWM_DRIVER PWMD2               // default: PWMD2
#define WS2812_PWM_CHANNEL 3                  // default: 2
#define WS2812_PWM_PAL_MODE 2                 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 2                  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

/* USB CONFIG */
#define USB_POLLING_INTERVAL_MS 1
#define SPLIT_USB_DETECT

/* SERIAL SPLIT DRIVER */
#define SPLIT_TRANSPORT_MIRROR
#define SERIAL_PIN_TX B6  // USART TX pin
#define SERIAL_PIN_RX B7  // USART TX pin
#define SERIAL_USE_MULTI_TRANSACTION
#define SERIAL_TIMEOUT_HANDSHAKE 1
#define SERIAL_TIMEOUT_BUFFER 5
#define SERIAL_USART_SPEED 921600

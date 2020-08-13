/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID 0x4B4B   // KK
#define PRODUCT_ID 0x5941  // YA
#define DEVICE_VER 0x0001
#define MANUFACTURER YAEMK

/* key matrix size */
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

#define DIODE_DIRECTION COL2ROW
#define DEBUG_MATRIX_SCAN_RATE

#define ENCODER_RESOLUTION 2

// The pin connected to the data pin of the LEDs
#define RGB_DI_PIN A2
#define RGBLED_NUM 66
// The number of LEDs connected
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_SPLIT \
    { 33, 33 }
#define RGBLIGHT_SPLIT
#define RGBLIGHT_LIMIT_VAL 192
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS RGBLIGHT_LIMIT_VAL
#define RGB_MATRIX_SPLIT RGBLED_SPLIT
//#define SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)

#ifdef RGBLIGHT_ENABLE
//#    define RGBLIGHT_ANIMATIONS
//#define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_BREATHING
//#define RGBLIGHT_EFFECT_CHRISTMAS
//#define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#define RGBLIGHT_EFFECT_RGB_TEST
//#define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_TWINKLE

//#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_HUE_STEP 3  // number of steps to cycle through the hue by
#    define RGBLIGHT_SAT_STEP 6  // number of steps to increment the saturation by
#    define RGBLIGHT_VAL_STEP 6  // number of steps to increment the brightness by

//  #define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_SLEEP  //  the RGB lighting will be switched off when the host goes to sleep
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_DISABLE_WHEN_USB_SUSPENDED false  // turn off effects when suspended

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_HUE_STEP 3  // number of steps to cycle through the hue by
#    define RGB_MATRIX_SAT_STEP 6  // number of steps to increment the saturation by
#    define RGB_MATRIX_VAL_STEP 6  // number of steps to increment the brightness by
#endif

#define WS2812_TRST_US 80
#define WS2812_PWM_DRIVER PWMD2               // default: PWMD2
#define WS2812_PWM_CHANNEL 3                  // default: 2
#define WS2812_PWM_PAL_MODE 2                 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 2                  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.

#define USB_POLLING_INTERVAL_MS 1

#define SPLIT_USB_DETECT
//#define SPLIT_USB_TIMEOUT 10000

#define SERIAL_PIN_TX B6  // USART TX pin
#define SERIAL_PIN_RX B7  // USART TX pin
#define SERIAL_USE_MULTI_TRANSACTION

#define SERIAL_TIMEOUT_HANDSHAKE 1
#define SERIAL_TIMEOUT_BUFFER 5

#define SERIAL_USART_SPEED 921600
//#define SERIAL_USART_SPEED 4500000
//#define SERIAL_USART_SPEED 2250000
//#define SERIAL_SPEED 0
#define SERIAL_USART_DRIVER UARTD1  // USART driver of TX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7  // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 4
#define TAPPING_TOGGLE 2

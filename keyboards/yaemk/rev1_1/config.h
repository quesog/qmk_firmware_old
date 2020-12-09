#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x4B4B   // KK
#define PRODUCT_ID 0x5941  // YA
#define DEVICE_VER 0x0002
#define MANUFACTURER YAEMK
#define PRODUCT YAEMK 1.1
#define DESCRIPTION YAEMK 1.1

#define MATRIX_COL_PINS \
    { A8, B15, A9, B13, B12, B2, B1, A3 }
#define MATRIX_ROW_PINS \
    { A10, B14, A6, A4, A5 }
#define MATRIX_COL_PINS_RIGHT \
    { A3, B1, B2, B12, B13, A9, B15, A8 }
#define MATRIX_ROW_PINS_RIGHT \
    { A10, B14, A6, A4, A5 }

#define ENCODERS_PAD_A_RIGHT \
    { A7 }
#define ENCODERS_PAD_B_RIGHT \
    { B0 }
#define ENCODERS_PAD_A \
    { B0 }
#define ENCODERS_PAD_B \
    { A7 }

#define SPLIT_HAND_PIN B9

/* WS2812 DRIVER */
#define RGB_DI_PIN A2
#define RGBLIGHT_LIMIT_VAL 192
#define WS2812_TRST_US 80
#define WS2812_PWM_DRIVER PWMD2               // default: PWMD2
#define WS2812_PWM_CHANNEL 3                  // default: 2
#define WS2812_PWM_PAL_MODE 2                 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM2  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA
#define RGBLED_NUM 66
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGBLED_SPLIT \
    { 33, 33 }

/* SERIAL SPLIT DRIVER */
#define SPLIT_TRANSPORT_MIRROR
#define SERIAL_PIN_TX B6  // USART TX pin
#define SERIAL_PIN_RX B7  // USART TX pin
#define SERIAL_USE_MULTI_TRANSACTION
#define SERIAL_TIMEOUT_HANDSHAKE 1
#define SERIAL_TIMEOUT_BUFFER 5
#define SERIAL_USART_SPEED 921600

#define SPLIT_USB_DETECT

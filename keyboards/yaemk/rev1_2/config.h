#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x4B4B   // KK
#define PRODUCT_ID 0x5941  // YA
#define DEVICE_VER 0x0003
#define MANUFACTURER YAEMK
#define PRODUCT YAEMK 1.2
#define DESCRIPTION YAEMK 1.2

#define MATRIX_COL_PINS \
    { B15, B14, B13, B2, B1, B0, A7, A2 }
#define MATRIX_ROW_PINS \
    { A8, B12, A6, A5, A1 }
#define MATRIX_COL_PINS_RIGHT \
    { A2, A7, B0, B1, B2, B13, B14, B15 }
#define MATRIX_ROW_PINS_RIGHT \
    { A8, B12, A6, A5, A1 }
#define ENCODERS_PAD_A_RIGHT \
    { A3 }
#define ENCODERS_PAD_B_RIGHT \
    { A4 }
#define ENCODERS_PAD_A \
    { A4 }
#define ENCODERS_PAD_B \
    { A3 }

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP FALSE

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_HAND_PIN C13
#define SPLIT_PLUG_DETECT_PIN A9
#define SPLIT_USB_DETECT

/* WS2812 DRIVER */
#define RGB_DI_PIN A10
#define RGBLIGHT_LIMIT_VAL 255
#define WS2812_TRST_US 80
#define WS2812_PWM_DRIVER PWMD1               // default: PWMD2
#define WS2812_PWM_CHANNEL 3                  // default: 2
#define WS2812_PWM_PAL_MODE 6                 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 2
#define WS2812_DMA_STREAM STM32_DMA1_STREAM5  // DMA Stream for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_DMA_CHANNEL 5                  // DMA Channel for TIMx_UP, see the respective reference manual for the appropriate values for your MCU.
#define WS2812_EXTERNAL_PULLUP

#define RGBLED_NUM 80
#define DRIVER_LED_TOTAL RGBLED_NUM
#define RGBLED_SPLIT \
    { 40, 40 }

/* SERIAL SPLIT DRIVER */
#define SPLIT_TRANSPORT_MIRROR
#define SERIAL_PIN_TX B10  // USART TX pin
#define SERIAL_PIN_RX B11  // USART RX pin
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_RX_PAL_MODE 7
#define SERIAL_USART_DRIVER UARTD3
#define SERIAL_USE_MULTI_TRANSACTION
#define SERIAL_TIMEOUT_HANDSHAKE 1
#define SERIAL_TIMEOUT_BUFFER 5
#define SERIAL_USART_SPEED 921600

#if defined(OLED_DRIVER_ENABLE)
#    define OLED_DISPLAY_CUSTOM
#    define OLED_DISPLAY_WIDTH 64
#    define OLED_DISPLAY_HEIGHT 128
#    define OLED_COLUMN_OFFSET 32
#    define OLED_MATRIX_SIZE (OLED_DISPLAY_HEIGHT / 8 * OLED_DISPLAY_WIDTH)
#    define OLED_BLOCK_TYPE uint16_t
#    define OLED_SOURCE_MAP \
        { 0, 8, 16, 24, 32, 40, 48, 56 }
#    define OLED_TARGET_MAP \
        { 56, 48, 40, 32, 24, 16, 8, 0 }
#    define OLED_BLOCK_COUNT (sizeof(OLED_BLOCK_TYPE) * 8)
#    define OLED_BLOCK_SIZE (OLED_MATRIX_SIZE / OLED_BLOCK_COUNT)
#    define OLED_COM_PINS COM_PINS_ALT
#    define OLED_IC OLED_IC_SH1106
#    define OLED_BRIGHTNESS 30
#    define OLED_TIMEOUT 15000
#endif

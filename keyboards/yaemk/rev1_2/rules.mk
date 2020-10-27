MCU = GD32VF103
BOARD = RV_YAEMK


# project specific files
SRC =	led_config.c
LTO_ENABLE = no
#EXTRAFLAGS += -Ofast
EXTRAFLAGS += -Og
OPT_DEFS += -DSTM32_DMA_REQUIRED=TRUE
OPT_DEFS += -g
ALLOW_WARNINGS = yes

MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
NKRO_ENABLE = yes      # USB Nkey Rollover
KEYBOARD_SHARED_EP = no
RGB_MATRIX_ENABLE = WS2812
WS2812_DRIVER = pwm
ENCODER_ENABLE = yes
DEBOUNCE_TYPE = eager_pk
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart_duplex
VIA_ENABLE = yes
EEPROM_DRIVER = vendor

LAYOUTS = split_5x8

MCU = GD32VF103
BOARD = RV_YAEMK

#DFU_ARGS = -d 1eaf:0003 -a2 -R
#DFU_SUFFIX_ARGS = -v 1eaf -p 0003

# project specific files
SRC =	led_config.c
LTO_ENABLE = yes
EXTRAFLAGS += -O3
#EXTRAFLAGS += -Ofast
#EXTRAFLAGS += -O0
OPT_DEFS += -DSTM32_DMA_REQUIRED=TRUE
OPT_DEFS += -g

MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes	# Audio control and System control
CONSOLE_ENABLE = yes	# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes      # USB Nkey Rollover
KEYBOARD_SHARED_EP = no
RGBLIGHT_ENABLE = no
RGB_MATRIX_ENABLE = WS2812
WS2812_DRIVER = pwm
ENCODER_ENABLE = yes
DEBOUNCE_TYPE = eager_pk
OLED_DRIVER_ENABLE = no
WPM_ENABLE = no
SPLIT_KEYBOARD = yes
SERIAL_DRIVER = usart_duplex
VIA_ENABLE = no
EEPROM_DRIVER = vendor

LAYOUTS = split_5x8

# Choose to use RISC-V or ARM MCU
RISC-V = yes
VIA = yes

ifeq ($(strip $(RISC-V)), yes)
      MCU                =   GD32VF103
      BOARD              =   SIPEED_LONGAN_NANO
      LTO_ENABLE         =   no
      EXTRAFLAGS         += -Os
    # Default clock is 96MHz, 120MHz is out of spec but possible.
    # OPT_DEFS           += -DOVERCLOCK_120MHZ
      EEPROM_DRIVER      =   transient # Disabled for testing purposes
      OLED_DRIVER_ENABLE =   no

    ifeq ($(strip $(VIA)), yes)
        KEYBOARD_SHARED_EP = yes 
    endif
else
    MCU        =   STM32F303
    BOARD      =   QMK_PROTON_C
    LTO_ENABLE =   yes
    EXTRAFLAGS += -Os
    EEPROM_DRIVER      = i2c
    OLED_DRIVER_ENABLE = yes
endif

# YAEMK source files
LAYOUTS = split_5x8
SRC     = led_config.c

# Debugging
EXTRAFLAGS     += -g2
ALLOW_WARNINGS =   yes

# QMK features 
CONSOLE_ENABLE     = no
DEBOUNCE_TYPE      = eager_pk
ENCODER_ENABLE     = yes
EXTRAKEY_ENABLE    = yes
MOUSEKEY_ENABLE    = yes
NKRO_ENABLE        = yes
RGB_MATRIX_DRIVER  = WS2812
RGB_MATRIX_ENABLE  = yes
SERIAL_DRIVER      = usart_duplex
SPLIT_KEYBOARD     = yes
WPM_ENABLE         = yes
WS2812_DRIVER      = pwm
ifeq ($(strip $(VIA)), yes)
    VIA_ENABLE         = yes
endif
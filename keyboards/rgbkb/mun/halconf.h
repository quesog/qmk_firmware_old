#pragma once

//#define HAL_USE_DAC TRUE

//#define HAL_USE_GPT TRUE

#define HAL_USE_I2C TRUE

#define HAL_USE_PWM TRUE

#if USE_FULL_DUPLEX
    #define HAL_USE_UART TRUE
    #define UART_USE_WAIT TRUE
#else
    #define HAL_USE_SERIAL TRUE
#endif

#define HAL_USE_SERIAL_USB TRUE

#include_next <halconf.h>

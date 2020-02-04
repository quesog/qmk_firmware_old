#include "quantum.h"
#include "serial.h"
#include "printf.h"

#include "ch.h"
#include "hal.h"

#ifndef USE_GPIOV1
// The default PAL alternate modes are used to signal that the pins are used for USART
#    ifndef USART_TX_PAL_MODE
#        define USART_TX_PAL_MODE 7
#    endif
#endif

#ifndef USART_DRIVER
#    define USART_DRIVER SD1
#endif

#ifndef SELECT_SOFT_SERIAL_SPEED
#    define SELECT_SOFT_SERIAL_SPEED 1
// TODO: correct speeds...
//  0: about 189kbps (Experimental only)
//  1: about 137kbps (default)
//  2: about 75kbps
//  3: about 39kbps
//  4: about 26kbps
//  5: about 20kbps
#endif

// Serial pulse period in microseconds. At the moment, going lower than 12 causes communication failure
#if SELECT_SOFT_SERIAL_SPEED == 0
#    define USART_SPEED 230400
#elif SELECT_SOFT_SERIAL_SPEED == 1
#    define USART_SPEED 115200
#elif SELECT_SOFT_SERIAL_SPEED == 2
#    define USART_SPEED 57600
#elif SELECT_SOFT_SERIAL_SPEED == 3
#    define USART_SPEED 38400
#elif SELECT_SOFT_SERIAL_SPEED == 4
#    define USART_SPEED 19200
#elif SELECT_SOFT_SERIAL_SPEED == 5
#    define USART_SPEED 14400
#else
#    error invalid SELECT_SOFT_SERIAL_SPEED value
#endif

#define TIMEOUT 100

static inline void sdClear(SerialDriver* driver) {
    while (sdGetTimeout(driver, TIME_IMMEDIATE) != MSG_TIMEOUT) {
        // Do nothing with the data
    }
}

static inline msg_t sdPutHalfDuplex(SerialDriver* driver, uint8_t data) {
    msg_t ret = sdPut(driver, data);
    sdGet(driver);

    return ret;
}

static inline msg_t sdWriteTimeoutHalfDuplex(SerialDriver* driver, uint8_t* data, uint8_t size, uint32_t timeout) {
    msg_t ret = sdWriteTimeout(driver, data, size, timeout);

    // Half duplex requires us to read back the data we just wrote - just throw it away
    uint8_t dump[size];
    sdRead(driver, dump, size);

    return ret;
}

static inline msg_t sdWriteHalfDuplex(SerialDriver* driver, uint8_t* data, uint8_t size) {
    msg_t ret = sdWrite(driver, data, size);

    // Half duplex requires us to read back the data we just wrote - just throw it away
    uint8_t dump[size];
    sdRead(driver, dump, size);

    return ret;
}

static const SerialConfig sdcfg = {
    USART_SPEED,     // speed - mandatory
    0,               // CR1
    0,               // CR2
    USART_CR3_HDSEL  // CT3
};

void handle_soft_serial_slave(void);

/*
 * This thread runs on the slave and responds to transactions initiated
 * by the master
 */
static THD_WORKING_AREA(waSlaveThread, 2048);
static THD_FUNCTION(SlaveThread, arg) {
    (void)arg;
    chRegSetThreadName("slave_transport");

    while (true) {
        handle_soft_serial_slave();
    }
}

void usart_init(void) {
    sdStart(&USART_DRIVER, &sdcfg);

#if defined(USE_GPIOV1)
    palSetPadMode(PAL_PORT(SOFT_SERIAL_PIN), PAL_PAD(SOFT_SERIAL_PIN), PAL_MODE_STM32_ALTERNATE_OPENDRAIN);
#else
    palSetPadMode(PAL_PORT(SOFT_SERIAL_PIN), PAL_PAD(SOFT_SERIAL_PIN), PAL_MODE_ALTERNATE(USART_TX_PAL_MODE) | PAL_STM32_OTYPE_OPENDRAIN);
#endif
}

void usart_slave_init(void) {
    usart_init();

    // Start transport thread
    chThdCreateStatic(waSlaveThread, sizeof(waSlaveThread), HIGHPRIO, SlaveThread, NULL);
}

static SSTD_t* Transaction_table      = NULL;
static uint8_t Transaction_table_size = 0;

void soft_serial_initiator_init(SSTD_t* sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;

    usart_init();
}

void soft_serial_target_init(SSTD_t* sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;

    usart_slave_init();
}

void handle_soft_serial_slave(void) {
    uint8_t sstd_index = sdGet(&USART_DRIVER);  // first chunk is always transaction id
    SSTD_t* trans      = &Transaction_table[sstd_index];

    if (trans->initiator2target_buffer_size) {
        sdRead(&USART_DRIVER, trans->initiator2target_buffer, trans->initiator2target_buffer_size);
    }

    if (trans->target2initiator_buffer_size) {
        sdWriteHalfDuplex(&USART_DRIVER, trans->target2initiator_buffer, trans->target2initiator_buffer_size);
    }

    if (trans->status) {
        *trans->status = TRANSACTION_ACCEPTED;
    }
}

/////////
//  start transaction by initiator
//
// int  soft_serial_transaction(int sstd_index)
//
// Returns:
//    TRANSACTION_END
//    TRANSACTION_NO_RESPONSE
//    TRANSACTION_DATA_ERROR
// this code is very time dependent, so we need to disable interrupts
#ifndef SERIAL_USE_MULTI_TRANSACTION
int soft_serial_transaction(void) {
    int sstd_index = 0;
#else
int soft_serial_transaction(int sstd_index) {
#endif

    if (sstd_index > Transaction_table_size) return TRANSACTION_TYPE_ERROR;
    SSTD_t* trans = &Transaction_table[sstd_index];
    msg_t   res   = 0;

    sdClear(&USART_DRIVER);

    sdPutHalfDuplex(&USART_DRIVER, sstd_index);  // first chunk is always transaction id

    if (trans->initiator2target_buffer_size) {
        res = sdWriteTimeoutHalfDuplex(&USART_DRIVER, trans->initiator2target_buffer, trans->initiator2target_buffer_size, MS2ST(TIMEOUT));
        if (res < 0) {
            dprintf("serial::usart_transmit NO_RESPONSE\n");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    if (trans->target2initiator_buffer_size) {
        res = sdReadTimeout(&USART_DRIVER, trans->target2initiator_buffer, trans->target2initiator_buffer_size, MS2ST(TIMEOUT));
        if (res < 0) {
            dprintf("serial::usart_receive NO_RESPONSE\n");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    return TRANSACTION_END;
}

#include "quantum.h"
#include "serial.h"
#include "printf.h"

#include "ch.h"
#include "hal.h"

#ifndef USART_CR1_M0
#    define USART_CR1_M0 USART_CR1_M  // some platforms (f1xx) dont have this so
#endif

#ifndef USE_GPIOV1
// The default PAL alternate modes are used to signal that the pins are used for USART
#    ifndef SERIAL_USART_TX_PAL_MODE
#        define SERIAL_USART_TX_PAL_MODE 7
#    endif
#endif

#ifndef SERIAL_USART_DRIVER
#    define SERIAL_USART_DRIVER UARTD1
#endif

#ifndef SERIAL_USART_CR1
#    define SERIAL_USART_CR1 (USART_CR1_PCE | USART_CR1_PS | USART_CR1_M0)  // parity enable, odd parity, 9 bit length
#endif

#ifndef SERIAL_USART_CR2
#    define SERIAL_USART_CR2 USART_CR2_STOP_1  // 1 stop bits
#endif

#ifndef SERIAL_USART_CR3
#    define SERIAL_USART_CR3 0x0
#endif

#ifdef SERIAL_PIN_TX
#    define SERIAL_USART_TX_PIN SERIAL_PIN_TX
#endif

#ifdef SERIAL_PIN_RX
#    define SERIAL_USART_RX_PIN SERIAL_PIN_RX
#endif

#ifndef SELECT_SERIAL_SPEED
#    define SELECT_SERIAL_SPEED 1
#endif

#ifdef SERIAL_USART_SPEED
// Allow advanced users to directly set SERIAL_USART_SPEED
#elif SERIAL_SPEED == 0
#    define SERIAL_USART_SPEED 460800
#elif SERIAL_SPEED == 1
#    define SERIAL_USART_SPEED 230400
#elif SERIAL_SPEED == 2
#    define SERIAL_USART_SPEED 115200
#elif SERIAL_SPEED == 3
#    define SERIAL_USART_SPEED 57600
#elif SERIAL_SPEED == 4
#    define SERIAL_USART_SPEED 38400
#elif SERIAL_SPEED == 5
#    define SERIAL_USART_SPEED 19200
#else
#    error invalid SERIAL_SPEED value
#endif

#ifndef SERIAL_TIMEOUT_HANDSHAKE
#    define SERIAL_TIMEOUT_HANDSHAKE 100
#endif

#ifndef SERIAL_TIMEOUT_BUFFER
#    define SERIAL_TIMEOUT_BUFFER 100
#endif

#define HANDSHAKE_MAGIC 7

static void rxchar(UARTDriver* uartp, uint16_t c);

/*
 * UART driver configuration structure. Only the blocking DMA enabled API is used,
 * therefore all callback functions are set to NULL.
 */
static UARTConfig uart_config = {.txend1_cb = NULL, .txend2_cb = NULL, .rxend_cb = NULL, .rxchar_cb = rxchar, .rxerr_cb = NULL, .speed = (SERIAL_USART_SPEED), .cr1 = (SERIAL_USART_CR1), .cr2 = (SERIAL_USART_CR2), .cr3 = (SERIAL_USART_CR3)};

static SSTD_t* Transaction_table      = NULL;
static uint8_t Transaction_table_size = 0;
extern mutex_t transactions_mutex;

static volatile uint8_t handshake = 0xFF;

static thread_reference_t tp_target = NULL;

static msg_t mailbox_receive_buffer[8];
MAILBOX_DECL(transaction_received_mailbox, &mailbox_receive_buffer, 8);

int start_transaction(uint8_t sstd_index);
int receive_transaction(uint8_t sstd_index);

/*
 * This callback is invoked when a character is received but the application
 * was not ready to receive it, the character is passed as parameter.
 * Receive transaction table index from initiator, which doubles as basic handshake token. */
static void rxchar(UARTDriver* uartp, uint16_t c) {
    (void)uartp;
    (void)c;
    chSysLockFromISR();
    handshake = (uint8_t)c;
    chEvtSignalI(tp_target, (eventmask_t)1);
    chSysUnlockFromISR();
}

__attribute__((weak)) void usart_init(void) {
#if defined(USE_GPIOV1)
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_STM32_ALTERNATE_PUSHPULL);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_INPUT_PULLDOWN);
#else
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_STM32_OTYPE_PUSHPULL | PAL_STM32_OSPEED_HIGHEST);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_INPUT_PULLDOWN);
#endif
}

/**
 * @brief React to transactions started by the initiator.
 * This version uses duplex send and receive usart pheriphals and DMA backed transfers.
 */
int receive_transaction(uint8_t sstd_index) {
    // println("Receiving!");
    size_t buffer_size = (size_t)sizeof(sstd_index);
    msg_t  msg         = 0;

    if (sstd_index > Transaction_table_size) {
        return TRANSACTION_TYPE_ERROR;
    }

    SSTD_t* trans = &Transaction_table[sstd_index];

    /* Send back the handshake which is XORed as a simple checksum,
     to signal that the target is ready to receive possible transaction buffers  */
    sstd_index ^= HANDSHAKE_MAGIC;
    buffer_size = (size_t)sizeof(sstd_index);
    msg         = uartSendFullTimeout(&SERIAL_USART_DRIVER, &buffer_size, &sstd_index, TIME_MS2I(SERIAL_TIMEOUT_HANDSHAKE));

    if (msg != MSG_OK) {
        if (trans->status) {
            *trans->status = TRANSACTION_NO_RESPONSE;
        }

        println("Receive: Handshake Failed!");
        return TRANSACTION_NO_RESPONSE;
    }

    /* Receive transaction buffer from the initiator. If this transaction requires it.*/
    buffer_size = (size_t)trans->initiator2target_buffer_size;
    if (buffer_size) {
        msg = uartReceiveTimeout(&SERIAL_USART_DRIVER, &buffer_size, trans->initiator2target_buffer, TIME_MS2I(SERIAL_TIMEOUT_BUFFER));
        if (msg != MSG_OK) {
            if (trans->status) {
                *trans->status = TRANSACTION_NO_RESPONSE;
            }

            println("Receive: Receive Failed!");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    /* Send transaction buffer to the initiator. If this transaction requires it. */
    buffer_size = (size_t)trans->target2initiator_buffer_size;
    if (buffer_size) {
        msg = uartSendFullTimeout(&SERIAL_USART_DRIVER, &buffer_size, trans->target2initiator_buffer, TIME_MS2I(SERIAL_TIMEOUT_BUFFER));
        if (msg != MSG_OK) {
            if (trans->status) {
                *trans->status = TRANSACTION_NO_RESPONSE;
            }

            println("Receive: Send Failed!");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    if (trans->status) {
        *trans->status = TRANSACTION_ACCEPTED;
    }

    return TRANSACTION_ACCEPTED;
}

/*
 * This thread runs on the target half and reacts to transactions init from the initiator.
 */
static THD_WORKING_AREA(waTargetThread, 512);
static THD_FUNCTION(TargetThread, arg) {
    (void)arg;
    chRegSetThreadName("target_usart_tx_rx");

    tp_target = chThdGetSelfX();

    while (true) {
        chEvtWaitAny((eventmask_t)1);

        // chMtxLock(&transactions_mutex);
        int msg = receive_transaction(handshake);
        // chMtxUnlockAll();
        if (msg == TRANSACTION_ACCEPTED) {
            chSysLock();
            chMBPostI(&transaction_received_mailbox, (msg_t)handshake);
            chSysUnlock();
        }
    }
}

int start_transaction(uint8_t sstd_index) {
    if (sstd_index > Transaction_table_size) {
        return TRANSACTION_TYPE_ERROR;
    }

    SSTD_t* const trans       = &Transaction_table[sstd_index];
    msg_t         msg         = 0;
    size_t        buffer_size = (size_t)sizeof(sstd_index);

    /* Send transaction table index to the target, which doubles as basic handshake token. */
    uartSendFullTimeout(&SERIAL_USART_DRIVER, &buffer_size, &sstd_index, TIME_MS2I(SERIAL_TIMEOUT_HANDSHAKE));

    uint8_t sstd_index_shake = 0xFF;
    /* Receive the handshake token from the target. The token was XORed by the target as a simple checksum.
     If the tokens match, the initiator will start to send and receive possible transaction buffers. */
    msg = uartReceiveTimeout(&SERIAL_USART_DRIVER, &buffer_size, &sstd_index_shake, TIME_MS2I(SERIAL_TIMEOUT_HANDSHAKE));
    if (msg != MSG_OK || (sstd_index_shake != (sstd_index ^ HANDSHAKE_MAGIC))) {
        println("Send: Handshake Failed");
        return TRANSACTION_NO_RESPONSE;
    }

    /* Send transaction buffer to the target. If this transaction requires it. */
    buffer_size = (size_t)trans->initiator2target_buffer_size;
    if (buffer_size) {
        msg = uartSendFullTimeout(&SERIAL_USART_DRIVER, &buffer_size, trans->initiator2target_buffer, TIME_MS2I(SERIAL_TIMEOUT_BUFFER));
        if (msg != MSG_OK) {
            println("Send: Send Failed");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    /* Receive transaction buffer from the target. If this transaction requires it. */
    buffer_size = (size_t)trans->target2initiator_buffer_size;
    if (buffer_size) {
        msg = uartReceiveTimeout(&SERIAL_USART_DRIVER, &buffer_size, trans->target2initiator_buffer, TIME_MS2I(SERIAL_TIMEOUT_BUFFER));
        if (msg != MSG_OK) {
            println("Send: Receive Failed");
            return TRANSACTION_NO_RESPONSE;
        }
    }

    return TRANSACTION_END;
}

/**
 * @brief Start transaction from the initiator to the target.
 * This version uses duplex send and receive usart pheriphals and DMA backed transfers.
 *
 * @param index Transaction Table index of the transaction to start.
 * @return int TRANSACTION_NO_RESPONSE in case of Timeout.
 *             TRANSACTION_TYPE_ERROR in case of invalid transaction index.
 *             TRANSACTION_END in case of success.
 */
int soft_serial_transaction(int sstd_index) {
    int status = TRANSACTION_END;

    for (int8_t error_count = 0; error_count < 3; error_count++) {
        int status = start_transaction(sstd_index);
        if (status == TRANSACTION_END) {
            break;
        }
    };

    return status;
}

void serial_init(SSTD_t* const sstd_table, int sstd_table_size) {
    Transaction_table      = sstd_table;
    Transaction_table_size = (uint8_t)sstd_table_size;
    usart_init();
    uartStart(&SERIAL_USART_DRIVER, &uart_config);
    chThdCreateStatic(waTargetThread, sizeof(waTargetThread), NORMALPRIO + 2, TargetThread, NULL);
}

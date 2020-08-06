#include <string.h>
#include <stddef.h>

#include "config.h"
#include "matrix.h"
#include "quantum.h"

#define ERROR_DISCONNECT_COUNT 5
#define ROWS_PER_HAND (MATRIX_ROWS / 2)

extern matrix_row_t matrix[MATRIX_ROWS];  // debounced values
// row offsets for each hand
extern uint8_t          thisHand, thatHand;
extern keyboard_state_t keyboard_state;

#ifdef RGBLIGHT_ENABLE
#    include "rgblight.h"
#endif

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef ENCODER_ENABLE
#    include "encoder.h"
static pin_t encoders_pad[] = ENCODERS_PAD_A;
#    define NUMBER_OF_ENCODERS (sizeof(encoders_pad) / sizeof(pin_t))
#endif

#if defined(USE_I2C)

#    include "i2c_master.h"
#    include "i2c_slave.h"

typedef struct _I2C_slave_buffer_t {
    matrix_row_t smatrix[ROWS_PER_HAND];
    uint8_t      backlight_level;
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    rgblight_syncinfo_t rgblight_sync;
#    endif
#    ifdef ENCODER_ENABLE
    uint8_t encoder_state[NUMBER_OF_ENCODERS];
#    endif
#    ifdef WPM_ENABLE
    uint8_t current_wpm;
#    endif
} I2C_slave_buffer_t;

static I2C_slave_buffer_t *const i2c_buffer = (I2C_slave_buffer_t *)i2c_slave_reg;

#    define I2C_BACKLIGHT_START offsetof(I2C_slave_buffer_t, backlight_level)
#    define I2C_RGB_START offsetof(I2C_slave_buffer_t, rgblight_sync)
#    define I2C_KEYMAP_START offsetof(I2C_slave_buffer_t, smatrix)
#    define I2C_ENCODER_START offsetof(I2C_slave_buffer_t, encoder_state)
#    define I2C_WPM_START offsetof(I2C_slave_buffer_t, current_wpm)

#    define TIMEOUT 100

#    ifndef SLAVE_I2C_ADDRESS
#        define SLAVE_I2C_ADDRESS 0x32
#    endif

// Get rows from other half over i2c
bool transport_master(matrix_row_t matrix[]) {
    i2c_readReg(SLAVE_I2C_ADDRESS, I2C_KEYMAP_START, (void *)matrix, sizeof(i2c_buffer->smatrix), TIMEOUT);

    // write backlight info
#    ifdef BACKLIGHT_ENABLE
    uint8_t level = is_backlight_enabled() ? get_backlight_level() : 0;
    if (level != i2c_buffer->backlight_level) {
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_BACKLIGHT_START, (void *)&level, sizeof(level), TIMEOUT) >= 0) {
            i2c_buffer->backlight_level = level;
        }
    }
#    endif

#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    if (rgblight_get_change_flags()) {
        rgblight_syncinfo_t rgblight_sync;
        rgblight_get_syncinfo(&rgblight_sync);
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_RGB_START, (void *)&rgblight_sync, sizeof(rgblight_sync), TIMEOUT) >= 0) {
            rgblight_clear_change_flags();
        }
    }
#    endif

#    ifdef ENCODER_ENABLE
    i2c_readReg(SLAVE_I2C_ADDRESS, I2C_ENCODER_START, (void *)i2c_buffer->encoder_state, sizeof(i2c_buffer->encoder_state), TIMEOUT);
    encoder_update_raw(i2c_buffer->encoder_state);
#    endif

#    ifdef WPM_ENABLE
    uint8_t current_wpm = get_current_wpm();
    if (current_wpm != i2c_buffer->current_wpm) {
        if (i2c_writeReg(SLAVE_I2C_ADDRESS, I2C_WPM_START, (void *)&current_wpm, sizeof(current_wpm), TIMEOUT) >= 0) {
            i2c_buffer->current_wpm = current_wpm;
        }
    }
#    endif
    return true;
}

void transport_slave(matrix_row_t matrix[]) {
    // Copy matrix to I2C buffer
    memcpy((void *)i2c_buffer->smatrix, (void *)matrix, sizeof(i2c_buffer->smatrix));

// Read Backlight Info
#    ifdef BACKLIGHT_ENABLE
    backlight_set(i2c_buffer->backlight_level);
#    endif

#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    // Update the RGB with the new data
    if (i2c_buffer->rgblight_sync.status.change_flags != 0) {
        rgblight_update_sync(&i2c_buffer->rgblight_sync, false);
        i2c_buffer->rgblight_sync.status.change_flags = 0;
    }
#    endif

#    ifdef ENCODER_ENABLE
    encoder_state_raw(i2c_buffer->encoder_state);
#    endif

#    ifdef WPM_ENABLE
    set_current_wpm(i2c_buffer->current_wpm);
#    endif
}

void transport_master_init(void) { i2c_init(); }

void transport_slave_init(void) { i2c_slave_init(SLAVE_I2C_ADDRESS); }

#else  // USE_SERIAL

#    include "serial.h"

extern mailbox_t transaction_received_mailbox;
void             react_received_primary(matrix_row_t matrix[]);
void             react_received_secondary(void);
void             transport_secondary(matrix_row_t matrix[]);
bool             transport_primary(void);

typedef struct _Serial_s2m_buffer_t {
    // TODO: if MATRIX_COLS > 8 change to uint8_t packed_matrix[] for pack/unpack
    matrix_row_t smatrix[ROWS_PER_HAND];

#    ifdef ENCODER_ENABLE
    uint8_t      encoder_state[NUMBER_OF_ENCODERS];
#    endif

} Serial_s2m_buffer_t;

typedef struct _Serial_m2s_buffer_t {
#    ifdef BACKLIGHT_ENABLE
    uint8_t backlight_level;
#    endif
#    ifdef WPM_ENABLE
    uint8_t current_wpm;
#    endif
} Serial_m2s_buffer_t;

#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
// When MCUs on both sides drive their respective RGB LED chains,
// it is necessary to synchronize, so it is necessary to communicate RGB
// information. In that case, define RGBLIGHT_SPLIT with info on the number
// of LEDs on each half.
//
// Otherwise, if the master side MCU drives both sides RGB LED chains,
// there is no need to communicate.

typedef struct _Serial_rgblight_t {
    rgblight_syncinfo_t rgblight_sync;
} Serial_rgblight_t;

volatile Serial_rgblight_t serial_rgblight = {};
uint8_t volatile status_rgblight           = 0;
#    endif

volatile Serial_s2m_buffer_t serial_s2m_buffer = {};
volatile Serial_m2s_buffer_t serial_m2s_buffer = {};
uint8_t volatile status0                       = 0;

enum serial_transaction_id {
    SEND_METADATA_TO_SECONDARY = 0,
    SEND_MATRIX_TO_PRIMARY,
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    PUT_RGBLIGHT,
#    endif
};

MUTEX_DECL(transactions_mutex);
SSTD_t transactions[] = {
    [SEND_METADATA_TO_SECONDARY] =
        {
            (uint8_t *)&status0,
            sizeof(serial_m2s_buffer),
            (uint8_t *)&serial_m2s_buffer,
            0,
            NULL,
        },
    [SEND_MATRIX_TO_PRIMARY] =
        {
            (uint8_t *)&status0,
            sizeof(serial_s2m_buffer),
            (uint8_t *)&serial_s2m_buffer,
            0,
            NULL,
        },
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    [PUT_RGBLIGHT] =
        {
            (uint8_t *)&status_rgblight, sizeof(serial_rgblight), (uint8_t *)&serial_rgblight, 0, NULL  // no slave to master transfer
        },
#    endif
};


void transport_master_init(void) { soft_serial_initiator_init(transactions, TID_LIMIT(transactions)); }
void transport_slave_init(void) { soft_serial_target_init(transactions, TID_LIMIT(transactions)); }

#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

// rgblight synchronization information communication.

void transport_rgblight_primary(void) {
    if (rgblight_get_change_flags()) {
        rgblight_get_syncinfo((rgblight_syncinfo_t *)&serial_rgblight.rgblight_sync);
        if (soft_serial_transaction(PUT_RGBLIGHT) == TRANSACTION_END) {
            rgblight_clear_change_flags();
        }
    }
}

void transport_rgblight_secondary(void) {
    if (status_rgblight == TRANSACTION_ACCEPTED) {
        rgblight_update_sync((rgblight_syncinfo_t *)&serial_rgblight.rgblight_sync, false);
        status_rgblight = TRANSACTION_END;
    }
}

#    else
#        define transport_rgblight_primary()
#        define transport_rgblight_secondary()
#    endif

void transport_task(void) {
    if (is_keyboard_master()) {
        static uint8_t error_count;
        transport_rgblight_primary();
        if (!transport_primary()) {
            error_count++;
            // TODO ERROR HANDLING DOES NOTHING ATM
            if (error_count > ERROR_DISCONNECT_COUNT) {
                // reset other half if disconnected
                for (int i = 0; i < ROWS_PER_HAND; ++i) {
                    matrix[thatHand + i] = 0;
                }
            }
        } else {
            error_count = 0;
        }
        react_received_primary(matrix + thatHand);
    } else {
        transport_rgblight_secondary();
        transport_secondary(matrix + thisHand);
        react_received_secondary();
    }
}

bool transport_primary(void) {
    chMtxLock(&transactions_mutex);

    bool           send_meta           = false;
#    ifdef BACKLIGHT_ENABLE
    static uint8_t backlight_level_old = 0;
    serial_m2s_buffer.backlight_level  = is_backlight_enabled() ? get_backlight_level() : 0;
    send_meta                          = backlight_level_old != serial_m2s_buffer.backlight_level;
#    endif

#    ifdef WPM_ENABLE
    static uint8_t wpm_old             = 0;
    serial_m2s_buffer.current_wpm      = get_current_wpm();
    send_meta                          = send_meta || wpm_old != serial_m2s_buffer.current_wpm;
#    endif

    chMtxUnlockAll();

    if (send_meta) {
        if (serial_transaction(SEND_METADATA_TO_SECONDARY) != TRANSACTION_END) {
            // return;
        }
    }
    return true;
}

void transport_secondary(matrix_row_t matrix[]) {
    if (keyboard_state.matrix_changed || keyboard_state.encoder_changed) {
        chMtxLock(&transactions_mutex);
        // TODO: if MATRIX_COLS > 8 change to pack()
        for (int i = 0; i < ROWS_PER_HAND; ++i) {
            serial_s2m_buffer.smatrix[i] = matrix[i];
        }
#    ifdef ENCODER_ENABLE
        //  if (keyboard_state.encoder_changed) {
        encoder_state_raw((uint8_t *)serial_s2m_buffer.encoder_state);
        //   }
#    endif
        chMtxUnlockAll();
        if (serial_transaction(SEND_MATRIX_TO_PRIMARY) != TRANSACTION_END) {
            // return;
        }
    }
}

// React on the primary half to received transactions
void react_received_primary(matrix_row_t matrix[]) {
    uint8_t sstd_index;
    chSysLock();
    msg_t msg = chMBFetchI(&transaction_received_mailbox, (msg_t *)(&sstd_index));
    chSysUnlock();

    if (msg != MSG_OK) {
        return;
    }

    // Primary Received Matrix Changes from the Secondary Half, so we have to update our Matrix with the changes
    if (sstd_index == SEND_MATRIX_TO_PRIMARY) {
        chMtxLock(&transactions_mutex);

        // TODO:  if MATRIX_COLS > 8 change to unpack()
        for (int i = 0; i < ROWS_PER_HAND; ++i) {
            matrix[i] = serial_s2m_buffer.smatrix[i];
        }
#    ifdef ENCODER_ENABLE
        encoder_update_raw((uint8_t *)serial_s2m_buffer.encoder_state);
#    endif
        chMtxUnlockAll();
    }
}

void react_received_secondary(void) {
    uint8_t sstd_index;
    chSysLock();
    msg_t msg = chMBFetchI(&transaction_received_mailbox, (msg_t *)(&sstd_index));
    chSysUnlock();

    if (msg != MSG_OK) {
        return;
    }

    if (sstd_index == SEND_METADATA_TO_SECONDARY) {
        chMtxLock(&transactions_mutex);

#    ifdef WPM_ENABLE
        set_current_wpm(serial_m2s_buffer.current_wpm);
#    endif

#    ifdef BACKLIGHT_ENABLE
        backlight_set(serial_m2s_buffer.backlight_level);
#    endif
        chMtxUnlockAll();
    }
}

#endif

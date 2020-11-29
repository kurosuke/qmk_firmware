#include <string.h>
#include <stddef.h>

#include "config.h"
#include "matrix.h"
#include "quantum.h"
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

#define ROWS_PER_HAND (MATRIX_ROWS / 2)

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


#    include "serial.h"

typedef struct _Serial_m2s_buffer_t {
    matrix_row_t smatrix[ROWS_PER_HAND];
    uint8_t stop;
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

volatile Serial_m2s_buffer_t serial_m2s_buffer = {};
uint8_t volatile status0                       = 0;

enum serial_transaction_id {
    GET_SLAVE_MATRIX = 0,
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    PUT_RGBLIGHT,
#    endif
    SEND_KEYMATRIX,

    // keycode
    //     1    2    3    4    5 : 1byte(1-5)
    //     6    7    8    9   10 : 1byes(6-8) 2bytes(1-2)
    //    11   12   13   14   15 : 2byte(3-7)
    //         17        19   20 : 3byte(1, 3-4)
    // encoder
    // LEFT  ENCODE VALUE(0-127) : 5byte(1-4)
    // RIGHT ENCODE VALUE(0-127) : 6byte(5-8)
};

SSTD_t transactions[] = {
#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)
    [PUT_RGBLIGHT] =
        {
            (uint8_t *)&status_rgblight, sizeof(serial_rgblight), (uint8_t *)&serial_rgblight, 0, NULL  // no slave to master transfer
        },
#    endif
    [SEND_KEYMATRIX] =
        {
            (uint8_t *)&status0,
            sizeof(serial_m2s_buffer),
            (uint8_t *)&serial_m2s_buffer,
            0, NULL
        },
};

void transport_master_init(void) { soft_serial_initiator_init(transactions, TID_LIMIT(transactions)); }

void transport_slave_init(void) { soft_serial_target_init(transactions, TID_LIMIT(transactions)); }

#    if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_SPLIT)

// rgblight synchronization information communication.

void transport_rgblight_master(void) {
    if (rgblight_get_change_flags()) {
        rgblight_get_syncinfo((rgblight_syncinfo_t *)&serial_rgblight.rgblight_sync);
        if (soft_serial_transaction(PUT_RGBLIGHT) == TRANSACTION_END) {
            rgblight_clear_change_flags();
        }
    }
}

void transport_rgblight_slave(void) {
    if (status_rgblight == TRANSACTION_ACCEPTED) {
        rgblight_update_sync((rgblight_syncinfo_t *)&serial_rgblight.rgblight_sync, false);
        status_rgblight = TRANSACTION_END;
    }
}

#    else
#        define transport_rgblight_master()
#        define transport_rgblight_slave()
#    endif


/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

bool transport_master(matrix_row_t matrixx[]) {
    int keyno = 0;
#    ifdef ENCODER_ENABLE
    uint8_t encoders[NUMBER_OF_ENCODERS];
    uint8_t encoder_left;
    uint8_t encoder_right;
#    endif /* ENCODER_ENABLE */
    transport_rgblight_master();

#ifdef MASTER_RIGHT
    for (int i = ROWS_PER_HAND; i < MATRIX_ROWS; ++i) {
#else
    for (int i = 0; i < ROWS_PER_HAND; ++i) {
#endif /* MASTER_RIGHT */
        serial_m2s_buffer.smatrix[keyno++] = matrix[i];
    }

#    ifdef BACKLIGHT_ENABLE
    // Write backlight level for slave to read
    serial_m2s_buffer.backlight_level = is_backlight_enabled() ? get_backlight_level() : 0;
#    endif /* BACKLIGHT_ENABLE */

#    ifdef ENCODER_ENABLE
    encoder_state_raw(encoders);

#ifdef MASTER_RIGHT
    encoder_left = encoders[0];
    encoder_right = encoders[1];
#else
    encoder_left = encoders[2];
    encoder_right = encoders[3];
#endif  /* MASTER_RIGHT */

    serial_m2s_buffer.smatrix[4] = encoder_left & 0x7f;
    serial_m2s_buffer.smatrix[5] = encoder_right & 0x7f;
#ifdef CONSOLE_ENABLEx
    uprintf("EN VAL: L:%u R:%u\n", encoder_left, encoder_right);
#endif
#    endif /* ENCODER_ENABLE */

#    ifdef WPM_ENABLE
    // Write wpm to slave
    serial_m2s_buffer.current_wpm = get_current_wpm();
#    endif

    serial_m2s_buffer.stop = 0xff;
    if (soft_serial_transaction(SEND_KEYMATRIX) != TRANSACTION_END) {
        return false;
    }

    return true;
}

void transport_slave(matrix_row_t matrixx[]) {
    xprintf("transport_slave\n");
}

// vi:set ts=4 sw=4 sts=4 ft=sh et:

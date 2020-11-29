#include QMK_KEYBOARD_H

#include "serial.h"
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Default Layer
   *  Master Side (USB Cable Connected Side)
   *  ,-------------------------------
   *  |    1    2    3    4   5  XXXX 
   *  |    6    7    8    9   0  XXXX
   *  |    a    b    c    d   e  XXXX 
   *  | XXXX    d XXXX    LSFT   RSFT  XXXX
   *  | XXXX XXXX XXXX XXXX XXXX XXXX 
   *  `-------------------------------
   *  Slave Side (USB Cable Not Connected Side)
   *  ,-------------------------------
   *  |    1    2    3    4   5  XXXX 
   *  |    6    7    8    9   0  XXXX
   *  |    a    b    c    d   e  XXXX 
   *  | XXXX    d XXXX    LSFT   RSFT  XXXX
   *  `-------------------------------
   *  LSHIFT + RSHIFT + d = QMK debug mode
   */

  [0] = LAYOUT( /* Base */ 

    // LEFT HAND
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     XXXXXXX,  
    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX,  
    KC_A,     KC_B,     KC_C,     KC_D,     KC_E,     XXXXXXX,
    XXXXXXX,  KC_D,     XXXXXXX,  KC_LSHIFT,KC_RSHIFT,XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    // RIGHT HAND: ifdef MASTER_RIGHT
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     XXXXXXX,  
    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     XXXXXXX,  
    KC_A,     KC_B,     KC_C,     KC_D,     KC_E,     XXXXXXX,
    XXXXXXX,  KC_D,     XXXXXXX,  KC_LSHIFT,KC_RSHIFT,XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX
  ),

  [1] = LAYOUT(
    KC_1,     KC_2,     KC_3,     KC_4,     KC_5,    XXXXXXX,  
    KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    XXXXXXX,  
    KC_A,     KC_B,     KC_C,     KC_D,     KC_E,    XXXXXXX,
    XXXXXXX,  KC_X,   XXXXXXX,    KC_Y,     KC_Z,    XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  

    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  
    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX   
  ),
};


void matrix_init_kb(void) {
  debug_enable = true;
  debug_matrix = true;
  debug_mouse  = true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif
    /* key repeat true */
    return true;
}

void matrix_init_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

void encoder_update_user(uint8_t index, bool clockwise) {
    uprintf("EN: index: %u, clockwise: %u\n", index, clockwise);
    if (index == 0 || index == 2) {
        if (clockwise) {
            tap_code16(KC_RIGHT);
        } else {
            tap_code16(KC_LEFT);
        }
    } else if (index == 1 || index == 3) {
        if (clockwise) {
            tap_code16(KC_DOWN);
        } else {
            tap_code16(KC_UP);
        }
    }
}

// vi:set ts=4 sw=4 sts=4 ft=sh et:

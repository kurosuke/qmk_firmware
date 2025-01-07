#include "quantum.h"
#include "rev1_4knob.h"
#include QMK_KEYBOARD_H
#include "quantum/rgblight/rgblight.h"

// カスタムキーコードの定義
enum custom_keycodes {
    REPEAT_W = SAFE_RANGE,
};

// グローバル変数
static bool w_repeat_active = false;
static uint16_t led_timer = 0;
const uint16_t LED_INTERVAL = 200;    // 200ms間隔でLED点滅

// LED色の定義
#define LED_YELLOW_H 43  // HSV色相値での黄色 (0-255の範囲)
#define LED_GREEN_H 85   // HSV色相値での緑色 (0-255の範囲)
#define LED_SAT 128      // 彩度
#define LED_VAL 64       // 明度

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case REPEAT_W:
            if (record->event.pressed) {
                // キーが押されたとき
                w_repeat_active = !w_repeat_active;  // トグル
                if (w_repeat_active) {
                    led_timer = timer_read();
                    // LED初期状態：緑色に点灯
                    rgblight_sethsv(LED_GREEN_H, LED_SAT, LED_VAL);
                    rgblight_enable();
                    
                    // Wキーを押した状態にする
                    register_code(KC_W);
                } else {
                    // Wキーを離す
                    unregister_code(KC_W);
                    // LEDをオフ
                    rgblight_disable();
                }
            }
            return false;
        default:
            return true;
    }
}

void matrix_scan_user(void) {
    if (w_repeat_active) {
        // LED点滅制御
        if (timer_elapsed(led_timer) > LED_INTERVAL) {
            static bool led_state = true;
            if (led_state) {
                rgblight_sethsv(LED_GREEN_H, LED_SAT, LED_VAL);
                rgblight_enable();
            } else {
                rgblight_disable();
            }
            led_state = !led_state;
            led_timer = timer_read();
        }
    }
}

// キーマップの定義（変更なし）
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESCAPE,KC_Q,   KC_W,    KC_E,    KC_R,    XXXXXXX,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_COMMA, XXXXXXX,
        KC_T,    KC_LCTL, KC_X,    MS_BTN1, MS_BTN2, XXXXXXX,
        XXXXXXX, REPEAT_W, XXXXXXX, KC_LSFT, KC_SPC,  XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [1] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,

        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

void keyboard_init_user(void) {
    // 初期化時に暗い緑色を設定
    rgblight_enable();
    rgblight_sethsv(LED_GREEN_H, 255, 128);  // H:85(緑), S:255(最大), V:128(暗め)
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(MS_LEFT, MS_RGHT), ENCODER_CCW_CW(MS_UP, MS_DOWN)  },
    //                  Encoder 1                                     Encoder 2
    [1] =   { ENCODER_CCW_CW(KC_WH_U, KC_WH_D), ENCODER_CCW_CW(KC_1, KC_2)  }
    //                  Encoder 1                                     Encoder 2
};
#endif

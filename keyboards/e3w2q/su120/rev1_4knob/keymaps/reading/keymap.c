#include "quantum.h"
#include "rev1_4knob.h"
#include QMK_KEYBOARD_H

// カスタムキーコードを定義
enum custom_keycodes {
    SAFE_MO1 = SAFE_RANGE,
    SAFE_MO2,
    // 必要に応じて追加
};


// キーマップの定義
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_BTN1, KC_LEFT_SHIFT, KC_LEFT_CTRL,SAFE_MO1, XXXXXXX, XXXXXXX,
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
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [1] = LAYOUT(
        KC_SPC,  KC_UP,  KC_DOWN,  XXXXXXX, XXXXXXX, XXXXXXX,
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


#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_WH_U, KC_WH_D), ENCODER_CCW_CW(KC_1, KC_2)  },
    //                  Encoder 1                                     Encoder 2(None)
    [1] =   { ENCODER_CCW_CW(KC_PAGE_DOWN, KC_PAGE_UP), ENCODER_CCW_CW(KC_1, KC_2)  }
    //                  Encoder 1                                     Encoder 2(None)
};
#endif


void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;

#ifdef XXXX
    // LEDピンをアウトプットに設定
    setPinOutput(B0);

    // 1回目の点滅
    writePinHigh(B0);
    wait_ms(100);
    writePinLow(B0);
    wait_ms(100);

    // 2回目の点滅
    writePinHigh(B0);
    wait_ms(100);
    writePinLow(B0);
#endif
}

#ifdef OLED_ENABLE

// QMKロゴデータ（32x32px）
static const char PROGMEM qmk_logo[] = {
// 'r', 32x32px
0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0x70, 0x38, 0x38, 0x1c, 0x9c, 0x8c, 0xce, 0xce, 0x0e, 
0x0e, 0xce, 0xce, 0x8c, 0x9c, 0x1c, 0x38, 0x38, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0xe0, 0xfc, 0xff, 0x07, 0x03, 0x60, 0x78, 0x7e, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x07, 0x00, 
0x00, 0x07, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0x7e, 0x78, 0x60, 0x03, 0x0f, 0xff, 0xfc, 0xe0, 0x00, 
0x00, 0x0f, 0x7f, 0xfe, 0xe0, 0x80, 0x0e, 0x3c, 0x7c, 0xfe, 0xfc, 0xf0, 0xe0, 0xc0, 0xc0, 0x00, 
0x00, 0xc0, 0xc0, 0xe0, 0xf0, 0xfc, 0xfe, 0x7c, 0x3c, 0x0e, 0x80, 0xe0, 0xff, 0x7f, 0x0f, 0x00, 
0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1c, 0x1c, 0x38, 0x31, 0x73, 0x73, 0x63, 0x67, 0x60, 
0x60, 0x67, 0x63, 0x73, 0x73, 0x31, 0x38, 0x1c, 0x1c, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

// レイヤー状態を追跡する変数
static uint8_t saved_layer = 0;
static bool needs_update = false;  // 追加: 更新フラグ


void oled_display(void)
{
#ifdef CONSOLE_ENABLE
    uprintf("oled display\n");
#endif 
    // テストパターンの表示（4ページ分）
    uint8_t  bytes_per_page =  sizeof(qmk_logo)/4;
    for (uint8_t page = 0; page < 4; page++) {
        oled_set_cursor(0, page);
        oled_write_raw_P(qmk_logo + (bytes_per_page*page), bytes_per_page);
    }
    
    // エンコーダモード表示
    oled_set_cursor(7, 0);
    switch (get_highest_layer(layer_state)) {
        case 0:
#ifdef CONSOLE_ENABLE
            uprintf("Mode 0\n");
#endif 
            oled_write_P(PSTR("Enc: WHEEL   "), false);
            break;
        case 1:
#ifdef CONSOLE_ENABLE
            uprintf("Mode 1\n");
#endif 
            oled_write_P(PSTR("Enc: PG UP/DN"), false);
            break;
    }
    
    
    // キー配置表示
    oled_set_cursor(7, 3);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("BTN1 SHFT CTRL"), false);
            break;
        case 1:
            oled_write_P(PSTR("SPC   ^    v  "), false);
            break;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
#endif 
    switch (keycode) {
        case SAFE_MO1:
            if (record->event.pressed) {
                // キーを押した時：現在のレイヤーを保存して新しいレイヤーに切り替え
                saved_layer = get_highest_layer(layer_state);
                layer_on(1);  // レイヤー1をオン
                needs_update = true;  // 更新フラグをセット
#ifdef CONSOLE_ENABLE
                uprintf("SELF MO(1)\n");
#endif
                oled_display();
            } else {
                // キーを離した時：保存していたレイヤーに戻す
                layer_off(1);  // レイヤー1をオフ
                needs_update = true;  // 更新フラグをセット
                layer_on(saved_layer);
#ifdef CONSOLE_ENABLE
                uprintf("SELF MO(0)\n");
#endif
                oled_display();
            }
            return false;  // 他のキーボードにキーコードを送信しない
            
        case SAFE_MO2:
            if (record->event.pressed) {
                saved_layer = get_highest_layer(layer_state);
                layer_on(2);
            } else {
                layer_off(2);
                layer_on(saved_layer);
            }
            return false;
    }
    return true;  // 他のキーは通常通り処理
}

bool oled_task_user(void) {
    if (needs_update) {  // フラグがセットされている場合のみ更新
        oled_display();
        needs_update = false;  // フラグをリセット
    }
    return true;  // trueを返して通常の更新も許可
}
#endif

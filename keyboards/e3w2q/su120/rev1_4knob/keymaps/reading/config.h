/* Copyright 2019 e3w2q
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define VIA_ENCODER_ENABLE false
#define EECONFIG_CLEAR_ENABLE ture

// config.h
#define I2C_DRIVER I2CD1
#define I2C1_SCL_PIN D0    // SCL
#define I2C1_SDA_PIN D1    // SD

#define I2C1_TIMINGR_PRESC 0U
#define I2C1_TIMINGR_SCLDEL 3U
#define I2C1_TIMINGR_SDADEL 1U
#define I2C1_TIMINGR_SCLH 3U
#define I2C1_TIMINGR_SCLL 9U

#define OLED_TIMEOUT 0  // タイムアウトを無効化
// または長い時間を設定
// #define OLED_TIMEOUT 600000  // 10分

// スリープを無効化
#define OLED_DISABLE_TIMEOUT

// キーボードの省電力タイマーを無効化または延長
#define USB_SUSPEND_WAKEUP_DELAY 0
#define NO_USB_STARTUP_CHECK

// place overrides here

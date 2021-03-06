/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"

#include "drivers/time.h"
#include "drivers/io.h"
#include "pwm_esc_detect.h"
#include "timer.h"

#ifdef USE_BRUSHED_ESC_AUTODETECT
uint8_t hardwareMotorType = MOTOR_UNKNOWN;

void detectBrushedESC(void)
{
    int i = 0;
    while (!(TIMER_HARDWARE[i].usageFlags & TIM_USE_MOTOR) && (i < TIMER_CHANNEL_COUNT)) {
        i++;
    }
    IO_t MotorDetectPin = IOGetByTag(TIMER_HARDWARE[i].tag);
    IOInit(MotorDetectPin, OWNER_SYSTEM, 0);
    IOConfigGPIO(MotorDetectPin, IOCFG_IPU);

    delayMicroseconds(10);  // allow configuration to settle

    // Check presence of brushed ESC's
    if (IORead(MotorDetectPin)) {
        hardwareMotorType = MOTOR_BRUSHLESS;
    } else {
        hardwareMotorType = MOTOR_BRUSHED;
    }
}
#endif

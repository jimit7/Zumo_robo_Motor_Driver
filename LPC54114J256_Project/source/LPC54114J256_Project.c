/*
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC54114_cm4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */
#define SCT_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
#define PWM_Left kSCTIMER_Out_5
#define PWM_Right	kSCTIMER_Out_7
/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

sctimer_config_t sctimerInfo;
   sctimer_pwm_signal_param_t pwmParam;
  // uint32_t stateNumber;
   uint32_t event;
   uint32_t sctimerClock;

   /* Board pin, clock, debug console init */
   /* attach 12 MHz clock to FLEXCOMM0 (debug consolie) */
  // CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

   /* enable clock for GPIO*/
   //CLOCK_EnableClock(kCLOCK_Gpio0);
   //CLOCK_EnableClock(kCLOCK_Gpio1);

   BOARD_InitPins();
   BOARD_BootClockFROHF48M();
   BOARD_InitDebugConsole();

   sctimerClock = SCT_CLK_FREQ;

   /* Default configuration operates the counter in 32-bit mode */
   SCTIMER_GetDefaultConfig(&sctimerInfo);

   /* Initialize SCTimer module */
   SCTIMER_Init(SCT0, &sctimerInfo);
   pwmParam.output = PWM_Left;
   pwmParam.level = kSCTIMER_HighTrue;
   pwmParam.dutyCyclePercent = 10;

   /* Schedule events in current state; State 0 */
   /* Schedule events for generating a 24KHz PWM with 10% duty cycle from first Out in the current state */
        if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm, 24000U, sctimerClock, &event) ==
          kStatus_Fail)
        {
          return -1;
        }

    pwmParam.output = PWM_Right;
    pwmParam.level = kSCTIMER_HighTrue;
    pwmParam.dutyCyclePercent = 10;

    /* Schedule events in current state; State 0 */
    /* Schedule events for generating a 24KHz PWM with 10% duty cycle from first Out in the current state */
        if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm, 24000U, sctimerClock, &event) ==
                kStatus_Fail)
            {
                return -1;
            }

     SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);
     while (1)
        {
        }
    return 0 ;
}



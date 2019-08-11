/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_usart.h"
#include "fsl_sctimer.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_USART USART2
#define DEMO_USART_CLK_SRC kCLOCK_Flexcomm2
#define DEMO_USART_CLK_FREQ CLOCK_GetFreq(kCLOCK_Flexcomm2)
#define SCTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
#define DEMO_FIRST_SCTIMER_OUT kSCTIMER_Out_4
#define DEMO_SECOND_SCTIMER_OUT kSCTIMER_Out_5
#define DEMO_THIRD_SCTIMER_OUT	kSCTIMER_Out_7
#define DEMO_FOURTH_SCTIMER_OUT	kSCTIMER_Out_2
 sctimer_config_t sctimerInfo;
 sctimer_pwm_signal_param_t pwmParam;
 uint32_t event1,event2,event3,event4,speed=60;
 uint32_t sctimerClock;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

uint8_t txbuff[] = "Usart polling example\r\nBoard will send back received characters\r\n";
//uint8_t rxbuff[20] = {0};

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    uint8_t ch;
    usart_config_t config;



   sctimer_config_t sctimerInfo;
   sctimer_pwm_signal_param_t pwmParam;

   uint32_t event1,event2,event3,event4,speed=80;
   uint32_t sctimerClock;

    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk( BOARD_DEBUG_UART_CLK_ATTACH_CORE1);

    /* reset FLEXCOMM for USART */
    RESET_PeripheralReset( kFC0_RST_SHIFT_RSTn);
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);
    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();
    /*
     * config.baudRate_Bps = 115200U;
     * config.parityMode = kUSART_ParityDisabled;
     * config.stopBitCount = kUSART_OneStopBit;
     * config.loopback = false;
     * config.enableTx = false;
     * config.enableRx = false;
     */
    USART_GetDefaultConfig(&config);
    config.baudRate_Bps = 115200;
    config.enableTx = true;
    config.enableRx = true;
    USART_Init(DEMO_USART, &config, DEMO_USART_CLK_FREQ);

    sctimerClock = SCTIMER_CLK_FREQ;
    SCTIMER_GetDefaultConfig(&sctimerInfo);
    /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);



    	pwmParam.output = DEMO_FIRST_SCTIMER_OUT;
    	pwmParam.level = kSCTIMER_HighTrue;
    	pwmParam.dutyCyclePercent = 1;
    	if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 2400U, sctimerClock, &event1) == kStatus_Fail)
    	{
           return -1;
    	}

    	pwmParam.output = DEMO_SECOND_SCTIMER_OUT;
    	pwmParam.level = kSCTIMER_HighTrue;
       	pwmParam.dutyCyclePercent =2 ;
       	if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 2400U, sctimerClock, &event2) == kStatus_Fail)
       	{
       	        return -1;
       	}
       	pwmParam.output = DEMO_THIRD_SCTIMER_OUT;
        pwmParam.level = kSCTIMER_HighTrue;
        pwmParam.dutyCyclePercent = 1;
        if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 2400U, sctimerClock, &event3) == kStatus_Fail)
        {
              return -1;
        }

        pwmParam.output = DEMO_FOURTH_SCTIMER_OUT;
        pwmParam.level = kSCTIMER_HighTrue;
        pwmParam.dutyCyclePercent =2 ;
        if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 2400U, sctimerClock, &event4) == kStatus_Fail)
        {
          	        return -1;
        }

    USART_WriteBlocking(DEMO_USART, txbuff, sizeof(txbuff) - 1);

    while (1)
    {
        USART_ReadBlocking(DEMO_USART, &ch, 1);


        if(ch == 'f')
                	{
                	printf("Rotate on axis\n");
                	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT, speed, event1);
                	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT,1, event2);
                	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_THIRD_SCTIMER_OUT, 1, event3);
                	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FOURTH_SCTIMER_OUT,speed, event4);

                	}

        if(ch == 'a')
        	{
        	printf("right\n");
        	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT, speed, event1);
        	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT,1, event2);
        	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_THIRD_SCTIMER_OUT, 1, event3);
        	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FOURTH_SCTIMER_OUT,1, event4);

        	}
       if(ch == 'b')
        {
    	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT, 1, event1);
    	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT, 1, event2);
    	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_THIRD_SCTIMER_OUT, speed, event3);
    	   SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FOURTH_SCTIMER_OUT, 1, event4);

    	   printf("left\n");
        }
        if(ch == 'c')
        {
        	 SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT,speed, event1);
        	 SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT,1, event2);
             SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_THIRD_SCTIMER_OUT, speed, event3);
        	 SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FOURTH_SCTIMER_OUT, 1, event4);

        	printf("go straight\n");
        }
        if(ch == 'd')
        {
        	printf("stop");
        	 SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT, 1, event1);
        	 SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT, 1, event2);
        	 SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_THIRD_SCTIMER_OUT, 1, event3);
        	 SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FOURTH_SCTIMER_OUT, 1, event4);

        }
        if(ch =='e')
        {
        	printf("reverse");
        //rintf("right\n");
        	SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT, 1, event1);
        	SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT,speed, event2);
        	SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_THIRD_SCTIMER_OUT, 1, event3);
        	SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FOURTH_SCTIMER_OUT,speed, event4);

        }
        //USART_WriteBlocking(DEMO_USART, &ch, 1);
    }
}

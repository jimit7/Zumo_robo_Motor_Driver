/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

#include "pin_mux.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
//#define APP_BOARD_TEST_LED_PORT 1U
//#define APP_BOARD_TEST_LED_PIN 10U
//#define APP_SW_PORT BOARD_SW1_GPIO_PORT
//#define APP_SW_PIN  BOARD_SW1_GPIO_PIN
#define GPIO_PORT 0U
#define Left_PIN1 2U
#define Left_PIN2 19U
#define Right_PIN1 25U
#define Right_PIN2 26U
#define BOARD_LED_PORT 1U
#define BOARD_LED_PIN 10U
volatile uint32_t g_systickCounter;

/*******************************************************************************
 * Code
 ******************************************************************************/
void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while(g_systickCounter != 0U)
    {
    }
}

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 100000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
   // uint32_t port_state = 0;
    uint32_t pin1=1,pin2=1,pin3=1,pin4=1;
    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalInput,
    };
    gpio_pin_config_t led_config2 = {
         kGPIO_DigitalOutput, 0,
     };

    /* Board pin, clock, debug console init */
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
    /* enable clock for GPIO*/
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);

    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("\r\n GPIO Driver example\r\n");
    PRINTF("\r\n The LED is taking turns to shine.\r\n");

    /* Init SW GPIO PORT. */
    GPIO_PortInit(GPIO, GPIO_PORT);

    /* Init output LED GPIO. */
    GPIO_PortInit(GPIO, GPIO_PORT);
    GPIO_PinInit(GPIO, GPIO_PORT, Left_PIN1, &led_config);
    GPIO_PinInit(GPIO, GPIO_PORT, Left_PIN2, &led_config);
    GPIO_PinInit(GPIO, GPIO_PORT, Right_PIN1, &led_config);
    GPIO_PinInit(GPIO, GPIO_PORT, Right_PIN2, &led_config);
    pin1= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN1);
    pin2= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN2);
    pin3= GPIO_PinRead(GPIO, GPIO_PORT, Right_PIN1);
    pin4= GPIO_PinRead(GPIO, GPIO_PORT, Right_PIN2);
    GPIO_PortInit(GPIO, BOARD_LED_PORT);
       GPIO_PinInit(GPIO, BOARD_LED_PORT, BOARD_LED_PIN, &led_config2);

       /* Set systick reload value to generate 1ms interrupt */
       if(SysTick_Config(SystemCoreClock / 1000U))
       {
           while(1)
           {
           }
       }




    if(pin1=0)
    {
    	  SysTick_DelayTicks(1000U);
    	           GPIO_PortToggle(GPIO, BOARD_LED_PORT, 1u << BOARD_LED_PIN);
    }

        if(pin2=0)
        {
        	  SysTick_DelayTicks(100U);
        	           GPIO_PortToggle(GPIO, BOARD_LED_PORT, 1u << BOARD_LED_PIN);
        }

            if(pin3=0)
            {
            	  SysTick_DelayTicks(1000U);
            	           GPIO_PortToggle(GPIO, BOARD_LED_PORT, 1u << BOARD_LED_PIN);
            }

                if(pin4=0)
                {
                	  SysTick_DelayTicks(1000U);
                	           GPIO_PortToggle(GPIO, BOARD_LED_PORT, 1u << BOARD_LED_PIN);
                }
    //GPIO_PinWrite(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_PIN, 1);

    /* Port masking */
   // GPIO_PortMaskedSet(GPIO, APP_BOARD_TEST_LED_PORT, 0x0000FFFF);
   // GPIO_PortMaskedWrite(GPIO, APP_BOARD_TEST_LED_PORT, 0xFFFFFFFF);
    //port_state = GPIO_PortRead(GPIO, APP_SW_PORT);
    //PRINTF("\r\n Standard port read: %x\r\n", port_state);
    //port_state = GPIO_PortMaskedRead(GPIO, APP_SW_PORT);
    //PRINTF("\r\n Masked port read: %x\r\n", port_state);

    //while (1)
    //{
      //  port_state = GPIO_PortRead(GPIO, APP_SW_PORT);
       // if (!(port_state & (1 << APP_SW_PIN)))
       // {
          //  PRINTF("\r\n Port state: %x\r\n", port_state);
          //  GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1u << APP_BOARD_TEST_LED_PIN);
       // }
       // delay();
    //}
}

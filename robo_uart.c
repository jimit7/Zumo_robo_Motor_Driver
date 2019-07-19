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
#include "fsl_usart_dma.h"
#include "fsl_dma.h"
#include "fsl_sctimer.h"
#include "pin_mux.h"
#include <stdbool.h>
//#include <iostream>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_USART USART2
#define DEMO_USART_CLK_SRC kCLOCK_Flexcomm2
#define DEMO_USART_CLK_FREQ CLOCK_GetFreq(kCLOCK_Flexcomm2)
#define USART_RX_DMA_CHANNEL 0
#define USART_TX_DMA_CHANNEL 1
#define EXAMPLE_UART_DMA_BASEADDR DMA0
#define ECHO_BUFFER_LENGTH 1




#define SCTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
#define DEMO_FIRST_SCTIMER_OUT kSCTIMER_Out_2
#define DEMO_SECOND_SCTIMER_OUT kSCTIMER_Out_4
#define DEMO_THIRD_SCTIMER_OUT	kSCTIMER_Out_5
#define DEMO_FOURTH_SCTIMER_OUT	kSCTIMER_Out_7
#define GPIO_PORT 0U
#define Left_PIN1 19U
#define Left_PIN2 18U
#define Right_PIN1 20U
#define Right_PIN2 21U

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/* UART user callback */
void UART_UserCallback(USART_Type *base, usart_dma_handle_t *handle, status_t status, void *userData);

/*******************************************************************************
 * Variables
 ******************************************************************************/

usart_dma_handle_t g_uartDmaHandle;
dma_handle_t g_uartTxDmaHandle;
dma_handle_t g_uartRxDmaHandle;
uint8_t g_tipString[]                  = "USART DMA example\r\nSend back received data\r\nEcho every 8 characters\r\n";
uint8_t g_txBuffer[ECHO_BUFFER_LENGTH] = {0};
uint8_t g_rxBuffer[ECHO_BUFFER_LENGTH] = {0};
volatile bool rxBufferEmpty            = true;
volatile bool txBufferFull             = false;
volatile bool txOnGoing                = false;
volatile bool rxOnGoing                = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
/* UART user callback */
void USART_UserCallback(USART_Type *base, usart_dma_handle_t *handle, status_t status, void *userData)
{
    userData = userData;

    if (kStatus_USART_TxIdle == status)
    {
        txBufferFull = false;
        txOnGoing    = false;
    }

    if (kStatus_USART_RxIdle == status)
    {
        rxBufferEmpty = false;
        rxOnGoing     = false;
    }
}





uart_init()
{
	usart_config_t config;
	    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
	   CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);

	    /* reset FLEXCOMM for USART */
	    RESET_PeripheralReset(kFC0_RST_SHIFT_RSTn);

	    BOARD_InitPins();
	    BOARD_BootClockFROHF48M();
	    BOARD_InitDebugConsole();

	    /* Initialize the UART. */
	    /*
	     * config.baudRate_Bps = 115200U;
	     * config.parityMode = kUART_ParityDisabled;
	     * config.stopBitCount = kUART_OneStopBit;
	     * config.txFifoWatermark = 0;
	     * config.rxFifoWatermark = 1;
	     * config.enableTx = false;
	     * config.enableRx = false;
	     */
	    USART_GetDefaultConfig(&config);
	    config.baudRate_Bps = BOARD_DEBUG_UART_BAUDRATE;
	    config.enableTx     = true;
	    config.enableRx     = true;

	    USART_Init(DEMO_USART, &config, DEMO_USART_CLK_FREQ);

	    /* Configure DMA. */
	    DMA_Init(EXAMPLE_UART_DMA_BASEADDR);
	    DMA_EnableChannel(EXAMPLE_UART_DMA_BASEADDR, USART_TX_DMA_CHANNEL);
	    DMA_EnableChannel(EXAMPLE_UART_DMA_BASEADDR, USART_RX_DMA_CHANNEL);

	    DMA_CreateHandle(&g_uartTxDmaHandle, EXAMPLE_UART_DMA_BASEADDR, USART_TX_DMA_CHANNEL);
	    DMA_CreateHandle(&g_uartRxDmaHandle, EXAMPLE_UART_DMA_BASEADDR, USART_RX_DMA_CHANNEL);

	    /* Create UART DMA handle. */
	    USART_TransferCreateHandleDMA(DEMO_USART, &g_uartDmaHandle, USART_UserCallback, NULL, &g_uartTxDmaHandle,
	                                  &g_uartRxDmaHandle);


}


/*!
 * @brief Main function
 */
int main(void)
{
uart_init();

	    usart_transfer_t xfer;
	    usart_transfer_t sendXfer;
	    usart_transfer_t receiveXfer;
	    /* Send g_tipString out. */
	   	    xfer.data     = g_tipString;
	   	    xfer.dataSize = sizeof(g_tipString) - 1;
	   	    txOnGoing     = true;
	   	   // USART_TransferSendDMA(DEMO_USART, &g_uartDmaHandle, &xfer);

	   	    /* Wait send finished */
	   	   // while (txOnGoing)
	   	  //  {
	   	   // }

	   	    /* Start to echo. */
	   	  //  sendXfer.data        = g_txBuffer;
	   	   // sendXfer.dataSize    = sizeof(g_txBuffer);
	   	    receiveXfer.data     = g_rxBuffer;
	   	    receiveXfer.dataSize = sizeof(g_rxBuffer);


	   	     sctimer_config_t sctimerInfo;
	   	     sctimer_pwm_signal_param_t pwmParam;
	   	     uint32_t event1,event2,event3,event4,speed=60;
	   	     uint32_t sctimerClock;
	   	    // uint8_t right=0,a,left=0,b,c=0;
	   	     /* Board pin, clock, debug console init */
	   	     /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
	   	     CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
	   	     CLOCK_EnableClock(kCLOCK_Gpio0);
	   	     CLOCK_EnableClock(kCLOCK_Gpio1);
	   	     BOARD_InitPins();
	   	     BOARD_BootClockFROHF48M();
	   	     BOARD_InitDebugConsole();

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
	   	     pwmParam.output = DEMO_FOURTH_SCTIMER_OUT;
	   	     pwmParam.level = kSCTIMER_HighTrue;
	   	     pwmParam.dutyCyclePercent = 1;
	   	     if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 2400U, sctimerClock, &event3) == kStatus_Fail)
	   	     {
	   	    	 return -1;
	   	     }

	   	     pwmParam.output = DEMO_THIRD_SCTIMER_OUT;
	   	     pwmParam.level = kSCTIMER_HighTrue;
	   	     pwmParam.dutyCyclePercent =2 ;
	   	     if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 2400U, sctimerClock, &event4) == kStatus_Fail)
	   	     {
	   	        return -1;
	   	     }





    while (1)
    {
        /* If RX is idle and g_rxBuffer is empty, start to read data to g_rxBuffer. */
        if ((!rxOnGoing) && rxBufferEmpty)
        {
            rxOnGoing = true;
            USART_TransferReceiveDMA(DEMO_USART, &g_uartDmaHandle, &receiveXfer);
            printf("d\n",g_rxBuffer);
        }


    }
}

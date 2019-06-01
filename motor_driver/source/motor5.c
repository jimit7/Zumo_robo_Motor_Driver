

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_sctimer.h"
#include "fsl_gpio.h"
#include "pin_mux.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SCTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
#define DEMO_FIRST_SCTIMER_OUT kSCTIMER_Out_4
#define DEMO_SECOND_SCTIMER_OUT kSCTIMER_Out_2
#define DEMO_THIRD_SCTIMER_OUT	kSCTIMER_Out_5
#define DEMO_FOURTH_SCTIMER_OUT	kSCTIMER_Out_7
#define GPIO_PORT 0U
#define Left_PIN1 18U
#define Left_PIN2 19U
#define Right_PIN1 20U
#define Right_PIN2 21U
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
 	gpio_pin_config_t led_config = {
	        kGPIO_DigitalInput,1
	    };
    sctimer_config_t sctimerInfo;
    sctimer_pwm_signal_param_t pwmParam;
    uint32_t stateNumber;
    uint32_t event1,event2,eventin;
    uint32_t sctimerClock;

    /* Board pin, clock, debug console init */
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);
    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();
    GPIO_PortInit(GPIO, GPIO_PORT);
    GPIO_PinInit(GPIO, GPIO_PORT, Left_PIN1, &led_config);

    sctimerClock = SCTIMER_CLK_FREQ;


    SCTIMER_GetDefaultConfig(&sctimerInfo);

    /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);

    stateNumber = SCTIMER_GetCurrentState(SCT0);
    pwmParam.output = DEMO_FIRST_SCTIMER_OUT;
    pwmParam.level = kSCTIMER_HighTrue;
    pwmParam.dutyCyclePercent = 50;
       if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 24000U, sctimerClock, &event1) == kStatus_Fail)
       {
           return -1;
       }

       PRINTF("\r\n pin 1state: %x\r\n", stateNumber);
    if (SCTIMER_CreateAndScheduleEvent(SCT0, kSCTIMER_InputRiseEvent, 0, kSCTIMER_Input_1, kSCTIMER_Counter_L,
                                          &eventin) == kStatus_Fail)
       {
           return -1;
       }
    SCTIMER_SetupNextStateAction(SCT0, stateNumber + 1, eventin);
    SCTIMER_IncreaseState(SCT0);

       pwmParam.output = DEMO_SECOND_SCTIMER_OUT;
       pwmParam.level = kSCTIMER_HighTrue;
       pwmParam.dutyCyclePercent = 50;
       if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm, 24000U, sctimerClock, &event2) ==
           kStatus_Fail)
       {
           return -1;
       }
       if (SCTIMER_CreateAndScheduleEvent(SCT0, kSCTIMER_InputRiseEvent,0, kSCTIMER_Input_1, kSCTIMER_Counter_L,
                                                 &eventin) == kStatus_Fail)
              {
                  return -1;
              }

       SCTIMER_SetupNextStateAction(SCT0, stateNumber, eventin);
       SCTIMER_IncreaseState(SCT0);

    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);


    while (1)
    {
    }}



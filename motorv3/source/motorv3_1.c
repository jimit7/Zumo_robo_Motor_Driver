

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
#define DEMO_FIRST_SCTIMER_OUT kSCTIMER_Out_2
#define DEMO_SECOND_SCTIMER_OUT kSCTIMER_Out_4
#define DEMO_THIRD_SCTIMER_OUT	kSCTIMER_Out_5
#define DEMO_FOURTH_SCTIMER_OUT	kSCTIMER_Out_7
#define GPIO_PORT 0U
#define Left_PIN1 18U
#define Left_PIN2 19U
#define Right_PIN1 25U
#define Right_PIN2 26U
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
	        kGPIO_DigitalInput,
	    };
    sctimer_config_t sctimerInfo;
    sctimer_pwm_signal_param_t pwmParam;
    uint32_t event,pin;
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

    /* Print a note to terminal */
    PRINTF("\r\nSCTimer example to output 2 center-aligned PWM signals\r\n");
    PRINTF("\r\nProbe the signal using an oscilloscope");

    SCTIMER_GetDefaultConfig(&sctimerInfo);

    /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);
    while(1){
    pin= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN1);
    if(pin == 0)
    {
    	  PRINTF("\r\n pin state: %x\r\n", pin);
    /* Configure first PWM with frequency 24kHZ from first output */
    pwmParam.output = DEMO_FIRST_SCTIMER_OUT;
    pwmParam.level = kSCTIMER_HighTrue;
    pwmParam.dutyCyclePercent = 50;
    if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 2400U, sctimerClock, &event) == kStatus_Fail)
    {
        return -1;
    }
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);
    }

 if((pin==1)){
    /* Configure second PWM with different duty cycle but same frequency as before */
    pwmParam.output = DEMO_SECOND_SCTIMER_OUT;
    pwmParam.level = kSCTIMER_HighTrue;
    pwmParam.dutyCyclePercent = 50;
    PRINTF("forward");
    if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 2400U, sctimerClock, &event) == kStatus_Fail)
    {
        return -1;
    }
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);
    PRINTF("forward+\n");
    }


    /* Start the timer */
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);

    while (1)
    {
    }}
}


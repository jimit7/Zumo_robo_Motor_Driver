
#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_sctimer.h"

#include "pin_mux.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define SCTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
#define DEMO_FIRST_SCTIMER_OUT kSCTIMER_Out_4
#define DEMO_SECOND_SCTIMER_OUT kSCTIMER_Out_2
#define DEMO_THIRD_SCTIMER_OUT	kSCTIMER_Out_7
#define DEMO_FOURTH_SCTIMER_OUT	kSCTIMER_Out_5
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
    sctimer_config_t sctimerInfo;
    sctimer_pwm_signal_param_t pwmParam;
    gpio_pin_config_t gpio_config = {
           kGPIO_DigitalInput,
       };

    uint32_t event;
    uint32_t pin1,pin2,pin3;
    uint32_t sctimerClock;
    uint8_t speed;
    uint8_t count = 0;
    /* Board pin, clock, debug console init */
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

        /* enable clock for GPIO*/
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);
    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();
    GPIO_PortInit(GPIO, GPIO_PORT);
    GPIO_PinInit(GPIO, GPIO_PORT, Left_PIN1, &gpio_config);
    GPIO_PinInit(GPIO, GPIO_PORT, Left_PIN2, &gpio_config);
    GPIO_PinInit(GPIO, GPIO_PORT, Right_PIN1,&gpio_config);
    GPIO_PinInit(GPIO, GPIO_PORT, Right_PIN2,&gpio_config);
    sctimerClock = SCTIMER_CLK_FREQ;
    while(1){
    pin1= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN1);

    if(pin1 == 0) 			{
    	count+=1;
    	if(count==1)
    	{
    		speed = 25;
    	}
    	else if(count==2)
    	{
    	   speed = 50;
    	 }
    	else if(count==3)
    	{
    	    		speed = 75;
    	 }
    	else if(count==4)
    	{
    	    		speed = 98;
    	}
    	else
    	{
    		count=0;
    		speed =5;
    	}
    }


    /* Print a note to terminal */

    SCTIMER_GetDefaultConfig(&sctimerInfo);

    /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);

    /* Configure first PWM with frequency 24kHZ from first output */
    pwmParam.output = DEMO_FIRST_SCTIMER_OUT;
    pwmParam.level = kSCTIMER_HighTrue;
    pwmParam.dutyCyclePercent = speed;
    pin2= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN2);
   // if((pin2 == 0))
   //{
    if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 20000U, sctimerClock, &event) == kStatus_Fail)
    {
        return -1;
    }
    }//
    /* Configure second PWM with different duty cycle but same frequency as before */
// else {
    pwmParam.output = DEMO_SECOND_SCTIMER_OUT;
    pwmParam.level = kSCTIMER_LowTrue;
    pwmParam.dutyCyclePercent = speed;
    if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 20000U, sctimerClock, &event) == kStatus_Fail)
    {
        return -1;
    }
    //}






    /* Start the timer */
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);

  //  }//
//}//
    }

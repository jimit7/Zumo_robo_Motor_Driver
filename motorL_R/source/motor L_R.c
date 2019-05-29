
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
   //uint8_t stop =1;
    uint32_t event1,event2;
    uint32_t pin1,pin2,pin3;
    uint32_t sctimerClock;
    uint8_t speed;
    uint8_t count = 0 ,right=0;
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
    while(1)
 {
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
    	}}
    	pin2= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN2);


    /* Print a note to terminal */

    SCTIMER_GetDefaultConfig(&sctimerInfo);

    /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);

    /* Configure first PWM with frequency 24kHZ from first output */
    pwmParam.output = DEMO_FIRST_SCTIMER_OUT;
    pwmParam.level = kSCTIMER_HighTrue;
    pwmParam.dutyCyclePercent =speed;
    pin2= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN2);

    if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 20000U, sctimerClock, &event1) == kStatus_Fail)
    {
        return -1;
    }
    pwmParam.output = DEMO_SECOND_SCTIMER_OUT;
    pwmParam.level = kSCTIMER_HighTrue;
    pwmParam.dutyCyclePercent = speed;
    if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_EdgeAlignedPwm , 20000U, sctimerClock, &event2) == kStatus_Fail)
    {
           return -1;
    }
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);


if(pin2==0)
{
right+=1;
    	if((right==2))
    /* Configure second PWM with different duty cycle but same frequency as before */
    {
    	printf("hwweee");
    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT, speed, event2);
    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT, 1, event1);
    }



else if((right==3))
        /* Configure second PWM with different duty cycle but same frequency as before */
        {
        	printf("hjj");
        SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT, 1, event2);
        SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT,speed, event1);
        }
else
{
	right=0;
}
     }
}

 }
/* Start the timer */
   // SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);

  //  }//
//}//




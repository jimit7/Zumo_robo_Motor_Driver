

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
#define Right_PIN1 21U
#define Right_PIN2 20U
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
    sctimer_pwm_signal_param_t pwmParam1 ,pwmParam2;
    uint32_t event1,event2,pin1 ,	speed=70;
    uint32_t sctimerClock;
uint8_t right,forward;
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

   pin1= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN1);



    pwmParam1.output = DEMO_FIRST_SCTIMER_OUT;
    pwmParam1.level = kSCTIMER_HighTrue;
    pwmParam1.dutyCyclePercent = 10;

       /* Schedule events in current state; State 0 */
       /* Schedule events for generating a 24KHz PWM with 10% duty cycle from first Out in the current state */
       if (SCTIMER_SetupPwm(SCT0, &pwmParam1, kSCTIMER_EdgeAlignedPwm, 24000U, sctimerClock, &event1) ==
           kStatus_Fail)
       {
           return -1;
       }







    pwmParam2.output = DEMO_SECOND_SCTIMER_OUT;
    pwmParam2.level = kSCTIMER_HighTrue;
    pwmParam2.dutyCyclePercent = 10;

          /* Schedule events in current state; State 0 */
          /* Schedule events for generating a 24KHz PWM with 10% duty cycle from first Out in the current state */
          if (SCTIMER_SetupPwm(SCT0, &pwmParam2, kSCTIMER_EdgeAlignedPwm, 24000U, sctimerClock, &event2) ==
              kStatus_Fail)
          {
              return -1;
          }



         while(1){
        	  if(pin1== 0)

{
        		right = right +1;
        		                     if (right == 1){

        							    forward = 1;
        		                     }

        		                     if (right == 2){

        							    forward = 2;
        		                     }


        		                     if (right == 3){

        							    forward = 3;
        		                     }

        						     if (right>=4)
        						     {
        							 right = 0;
        							 }
        		}





        	if (forward ==1 )
        	{
        		 SCTIMER_UpdatePwmDutycycle(SCT0, DEMO_FIRST_SCTIMER_OUT, 1, event1);
        		 SCTIMER_UpdatePwmDutycycle(SCT0, DEMO_SECOND_SCTIMER_OUT, 1, event2);
        		 printf("a\n");
        	}


        	if (forward ==2 )
        	{
        		 SCTIMER_UpdatePwmDutycycle(SCT0, DEMO_FIRST_SCTIMER_OUT, speed, event1);
        	     SCTIMER_UpdatePwmDutycycle(SCT0, DEMO_SECOND_SCTIMER_OUT, 1, event2);
        	     printf("b\n");
        	}

        	if (forward == 3 )

        	{
        	     SCTIMER_UpdatePwmDutycycle(SCT0, DEMO_FIRST_SCTIMER_OUT, 1, event1);
        	     SCTIMER_UpdatePwmDutycycle(SCT0, DEMO_SECOND_SCTIMER_OUT,speed, event2);
        	     printf("c\n");
        	}


         }
}


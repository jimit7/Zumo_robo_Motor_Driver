

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
#define Right_PIN1 19U
#define R_PIN1 20U
#define L_PIN2 21U
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
 	gpio_pin_config_t led1_config = {
 		        kGPIO_DigitalInput,
 		    };
 	gpio_pin_config_t led2_config = {
 		        kGPIO_DigitalInput,
 		    };
    sctimer_config_t sctimerInfo;
    sctimer_pwm_signal_param_t pwmParam;
    uint32_t event1,event2,event3,event4,pin1 ,	speed;
    uint32_t sctimerClock;
    uint8_t right,a,left,b,c;
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
    GPIO_PinInit(GPIO, GPIO_PORT, Right_PIN1, &led1_config);
    GPIO_PinInit(GPIO, GPIO_PORT, R_PIN1, &led2_config);
    sctimerClock = SCTIMER_CLK_FREQ;



    SCTIMER_GetDefaultConfig(&sctimerInfo);

    /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);

   // pin1= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN1);



    	  //PRINTF("\r\n pin state: %x\r\n", pin);
    /* Configure first PWM with frequency 24kHZ from first output */
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
       c=0,left=0,right=0;
    //SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);
while(1)
{
	//pin1= GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN1);//uint32_t speed=70;


	if(GPIO_PinRead(GPIO, GPIO_PORT, R_PIN1)==0)
	{
	//while(GPIO_PinRead(GPIO, GPIO_PORT, R_PIN1)==0)
	//{
		c=c+1;
		if(c==1)
		{
			speed=60;
    printf("a\n");
		}
		else if(c==2)
		{
			speed =70;
			 printf("b\n");
		}
		else if(c==3)
		{
			speed =80;
			 printf("c\n");

		}
		else if(c==4)
		{
			speed = 90;
			 printf("c\n");
		}
		else if(c==5)
		{
			speed = 100;
			 printf("d\n");

		}
		else
		{
			speed=60;
			 printf("e	\n");
			c=0;

		}
	//}




















	if(GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN1)==0)
	{

		while(GPIO_PinRead(GPIO, GPIO_PORT, Left_PIN1)==0)
	{
		right=right+1;
		if(right==1)
	    {
		a = 1;
		}
		else if(right==2){
			a=2;
		}
		else
		{
			right =0 ;
			a=0;
		}
	}
	}
	if(GPIO_PinRead(GPIO, GPIO_PORT, Right_PIN1)==0)
		{

			while(GPIO_PinRead(GPIO, GPIO_PORT, Right_PIN1)==0)
		{
			left=left+1;
			if(left==1)
		    {
			b = 1;
			}
			else if(left==2){
				b=2;
			}
			else
			{
				left =0 ;
				b=0;
			}
		}
		}

		 if(a==1)
		{
			printf("one");
						    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT, 1, event2);
						    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT, speed, event1);
		}
		 if(a==2)
				{
					printf("two");
								    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_SECOND_SCTIMER_OUT, speed, event2);
								    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FIRST_SCTIMER_OUT, 1, event1);
				}


		 if(b==1)
		{
			printf("third");
						    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_THIRD_SCTIMER_OUT, 1, event2);
						    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FOURTH_SCTIMER_OUT, speed, event1);
		}
		 if(b==2)
				{
					printf("fouth");
								    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_THIRD_SCTIMER_OUT, speed, event2);
								    SCTIMER_UpdatePwmDutycycle(SCT0,DEMO_FOURTH_SCTIMER_OUT, 1, event1);
				}

		}

	}
       return 0;
}

	 // SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);







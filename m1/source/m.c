

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
//#define SCTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_BusClk)
#define LEFT_MOTOR_SIGNAL1 kSCTIMER_Out_2                //D5 pin
#define LEFT_MOTOR_SIGNAL2 kSCTIMER_Out_7				//D7 pin
#define RIGHT_MOTOR_SIGNAL1 kSCTIMER_Out_4				//D10 pin
#define RIGHT_MOTOR_SIGNAL2 kSCTIMER_Out_5				//D9 pin
#define GPIO_PORT 0U
#define l_motor_speedup 18U
#define l_motor_speeddn 19U
#define r_motor_speedup 20U
#define r_motor_speeddn 21U
#define l_motor_dir 25U
#define r_motor_dir 26U

/*
 * @brief   Application entry point.
 */
int main(void) {
	uint32_t dutycycle_left=60,dutycycle_right=60,a=3,b=3;

		/* Define the init structure for the output LED pin*/
	    gpio_pin_config_t left_motor_speedup = {
	        kGPIO_DigitalInput, 1,
	    };
	    gpio_pin_config_t left_motor_speeddn = {
	    	        kGPIO_DigitalInput, 1,
	    	    };

	    gpio_pin_config_t right_motor_speedup = {
	   	        kGPIO_DigitalInput, 1,
	   	    };

	    gpio_pin_config_t right_motor_speeddn = {
	   	        kGPIO_DigitalInput, 1,
	   	    };

	    gpio_pin_config_t left_motor_dir = {
	   	        kGPIO_DigitalInput, 1,
	   	    };
	    gpio_pin_config_t right_motor_dir = {
	   	        kGPIO_DigitalInput, 1,
	   	    };

	 sctimer_config_t sctimerInfo;
		    sctimer_pwm_signal_param_t pwmParam_left1,pwmParam_left2,pwmParam_right1,pwmParam_right2;
		    uint32_t event_left1,event_left2,event_right1,event_right2;
		    uint32_t sctimerClock;










  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
   // BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    /* enable clock for GPIO*/
       CLOCK_EnableClock(kCLOCK_Gpio0);
       CLOCK_EnableClock(kCLOCK_Gpio1);


      // GPIO_PortInit(GPIO, BOARD_lefft_motor_speedup_PORT);
     GPIO_PinInit(GPIO, GPIO_PORT, l_motor_speedup, &left_motor_speedup);
     GPIO_PinInit(GPIO, GPIO_PORT, l_motor_speeddn, &left_motor_speeddn);

     GPIO_PinInit(GPIO, GPIO_PORT, r_motor_speedup, &right_motor_speedup);
     GPIO_PinInit(GPIO, GPIO_PORT, r_motor_speeddn, &right_motor_speeddn);

     GPIO_PinInit(GPIO, GPIO_PORT, l_motor_dir, &left_motor_dir);
     GPIO_PinInit(GPIO, GPIO_PORT, r_motor_dir, &right_motor_dir);


    sctimerClock = SCTIMER_CLK_FREQ;

    SCTIMER_GetDefaultConfig(&sctimerInfo);
    /* Configure first PWM with frequency 24kHZ from LEFT MOTOR FIRST SIGNAL output */
        pwmParam_left1.output = LEFT_MOTOR_SIGNAL1;
        pwmParam_left1.level = kSCTIMER_HighTrue;
        pwmParam_left1.dutyCyclePercent = 10;


           /* Configure first PWM with frequency 24kHZ from LEFT MOTOR SECOND SIGNAL output */
        pwmParam_left2.output = LEFT_MOTOR_SIGNAL2;
        pwmParam_left2.level = kSCTIMER_HighTrue;
        pwmParam_left2.dutyCyclePercent = 1;

              /* Configure first PWM with frequency 24kHZ from RIGHT MOTOR FIRST SIGNAL output */
        pwmParam_right1.output = RIGHT_MOTOR_SIGNAL1;
        pwmParam_right1.level = kSCTIMER_HighTrue;
        pwmParam_right1.dutyCyclePercent = 10;

        /* Configure first PWM with frequency 24kHZ from RIGHT MOTOR SECOND SIGNAL output */
        pwmParam_right2.output = RIGHT_MOTOR_SIGNAL2;
        pwmParam_right2.level = kSCTIMER_HighTrue;
        pwmParam_right2.dutyCyclePercent = 1;



           /* Initialize SCTimer module */
        SCTIMER_Init(SCT0, &sctimerInfo);

        SCTIMER_SetupPwm(SCT0, &pwmParam_left1, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event_left1);
        SCTIMER_SetupPwm(SCT0, &pwmParam_left2, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event_left2);

        SCTIMER_SetupPwm(SCT0, &pwmParam_right1, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event_right1);
        SCTIMER_SetupPwm(SCT0, &pwmParam_right2, kSCTIMER_CenterAlignedPwm, 24000U, sctimerClock, &event_right2);

        SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);





    /* Force the counter to be placed into memory. */

    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {

    	if(GPIO_PinRead(GPIO, GPIO_PORT, l_motor_speedup)==0)
    	{
    		while(GPIO_PinRead(GPIO, GPIO_PORT, l_motor_speedup)==0);
    		dutycycle_left=dutycycle_left+5;
    		if(dutycycle_left>100)
    			dutycycle_left=60;
    		a=0;

    	}

    	if(GPIO_PinRead(GPIO, GPIO_PORT, l_motor_speeddn)==0)
    	    	{
    		while(GPIO_PinRead(GPIO, GPIO_PORT, l_motor_speeddn)==0);
    		dutycycle_left=dutycycle_left-5;
    		if(dutycycle_left<60)
    			dutycycle_left=60;
    	    	}


    	if(GPIO_PinRead(GPIO, GPIO_PORT, r_motor_speedup)==0)
    	    	{
    		while(GPIO_PinRead(GPIO, GPIO_PORT, r_motor_speedup)==0);
    		dutycycle_right=dutycycle_right+5;
    		 if(dutycycle_right>=100)
    		    dutycycle_right=60;
    		 b=0;
    	    	}


    	if(GPIO_PinRead(GPIO, GPIO_PORT, r_motor_speeddn)==0)
    	    	{
    		while(GPIO_PinRead(GPIO, GPIO_PORT, r_motor_speeddn)==0);
    		dutycycle_right=dutycycle_right-5;

    		if(dutycycle_right<=60)
    			dutycycle_right=60;
    	    	}

    	if(GPIO_PinRead(GPIO, GPIO_PORT, l_motor_dir)==0)
    	{
    		while(GPIO_PinRead(GPIO, GPIO_PORT, l_motor_dir)==0);
    		a=a+1;
    		if (a>2)
    		{
    			a=0;

    		}

    	}

    	if(GPIO_PinRead(GPIO, GPIO_PORT, r_motor_dir)==0)
    	    	{
    		while(GPIO_PinRead(GPIO, GPIO_PORT, r_motor_dir)==0);
    		b=b+1;
    		  if (b>2)
    		   {
    		   	b=0;

    		    }}
    if(a==0){
    	SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL1,dutycycle_left,event_left1);
    	SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL2,1,event_left2);
    }
    if(a==1)
    {
    	SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL1,1,event_left1);
    	SCTIMER_UpdatePwmDutycycle(SCT0,LEFT_MOTOR_SIGNAL2,dutycycle_left,event_left2);

    }

    if(b==0){
    	SCTIMER_UpdatePwmDutycycle(SCT0,RIGHT_MOTOR_SIGNAL1,dutycycle_right,event_right1);
    	SCTIMER_UpdatePwmDutycycle(SCT0,RIGHT_MOTOR_SIGNAL2,1,event_right2);
    }
    if(b==1){
        	SCTIMER_UpdatePwmDutycycle(SCT0,RIGHT_MOTOR_SIGNAL1,1,event_right1);
        	SCTIMER_UpdatePwmDutycycle(SCT0,RIGHT_MOTOR_SIGNAL2,dutycycle_right,event_right2);
        }


}
return 0;
}

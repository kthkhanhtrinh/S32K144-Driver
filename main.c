#include "Gpio.h"
#include "Gpio_Register.h"
#include "Softimer.h"

#define BLUE_LED 0
#define RED_LED 15
#define GREEN_LED 16

void Gpio_switchColor(void);

volatile unsigned int TIMER_ID = 0;

int main(void)
{
	Gpio_init();
	int i;
	for(i = 0;i < SOFTTIMER_NUM;i++)
	{
		Softtimer_Init(&softTimer[i]);		
	}
	/* 5 second - blink blue 5s*/
	Softtimer_StartTimer(&softTimer[TIMER_ID_0], timeCounterMs, 
												TRUE, 50, ONE_SHOT_MODE, &Ggio_blinkLed_Blue);
	/* 1 second */
	Softtimer_StartTimer(&softTimer[TIMER_ID_1], timeCounterMs, 
												TRUE, 10, CONTINUOUS_MODE, &Ggio_blinkLed);
	/*0.5 second */
	Softtimer_StartTimer(&softTimer[TIMER_ID_2], timeCounterMs, 
												TRUE, 5, CONTINUOUS_MODE, &Ggio_blinkLed);
	/*Led off*/
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDOR, BLUE_LED, 1);
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDOR, RED_LED, 1);
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDOR, GREEN_LED, 1);
	
	while(1)
	{
		Softtimer_MainFunction(&softTimer[TIMER_ID_0]);
		if(softTimer[TIMER_ID_0].enableFlag == TRUE)
		{
			Gpio_ClearPinValue(&GPIOD_Reg->GPIO_PDOR, BLUE_LED);
		}
		if(tmp_program == PG1)
		{
			Softtimer_MainFunction(&softTimer[TIMER_ID_1]);
		}
		else if (tmp_program == PG2)
		{
			Softtimer_MainFunction(&softTimer[TIMER_ID_2]);
		}
		
	}
	
}

#include "Gpio.h"
#include "Gpio_Register.h"
volatile led_color tmp_color = GREEN;

void Gpio_init(void)
{
	/*========== LED INIT ==========*/
	/* Enable clk for port D */
	Gpio_SetPinValue(&PCC_Reg->PCC_PORTD, 30, 1);	
	
	/* Set pin as GPIO */
	Gpio_SetPinValue(&PORTD->PCR[RED_LED], 8, 1);
	Gpio_SetPinValue(&PORTD->PCR[BLUE_LED], 8, 1);
	Gpio_SetPinValue(&PORTD->PCR[GREEN_LED], 8, 1);

	/* Disable pull-up/pull-down */
	Gpio_ClearPinValue(&PORTD->PCR[RED_LED], 1);
	Gpio_ClearPinValue(&PORTD->PCR[BLUE_LED], 1);
	Gpio_ClearPinValue(&PORTD->PCR[GREEN_LED], 1);
	
	/* Set pin as output*/
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDDR, RED_LED, 1);
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDDR, BLUE_LED, 1);
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDDR, GREEN_LED, 1);

	
	/* ========== BUTTON INIT ========== */
	/*Enable clock for port C*/
	Gpio_SetPinValue(&PCC_Reg->PCC_PORTC, 30, 1);
	
	/*Set pin as GPIO*/
	Gpio_SetPinValue(&PORTC->PCR[BTN0], 8, 1);
	Gpio_SetPinValue(&PORTC->PCR[BTN1], 8, 1);
	
	/*Disable pull-up/pull-down*/
	Gpio_ClearPinValue(&PORTC->PCR[BTN0], 1);
	Gpio_ClearPinValue(&PORTC->PCR[BTN1], 1);
	
	/*Set interrupt*/
	Gpio_SetPinValue(&PORTC->PCR[BTN0], 16, 10);
	Gpio_SetPinValue(&PORTC->PCR[BTN1], 16, 10);
	
	/*set pin as input*/
	Gpio_ClearPinValue(&GPIOC_Reg->GPIO_PDDR, BTN0);
	Gpio_ClearPinValue(&GPIOC_Reg->GPIO_PDDR, BTN1);
	
	/*enable NVIC for Port C*/
	Gpio_SetPinValue(&NVIC_Reg->NVIC_ISER[1], 29, 1);
}

void Gpio_ledOff(void)
{
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDOR, BLUE_LED, 1);
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDOR, RED_LED, 1);
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDOR, GREEN_LED, 1);
}

void Ggio_blinkLed(void){
	/*turn off all led*/
	Gpio_ledOff();
	/*Turn on led following the input state*/
	
	if(tmp_color == GREEN)
	{
		Gpio_ClearPinValue(&GPIOD_Reg->GPIO_PDOR, GREEN_LED);
	}
	else if(tmp_color == BLUE)
	{
		Gpio_ClearPinValue(&GPIOD_Reg->GPIO_PDOR, BLUE_LED);
	}
	else if(tmp_color == RED)
	{
		Gpio_ClearPinValue(&GPIOD_Reg->GPIO_PDOR, RED_LED);
	}
	Gpio_switchColor();
}

void Gpio_switchColor(void){
	if(tmp_program == PG1){
		if(tmp_color == GREEN)
		{
			tmp_color = RED;
		}
		else if (tmp_color == RED)
		{
			tmp_color = BLUE;
		}
		else
		{
			tmp_color = GREEN;
		}	
	}
	else if(tmp_program == PG2)
	{
		if(tmp_color == GREEN)
		{
			tmp_color = RED;
		}
		else 
		{
			tmp_color = GREEN;
		}
	}
}

void Ggio_blinkLed_Blue(void)
{
	Gpio_SetPinValue(&GPIOD_Reg->GPIO_PDOR, BLUE_LED, 1);
	/*Gpio_ClearPinValue(&GPIOD_Reg->GPIO_PDDR,BLUE_LED);*/
}



unsigned int Gpio_GetPinValue(volatile unsigned int *port, unsigned int pin)
{
	return (*port >> pin) & 0x01;
}


void Gpio_SetPinValue(volatile unsigned int *port, unsigned int pin, const unsigned int value)
{
	(*port) |= (value << pin);
}

void Gpio_ClearPinValue(volatile unsigned int *port, unsigned int pin)
{
	(*port) &= ~(1 << pin);
}



#include "Gpio_Register.h"
#include "Gpio.h"

void PORTC_IRQHandler(void);

volatile button_num tmp_program = NON;

void PORTC_IRQHandler(void){
	/*Check interrupt btn0 = 12*/
	if( Gpio_GetPinValue(&PORTC->PCR[BTN0], 24) == 1)
	{
		/*write 1 to clear interrupt signal*/
		Gpio_SetPinValue(&PORTC->PCR[BTN0], 24, 1);
		tmp_program = PG1;
	}
	
	if( Gpio_GetPinValue(&PORTC->PCR[BTN1], 24) == 1)
	{
		Gpio_SetPinValue(&PORTC->PCR[BTN1], 24, 1);
		tmp_program = PG2;
	}
	
}


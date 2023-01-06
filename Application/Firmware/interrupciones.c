/*
 * interrupciones.c
 *
 *  Created on: 13/06/2014
 *      Author: TinchoPC
 */

#include "LPC17xx.h"
#include "My_Types.h"
#include "GPIO.h"
#include "SYSTICKTMR.h"
#include "Info_Exp_3.h"
#include "24LC256.h"

extern volatile uint32_t i;
uint8_t tick=0;

void SysTick_Handler(void)
{
	tick++;
	Exp3_Display ();
	Exp3_KeyboardSW();
	//GPIO_TogglePin(PORT_2,PIN_2);
	if(tick==100)
	{
		i++;
		tick=0;
	}
	SYSTICKTMR_GetValue();
	return;
}



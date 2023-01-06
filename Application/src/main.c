/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
*/


#include "LPC17xx.h"
#include "system_LPC17xx.h"
#include "My_Types.h"
#include "SYSTICKTMR.h"
#include "Info_Exp_3.h"
#include "24LC256.h"
#include "GPIO.h"
#include "Oscilador.h"
#include "I2C.h"


// TODO: insert other include files here

// TODO: insert other definitions and declarations here
volatile uint32_t i=0;
//void Init(void);
uint32_t func(uint8_t dato);

int main(void) {
	//uint8_t button=0;
	uint8_t valores[8]={0x20,0x30,0x40,0x50,0x60,0x70,0x80,0x90};			//32,48,64,80,96,112,128,144
	//uint8_t last_button=NO_KEY;
	GPIO_InitPinAsGPIO(PORT_2, PIN_1, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(PORT_2, PIN_2, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(PORT_2, PIN_3, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);

	GPIO_CLRpIN(PORT_2, PIN_1, ACTIVE_HIGH);
	GPIO_CLRpIN(PORT_2, PIN_2, ACTIVE_HIGH);
	GPIO_CLRpIN(PORT_2, PIN_3, ACTIVE_HIGH);
	uint16_t direccion=0;
	//uint8_t imprimir=VACIO;
	SystemInit();			// CLK_CPU = 100MHz
	//Init();
	Exp3_Init();
	EEPROM_Init();
	// TODO: insert code here
	SYSTICKTMR_Init(ENABLED, CLK_CPU);
	SYSTICKTMR_SetCounter((SYSTICK_TMR->STCALIB)/5);

	EEPROM_Write(valores,8,1);

	while(1) {
		switch(Exp3_Keyboard())
		{
		case SW1:
			EEPROM_Read(1,1,func);
			break;
		case SW2:
			EEPROM_Read(2,1,func);
			break;
		case SW3:
			EEPROM_Read(3,1,func);
			break;
		case SW4:
			EEPROM_Read(4,1,func);
			break;
		case SW5:
			EEPROM_Read(5,1,func);
			break;
		case SW6:
			EEPROM_Read(6,1,func);
			break;
		case SW7:
			EEPROM_Read(7,1,func);
			break;
		case SW8:
			EEPROM_Read(8,1,func);
			break;
		}
	}
	return 0 ;
}

uint32_t func(uint8_t dato)
{
	if (dato==0x80){

		GPIO_SETpIN(PORT_2, PIN_1, ACTIVE_HIGH);

	}
	Exp3_Print(dato);
	return(0);
}


//void Init(void)
//{
	//GPIO_CLRpIN(2,1,ACTIVE_HIGH);
//	return;
//}

/*
 * Info_Exp_1.c
 *
 *  Created on: 25/08/2014
 *      Author: TinchoPC
 */
/*****************************************************************************************************//**
*
* @file		Info_Exp_3.c
* @brief	Módulo para manejo de la Expansion N°3.
*
* @version	1.00
* @date		XX/XX/XXXX
* @author	Martin C. A. Yunis (MCAY)
*
*
*********************************************************************************************************
*** REVISION HISTORY
*
********************************************************************************************************/

/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "Info_Exp_1.h"

/********************************************************************************************************
*** PRIVATE DEFINES
********************************************************************************************************/


/********************************************************************************************************
*** PRIVATE MACROS
********************************************************************************************************/


/********************************************************************************************************
*** PRIVATE DATA TYPES
********************************************************************************************************/


/********************************************************************************************************
*** PRIVATE TABLES
********************************************************************************************************/


/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/


/********************************************************************************************************
*** PRIVATE GLOBAL VARIABLES
********************************************************************************************************/

static uint8_t	Tecla = NO_KEY;

/********************************************************************************************************
*** PRIVATE FUNCTION PROTOTYPES
********************************************************************************************************/



/********************************************************************************************************
*** CONFIGURATION ERRORS
********************************************************************************************************/


/*-----------------------------------------------------------------------------------------------------*/


/********************************************************************************************************
*** PUBLIC FUNCTIONS
********************************************************************************************************/

/***************************************************************************//**
 * @fn			Exp1_Init()
 * @brief		Inicializacion de linea de 8 leds, 3 botones y dos dip switch (uno de 8 llaves y otro de 3).
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp1_Init(void)
{

	GPIO_InitPinAsGPIO(LED1, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(LED2, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(LED3, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(LED4, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(LED5, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(LED6, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(LED7, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(LED8, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);


	GPIO_InitPinAsGPIO(DIP1_1_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIP1_2_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIP1_3_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIP1_4_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIP1_5_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIP1_6_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIP1_7_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIP1_8_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);


	GPIO_InitPinAsGPIO(DIP2_1_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIP2_2_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIP2_3_INIT, DIR_IN, RES_PULL_UP, NOT_OPEN_DRAIN);


	return;
}

/***************************************************************************//**
 * @fn			Exp1_On()
 * @brief		Enciende el led pasado como parametro.
 * @param[in] 	Led_Typedef		Led a encender
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp1_On(Led_Typedef led)
{
	switch(led)
	{
	case LED_1:
		GPIO_SETpIN(LED1,ACTIVE_HIGH);
		break;
	case LED_2:
		GPIO_SETpIN(LED2,ACTIVE_HIGH);
		break;
	case LED_3:
		GPIO_SETpIN(LED3,ACTIVE_HIGH);
		break;
	case LED_4:
		GPIO_SETpIN(LED4,ACTIVE_HIGH);
		break;
	case LED_5:
		GPIO_SETpIN(LED5,ACTIVE_HIGH);
		break;
	case LED_6:
		GPIO_SETpIN(LED6,ACTIVE_HIGH);
		break;
	case LED_7:
		GPIO_SETpIN(LED7,ACTIVE_HIGH);
		break;
	case LED_8:
		GPIO_SETpIN(LED8,ACTIVE_HIGH);
		break;
	}
	return;

}

/***************************************************************************//**
 * @fn			Exp1_Off()
 * @brief		Apaga el led pasado como parametro.
 * @param[in] 	Led_Typedef		Led a encender
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp1_Off(Led_Typedef led)
{
	switch(led)
	{
	case LED_1:
		GPIO_CLRpIN(LED1,ACTIVE_HIGH);
		break;
	case LED_2:
		GPIO_CLRpIN(LED2,ACTIVE_HIGH);
		break;
	case LED_3:
		GPIO_CLRpIN(LED3,ACTIVE_HIGH);
		break;
	case LED_4:
		GPIO_CLRpIN(LED4,ACTIVE_HIGH);
		break;
	case LED_5:
		GPIO_CLRpIN(LED5,ACTIVE_HIGH);
		break;
	case LED_6:
		GPIO_CLRpIN(LED6,ACTIVE_HIGH);
		break;
	case LED_7:
		GPIO_CLRpIN(LED7,ACTIVE_HIGH);
		break;
	case LED_8:
		GPIO_CLRpIN(LED8,ACTIVE_HIGH);
		break;
	}
	return;

}

/***************************************************************************//**
 * @fn			Exp1_KeyboardHW()
 * @brief		Driver de teclado que incluye 3 teclas y dos dip switch.
 * @param[in] 	void
 *
 *
 * @return 		uint8_t
 ******************************************************************************/

uint8_t Exp1_KeyboardHW(void)
{
	if(GPIO_GETpINsTATE(DIP1_1)==ON) return(DIP_1_1);
	if(GPIO_GETpINsTATE(DIP1_2)==ON) return(DIP_1_2);
	if(GPIO_GETpINsTATE(DIP1_3)==ON) return(DIP_1_3);
	if(GPIO_GETpINsTATE(DIP1_4)==ON) return(DIP_1_4);
	if(GPIO_GETpINsTATE(DIP1_5)==ON) return(DIP_1_5);
	if(GPIO_GETpINsTATE(DIP1_6)==ON) return(DIP_1_6);
	if(GPIO_GETpINsTATE(DIP1_7)==ON) return(DIP_1_7);
	if(GPIO_GETpINsTATE(DIP1_8)==ON) return(DIP_1_8);

	if(GPIO_GETpINsTATE(DIP2_1)==ON) return(DIP_2_1);
	if(GPIO_GETpINsTATE(DIP2_2)==ON) return(DIP_2_2);
	if(GPIO_GETpINsTATE(DIP2_3)==ON) return(DIP_2_3);

	return(NO_KEY);
}

/***************************************************************************//**
 * @fn			Exp1_KeyboardHW()
 * @brief		Driver de teclado que incluye 3 teclas y dos dip switch.
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp1_KeyboardSW(void)
{
	static uint8_t codigo_anterior = NO_KEY;
	static uint8_t estados_estables = 0;

	uint8_t codigo_actual;

	codigo_actual = Exp1_KeyboardHW();

	if (codigo_actual == NO_KEY)
	{
		// -- No se pulso tecla o rebote --
		codigo_anterior = NO_KEY;
		estados_estables = 0;
		return;
	}

	if (estados_estables == 0)
	{
		// -- Primera vez que lee esa tecla --
		codigo_anterior = codigo_actual;
		estados_estables = 1;
		return;
	}
	if (estados_estables == CANTIDAD_DE_REBOTES)
	{
		// -- Acepta la tecla --
		estados_estables = CANTIDAD_DE_REBOTES + 1;
		Tecla = codigo_anterior;
		return;
	}
	if (estados_estables > CANTIDAD_DE_REBOTES)
	{
		// -- La tecla fue aceptada pero sigue presionada --
		return;

	}
	if (codigo_actual == codigo_anterior)
	{
		estados_estables ++;
	}
	else
	{
		estados_estables = 0;
	}
	return;

}

/***************************************************************************//**
 * @fn			Exp1_Keyboard()
 * @brief		Retorna la Tecla que fue pulsada por ultima vez.
 * @param[in] 	void
 *
 *
 * @return 		Tecla
 ******************************************************************************/

uint8_t	Exp1_Keyboard(void)
{
	uint8_t tecla;
	tecla = Tecla;
	Tecla = NO_KEY;
	return(tecla);
}

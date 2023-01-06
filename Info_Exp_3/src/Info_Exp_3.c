/*
 * Info_Exp_3.c
 *
 *  Created on: 21/08/2014
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

#include "Info_Exp_3.h"

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

static uint8_t digitos[CANTIDAD_DIGITOS];

static uint8_t Tecla = NO_KEY;

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
 * @fn			Exp3_Init()
 * @brief		Inicializacion de Display 7seg de 6 digitos y Teclado Matricial de 2x4.
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp3_Init(void)
{
	GPIO_InitPinAsGPIO(BCD_A, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(BCD_B, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(BCD_C, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(BCD_D, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(BCD_DP, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);

	GPIO_InitPinAsGPIO(RESET, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(CLOCK, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);

	GPIO_InitPinAsGPIO(FILA_0, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(FILA_1, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(FILA_2, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(FILA_3, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(COLUMNA_0, DIR_IN, RES_PULL_DOWN, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(COLUMNA_1, DIR_IN, RES_PULL_DOWN, NOT_OPEN_DRAIN);

	return;
}

/***************************************************************************//**
 * @fn			Exp3_Print()
 * @brief		Driver de impresion en Display 7seg de 6 digitos.
 * @param[in] 	uint32_t	number:
 * 									Numero a imprimir en el display.
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp3_Print(uint32_t number)
{
	uint8_t k=0;
	if(number>999999)
	{
		return;
	}

	for(k=0;k<CANTIDAD_DIGITOS;k++)
	{
		digitos[k]=(number%10);
		number/=10;
	}
	return;
}

/***************************************************************************//**
 * @fn			Exp3_Display()
 * @brief		Actualiza los valores representados en los 7Seg.
 * @param[in] 	void
 *
 * @return 		void
 ******************************************************************************/

void Exp3_Display (void)
{
	static int8_t j=CANTIDAD_DIGITOS-1;
	static uint8_t flag=0;

	if(flag==0)
	{
		GPIO_SETpIN(RESET,ACTIVE_HIGH);
		flag=1;
	}else{
		GPIO_SETpIN(CLOCK,ACTIVE_HIGH);
	}

	GPIO_CLRpIN(RESET,ACTIVE_HIGH);

	GPIO_CLRpIN(BCD_A,ACTIVE_HIGH);
	GPIO_CLRpIN(BCD_B,ACTIVE_HIGH);
	GPIO_CLRpIN(BCD_C,ACTIVE_HIGH);
	GPIO_CLRpIN(BCD_D,ACTIVE_HIGH);


	if((digitos[j]&(0x01<<BIT0))!=0)
	{
		GPIO_SETpIN(BCD_A,ACTIVE_HIGH);
	}
	if((digitos[j]&(0x01<<BIT1))!=0)
	{
		GPIO_SETpIN(BCD_B,ACTIVE_HIGH);
	}
	if((digitos[j]&(0x01<<BIT2))!=0)
	{
		GPIO_SETpIN(BCD_C,ACTIVE_HIGH);
	}
	if((digitos[j]&(0x01<<BIT3))!=0)
	{
		GPIO_SETpIN(BCD_D,ACTIVE_HIGH);
	}
	j--;
	if(j<0)
	{
		j=CANTIDAD_DIGITOS-1;

		flag=0;

	}
	GPIO_CLRpIN(CLOCK,ACTIVE_HIGH);
	return;
}


/***************************************************************************//**
 * @fn			Exp3_Clear()
 * @brief		Apaga el Display 7seg de 6 digitos.
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp3_Clear(void)
{
	uint8_t i=0;
	for(i=0;i<CANTIDAD_DIGITOS;i++)
	{
		digitos[i]=0x0a;
	}

	return;
}

/***************************************************************************//**
 * @fn			Exp3_KeyboardHW()
 * @brief		Driver del teclado matricial de 4 filas y dos columnas.
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/

uint8_t Exp3_KeyboardHW(void)
{
	GPIO_SETpIN(FILA_0,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_1,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_2,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_3,ACTIVE_HIGH);

	GPIO_SETpIN(FILA_0,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_1,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_2,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_3,ACTIVE_HIGH);

	if(GPIO_GETpINsTATE(COLUMNA_0,ACTIVE_HIGH)==ON)		return (SW4);
	if(GPIO_GETpINsTATE(COLUMNA_1,ACTIVE_HIGH)==ON)		return (SW5);

	GPIO_CLRpIN(FILA_0,ACTIVE_HIGH);
	GPIO_SETpIN(FILA_1,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_2,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_3,ACTIVE_HIGH);

	GPIO_CLRpIN(FILA_0,ACTIVE_HIGH);
	GPIO_SETpIN(FILA_1,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_2,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_3,ACTIVE_HIGH);

	if(GPIO_GETpINsTATE(COLUMNA_0,ACTIVE_HIGH)==ON)		return (SW1);
	if(GPIO_GETpINsTATE(COLUMNA_1,ACTIVE_HIGH)==ON)		return (SW8);

	GPIO_CLRpIN(FILA_0,ACTIVE_HIGH);
	GPIO_SETpIN(FILA_1,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_2,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_3,ACTIVE_HIGH);

	GPIO_CLRpIN(FILA_0,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_1,ACTIVE_HIGH);
	GPIO_SETpIN(FILA_2,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_3,ACTIVE_HIGH);

	if(GPIO_GETpINsTATE(COLUMNA_0,ACTIVE_HIGH)==ON)		return (SW3);
	if(GPIO_GETpINsTATE(COLUMNA_1,ACTIVE_HIGH)==ON)		return (SW6);

	GPIO_CLRpIN(FILA_0,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_1,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_2,ACTIVE_HIGH);
	GPIO_SETpIN(FILA_3,ACTIVE_HIGH);

	GPIO_CLRpIN(FILA_0,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_1,ACTIVE_HIGH);
	GPIO_CLRpIN(FILA_2,ACTIVE_HIGH);
	GPIO_SETpIN(FILA_3,ACTIVE_HIGH);

	if(GPIO_GETpINsTATE(COLUMNA_0,ACTIVE_HIGH)==ON)		return (SW2);
	if(GPIO_GETpINsTATE(COLUMNA_1,ACTIVE_HIGH)==ON)		return (SW7);

	return(NO_KEY);
}

/***************************************************************************//**
 * @fn			Exp3_KeyboardSW()
 * @brief		Software antirebote del teclado matricial.
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp3_KeyboardSW(void)
{
	static uint8_t codigo_anterior = NO_KEY;
	static uint8_t estados_estables = 0;

	uint8_t codigo_actual;

	codigo_actual = Exp3_KeyboardHW();

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
 * @fn			Exp3_Keyboard()
 * @brief		Retorna la Tecla que fue pulsada por ultima vez.
 * @param[in] 	void
 *
 *
 * @return 		Tecla
 ******************************************************************************/

uint8_t	Exp3_Keyboard(void)
{
	uint8_t tecla;
	tecla = Tecla;
	Tecla = NO_KEY;
	return(tecla);
}


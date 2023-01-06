/*
 * EINT.c
 *
 *  Created on: 06/06/2014
 *      Author: TinchoPC
 */


/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "EINT.h"

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
 * @fn			EINT_ENABLE()
 * @brief		Habilita la interrupcion Externa correspondiente al pin pasado como parametro y configura la salida con esa funcion
 * @param[in]	entrada		Número de Interrupcion Externa: Debe ser uno de los siguientes:
 *                          - EINT0
 *                          - EINT1
 *                          - EINT2
 *                          - EINT3
 *
 * @return 		void
 ******************************************************************************/
/*void EINT_Enable(EINTX entrada)
{
	GPIO_InitPinNotAsGPIO(EINT_PORT,(EINT0_PIN + entrada), EINT_FUNC, RES_NONE, NOT_OPEN_DRAIN);
	NVIC_Enable(EINT0_NVIC+entrada);
	return;
}
*/
/***************************************************************************//**
 * @fn			EINT_GETfLAG()
 * @brief		Devuelve el valor del flag correspondiente a la entrada externa pasada como parametro
 * @param[in]	entrada		Número de Interrupcion Externa: Debe ser uno de los siguientes:
 *                          - EINT0
 *                          - EINT1
 *                          - EINT2
 *                          - EINT3
 * @return 		BOOL
 ******************************************************************************/
BOOL EINT_GetFlag(EINTX entrada)
{
	if(GET_BIT(EXTINT,entrada)==0)
	{
		return(FALSE);
	}
	else
	{
		return(TRUE);
	}
}

/***************************************************************************//**
 * @fn			EINT_SET_MODE()
 * @brief		Configura el modo de la interrupcion externa correspondiente al pin pasado como parametro
 * @param[in]	entrada		Número de Interrupcion Externa: Debe ser uno de los siguientes:
 *                          - EINT0
 *                          - EINT1
 *                          - EINT2
 *                          - EINT3
 * @param[in]	modo		Modo de la Interrupcion Externa: Debe ser uno de los siguientes:
 *                          - LEVEL
 *                          - FLANK
 *
 * @return 		void
 ******************************************************************************/
void EINT_SetMode(EINTX entrada,EINT_MODE modo)
{
	if (modo==LEVEL)
	{
		EXTMODE &= ~(0x01 << entrada);
	}
	else
	{
		EXTMODE |= (0x01 << entrada);
	}
	return;
}

/***************************************************************************//**
 * @fn			EINT_SET_POLAR()
 * @brief		Configura la polaridad del modo de la interrupcion externa correspondiente al pin pasado como parametro
 * @param[in]	entrada		Número de Interrupcion Externa: Debe ser uno de los siguientes:
 *                          - EINT0
 *                          - EINT1
 *                          - EINT2
 *                          - EINT3
 * @param[in]	polaridad	Polaridad del modo de la Interrupcion Externa: Debe ser uno de los siguientes:
 *                          - POSITIVE
 *                          - NEGATIVE
 *
 * @return 		void
 ******************************************************************************/
void EINT_SetPolar(EINTX entrada,EINT_POLAR polaridad)
{
	if (polaridad==NEGATIVE)
	{
		EXTPOLAR &= ~(0x01 << entrada);
	}
	else
	{
		EXTPOLAR |= (0x01 << entrada);
	}
	return;
}

/***************************************************************************//**
 * @fn			EINT_CREATE()
 * @brief		Crea una Interrupcion Externa correspondiente al pin pasado como variable y setea el modo y la polaridad de acuerdo a los valores administrados
 * @param[in]	entrada		Número de Interrupcion Externa: Debe ser uno de los siguientes:
 *                          - EINT0
 *                          - EINT1
 *                          - EINT2
 *                          - EINT3
 * @param[in]	modo		Modo de la Interrupcion Externa: Debe ser uno de los siguientes:
 *                          - LEVEL
 *                          - FLANK
 * @param[in]	polaridad	Polaridad del modo de la Interrupcion Externa: Debe ser uno de los siguientes:
 *                          - POSITIVE
 *                          - NEGATIVE
 *
 * @return 		void
 ******************************************************************************/
void EINT_Create(EINTX entrada,EINT_MODE modo,EINT_POLAR polaridad)
{
	EINT_Enable(entrada);
	EINT_SetMode(entrada, modo);
	EINT_SetPolar(entrada, polaridad);

	return;
}

/********************************************************************************************************
*** PRIVATE FUNCTIONS
********************************************************************************************************/


/*-----------------------------------------------------------------------------------------------------*/

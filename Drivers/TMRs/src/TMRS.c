/*
 * TMRS.c
 *
 *  Created on: 07/06/2014
 *      Author: TinchoPC
 */


/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "TMRS.h"


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
 * @fn			TMR_On()
 * @brief		Enciende el Periferico Timer correspondiente al parametro pasado
 * @param[in]	timer		Número de Timer: Debe ser uno de los siguientes:
 *	                        	-TMR0
 *								-TMR1
 *								-TMR2
 *								-TMR3
 *
 * @return 		void
 ******************************************************************************/
void TMR_On(TMR_Typedef timer)
{
	switch(timer)
	{
	case TMR0:
		PCONP |= (0x01 << TMR0_ON);
		break;
	case TMR1:
		PCONP |= (0x01 << TMR1_ON);
		break;
	case TMR2:
		PCONP |= (0x01 << TMR2_ON);
		break;
	case TMR3:
		PCONP |= (0x01 << TMR3_ON);
		break;
	}
	return;
}

/***************************************************************************//**
 * @fn			TMR_Off()
 * @brief		Apaga el Periferico Timer correspondiente al parametro pasado
 * @param[in]	timer		Número de Timer: Debe ser uno de los siguientes:
 *	                        	-TMR0
 *								-TMR1
 *								-TMR2
 *								-TMR3
 *
 * @return 		void
 ******************************************************************************/
void TMR_Off(TMR_Typedef timer)
{
	switch(timer)
	{
	case TMR0:
		PCONP &= ~(0x01 << TMR0_ON);
		break;
	case TMR1:
		PCONP &= ~(0x01 << TMR1_ON);
		break;
	case TMR2:
		PCONP &= ~(0x01 << TMR2_ON);
		break;
	case TMR3:
		PCONP &= ~(0x01 << TMR3_ON);
		break;
	}
	return;
}

/***************************************************************************//**
 * @fn			TMR_Enable()
 * @brief		Habilita o deshabilita el contador del timer correspondiente al parametro pasado
 * @param[in]	timer		Número de Timer: Debe ser uno de los siguientes:
 *	                        	-TMR0
 *								-TMR1
 *								-TMR2
 *								-TMR3
 *@param[in]	value		Habilitacion / Deshabilitacion: Debe ser uno de los siguientes:
 *	                        	-TRUE
 *								-FALSE
 *
 * @return 		void
 ******************************************************************************/
void TMR_Enable(TMR_Typedef timer, BOOL value)
{
	volatile uint32_t *p = NULL;
	switch(timer)
	{
	case TMR0:
		p = &(LPC_TMR0->TCR);
		break;
	case TMR1:
		*p = LPC_TMR1->TCR;
		break;
	case TMR2:
		*p = LPC_TMR2->TCR;
		break;
	case TMR3:
		*p = LPC_TMR3->TCR;
		break;
	}
	if(value == TRUE)
	{
		*p |= (0x01);
	}
	else
	{
		*p &= ~(0x01);
	}
	return;
}

/***************************************************************************//**
 * @fn			TMR_Reset()
 * @brief		Resetea el contador del timer correspondiente al parametro pasado
 * @param[in]	timer		Número de Timer: Debe ser uno de los siguientes:
 *	                        	-TMR0
 *								-TMR1
 *								-TMR2
 *								-TMR3
 *
 * @return 		void
 ******************************************************************************/
void TMR_Reset(TMR_Typedef timer)
{
	switch(timer)
	{
	case TMR0:
		LPC_TMR0->TCR |= (0x01 << 1);
		break;
	case TMR1:
		LPC_TMR1->TCR |= (0x01 << 1);
		break;
	case TMR2:
		LPC_TMR2->TCR |= (0x01 << 1);
		break;
	case TMR3:
		LPC_TMR3->TCR |= (0x01 << 1);
		break;
	}
	return;
}

/***************************************************************************//**
 * @fn			TMR_GetFlag()
 * @brief		Retorna el valor del Flag correspondiente al parametro pasado
 * @param[in]	timer		Número de Timer: Debe ser uno de los siguientes:
 *	                        	-TMR0
 *								-TMR1
 *								-TMR2
 *								-TMR3
 * @param[in]	parametro		Tipo de Flag: Debe ser uno de los siguientes:
 *	                        	-MR0
 *								-MR1
 *								-MR2
 *								-MR3
 *								-CR0
 *								-CR1
 *
 * @return 		BOOL
 ******************************************************************************/
BOOL TMR_GetFlag(TMR_Typedef timer, TMR_Type_Typedef parametro)
{
	switch(timer)
	{
	case TMR0:
		return(GET_BIT(LPC_TMR0->IR,parametro));
		break;
	case TMR1:
		return(GET_BIT(LPC_TMR1->IR,parametro));
		break;
	case TMR2:
		return(GET_BIT(LPC_TMR2->IR,parametro));
		break;
	case TMR3:
		return(GET_BIT(LPC_TMR3->IR,parametro));
		break;
	default:
		break;
	}
	return (FALSE);
}

/***************************************************************************//**
 * @fn			TMR_Set()
 * @brief		Setea la Captura/Match y la configura dependiendo de los campos de la estructura administrada
 *  @param[in]	timer		Número de Timer: Debe ser uno de los siguientes:
 *	                        	-TMR0
 *								-TMR1
 *								-TMR2
 *								-TMR3
 * @param[in]	parametro		Estructura que tiene los siguentes campos:
 *	                        	-tipo --> Selecciona cual de los match/capture es
 *								-value --> en caso de ser Match este es el valor configurado
 *								-parametro0 --> Match: 		Habilita/Deshabilita la interrupcion
 *												Capture: 	Habilita/Deshabilita la deteccion de flanco ascendente para la captura
 *
 *								-parametro1 --> Match: 		Habilita/Deshabilita el reset al llegar al match correspondiente
 *												Capture:	Habilita/Deshabilita la deteccion de flanco descendente para la captura
 *
 *								-parametro2 --> Match: 		Habilita/Deshabilita el stop al llegar al match correspondiente
 *												Capture:	Habilita/Deshabilita la interrupcion
 *
 * @return 		void
 ******************************************************************************/
void TMR_Set(TMR_Typedef timer, TMR_CAPT_MATCH_Typedef *parametro)
{
	LPC_TMR_Typedef *puntero = NULL;

	switch (timer)
	{
	case TMR0:
		puntero = LPC_TMR0;
		break;
	case TMR1:
		puntero = LPC_TMR1;
		break;
	case TMR2:
		puntero = LPC_TMR2;
		break;
	case TMR3:
		puntero = LPC_TMR3;
		break;
	}
	if(parametro->tipo<CR0)
	{
		if(parametro->parametro0 == DISABLED)
		{
			puntero->MCR &= ~(0x01 << (parametro->tipo)*3);
		}else{
			puntero->MCR |= (0x01 << (parametro->tipo)*3);
		}
		if(parametro->parametro1 == DISABLED)
		{
			puntero->MCR &= ~(0x01 << ((parametro->tipo)*3+1));
		}else{
			puntero->MCR |= (0x01 << ((parametro->tipo)*3+1));
		}
		if(parametro->parametro2 == DISABLED)
		{
			puntero->MCR &= ~(0x01 << ((parametro->tipo)*3+2));
		}else{
			puntero->MCR |= (0x01 << ((parametro->tipo)*3+2));
		}
	}else{
		if(parametro->parametro0 == DISABLED)
		{
			puntero->CCR &= ~(0x01 << ((parametro->tipo)-4)*3);
		}else{
			puntero->CCR |= (0x01 << (parametro->tipo)*3);
		}
		if(parametro->parametro1 == DISABLED)
		{
			puntero->CCR &= ~(0x01 << (((parametro->tipo)-4)*3+1));
		}else{
			puntero->CCR |= (0x01 << (((parametro->tipo)-4)*3+1));
		}
		if(parametro->parametro2 == DISABLED)
		{
			puntero->CCR &= ~(0x01 << (((parametro->tipo)-4)*3+2));
		}else{
			puntero->CCR |= (0x01 << (((parametro->tipo)-4)*3+2));
		}
	}
	switch (parametro->tipo)
	{
	case MR0:
		puntero->MR0 =parametro->value;
		break;
	case MR1:
		puntero->MR1 =parametro->value;
		break;
	case MR2:
		puntero->MR2 =parametro->value;
		break;
	case MR3:
		puntero->MR3 =parametro->value;
		break;
	default:
		break;
	}
	return;
}

/***************************************************************************//**
 * @fn			TMR_ConfigClock()
 * @brief		Setea la base de tiempo del timer pasado como parametro
 * @param[in]	timer		Número de Timer: Debe ser uno de los siguientes:
 *	                        	-TMR0
 *								-TMR1
 *								-TMR2
 *								-TMR3
 * @param[in]	clock		Tipo de Clock: Debe ser uno de los siguientes:
 *	                        	-CLK_4
 *								-CLK_1
 *								-CLK_2
 *								-CLK_8
 *
 * @return 		BOOL
 ******************************************************************************/
void TMR_ConfigClock(TMR_Typedef timer, CLK_Typedef clock)
{
	switch(timer)
	{
	case TMR0:
		PCLKSEL0 &= ~((0x01|(0x01 << 1)) << TMR0_CLK);
		PCLKSEL0 |= (clock << TMR0_CLK);
		break;
	case TMR1:
		PCLKSEL0 &= ~((0x01|(0x01 << 1)) << TMR1_CLK);
		PCLKSEL0 |= (clock << TMR1_CLK);
		break;
	case TMR2:
		PCLKSEL1 &= ~((0x01|(0x01 << 1)) << TMR2_CLK);
		PCLKSEL1 |= (clock << TMR2_CLK);
		break;
	case TMR3:
		PCLKSEL1 &= ~((0x01|(0x01 << 1)) << TMR3_CLK);
		PCLKSEL1 |= (clock << TMR3_CLK);
		break;
	}
	return;
}

/***************************************************************************//**
 * @fn			TMR_ConfigCapture()
 * @brief		Configura la captura, que salida la activa y con que flanco
 * @param[in]	timer		Número de Timer: Debe ser uno de los siguientes:
 *	                        	-TMR0
 *								-TMR1
 *								-TMR2
 *								-TMR3
 * @param[in]	flanco		Tipo de Flanco: Debe ser uno de los siguientes:
 *	                        	-TMR_ASC
 *								-TMR_DESC
 *								-TMR_AMBOS
 * @param[in]	canal		Canal: Debe ser uno de los siguientes:
 *	                        	-TMR_CHANNEL0
 *								-TMR_CHANNEL1
 *
 * @return 		BOOL
 ******************************************************************************/
void TMR_ConfigCapture(TMR_Typedef timer, TMR_FLANK_Typedef flanco, TMR_CHANNEL_Typedef canal)
{
	volatile uint32_t *p = NULL;
	switch(timer)
	{
	case TMR0:
		p = &(LPC_TMR0->CTCR);
		break;
	case TMR1:
		p = &(LPC_TMR1->CTCR);
		break;
	case TMR2:
		p = &(LPC_TMR2->CTCR);
		break;
	case TMR3:
		p = &(LPC_TMR3->CTCR);
		break;
	}

	*p &= ~((0x01 << 0)|(0x01 << 1)|(0x01 << 2)|(0x01 << 3));
	*p |= (flanco);

	if(canal == TMR_CHANNEL1)
	{
		*p |= (0x01 << 3);
	}
	return;
}

/***************************************************************************//**
 * @fn			TMR_ConfigMatch()
 * @brief		Configura el estado proximo de la salida seleccionada al matchear
 * @param[in]	timer		Número de Timer: Debe ser uno de los siguientes:
 *	                        	-TMR0
 *								-TMR1
 *								-TMR2
 *								-TMR3
 * @param[in]	tipo		Tipo de Flag: Debe ser uno de los siguientes:
 *	                        	-MR0
 *								-MR1
 *								-MR2
 *								-MR3
 *								-CR0
 *								-CR1
 * @param[in] 	estado		Estado que devera tener la salida luego de matchear: Debe ser uno de los siguientes:
 * 								-NO_CHANGE
 *								-CLR_PINOUT
 *								-SET_PINOUT
 *								-TOGGLE_PINOUT
 *
 * @return 		void
 ******************************************************************************/
void TMR_ConfigMatch(TMR_Typedef timer, TMR_Type_Typedef tipo, MATCH_STATE_Typedef estado,TMR_CHANNEL_Typedef canal)
{
	if ((tipo == CR0) || (tipo == CR1))
	{
		return;
	}
	volatile uint32_t *p = NULL;
	switch(timer)
	{
	case TMR0:
		p = &(LPC_TMR0->EMR);
		break;
	case TMR1:
		p = &(LPC_TMR1->EMR);
		break;
	case TMR2:
		p = &(LPC_TMR2->EMR);
		break;
	case TMR3:
		p = &(LPC_TMR3->EMR);
		break;
	}

	if(canal == TMR_CHANNEL1)
	{
		*p &= ~(0x03 << (MATCH_OFFSET + (tipo*2)));
		*p |= (estado << (MATCH_OFFSET + (tipo*2)));
	}
	return;
}



/********************************************************************************************************
*** PRIVATE FUNCTIONS
********************************************************************************************************/


/*-----------------------------------------------------------------------------------------------------*/

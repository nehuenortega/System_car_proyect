/*
 * NVIC.c
 *
 *  Created on: 06/06/2014
 *      Author: TinchoPC
 */


/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "NVIC.h"


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
 * @fn			NVIC_Enable()
 * @brief		Habilita la interrupcion correspondiente al parametro pasado
 * @param[in]	parametro	Número de Interrupcion NVIC: Debe ser uno de los siguientes:
 *	                        	-NVIC_WDT
 *								-NVIC_TMR0
 *								-NVIC_TMR1
 *								-NVIC_TMR2
 *								-NVIC_TMR3
 *								-NVIC_UART0
 *								-NVIC_UART1
 *								-NVIC_UART2
 *								-NVIC_UART3
 *								-NVIC_PWM1
 *								-NVIC_I2C0
 *								-NVIC_I2C1
 *								-NVIC_I2C2
 *								-NVIC_SPI
 *								-NVIC_SSP0
 *								-NVIC_SSP1
 *								-NVIC_PLL0
 *								-NVIC_RTC
 *								-NVIC_EINT0
 *								-NVIC_EINT1
 *								-NVIC_EINT2
 *								-NVIC_EINT3
 *								-NVIC_ADC
 *								-NVIC_BOD
 *								-NVIC_USB
 *								-NVIC_CAN
 *								-NVIC_GPDMA
 *								-NVIC_I2S
 *								-NVIC_ETHERNET
 *								-NVIC_RITINT
 *								-NVIC_MC_PWM
 *								-NVIC_QEI
 *								-NVIC_PLL1
 *								-NVIC_USB_INT
 *								-NVIC_CAN_INT
 *
 * @return 		void
 ******************************************************************************/
void NVIC_Enable(NVIC_Typedef parametro)
{
	if (parametro < NVIC_PLL1)
	{
		ISER0 |= (0x01 << parametro);
	}
	else
	{
		ISER1 |= (0x01 << (parametro - NVIC_PLL1));
	}
	return;
}

 /***************************************************************************//**
  * @fn			NVIC_Disable()
  * @brief		Deshabilita la interrupcion correspondiente al parametro pasado
  * @param[in]	parametro	Número de Interrupcion NVIC: Debe ser uno de los siguientes:
  *	                        	-NVIC_WDT
  *								-NVIC_TMR0
  *								-NVIC_TMR1
  *								-NVIC_TMR2
  *								-NVIC_TMR3
  *								-NVIC_UART0
  *								-NVIC_UART1
  *								-NVIC_UART2
  *								-NVIC_UART3
  *								-NVIC_PWM1
  *								-NVIC_I2C0
  *								-NVIC_I2C1
  *								-NVIC_I2C2
  *								-NVIC_SPI
  *								-NVIC_SSP0
  *								-NVIC_SSP1
  *								-NVIC_PLL0
  *								-NVIC_RTC
  *								-NVIC_EINT0
  *								-NVIC_EINT1
  *								-NVIC_EINT2
  *								-NVIC_EINT3
  *								-NVIC_ADC
  *								-NVIC_BOD
  *								-NVIC_USB
  *								-NVIC_CAN
  *								-NVIC_GPDMA
  *								-NVIC_I2S
  *								-NVIC_ETHERNET
  *								-NVIC_RITINT
  *								-NVIC_MC_PWM
  *								-NVIC_QEI
  *								-NVIC_PLL1
  *								-NVIC_USB_INT
  *								-NVIC_CAN_INT
  *
  * @return 		void
  ******************************************************************************/
void NVIC_Disable(NVIC_Typedef parametro)
 {
 	if (parametro < NVIC_PLL1)
 	{
 		ICER0 &= ~(0x01 << parametro);
 	}
 	else
 	{
 		ICER1 &= ~(0x01 << (parametro - NVIC_PLL1));
 	}
 	return;
 }

 /***************************************************************************//**
   * @fn			NVIC_GetPend()
   * @brief		Retorna el flag de la interrupcion pendiente
   * @param[in]	parametro 		Número de Interrupcion NVIC: Debe ser uno de los siguientes:
   *	                        	-NVIC_WDT
   *								-NVIC_TMR0
   *								-NVIC_TMR1
   *								-NVIC_TMR2
   *								-NVIC_TMR3
   *								-NVIC_UART0
   *								-NVIC_UART1
   *								-NVIC_UART2
   *								-NVIC_UART3
   *								-NVIC_PWM1
   *								-NVIC_I2C0
   *								-NVIC_I2C1
   *								-NVIC_I2C2
   *								-NVIC_SPI
   *								-NVIC_SSP0
   *								-NVIC_SSP1
   *								-NVIC_PLL0
   *								-NVIC_RTC
   *								-NVIC_EINT0
   *								-NVIC_EINT1
   *								-NVIC_EINT2
   *								-NVIC_EINT3
   *								-NVIC_ADC
   *								-NVIC_BOD
   *								-NVIC_USB
   *								-NVIC_CAN
   *								-NVIC_GPDMA
   *								-NVIC_I2S
   *								-NVIC_ETHERNET
   *								-NVIC_RITINT
   *								-NVIC_MC_PWM
   *								-NVIC_QEI
   *								-NVIC_PLL1
   *								-NVIC_USB_INT
   *								-NVIC_CAN_INT
   *
   * @return 		BOOL
   ******************************************************************************/
BOOL NVIC_GetPend(NVIC_Typedef parametro)
{
	if (parametro < NVIC_PLL1)
	{
		if(GET_BIT(ISPR0,parametro) == FALSE)
		{
			return (FALSE);
		}
		else
		{
			return (TRUE);
		}
	}
	else
	{
		if(GET_BIT(ISPR1,(parametro - NVIC_PLL1)) == FALSE)
		{
			return (FALSE);
		}
		else
		{
			return (TRUE);
		}
	}
}

 /***************************************************************************//**
   * @fn			NVIC_Clr()
   * @brief		Limpia el flag de la interrupcion correspondiente al parametro pasado
   * @param[in]	parametro	Número de Interrupcion NVIC: Debe ser uno de los siguientes:
   *	                        	-NVIC_WDT
   *								-NVIC_TMR0
   *								-NVIC_TMR1
   *								-NVIC_TMR2
   *								-NVIC_TMR3
   *								-NVIC_UART0
   *								-NVIC_UART1
   *								-NVIC_UART2
   *								-NVIC_UART3
   *								-NVIC_PWM1
   *								-NVIC_I2C0
   *								-NVIC_I2C1
   *								-NVIC_I2C2
   *								-NVIC_SPI
   *								-NVIC_SSP0
   *								-NVIC_SSP1
   *								-NVIC_PLL0
   *								-NVIC_RTC
   *								-NVIC_EINT0
   *								-NVIC_EINT1
   *								-NVIC_EINT2
   *								-NVIC_EINT3
   *								-NVIC_ADC
   *								-NVIC_BOD
   *								-NVIC_USB
   *								-NVIC_CAN
   *								-NVIC_GPDMA
   *								-NVIC_I2S
   *								-NVIC_ETHERNET
   *								-NVIC_RITINT
   *								-NVIC_MC_PWM
   *								-NVIC_QEI
   *								-NVIC_PLL1
   *								-NVIC_USB_INT
   *								-NVIC_CAN_INT
   *
   * @return 		void
   ******************************************************************************/
void NVIC_Clr(NVIC_Typedef parametro)
  {
  	if (parametro < NVIC_PLL1)
  	{
  		ICPR0 |= (0x01 << parametro);
  	}
  	else
  	{
  		ICPR1 |= (0x01 << (parametro - NVIC_PLL1));
  	}
  	return;
  }

/***************************************************************************//**
   * @fn			NVIC_Priority()
   * @brief		Sete la prioridad de la interrupcion correspondiente al parametro pasado
   * @param[in]	parametro	Número de Interrupcion NVIC: Debe ser uno de los siguientes:
   *	                        	-NVIC_WDT
   *								-NVIC_TMR0
   *								-NVIC_TMR1
   *								-NVIC_TMR2
   *								-NVIC_TMR3
   *								-NVIC_UART0
   *								-NVIC_UART1
   *								-NVIC_UART2
   *								-NVIC_UART3
   *								-NVIC_PWM1
   *								-NVIC_I2C0
   *								-NVIC_I2C1
   *								-NVIC_I2C2
   *								-NVIC_SPI
   *								-NVIC_SSP0
   *								-NVIC_SSP1
   *								-NVIC_PLL0
   *								-NVIC_RTC
   *								-NVIC_EINT0
   *								-NVIC_EINT1
   *								-NVIC_EINT2
   *								-NVIC_EINT3
   *								-NVIC_ADC
   *								-NVIC_BOD
   *								-NVIC_USB
   *								-NVIC_CAN
   *								-NVIC_GPDMA
   *								-NVIC_I2S
   *								-NVIC_ETHERNET
   *								-NVIC_RITINT
   *								-NVIC_MC_PWM
   *								-NVIC_QEI
   *								-NVIC_PLL1
   *								-NVIC_USB_INT
   *								-NVIC_CAN_INT
   *
   * @param[in]	prioridad	  Prioridad de la Interrucion
   * 								NVIC_PRIRITY_0
   *								NVIC_PRIRITY_1
   *								NVIC_PRIRITY_2
   *								NVIC_PRIRITY_3
   *								NVIC_PRIRITY_4
   *								NVIC_PRIRITY_5
   *								NVIC_PRIRITY_6
   *								NVIC_PRIRITY_7
   *								NVIC_PRIRITY_8
   *								NVIC_PRIRITY_9
   *								NVIC_PRIRITY_10
   *								NVIC_PRIRITY_11
   *								NVIC_PRIRITY_12
   *								NVIC_PRIRITY_13
   *								NVIC_PRIRITY_14
   *								NVIC_PRIRITY_15
   *								NVIC_PRIRITY_16
   *								NVIC_PRIRITY_17
   *								NVIC_PRIRITY_18
   *								NVIC_PRIRITY_19
   *								NVIC_PRIRITY_20
   *								NVIC_PRIRITY_21
   *								NVIC_PRIRITY_22
   *								NVIC_PRIRITY_23
   *								NVIC_PRIRITY_24
   *								NVIC_PRIRITY_25
   *								NVIC_PRIRITY_26
   *								NVIC_PRIRITY_27
   *								NVIC_PRIRITY_28
   *								NVIC_PRIRITY_29
   *								NVIC_PRIRITY_30
   *								NVIC_PRIRITY_31
   *
   * @return 		void
   ******************************************************************************/
void NVIC_Priority(NVIC_Typedef parametro, NVIC_PRIORITY prioridad)
{
	uint8_t value=0;
	value=(int)(parametro/4);
	parametro-=value*4;
	*(&IPR0 + value) &= ~(0x1F << (8 * parametro + NVIC_OFFSET_PRIORITY));
	*(&IPR0 + value) |= (prioridad << (8 * parametro + NVIC_OFFSET_PRIORITY));
	return;
}

 /********************************************************************************************************
*** PRIVATE FUNCTIONS
********************************************************************************************************/


/*-----------------------------------------------------------------------------------------------------*/

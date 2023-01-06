/*****************************************************************************************************//**
*
* @file		GPIO.c
* @brief	Módulo para manejo de Entradas y Salidas de Propósito General (GPIO: General Purpose IO).
* 			Este módulo es un complemento al desarrollado por NXP como librería y que esta incluido en
* 			este proyecto (lpc17xx_gpio.c y lpc17xx_gpio.h)
* @version	1.00
* @date		XX/XX/XXXX
* @author	Daniel J. López Amado (DJLA)
*
*
*********************************************************************************************************
*** REVISION HISTORY
*
********************************************************************************************************/

/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "GPIO.h"

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
 * @fn			GPIO_InitPinAsGIPO()
 * @brief		Inicializa el Pin pasado como parámetro como entrada o salida
 *              y configura la resistencia asociada y el modo de salida
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	dir 		Dirección del Pin: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_DIRECTION
 * @param[in] 	resMode 	Modo de la Resistencia: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_RES_MODE
 * @param[in] 	odMode 		Modo de la Salida: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_OD_MODE
 * @return 		void
 ******************************************************************************/
void GPIO_InitPinAsGPIO(uint8_t portNum, uint8_t pinNum, PIN_DIRECTION dir, PIN_RES_MODE resMode, PIN_OD_MODE odMode)
{
	GPIO_SetPinFunc(portNum,pinNum,DEFAULT_FUNC);
	GPIO_SETpINdIR(portNum,pinNum,dir);
	GPIO_SetResistorMode(portNum,pinNum,resMode);
	GPIO_SetOpenDrainMode(portNum,pinNum,odMode);
}

/***************************************************************************//**
 * @fn			GPIO_InitPinNotAsGPIO()
 * @brief		Inicializa el Pin pasado como parámetro como entrada o salida
 *              y configura la resistencia asociada y el modo de salida
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	func 		Función del Pin: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_FUNCTION
 * @param[in] 	resMode 	Modo de la Resistencia: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_RES_MODE
 * @param[in] 	odMode 		Modo de la Salida: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_OD_MODE
 * @return 		void
 ******************************************************************************/
void GPIO_InitPinNotAsGPIO(uint8_t portNum, uint8_t pinNum, PIN_FUNCTION func, PIN_RES_MODE resMode, PIN_OD_MODE odMode)
{
	GPIO_SetPinFunc(portNum,pinNum,func);
	GPIO_SetResistorMode(portNum,pinNum,resMode);
	GPIO_SetOpenDrainMode(portNum,pinNum,odMode);
}

/***************************************************************************//**
 * @fn			GPIO_SetPinFunc()
 * @brief		Setea la Función del Pin pasado como parámetro
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	func 		Funcion: Debe ser uno de los tipos definidos en
 *                          la enumeración PIN_FUNCTION
 * @return 		void
 ******************************************************************************/
void GPIO_SetPinFunc(uint8_t portNum, uint8_t pinNum, PIN_FUNCTION func)
{
	uint32_t pinNum_t = pinNum;
	uint32_t pinSelReg_idx = 2 * portNum;
	uint32_t *pPinCon = (uint32_t *)&LPC_PINCON->PINSEL0;

	if (pinNum_t >= 16)
	{
		pinNum_t -= 16;
		pinSelReg_idx++;
	}
	*(uint32_t *)(pPinCon + pinSelReg_idx) &= ~(0x03UL << (pinNum_t * 2));
	*(uint32_t *)(pPinCon + pinSelReg_idx) |= ((uint32_t)func) << (pinNum_t * 2);
}

/***************************************************************************//**
 * @fn			GPIO_SetResistorMode()
 * @brief		Setea el Modo de la resistencia asociada al Pin
 *				Nota: Los pines P0[27] a P0[30] no pueden ser seteados ya que
 *				no tiene resistencia de pull-up o pull-donw.
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	resMode 	Modo de la Resistencia: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_RES_MODE
 * @return 		void
 ******************************************************************************/
void GPIO_SetResistorMode ( uint8_t portNum, uint8_t pinNum, PIN_RES_MODE resMode)
{
	uint32_t pinNum_t = pinNum;
	uint32_t pinModeReg_idx = 2 * portNum;
	uint32_t *pPinCon = (uint32_t *)&LPC_PINCON->PINMODE0;

	// Para los Pines P0[27] al P0[30] retorna sin setear nada.
	if(portNum == PORT_0 && (pinNum >= PIN_27 && pinNum <= PIN_30))
	{
		return;
	}
	if (pinNum_t >= 16)
	{
		pinNum_t -= 16;
		pinModeReg_idx++ ;
	}
	*(uint32_t *)(pPinCon + pinModeReg_idx) &= ~(0x03UL << (pinNum_t * 2));
	*(uint32_t *)(pPinCon + pinModeReg_idx) |= ((uint32_t)resMode) << (pinNum_t * 2);
}

/***************************************************************************//**
 * @fn			GPIO_SetOpenDrainMode()
 * @brief		Setea el Modo de la Salida asociada al  Pin
 *				Nota: Los pines P0[27] y P0[28] no pueden ser seteados ya que
 *				son siempre open-drain
  * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	odMode 	Modo de la Salida: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_OD_MODE
 * @return 		void
 ******************************************************************************/
void GPIO_SetOpenDrainMode( uint8_t portNum, uint8_t pinNum, PIN_OD_MODE odMode)
{
	uint32_t *pPinCon = (uint32_t *)&LPC_PINCON->PINMODE_OD0;

	// Para los Pines P0[27] y P0[28] retorna sin setear nada.
	if(portNum == PORT_0 && (pinNum >= PIN_27 && pinNum <= PIN_28))
		return;

	if (odMode == OPEN_DRAIN)
	{
		*(uint32_t *)(pPinCon + portNum) |= (0x01UL << pinNum);
	}
	else
	{
		*(uint32_t *)(pPinCon + portNum) &= ~(0x01UL << pinNum);
	}
}

/***************************************************************************//**
 * @fn			GPIO_SETpINdIR()
 * @brief		Setea la dirección del Pin pasado como parámetro:
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	dir 		Dirección del Pin: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_DIRECTION
 * @return		void
 ******************************************************************************/
void GPIO_SETpINdIR(uint8_t portNum, uint8_t pinNum, PIN_DIRECTION dir)
{
	if (dir==DIR_OUT)
	{
		(LPC_GPIO0 + portNum)->FIODIR |= (0x01<<pinNum);
	}
	else
	{
		(LPC_GPIO0 + portNum)->FIODIR &= ~(0x01<<pinNum);
	}
}

/***************************************************************************//**

 * @fn			GPIO_GETpINsTATE()
 * @brief		Retorna el Estado del Pin pasado como parámetro teniendo en
 *              cuenta su Nivel de Actividad
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	activity	Nivel de Actividad: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_ACTIVITY
 * @return		Estado del Pin. Es uno de los tipos definidos en la enumeración DIGITAL_STATE
 ******************************************************************************/
DIGITAL_STATE GPIO_GETpINsTATE(uint8_t portNum, uint8_t pinNum, PIN_ACTIVITY activity)
{
	if (GET_BIT((LPC_GPIO0 + portNum)->FIOPIN,pinNum)==OFF)
	{
		if(activity==ACTIVE_LOW)
		{
			return(ON);
		}
		else
		{
			return(OFF);
		}
	}
	else
	{
		if(activity==ACTIVE_HIGH)
		{
			return(ON);
		}
		else
		{
			return(OFF);
		}
	}
}

/***************************************************************************//**
 * @fn			GPIO_SETpINsTATE()
 * @brief		Setea el Estado del Pin pasado como parámetro segun se indica:
 *              STATE_ON  && ACTIVE_HIGH ==> Pone un 1 en el Pin
 *              STATE_ON  && ACTIVE_LOW  ==> Pone un 0 en el Pin
 *              STATE_OFF && ACTIVE_HIGH ==> Pone un 0 en el Pin
 *              STATE_OFF && ACTIVE_LOW  ==> Pone un 1 en el Pin
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	activity	Nivel de Actividad: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_ACTIVITY
 * @param[in]	state	 	Estado del Pin: Valores posibles
 *			                - STATE_OFF
 *          			    - STATE_ON
 * @return		void
 ******************************************************************************/
void GPIO_SETpINsTATE(uint8_t portNum, uint8_t pinNum, PIN_ACTIVITY activity, DIGITAL_STATE state)
{
	if (state==STATE_ON)
	{
		GPIO_SETpIN(portNum, pinNum, activity);
	}
	else
	{
		GPIO_CLRpIN(portNum, pinNum, activity);
	}
	return;
}

/***************************************************************************//**
 * @fn			GPIO_SETpIN()
 * @brief		Pone a STATE_ON el Estado del Pin pasado como parámetro segun se indica:
 *              ACTIVE_HIGH ==> Pone un 1 en el Pin
 *              ACTIVE_LOW  ==> Pone un 0 en el Pin
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	activity	Nivel de Actividad: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_ACTIVITY
 * @return		void
 ******************************************************************************/
void GPIO_SETpIN(uint8_t portNum, uint8_t pinNum, PIN_ACTIVITY activity)
{
	if(activity==ACTIVE_HIGH)
	{
		(LPC_GPIO0 + portNum)->FIOSET = (0x01<<pinNum);
	}
	else
	{
		(LPC_GPIO0 + portNum)->FIOCLR = (0x01<<pinNum);
	}
	return;
}

/***************************************************************************//**
 * @fn			GPIO_CLRpIN()
 * @brief		Pone a STATE_OFF el Estado del Pin pasado como parámetro segun se indica:
 *              ACTIVE_HIGH ==> Pone un 0 en el Pin
 *              ACTIVE_LOW  ==> Pone un 1 en el Pin
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 * @param[in] 	activity	Nivel de Actividad: Debe ser uno de los tipos
 *                          definidos en la enumeración PIN_ACTIVITY
 * @return		void
 ******************************************************************************/
void GPIO_CLRpIN(uint8_t portNum, uint8_t pinNum, PIN_ACTIVITY activity)
{
	if(activity==ACTIVE_LOW)
	{
		(LPC_GPIO0 + portNum)->FIOSET = (0x01<<pinNum);
	}
	else
	{
		(LPC_GPIO0 + portNum)->FIOCLR = (0x01<<pinNum);
	}
	return;
}

/***************************************************************************//**
 * @fn			GPIO_TOGGLEpIN()
 * @brief		Togglea el Estado del Pin pasado como parámetro segun se indica:
 *              STATE_OFF ==> STATE_ON
 *              STATE_ON ==> STATE_OFF
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 *
 * @return		void
 ******************************************************************************/
void GPIO_TogglePin(uint8_t portNum, uint8_t pinNum)
{
	(LPC_GPIO0 + portNum)->FIOPIN ^= (0x01<<pinNum);
	return;
}

/***************************************************************************//**
 * @fn			GPIO_IntAsc()
 * @brief		Habilita la interrupcion por flanco ascendente del pin y el puerto pasado como parametro
 * @param[in]	value		Valor de habilitacion: Debe ser uno de los siguientes:
 *                          - ENABLE
 *                          - DISABLE
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 *
 * @return		void
 ******************************************************************************/
void GPIO_IntAsc(FUNCTIONAL_STATE value, uint8_t portNum, uint8_t pinNum)
{
	LPC_GPIO_INT_TypeDef *p=NULL;
	if (portNum == PORT_0)
	{
		p= GPIO_INT0;
	}
	else if (portNum == PORT_2)
	{
		p= GPIO_INT2;
	}
	else
	{
		return;
	}
	if (value == DISABLED)
	{
		(p->INTENR) &= ~(0x01 << pinNum);
	}
	else
	{
		(p->INTENR) |= (0x01 << pinNum);
	}
	return;
}

/***************************************************************************//**
 * @fn			GPIO_IntDesc()
 * @brief		Habilita la interrupcion por flanco descendente del pin y el puerto pasado como parametro
 * @param[in]	value		Valor de habilitacion: Debe ser uno de los siguientes:
 *                          - ENABLE
 *                          - DISABLE
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 *
 * @return		void
 ******************************************************************************/
void GPIO_IntDesc(FUNCTIONAL_STATE value, uint8_t portNum, uint8_t pinNum)
{
	LPC_GPIO_INT_TypeDef *p=NULL;
	if (portNum == PORT_0)
	{
		p= GPIO_INT0;
	}
	else if (portNum == PORT_2)
	{
		p= GPIO_INT2;
	}
	else
	{
		return;
	}
	if (value == DISABLED)
	{
		(p->INTENF) &= ~(0x01 << pinNum);
	}
	else
	{
		(p->INTENF) |= (0x01 << pinNum);
	}
	return;
}

/***************************************************************************//**
 * @fn			GPIO_GetFlagAsc()
 * @brief		Indica el estado de la interrupcion por flanco ascendente del pin y el puerto pasado como parametro
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 *
 * @return		DIGITAL_STATE
 ******************************************************************************/
DIGITAL_STATE GPIO_GetFlagAsc(uint8_t portNum, uint8_t pinNum)
{
	LPC_GPIO_INT_TypeDef *p=NULL;
	if (portNum == PORT_0)
	{
		p= GPIO_INT0;
	}
	else if (portNum == PORT_2)
	{
		p= GPIO_INT2;
	}
	else
	{
		return(OFF);
	}
	if (GET_BIT((p->INTSTATR),pinNum) == OFF)
	{
		return(OFF);
	}
	else
	{
		return(ON);
	}
	return(OFF);
}

/***************************************************************************//**
 * @fn			GPIO_GetFlagDesc()
 * @brief		Indica el estado de la interrupcion por flanco ascendente del pin y el puerto pasado como parametro
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 *
 * @return		DIGITAL_STATE
 ******************************************************************************/
DIGITAL_STATE GPIO_GetFlagDesc(uint8_t portNum, uint8_t pinNum)
{
	LPC_GPIO_INT_TypeDef *p=NULL;
	if (portNum == PORT_0)
	{
		p= GPIO_INT0;
	}
	else if (portNum == PORT_2)
	{
		p= GPIO_INT2;
	}
	else
	{
		return(OFF);
	}
	if (GET_BIT((p->INTSTATF),pinNum) == OFF)
	{
		return(OFF);
	}
	else
	{
		return(ON);
	}
	return(OFF);
}

/***************************************************************************//**
 * @fn			GPIO_IntClr()
 * @brief		Limpia los Flags ubicados en INTSTATF e INTSTATR correspondientes al puerto y pin que fueron pasados como parametro
 * @param[in]	portNum		Número de Puerto: Debe ser uno de los siguientes:
 *                          - PORT_0
 *                          - PORT_1
 *                          - PORT_2
 *                          - PORT_3
 * @param[in]	pinNum		Número de Pin: Debe ser uno de los siguientes:
 *                          - Desde PIN_0 hasta PIN_31
 *
 * @return		void
 ******************************************************************************/
void GPIO_IntClr(uint8_t portNum, uint8_t pinNum)
{
	LPC_GPIO_INT_TypeDef *p=NULL;
	if (portNum == PORT_0)
	{
		p= GPIO_INT0;
	}
	else if (portNum == PORT_2)
	{
		p= GPIO_INT2;
	}
	else
	{
		return;
	}
	(p->INTCLR) |= (0x01 << pinNum);
	return;
}

/********************************************************************************************************
*** PRIVATE FUNCTIONS
********************************************************************************************************/


/*-----------------------------------------------------------------------------------------------------*/

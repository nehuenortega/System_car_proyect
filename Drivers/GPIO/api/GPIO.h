/*****************************************************************************************************//**
*
* @file		GPIO.h
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
*** MODULE
********************************************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_


/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/
#include "LPC17xx.h"
#include "My_Types.h"

/********************************************************************************************************
*** DEFINES
********************************************************************************************************/
// Definición de Puertos
#define PORT_0		 0
#define PORT_1		 1
#define PORT_2		 2
#define PORT_3		 3
#define PORT_4		 4

// Definición de Pines
#define PIN_0		 0
#define PIN_1		 1
#define PIN_2		 2
#define PIN_3		 3
#define PIN_4		 4
#define PIN_5		 5
#define PIN_6		 6
#define PIN_7		 7
#define PIN_8		 8
#define PIN_9		 9
#define PIN_10		10
#define PIN_11		11
#define PIN_12		12
#define PIN_13		13
#define PIN_14		14
#define PIN_15		15
#define PIN_16		16
#define PIN_17		17
#define PIN_18		18
#define PIN_19		19
#define PIN_20		20
#define PIN_21		21
#define PIN_22		22
#define PIN_23		23
#define PIN_24		24
#define PIN_25		25
#define PIN_26		26
#define PIN_27		27
#define PIN_28		28
#define PIN_29		29
#define PIN_30		30
#define PIN_31		31


/********************************************************************************************************
*** MACROS
********************************************************************************************************/







/********************************************************************************************************
*** DATA TYPES
********************************************************************************************************/
typedef enum {RES_PULL_UP = 0, RES_LAST_STATE = 1, RES_NONE = 2, RES_PULL_DOWN = 3} PIN_RES_MODE;
typedef enum {NOT_OPEN_DRAIN = 0, OPEN_DRAIN = 1} PIN_OD_MODE;
typedef enum {ACTIVE_LOW = 0, ACTIVE_HIGH = 1} PIN_ACTIVITY ;
typedef enum {DEFAULT_FUNC = 0, FIRST_ALT_FUNC = 1, SECOND_ALT_FUNC = 2, THIRD_ALT_FUNC = 3} PIN_FUNCTION;
typedef enum {DIR_IN = 0, DIR_OUT = 1} PIN_DIRECTION;


/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/


/********************************************************************************************************
*** PUBLIC FUNCTION PROTOTYPES
********************************************************************************************************/
void GPIO_InitPinAsGPIO(uint8_t portNum, uint8_t pinNum, PIN_DIRECTION dir, PIN_RES_MODE resMode, PIN_OD_MODE odMode);
void GPIO_InitPinNotAsGPIO(uint8_t portNum, uint8_t pinNum, PIN_FUNCTION func, PIN_RES_MODE resMode, PIN_OD_MODE odMode);
void GPIO_SetPinFunc(uint8_t portNum, uint8_t pinNum, PIN_FUNCTION func);
void GPIO_SetResistorMode ( uint8_t portNum, uint8_t pinNum, PIN_RES_MODE resMode);
void GPIO_SetOpenDrainMode( uint8_t portNum, uint8_t pinNum, PIN_OD_MODE odMode);
void GPIO_SETpINdIR(uint8_t portNum, uint8_t pinNum, PIN_DIRECTION dir);
DIGITAL_STATE GPIO_GETpINsTATE(uint8_t portNum, uint8_t pinNum, PIN_ACTIVITY activity);
void GPIO_SETpINsTATE(uint8_t portNum, uint8_t pinNum, PIN_ACTIVITY activity, DIGITAL_STATE state);
void GPIO_SETpIN(uint8_t portNum, uint8_t pinNum, PIN_ACTIVITY activity);
void GPIO_CLRpIN(uint8_t portNum, uint8_t pinNum, PIN_ACTIVITY activity);
void GPIO_TogglePin(uint8_t portNum, uint8_t pinNum);

/*       GPIO Interrupt functions           */

void GPIO_IntAsc(FUNCTIONAL_STATE value, uint8_t portNum, uint8_t pinNum);
void GPIO_IntDesc(FUNCTIONAL_STATE value, uint8_t portNum, uint8_t pinNum);
DIGITAL_STATE GPIO_GetFlagAsc(uint8_t portNum, uint8_t pinNum);
DIGITAL_STATE GPIO_GetFlagDesc(uint8_t portNum, uint8_t pinNum);
void GPIO_IntClr(uint8_t portNum, uint8_t pinNum);

/********************************************************************************************************
*** MODULE END
********************************************************************************************************/

#endif

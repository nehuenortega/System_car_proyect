/*
 * Info_Exp_3.h
 *
 *  Created on: 21/08/2014
 *      Author: TinchoPC
 */


/********************************************************************************************************
*** MODULE
********************************************************************************************************/
#ifndef INFO_EXP_3_H_
#define INFO_EXP_3_H_


/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/
#include "LPC17xx.h"
#include "My_Types.h"
#include "MasterBoard.h"
#include "GPIO.h"

/********************************************************************************************************
*** DEFINES
********************************************************************************************************/

#define BCD_A			EXPANSION0
#define BCD_B			EXPANSION1
#define BCD_C			EXPANSION2
#define BCD_D			EXPANSION3

#define BCD_DP			EXPANSION4

#define RESET			EXPANSION6
#define CLOCK			EXPANSION5

#define FILA_0			EXPANSION7
#define FILA_1			EXPANSION8
#define FILA_2			EXPANSION9
#define FILA_3			EXPANSION10
#define COLUMNA_0		EXPANSION11				//ENTRADAS
#define COLUMNA_1		EXPANSION12				//ENTRADAS


#define CANTIDAD_DIGITOS	6

#define NO_KEY	0
#define SW1 	1
#define SW2 	2
#define SW3 	3
#define SW4 	4
#define SW5 	5
#define SW6 	6
#define SW7 	7
#define SW8 	8

#define CANTIDAD_DE_REBOTES	10










/********************************************************************************************************
*** MACROS
********************************************************************************************************/







/********************************************************************************************************
*** DATA TYPES
********************************************************************************************************/



/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/



/********************************************************************************************************
*** PUBLIC FUNCTION PROTOTYPES
********************************************************************************************************/

void Exp3_Init(void);

//-- Modulo Display --

void Exp3_Print(uint32_t number);
void Exp3_Display(void);
void Exp3_Clear(void);

//-- Modulo Teclado --

uint8_t Exp3_KeyboardHW(void);
void Exp3_KeyboardSW(void);
uint8_t	Exp3_Keyboard(void);



/********************************************************************************************************
*** MODULE END
********************************************************************************************************/

#endif
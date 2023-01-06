/*
 * Info_Exp_1.h
 *
 *  Created on: 25/08/2014
 *      Author: TinchoPC
 */


/********************************************************************************************************
*** MODULE
********************************************************************************************************/
#ifndef INFO_EXP_1_H_
#define INFO_EXP_1_H_


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



#define LED1	 EXPANSION0
#define LED2	 EXPANSION1
#define LED3	 EXPANSION2
#define LED4	 EXPANSION3
#define LED5	 EXPANSION4
#define LED6	 EXPANSION5
#define LED7	 EXPANSION6
#define LED8	 EXPANSION7

#define DIP1_1_INIT	 EXPANSION8
#define DIP1_2_INIT	 EXPANSION9
#define DIP1_3_INIT	 EXPANSION10
#define DIP1_4_INIT	 EXPANSION11
#define DIP1_5_INIT	 EXPANSION12
#define DIP1_6_INIT	 EXPANSION13
#define DIP1_7_INIT	 EXPANSION14
#define DIP1_8_INIT	 EXPANSION15

#define DIP2_1_INIT	 EXPANSION16
#define DIP2_2_INIT	 EXPANSION17
#define DIP2_3_INIT	 EXPANSION18

#define DIP1_1	 EXPANSION8,ACTIVE_LOW
#define DIP1_2	 EXPANSION9,ACTIVE_LOW
#define DIP1_3	 EXPANSION10,ACTIVE_LOW
#define DIP1_4	 EXPANSION11,ACTIVE_LOW
#define DIP1_5	 EXPANSION12,ACTIVE_LOW
#define DIP1_6	 EXPANSION13,ACTIVE_LOW
#define DIP1_7	 EXPANSION14,ACTIVE_LOW
#define DIP1_8	 EXPANSION15,ACTIVE_LOW

#define DIP2_1	 EXPANSION16,ACTIVE_LOW
#define DIP2_2	 EXPANSION17,ACTIVE_LOW
#define DIP2_3	 EXPANSION18,ACTIVE_LOW

#define NO_KEY		0
#define SW1			1
#define SW2			2
#define SW3			3
#define DIP_1_1		1
#define DIP_1_2		2
#define DIP_1_3		3
#define DIP_1_4		4
#define DIP_1_5		5
#define DIP_1_6		6
#define DIP_1_7		7
#define DIP_1_8		8
#define DIP_2_1		9
#define DIP_2_2		10
#define DIP_2_3		11

#define	CANTIDAD_DE_REBOTES	10


/********************************************************************************************************
*** MACROS
********************************************************************************************************/



/********************************************************************************************************
*** DATA TYPES
********************************************************************************************************/

typedef enum {LED_1,LED_2,LED_3,LED_4,LED_5,LED_6,LED_7,LED_8} Led_Typedef;

/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/



/********************************************************************************************************
*** PUBLIC FUNCTION PROTOTYPES
********************************************************************************************************/

void Exp1_Init(void);
void Exp1_On(Led_Typedef led);
void Exp1_Off(Led_Typedef led);

uint8_t Exp1_KeyboardHW(void);
void Exp1_KeyboardSW(void);
uint8_t Exp1_Keyboard(void);

/********************************************************************************************************
*** MODULE END
********************************************************************************************************/

#endif

/*
 * NVIC.h
 *
 *  Created on: 06/06/2014
 *      Author: TinchoPC
 */


/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "LPC17xx.h"
#include "My_Types.h"

/********************************************************************************************************
*** DEFINES
********************************************************************************************************/

#define NVIC_OFFSET_PRIORITY	3

/********************************************************************************************************
*** MACROS
********************************************************************************************************/



/********************************************************************************************************
*** DATA TYPES
********************************************************************************************************/


typedef enum {
				NVIC_WDT 			= 0,
				NVIC_TMR0 			= 1,
				NVIC_TMR1 			= 2,
				NVIC_TMR2 			= 3,
				NVIC_TMR3 			= 4,
				NVIC_UART0 			= 5,
				NVIC_UART1 			= 6,
				NVIC_UART2 			= 7,
				NVIC_UART3 			= 8,
				NVIC_PWM1 			= 9,
				NVIC_I2C0 			= 10,
				NVIC_I2C1 			= 11,
				NVIC_I2C2 			= 12,
				NVIC_SPI 			= 13,
				NVIC_SSP0 			= 14,
				NVIC_SSP1 			= 15,
				NVIC_PLL0 			= 16,
				NVIC_RTC 			= 17,
				NVIC_EINT0 			= 18,
				NVIC_EINT1 			= 19,
				NVIC_EINT2 			= 20,
				NVIC_EINT3			= 21,
				NVIC_ADC			= 22,
				NVIC_BOD			= 23,
				NVIC_USB			= 24,
				NVIC_CAN			= 25,
				NVIC_GPDMA			= 26,
				NVIC_I2S			= 27,
				NVIC_ETHERNET		= 28,
				NVIC_RITINT			= 29,
				NVIC_MC_PWM			= 30,
				NVIC_QEI			= 31,
				NVIC_PLL1 			= 32,
				NVIC_USB_INT		= 33,
				NVIC_CAN_INT		= 34} NVIC_Typedef;

typedef enum {
				NVIC_PRIRITY_0		= 0,
				NVIC_PRIRITY_1		= 1,
				NVIC_PRIRITY_2		= 2,
				NVIC_PRIRITY_3		= 3,
				NVIC_PRIRITY_4		= 4,
				NVIC_PRIRITY_5		= 5,
				NVIC_PRIRITY_6		= 6,
				NVIC_PRIRITY_7		= 7,
				NVIC_PRIRITY_8		= 8,
				NVIC_PRIRITY_9		= 9,
				NVIC_PRIRITY_10		= 10,
				NVIC_PRIRITY_11		= 11,
				NVIC_PRIRITY_12		= 12,
				NVIC_PRIRITY_13		= 13,
				NVIC_PRIRITY_14		= 14,
				NVIC_PRIRITY_15		= 15,
				NVIC_PRIRITY_16		= 16,
				NVIC_PRIRITY_17		= 17,
				NVIC_PRIRITY_18		= 18,
				NVIC_PRIRITY_19		= 19,
				NVIC_PRIRITY_20		= 20,
				NVIC_PRIRITY_21		= 21,
				NVIC_PRIRITY_22		= 22,
				NVIC_PRIRITY_23		= 23,
				NVIC_PRIRITY_24		= 24,
				NVIC_PRIRITY_25		= 25,
				NVIC_PRIRITY_26		= 26,
				NVIC_PRIRITY_27		= 27,
				NVIC_PRIRITY_28		= 28,
				NVIC_PRIRITY_29		= 29,
				NVIC_PRIRITY_30		= 30,
				NVIC_PRIRITY_31		= 31} NVIC_PRIORITY;

/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/


/********************************************************************************************************
*** PUBLIC FUNCTION PROTOTYPES
********************************************************************************************************/
void NVIC_Enable(NVIC_Typedef parametro);
void NVIC_Disable(NVIC_Typedef parametro);
BOOL NVIC_GetPend(NVIC_Typedef parametro);
void NVIC_Clr(NVIC_Typedef parametro);
void NVIC_Priority(NVIC_Typedef parametro, NVIC_PRIORITY prioridad);

/********************************************************************************************************
*** MODULE END
********************************************************************************************************/


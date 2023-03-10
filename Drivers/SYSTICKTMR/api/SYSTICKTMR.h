/*
 * SYSTICKTMR.h
 *
 *  Created on: 07/06/2014
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
#define SYSTICK_TMR_ENABLE		0
#define SYSTICK_TMR_TICKINT		1
#define SYSTICK_TMR_CLKSOURCE	2
#define SYSTICK_TMR_COUNTFLAG	3

/********************************************************************************************************
*** MACROS
********************************************************************************************************/



/********************************************************************************************************
*** DATA TYPES
********************************************************************************************************/

typedef enum {CLK_STRCLK = 0,CLK_CPU = 1}CLK_SETUP;

/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/


/********************************************************************************************************
*** PUBLIC FUNCTION PROTOTYPES
********************************************************************************************************/

void SYSTICKTMR_Init(FUNCTIONAL_STATE state, CLK_SETUP clock);
BOOL SYSTICKTMR_GetFlag(void);
void SYSTICKTMR_SetCounter(uint32_t counter);
uint32_t SYSTICKTMR_GetValue(void);

/********************************************************************************************************
*** MODULE END
********************************************************************************************************/


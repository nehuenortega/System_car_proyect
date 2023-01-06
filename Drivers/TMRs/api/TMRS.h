/*
 * TMRS.h
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

#define TMR0_ON		1
#define TMR1_ON		2
#define TMR2_ON		22
#define TMR3_ON		23

#define TMR0_CLK	2
#define TMR1_CLK	4
#define TMR2_CLK	12
#define TMR3_CLK	14

#define MATCH_OFFSET	4

/********************************************************************************************************
*** MACROS
********************************************************************************************************/



/********************************************************************************************************
*** DATA TYPES
********************************************************************************************************/


typedef enum {
				TMR0 			= 0,
				TMR1 			= 1,
				TMR2 			= 2,
				TMR3 			= 3
				} TMR_Typedef;

typedef enum {
				MR0 			= 0,
				MR1 			= 1,
				MR2 			= 2,
				MR3 			= 3,
				CR0				= 4,
				CR1				= 5
				} TMR_Type_Typedef;

typedef struct {
				TMR_Type_Typedef tipo;
				uint32_t value;
				FUNCTIONAL_STATE parametro0;
				FUNCTIONAL_STATE parametro1;
				FUNCTIONAL_STATE parametro2;
				}TMR_CAPT_MATCH_Typedef;

typedef enum {
				TMR_ASC			= 1,
				TMR_DESC		= 2,
				TMR_AMBOS		= 3
				} TMR_FLANK_Typedef;

typedef enum {
				TMR_CHANNEL0	= 0,
				TMR_CHANNEL1	= 1
				}TMR_CHANNEL_Typedef;

typedef enum {
				NO_CHANGE		= 0,
				CLR_PINOUT		= 1,
				SET_PINOUT		= 2,
				TOGGLE_PINOUT	= 3
				}MATCH_STATE_Typedef;

/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/


/********************************************************************************************************
*** PUBLIC FUNCTION PROTOTYPES
********************************************************************************************************/

void TMR_On(TMR_Typedef timer);
void TMR_Off(TMR_Typedef timer);
void TMR_Enable(TMR_Typedef timer, BOOL value);
void TMR_Reset(TMR_Typedef timer);
BOOL TMR_GetFlag(TMR_Typedef timer, TMR_Type_Typedef parametro);
void TMR_Set(TMR_Typedef timer, TMR_CAPT_MATCH_Typedef *parametro);
void TMR_ConfigClock(TMR_Typedef timer, CLK_Typedef clock);
void TMR_ConfigCapture(TMR_Typedef timer, TMR_FLANK_Typedef flanco, TMR_CHANNEL_Typedef canal);
void TMR_ConfigMatch(TMR_Typedef timer, TMR_Type_Typedef tipo, MATCH_STATE_Typedef estado,TMR_CHANNEL_Typedef canal);


/********************************************************************************************************
*** MODULE END
********************************************************************************************************/

/********************************************************************************************************
*** MODULE
********************************************************************************************************/

/*
 *  EINT.h
 *
 *  Created on: 06/06/2014
 *****************************************************************/

/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "LPC17xx.h"
#include "My_Types.h"
#include "NVIC.h"
#include "GPIO.h"

/********************************************************************************************************
*** DEFINES
********************************************************************************************************/
#define EINT_PORT	PORT_2
#define EINT0_PIN	PIN_10
#define EINT_FUNC	FIRST_ALT_FUNC
#define EINT0_NVIC	18

/********************************************************************************************************
*** POSICIONES DE MEMORIA
********************************************************************************************************/


/********************************************************************************************************
*** MACROS
********************************************************************************************************/



/********************************************************************************************************
*** DATA TYPES
********************************************************************************************************/
typedef enum {EINT0 = 0,EINT1 = 1,EINT2 = 2,EINT3 = 3} EINTX;
typedef enum {LEVEL = 0, FLANK = 1}EINT_MODE;
typedef enum {NEGATIVE = 0, POSIVITE = 1}EINT_POLAR;


/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/


/********************************************************************************************************
*** PUBLIC FUNCTION PROTOTYPES
********************************************************************************************************/

void EINT_Enable(EINTX entrada);
void EINT_SetMode(EINTX entrada,EINT_MODE modo);
void EINT_SetPolar(EINTX entrada,EINT_POLAR polaridad);
void EINT_Create(EINTX entrada,EINT_MODE modo,EINT_POLAR polaridad);
BOOL EINT_GetFlag(EINTX entrada);

/********************************************************************************************************
*** MODULE END
********************************************************************************************************/


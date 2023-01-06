/*****************************************************************************************************//**
*
* @file		Info_Exp_2.h
* @brief	Módulo para manejo de la Expansion N°2.
*
* @version	1.00
* @date		XX/XX/XXXX
* @author	Martin C. A. Yunis (MCAY)
*
*
*********************************************************************************************************
*** REVISION HISTORY
*
********************************************************************************************************/


/********************************************************************************************************
*** MODULE
********************************************************************************************************/
#ifndef INFO_EXP_2_H_
#define INFO_EXP_2_H_


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

#define DIGITO0			 EXPANSION5,ACTIVE_HIGH
#define DIGITO1			 EXPANSION4,ACTIVE_HIGH
#define DIGITO2			 EXPANSION3,ACTIVE_HIGH
#define DIGITO3			 EXPANSION2,ACTIVE_HIGH
#define DIGITO4			 EXPANSION1,ACTIVE_HIGH
#define DIGITO5			 EXPANSION0,ACTIVE_HIGH

#define DIG0			 EXPANSION5
#define DIG1			 EXPANSION4
#define DIG2			 EXPANSION3
#define DIG3			 EXPANSION2
#define DIG4			 EXPANSION1
#define DIG5			 EXPANSION0

#define SEGMENTO_A		 EXPANSION6,ACTIVE_HIGH
#define SEGMENTO_B		 EXPANSION15,ACTIVE_HIGH
#define SEGMENTO_C		 EXPANSION14,ACTIVE_HIGH
#define SEGMENTO_D 		 EXPANSION13,ACTIVE_HIGH
#define SEGMENTO_E 		 EXPANSION12,ACTIVE_HIGH
#define SEGMENTO_F		 EXPANSION11,ACTIVE_HIGH
#define SEGMENTO_G 		 EXPANSION10,ACTIVE_HIGH
#define SEGMENTO_DP		 EXPANSION9,ACTIVE_HIGH

#define SEG_A		 EXPANSION6
#define SEG_B		 EXPANSION15
#define SEG_C		 EXPANSION14
#define SEG_D		 EXPANSION13
#define SEG_E 		 EXPANSION12
#define SEG_F		 EXPANSION11
#define SEG_G 		 EXPANSION10
#define SEG_DP		 EXPANSION9


#define VALUE_MAXIMO		999999
#define VALUE_MINIMO	 	-99999
#define DIGITOS_CANTIDAD	6


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

void Exp2_Init(void);
void Exp2_Print(int32_t number);
void Exp2_Display(void);
void Exp2_Clear(void);



/********************************************************************************************************
*** MODULE END
********************************************************************************************************/

#endif

/*
 * Info_Exp_2.c
 *
 *  Created on: 04/08/2014
 *      Author: TinchoPC
 */
/*****************************************************************************************************//**
*
* @file		Info_Exp_2.c
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
*** INCLUDES
********************************************************************************************************/

#include "Info_Exp_2.h"

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

uint8_t Tabla_Digitos_BCD_7seg[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/
static uint8_t digitos[6];

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
 * @fn			Exp2_Init()
 * @brief		Inicializacion de Display 7seg de 6 digitos.
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp2_Init(void)
{
	GPIO_InitPinAsGPIO(DIG0, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIG1, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIG2, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIG3, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIG4, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(DIG5, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);


	GPIO_InitPinAsGPIO(SEG_A, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(SEG_B, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(SEG_C, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(SEG_D, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(SEG_E, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(SEG_F, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(SEG_G, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);
	GPIO_InitPinAsGPIO(SEG_DP, DIR_OUT, RES_NONE, NOT_OPEN_DRAIN);

	return;
}


/***************************************************************************//**
 * @fn			Exp2_Print()
 * @brief		Driver de impresion en Display 7seg de 6 digitos.
 * @param[in] 	int32_t	number:
 * 									Numero a imprimir en el display.
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp2_Print(int32_t number)
{
	uint8_t k=0;
	uint8_t cantidad=DIGITOS_CANTIDAD;
	if ((number>VALUE_MAXIMO)||(number<(VALUE_MINIMO)))
	{
		digitos[5]=0x40;
		digitos[4]=0x79;
		digitos[3]=0x50;
		digitos[2]=0x50;
		digitos[1]=0x5c;
		digitos[0]=0x50;
		return;
	}

	if((number<0) && (number>=VALUE_MINIMO))
	{
		number= -number;
		if (number<10)
		{
			digitos[DIGITOS_CANTIDAD-5]=0x40;
			cantidad=DIGITOS_CANTIDAD-5;
		}else if (number<100)
		{
			digitos[DIGITOS_CANTIDAD-4]=0x40;
			cantidad=DIGITOS_CANTIDAD-4;
		}else if (number<1000)
		{
			digitos[DIGITOS_CANTIDAD-3]=0x40;
			cantidad=DIGITOS_CANTIDAD-3;
		}else if(number<10000)
		{
			digitos[DIGITOS_CANTIDAD-2]=0x40;
			cantidad=DIGITOS_CANTIDAD-2;
		}else{
			digitos[DIGITOS_CANTIDAD-1]=0x40;
			cantidad=DIGITOS_CANTIDAD-1;
		}

	}
	for(k=0;k<cantidad;k++)
	{
		digitos[k]=Tabla_Digitos_BCD_7seg[number%10];
		number/=10;
	}
	return;
}

/***************************************************************************//**
 * @fn			Exp2_Display()
 * @brief		Actualiza los valores representados en los 7seg.
 * @param[in] 	void
 *
 * @return 		void
 ******************************************************************************/

void Exp2_Display (void)
{
	static uint8_t j=0;

	// -- Apago todos los digitos --

	GPIO_CLRpIN(DIGITO0);
	GPIO_CLRpIN(DIGITO1);
	GPIO_CLRpIN(DIGITO2);
	GPIO_CLRpIN(DIGITO3);
	GPIO_CLRpIN(DIGITO4);
	GPIO_CLRpIN(DIGITO5);

	// -- Apago todos los segmentos --

	GPIO_CLRpIN(SEGMENTO_A);
	GPIO_CLRpIN(SEGMENTO_B);
	GPIO_CLRpIN(SEGMENTO_C);
	GPIO_CLRpIN(SEGMENTO_D);
	GPIO_CLRpIN(SEGMENTO_E);
	GPIO_CLRpIN(SEGMENTO_F);
	GPIO_CLRpIN(SEGMENTO_G);
	GPIO_CLRpIN(SEGMENTO_DP);

	if((digitos[j]&(0x01<<BIT0))!=0)
	{
		GPIO_SETpIN(SEGMENTO_A);
	}
	if((digitos[j]&(0x01<<BIT1))!=0)
	{
		GPIO_SETpIN(SEGMENTO_B);
	}
	if((digitos[j]&(0x01<<BIT2))!=0)
	{
		GPIO_SETpIN(SEGMENTO_C);
	}
	if((digitos[j]&(0x01<<BIT3))!=0)
	{
		GPIO_SETpIN(SEGMENTO_D);
	}
	if((digitos[j]&(0x01<<BIT4))!=0)
	{
		GPIO_SETpIN(SEGMENTO_E);
	}
	if((digitos[j]&(0x01<<BIT5))!=0)
	{
		GPIO_SETpIN(SEGMENTO_F);
	}
	if((digitos[j]&(0x01<<BIT6))!=0)
	{
		GPIO_SETpIN(SEGMENTO_G);
	}
	if((digitos[j]&(0x01<<BIT7))!=0)
	{
		GPIO_SETpIN(SEGMENTO_DP);
	}
	switch(j)
	{
	case 0:
		GPIO_SETpIN(DIGITO5);
		j++;
		break;
	case 1:
		GPIO_SETpIN(DIGITO4);
		j++;
		break;
	case 2:
		GPIO_SETpIN(DIGITO3);
		j++;
		break;
	case 3:
		GPIO_SETpIN(DIGITO2);
		j++;
		break;
	case 4:
		GPIO_SETpIN(DIGITO1);
		j++;
		break;
	case 5:
		GPIO_SETpIN(DIGITO0);
		j=0;
		break;
	}

	return;
}

/***************************************************************************//**
 * @fn			Exp2_Clear()
 * @brief		Apaga el Display 7seg de 6 digitos.
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/

void Exp2_Clear(void)
{
	uint8_t i=0;
	for(i=0;i<DIGITOS_CANTIDAD;i++)
	{
		digitos[i]=0x00;
	}
	return;
}







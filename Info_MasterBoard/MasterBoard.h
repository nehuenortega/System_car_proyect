/*****************************************************************************************************//**
*
* @file		MasterBoard.h
* @brief	Módulo para manejo de las Expansiones.
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
*** MODULE **********************************************************************************************
********************************************************************************************************/
#ifndef MASTERBOARD_H_
#define MASTERBOARD_H_

/********************************************************************************************************
*** INCLUDES ********************************************************************************************
********************************************************************************************************/

#include "GPIO.h"

/********************************************************************************************************
*** DEFINES *********************************************************************************************
********************************************************************************************************/

#define EXPANSION0       PORT_2,PIN_7
#define EXPANSION1       PORT_1,PIN_29
#define EXPANSION2       PORT_4,PIN_28
#define EXPANSION3       PORT_1,PIN_23
#define EXPANSION4       PORT_1,PIN_20
#define EXPANSION5       PORT_0,PIN_19
#define EXPANSION6       PORT_3,PIN_26
#define EXPANSION7       PORT_1,PIN_25
#define EXPANSION8       PORT_1,PIN_22
#define EXPANSION9       PORT_1,PIN_19
#define EXPANSION10      PORT_0,PIN_20
#define EXPANSION11      PORT_3,PIN_25
#define EXPANSION12      PORT_1,PIN_27
#define EXPANSION13      PORT_1,PIN_24
#define EXPANSION14      PORT_1,PIN_21
#define EXPANSION15      PORT_1,PIN_18
#define EXPANSION16      PORT_2,PIN_8
#define EXPANSION17      PORT_2,PIN_12
#define EXPANSION18      PORT_0,PIN_16             //	Rx1--Configurar S3
#define EXPANSION19      PORT_0,PIN_15             //	Tx1--Configurar S3
#define EXPANSION20      PORT_0,PIN_22             //	RTS1--Configurar S3
#define EXPANSION21      PORT_0,PIN_17             //	CTS1--Configurar S3

#endif

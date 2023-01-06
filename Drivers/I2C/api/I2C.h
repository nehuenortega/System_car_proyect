/*
 * I2C.h
 *
 *  Created on: 28/08/2014
 *      Author: TinchoPC
 */
/********************************************************************************************************
*** MODULE
********************************************************************************************************/
#ifndef I2C_H_
#define I2C_H_


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

#define	SDA0						PORT_0,PIN_27
#define	SCL0						PORT_0,PIN_28

#define	SDA1						PORT_0,PIN_0		// puede ser PORT_0,PIN_19
#define	SCL1						PORT_0,PIN_1		// puede ser PORT_0,PIN_20

#define	SDA2						PORT_0,PIN_10
#define	SCL2						PORT_0,PIN_11

#define I2C0_FUNCTION 				FIRST_ALT_FUNC
#define I2C1_FUNCTION				THIRD_ALT_FUNC
#define I2C2_FUNCTION 				SECOND_ALT_FUNC

#define	PCONP_I2C0					BIT7
#define	PCONP_I2C1					BIT19
#define	PCONP_I2C2					BIT26

#define	PCLK_I2C0					BIT14
#define	PCLK_I2C1					BIT6
#define	PCLK_I2C2					BIT20

#define I2C_STAT_START				0x08
#define I2C_STAT_REPEAT				0x10
#define I2C_STAT_WRITE_OK			0x18
#define I2C_STAT_WRITE_ERROR		0x20
#define I2C_STAT_DATA_WRITE			0x28
#define I2C_STAT_DATA_WRITE_ERROR	0x30
#define I2C_STAT_ARBITRATION_ERROR	0x38
#define I2C_STAT_READ_OK			0x40
#define I2C_STAT_READ_ERROR			0x48
#define I2C_STAT_DATA_READ			0x50
#define I2C_STAT_DATA_READ_ERROR	0x58

#define WRITE						0xFE
#define READ						0x01

#define VACIO						0x00
#define CLEAR						0xff

#define DATA_MAX					64
#define CANT_I2C					3

#define I2EN						BIT6
#define STA							BIT5
#define STO							BIT4
#define SI							BIT3
#define AA							BIT2

#define STATE_STAND_BY				0
#define STATE_READ					1
#define STATE_READING				2
#define STATE_WRITE					3
#define STATE_WRITTING				4

#define CANT_SLAVE_USED				1

/********************************************************************************************************
*** MACROS
********************************************************************************************************/



/********************************************************************************************************
*** DATA TYPES
********************************************************************************************************/

typedef enum {FREC_STANDARD=100000,FREC_FAST=400000,FREC_FAST_PLUS=1000000}I2C_FREC_Typedef;

typedef enum {I2C0 = 0,I2C1,I2C2}I2C_Typedef;

/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/



/********************************************************************************************************
*** PUBLIC FUNCTION PROTOTYPES
********************************************************************************************************/

void I2C_Init(I2C_Typedef i2c, CLK_Typedef clock, I2C_FREC_Typedef frecuency);
void I2C_On(I2C_Typedef i2c);
void I2C_Off(I2C_Typedef i2c);
void I2C_ME(I2C_Typedef i2c);
void I2C_Read(I2C_Typedef i2c, uint8_t slave, uint8_t cantidad, uint32_t (*I2C_Read_CallBack)(uint8_t data));
void I2C_Write(I2C_Typedef i2c, uint8_t slave, uint8_t *datos, uint32_t cantidad,void (*I2C_Write_CallBack)(void));
uint8_t I2C_GetState(I2C_Typedef i2c);
void I2C_SetAdress(I2C_Typedef i2c, uint8_t slave, uint8_t slave_adress);
uint8_t I2C_GetAdress(I2C_Typedef i2c, uint8_t slave_number);

/********************************************************************************************************
*** MODULE END
********************************************************************************************************/

#endif

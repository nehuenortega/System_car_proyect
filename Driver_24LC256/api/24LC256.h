/*
 * 24LC256.h
 *
 *  Created on: 28/08/2014
 *      Author: TinchoPC
 */


/********************************************************************************************************
*** MODULE
********************************************************************************************************/
#ifndef EEPROM_H_
#define EEPROM_H_


/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "LPC17xx.h"
#include "My_Types.h"
#include "I2C.h"

/********************************************************************************************************
*** DEFINES
********************************************************************************************************/

#define SLAVE0_ADRESS		0xA0
#define SLAVE0_NUMBER		0

#define ADRESS_MAX			63

#define MEM_ADRESS			2

#define PERIFERIC_I2C					I2C1
#define CLOCK_I2C						CLK_1
#define FRECUENCY_MODE					FREC_FAST

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

void EEPROM_Init(void);
void EEPROM_Write(uint8_t *data, uint8_t cantidad, uint16_t direccion);
void EEPROM_Read(uint16_t adress, uint8_t cantidad, uint32_t(*EEPROM_Read_CallBack)(uint8_t data));

/********************************************************************************************************
*** MODULE END
********************************************************************************************************/

#endif

/*
 * 24LC256.c
 *
 *  Created on: 28/08/2014
 *      Author: TinchoPC
 */
/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "24LC256.h"

/********************************************************************************************************
*** PRIVATE DEFINES
********************************************************************************************************/

#define EEPROM_STAND_BY		0
#define EEPROM_WRITE		1
#define EEPROM_READ			2

/********************************************************************************************************
*** PRIVATE MACROS
********************************************************************************************************/


/********************************************************************************************************
*** PRIVATE DATA TYPES
********************************************************************************************************/


/********************************************************************************************************
*** PRIVATE TABLES
********************************************************************************************************/


/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/


/********************************************************************************************************
*** PRIVATE GLOBAL VARIABLES
********************************************************************************************************/

uint8_t Estado = EEPROM_STAND_BY;
uint8_t Cantidad_de_Datos=VACIO;

/********************************************************************************************************
*** PRIVATE FUNCTION PROTOTYPES
********************************************************************************************************/

uint32_t (*Read_CallBack)(uint8_t data);
void EEPROM_WriteCallBack(void);

/********************************************************************************************************
*** CONFIGURATION ERRORS
********************************************************************************************************/


/*-----------------------------------------------------------------------------------------------------*/


/********************************************************************************************************
*** PUBLIC FUNCTIONS
********************************************************************************************************/

/***************************************************************************//**
 * @fn			EEPROM_Init()
 * @brief		Inicializacion de Memoria 24LC256, inicializa el bus de I2C y le da la dirección de la memoria.
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/
void EEPROM_Init(void)
{
	I2C_Init(PERIFERIC_I2C, CLOCK_I2C, FRECUENCY_MODE);
	I2C_SetAdress(PERIFERIC_I2C,SLAVE0_NUMBER, SLAVE0_ADRESS);

	return;
}


/***************************************************************************//**
 * @fn			EEPROM_Write()
 * @brief		Driver para escribir un dato en una Memoria 24LC256.
 * @param[in] 	data Puntero al dato a escribir
 *
 * @param[in] 	cantidad Cantidad de datos a escribir
 *
 * @param[in] 	direccion Direccion en la cual se va a escribir el primer dato del array
 *
 *
 *
 * @return 		void
 ******************************************************************************/
void EEPROM_Write(uint8_t *data, uint8_t cantidad, uint16_t adress)
{
	uint8_t datos[cantidad+MEM_ADRESS];
	uint8_t i=0;

	if(adress+cantidad > ADRESS_MAX)
	{
		return;
	}

	if(I2C_GetState(PERIFERIC_I2C)==STATE_STAND_BY)
	{
		Estado = EEPROM_WRITE;
		I2C_On(I2C1);
		datos[0]=HB(adress);
		datos[1]=LB(adress);
		for(i=0;i<cantidad;i++)
		{
			datos[i+MEM_ADRESS]=*(data+i);
		}
		I2C_Write(PERIFERIC_I2C, SLAVE0_NUMBER, &(datos[0]), MEM_ADRESS+cantidad,EEPROM_WriteCallBack);
	}
	return;
}


/***************************************************************************//**
 * @fn			EEPROM_Read()
 * @brief		Driver para leer un dato desde una Memoria 24LC256, se le dice la direccion y la cantidad a leer, y al leer cada dato llama a una función.
 * @param[in] 	adress posicion de memoria del primer dato que se desea leer
 *
 * @param[in] 	cantidad Cantidad de datos a leer
 *
 * @param[in] 	EEPROM_Read_CallBack	Función que se ejecutará al leer cada dato
 *
 *
 * @return 		void
 ******************************************************************************/
void EEPROM_Read(uint16_t adress, uint8_t cantidad, uint32_t (*EEPROM_Read_CallBack)(uint8_t data))
{
	uint8_t datos[MEM_ADRESS];

		if(adress+cantidad > ADRESS_MAX)
		{
			return;
		}

		if(I2C_GetState(PERIFERIC_I2C)==STATE_STAND_BY)
		{
			Estado = EEPROM_READ;
			I2C_On(I2C1);
			Cantidad_de_Datos=cantidad;
			Read_CallBack=EEPROM_Read_CallBack;
			datos[0]=HB(adress);
			datos[1]=LB(adress);
			I2C_Write(PERIFERIC_I2C, SLAVE0_NUMBER, &(datos[0]), MEM_ADRESS,EEPROM_WriteCallBack);
		}
	return;
}



/***************************************************************************//**
 * @fn			EEPROM_WriteCallBack()
 * @brief		Función que se llama al Escribir un dato, usada en el caso de lectura, ya que primero se debe escribir la dirección que se desea leer.
 * @param[in] 	void
 *
 *
 * @return 		void
 ******************************************************************************/
void EEPROM_WriteCallBack(void)
{
	if(Estado == EEPROM_READ)
	{
		I2C_Read(PERIFERIC_I2C,SLAVE0_NUMBER,Cantidad_de_Datos,Read_CallBack);
	}
	return;
}


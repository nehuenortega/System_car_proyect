/*

 * I2C.c
 *
 *  Created on: 28/08/2014
 *      Author: TinchoPC
 */
/********************************************************************************************************
*** INCLUDES
********************************************************************************************************/

#include "I2C.h"
#include "system_LPC17xx.h"


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

const uint32_t Tabla_Direcciones[3]={(uint32_t)&(LPC_I2C0),(uint32_t)&(LPC_I2C1),(uint32_t)&(LPC_I2C2)};

/********************************************************************************************************
*** PUBLIC GLOBAL VARIABLES
********************************************************************************************************/

extern uint32_t SystemCoreClock;				//--  Clock del Sistema  --

/********************************************************************************************************
*** PRIVATE GLOBAL VARIABLES
********************************************************************************************************/

static uint8_t estado[CANT_I2C]={STATE_STAND_BY, STATE_STAND_BY, STATE_STAND_BY};
static uint8_t Data[DATA_MAX][CANT_I2C];
static uint8_t Buffer_Cant[CANT_I2C]={VACIO,VACIO,VACIO};
static uint8_t Buffer[CANT_I2C]={VACIO,VACIO,VACIO};
static uint8_t Slave_Adress[CANT_SLAVE_USED][CANT_I2C];

/********************************************************************************************************
*** PRIVATE FUNCTION PROTOTYPES
********************************************************************************************************/

uint32_t (*I2C_CallBack_Receiver[CANT_I2C])(uint8_t data);
void (*I2C_CallBack_Transmiter[CANT_I2C])(void);

/********************************************************************************************************
*** CONFIGURATION ERRORS
********************************************************************************************************/


/*-----------------------------------------------------------------------------------------------------*/


/********************************************************************************************************
*** PUBLIC FUNCTIONS
********************************************************************************************************/

/***************************************************************************//**
 * @fn			I2C_Init()
 * @brief		Inicializacion de Modulo I2C 1.
 * @param[in]	i2c		Periferico a utilizar. Debe ser uno de los siguientes:
 * 							-I2C0
 * 							-I2C1
 * 							-I2C2
 *
 * @param[in]   clock	Clock del periferico. Debe ser uno de los siguientes:
 * 							-CLK_1
 * 							-CLK_2
 * 							-CLK_4
 * 							-CLK_8
 *
 * @param[in]	frecuency	Frecuencia de transmicion del bus. Debe ser una de las siguientes:
 * 							-FREC_STANDARD -> 100KHz
 * 							-FREC_FAST -> 400KHz
 * 							-FREC_FAST_PLUS -> 1MHz
 *
 * @return 		void
 ******************************************************************************/
void I2C_Init(I2C_Typedef i2c, CLK_Typedef clock, I2C_FREC_Typedef frecuency)
{
	uint8_t clock_div=VACIO,i=VACIO;

	for(i=0;i<DATA_MAX;i++)
	{
		Data[i][i2c]=VACIO;
	}

	switch(clock)
	{
	case CLK_1:
		clock_div=1;
		break;
	case CLK_2:
		clock_div=2;
		break;
	case CLK_4:
		clock_div=4;
		break;
	case CLK_8:
		clock_div=8;
		break;
	}

	clock_div = SystemCoreClock/(clock_div*frecuency);

	switch(i2c)
	{
	case I2C0:

		PCONP |= (0x01 << PCONP_I2C0);

		PCLKSEL0 &= ~((0x01 << PCLK_I2C0) | (0x01 << (PCLK_I2C0+1)));
		PCLKSEL0 |= (clock << PCLK_I2C0);

		GPIO_InitPinNotAsGPIO(SDA0, I2C0_FUNCTION , RES_NONE, OPEN_DRAIN);
		GPIO_InitPinNotAsGPIO(SCL0, I2C0_FUNCTION , RES_NONE, OPEN_DRAIN);

		NVIC_Enable(NVIC_I2C0);

		LPC_I2C0.SCLL = (clock_div/2);
		LPC_I2C0.SCLH = (clock_div/2)+(clock_div%2);

		LPC_I2C0.CONCLR = CLEAR;

		break;
	case I2C1:

		PCONP |= (0x01 << PCONP_I2C1);

		PCLKSEL1 &= ~((0x01 << PCLK_I2C1) | (0x01 << (PCLK_I2C1+1)));
		PCLKSEL1 |= (clock << PCLK_I2C1);

		GPIO_InitPinNotAsGPIO(SDA1, I2C1_FUNCTION , RES_NONE, OPEN_DRAIN);
		GPIO_InitPinNotAsGPIO(SCL1, I2C1_FUNCTION , RES_NONE, OPEN_DRAIN);

		NVIC_Enable(NVIC_I2C1);

		LPC_I2C1.SCLL = (clock_div/2);
		LPC_I2C1.SCLH = (clock_div/2)+(clock_div%2);

		LPC_I2C1.CONCLR = CLEAR;

		break;
	case I2C2:

		PCONP |= (0x01 << PCONP_I2C2);

		PCLKSEL1 &= ~((0x01 << PCLK_I2C2) | (0x01 << (PCLK_I2C2+1)));
		PCLKSEL1 |= (clock << PCLK_I2C2);

		GPIO_InitPinNotAsGPIO(SDA2, I2C2_FUNCTION, RES_NONE, OPEN_DRAIN);
		GPIO_InitPinNotAsGPIO(SCL2, I2C2_FUNCTION, RES_NONE, OPEN_DRAIN);

		NVIC_Enable(NVIC_I2C2);

		LPC_I2C2.SCLL = (clock_div/2);
		LPC_I2C2.SCLH = (clock_div/2)+(clock_div%2);

		LPC_I2C2.CONCLR = CLEAR;

		break;
	}

	return;
}

/***************************************************************************//**
 * @fn			I2C_On()
 * @brief		Enciende el bus de I2C pasado como parametro
 * @param[in]	i2c		Periferico a utilizar. Debe ser uno de los siguientes:
 * 							-I2C0
 * 							-I2C1
 * 							-I2C2
 *
 * @return 		void
 ******************************************************************************/
void I2C_On(I2C_Typedef i2c)
{
	LPC_I2C_Typedef *p=(LPC_I2C_Typedef *)Tabla_Direcciones[i2c];
	p->CONSET=(0x01<<I2EN);
}

/***************************************************************************//**
 * @fn			I2C_Off()
 * @brief		Apaga el bus de I2C pasado como parametro
 * @param[in]	i2c		Periferico a utilizar. Debe ser uno de los siguientes:
 * 							-I2C0
 * 							-I2C1
 * 							-I2C2
 *
 * @return 		void
 ******************************************************************************/
void I2C_Off(I2C_Typedef i2c)
{
	LPC_I2C_Typedef *p=(LPC_I2C_Typedef *)Tabla_Direcciones[i2c];
	p->CONCLR=(0x01<<I2EN);
}

/***************************************************************************//**
 * @fn			I2C_ME()
 * @brief		Maquina de estado del bus de I2C indicado como parametro
 * @param[in]	i2c		Periferico a utilizar. Debe ser uno de los siguientes:
 * 							-I2C0
 * 							-I2C1
 * 							-I2C2
 *
 * @return 		void
 ******************************************************************************/
void I2C_ME(I2C_Typedef i2c)
{

	switch(estado[i2c])
	{
	case STATE_STAND_BY:
		break;
	case STATE_READ:
		break;
	case STATE_READING:
		break;
	case STATE_WRITE:
		break;
	case STATE_WRITTING:
		break;
	}
	return;
}


/***************************************************************************//**
 * @fn			I2C_Read()
 * @brief		lee del bus del Modulo I2C indicado y ejecuta una función.
 * @param[in]	i2c		Periferico a utilizar. Debe ser uno de los siguientes:
 * 							-I2C0
 * 							-I2C1
 * 							-I2C2
 *
 * @param[in] 	slave esclavo del que desea leer un dato
 *
 * @param[in] 	cantidad cantidad de datos a leer
 *
 * @param[in] 	I2C_Read_CallBack función que se llamará al leer un dato del bus
 *
 *
 * @return		void
 ******************************************************************************/
void I2C_Read(I2C_Typedef i2c, uint8_t slave, uint8_t cantidad, uint32_t (*I2C_Read_CallBack)(uint8_t data))
{
	LPC_I2C_Typedef *p=(LPC_I2C_Typedef *)Tabla_Direcciones[i2c];

	if (estado[i2c]==STATE_STAND_BY)
	{
		I2C_CallBack_Receiver[i2c]=I2C_Read_CallBack;

		Buffer[i2c]=I2C_GetAdress(i2c,slave)|READ;

		Buffer_Cant[i2c]=cantidad;

		estado[i2c]=STATE_READ;

		p->CONSET=(0x01<<STA);

	}
	return;
}


/***************************************************************************//**
 * @fn			I2C_Write()
 * @brief		Escribe 'cantidad' de datos en el bus de I2C pasado como parametro y al terminar ejecuta una función.
 * @param[in]	i2c		Periferico a utilizar. Debe ser uno de los siguientes:
 * 							-I2C0
 * 							-I2C1
 * 							-I2C2
 *
 * @param[in] 	slave	Esclavo en el cual escribir el dato
 *
 * @param[in] 	datos	Puntero al inicio del buffer de datos a escribir
 *
 * @param[in] 	cantidad	Cantidad de datos que se desean escribir
 *
 * @param[in] 	I2C_Write_CallBack función que se llamará al escribir todos los datos en el bus
 *
 *
 *
 * @return 		void
 ******************************************************************************/
void I2C_Write(I2C_Typedef i2c, uint8_t slave, uint8_t *datos, uint32_t cantidad, void (*I2C_Write_CallBack)(void))
{
	uint32_t i=0;
	LPC_I2C_Typedef *p=(LPC_I2C_Typedef *)Tabla_Direcciones[i2c];

	if(estado[i2c]==STATE_STAND_BY)
	{

		I2C_CallBack_Transmiter[i2c]=I2C_Write_CallBack;

		Buffer[i2c]=I2C_GetAdress(i2c,slave)&WRITE;

		for(i=0;i<cantidad;i++)
		{
			Data[i][i2c]=*(datos+i);
		}

		Buffer_Cant[i2c]=cantidad;

		estado[i2c]=STATE_WRITE;

		p->CONSET=(0x01<<STA);

	}
	return;
}

/***************************************************************************//**
 * @fn			I2C_GetState()
 * @brief		Retorna el estado del bus i2c correspondiente al parametro pasado
 * @param[in]	i2c		Periferico a utilizar. Debe ser uno de los siguientes:
 * 							-I2C0
 * 							-I2C1
 * 							-I2C2
 *
 * @return 		uint8_t	Estado del bus.
 ******************************************************************************/
uint8_t I2C_GetState(I2C_Typedef i2c)
{
	return(estado[i2c]);
}

/***************************************************************************//**
 * @fn			I2C_SetAdress()
 * @brief		Setea la direccion del esclavo pasado como parametro
 * @param[in]	i2c		Periferico a utilizar. Debe ser uno de los siguientes:
 * 							-I2C0
 * 							-I2C1
 * 							-I2C2
 *
 * @param[in] 	slave		Esclavo del que desea setear la direccion
 *
 * @param[in]  slave_adress	Direccion del esclavo a setear
 *
 *
 * @return 		void
 ******************************************************************************/
void I2C_SetAdress(I2C_Typedef i2c, uint8_t slave_number, uint8_t slave_adress)
{
	Slave_Adress[slave_number][i2c]= slave_adress;
	return;
}


/***************************************************************************//**
 * @fn			I2C_GetAdress()
 * @brief		Retorna la direccion del esclavo pasado como parametro.
 * @param[in]	i2c		Periferico a utilizar. Debe ser uno de los siguientes:
 * 							-I2C0
 * 							-I2C1
 * 							-I2C2
 *
 * @param[in] 	slave_number	numero de esclavo, del que se desea obtener la direccion
 *
 * @return 		uint8_t	Dirección del esclavo.
 ******************************************************************************/
uint8_t I2C_GetAdress(I2C_Typedef i2c, uint8_t slave_number)
{
	return(Slave_Adress[slave_number][i2c]);
}

/***************************************************************************//**
 * @fn			I2C1_IRQHandler()
 * @brief		Función interrupcion del bus I2C1, se autoejecuta al cambiar el estado del Flag SI, y se actualiza el valor del registro STAT.
 *
 * @return 		void
 ******************************************************************************/
void I2C1_IRQHandler(void)
{
	static uint32_t i=VACIO;

	switch(LPC_I2C1.STAT)
	{
	case I2C_STAT_START:

				LPC_I2C1.DAT=Buffer[I2C1];
				LPC_I2C1.CONCLR=(0x01<<STA);
				LPC_I2C1.CONSET=(0x01<<AA);

		break;
	case I2C_STAT_REPEAT:

				LPC_I2C1.DAT=Buffer[I2C1];
				LPC_I2C1.CONCLR=(0x01<<STA);
				LPC_I2C1.CONSET=(0x01<<AA);

		break;
	case I2C_STAT_WRITE_OK:

				LPC_I2C1.DAT=Data[i][I2C1];
				i++;
				estado[I2C1]=STATE_WRITTING;
				LPC_I2C1.CONSET=(0x01<<AA);

		break;
	case I2C_STAT_WRITE_ERROR:

				LPC_I2C1.CONSET=((0x01<<AA)|(0x01<<STO));
				i=0;
				estado[I2C1]=STATE_STAND_BY;

		break;
	case I2C_STAT_DATA_WRITE:

				if(i==Buffer_Cant[I2C1])
				{
					LPC_I2C1.CONSET=((0x01<<AA)|(0x01<<STO));
					i=0;
					Buffer_Cant[I2C1]=0;
					estado[I2C1]=STATE_STAND_BY;
					I2C_CallBack_Transmiter[I2C1]();

				}else{
					LPC_I2C1.DAT=Data[i][I2C1];
					i++;
					LPC_I2C1.CONSET=(0x01<<AA);
				}
		break;
	case I2C_STAT_DATA_WRITE_ERROR:

				LPC_I2C1.CONSET=((0x01<<AA)|(0x01<<STO));
				i=0;
				estado[I2C1]=STATE_STAND_BY;

		break;
	case I2C_STAT_ARBITRATION_ERROR:

				LPC_I2C1.CONSET=((0x01<<AA)|(0x01<<STA));
				estado[I2C1]=STATE_STAND_BY;

		break;
	case I2C_STAT_READ_OK:

				LPC_I2C1.CONSET=(0x01<<AA);

		break;
	case I2C_STAT_READ_ERROR:

				LPC_I2C1.CONSET=((0x01<<AA)|(0x01<<STO));
				i=0;
				estado[I2C1]=STATE_STAND_BY;

		break;
	case I2C_STAT_DATA_READ:
				if(i==Buffer_Cant[I2C1]-1)
				{
					I2C_CallBack_Receiver[I2C1](LPC_I2C1.DAT);
					LPC_I2C1.CONSET=(0x01<<STO);
					LPC_I2C1.CONCLR=(0x01<<AA);
					i=0;
					Buffer_Cant[I2C1]=0;
					estado[I2C1]=STATE_STAND_BY;
					I2C_Off(I2C1);

				}else{

					I2C_CallBack_Receiver[I2C1](LPC_I2C1.DAT);
					i++;
					LPC_I2C1.CONSET=(0x01<<AA);
					I2C_Off(I2C1);
				}
		break;
	case I2C_STAT_DATA_READ_ERROR:

				I2C_CallBack_Receiver[I2C1](LPC_I2C1.DAT);
				i=0;
				LPC_I2C1.CONSET=((0x01<<AA)|(0x01<<STO));
				estado[I2C1]=STATE_STAND_BY;

		break;
	}
	LPC_I2C1.CONCLR=(0x01<<SI);


	return;
}


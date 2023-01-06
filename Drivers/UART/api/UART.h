/*
 * UART.h
 *
 *  Created on: 15/09/2014
 *      Author: Administrador
 */

#ifndef UART_H_
#define UART_H_

#include "NVIC.h"

/*Define los valores del tipo UART_SOURCE*/
#define UART_0 UART0
#define UART_1 UART1
#define UART_2 UART2
#define UART_3 UART3
/*Define los valores del tipo UART_STATE*/
#define UART_DISABLE	DISABLE
#define UART_ENABLE 	ENABLE
#define UART_NONE_STATE NONE_STATE
/*Define los valores del tipo UART_INTERRUPT_FORCED*/
#define UART_NOT_FORCE	NOT_FORCE
#define	UART_FORCE		FORCE
#define	UART_NONE_FORCE NONE_FORCE
/*Los valores de UART_LEVEL_PRIORITY están en el rango de
 * PRIORITY_0 a PRIORITY_31 (consecutivos) o NONE_PRIORITY para no configurarla*/
/*Vslores standard para el Baudrate, se recomienda usar el formato
 * BVELOCIDAD para estar seguro de que se le configura un valor standard*/
#define B110	110
#define B300	300
#define B600	600
#define	B1200	1200
#define	B2400	2400
#define	B4800	4800
#define	B7200	7200
#define B9600	9600
#define	B19200	19200
#define B38400	38400
#define B57600	57600
#define B115200	115200
#define B230400	230400
#define B460800	460800
#define B921600	921600

#define NONE_INTERRUPT 					( 0x00 )
#define	RBR_INTERRUPT 					( 0x01 )
#define	THRE_INTERRUPT 					( 0x01 << 1 )
#define	RBR_THRE_INTERRUPT 				( RBR_INTERRUPT | THRE_INTERRUPT )
#define	RX_LINE_INTERRUPT 				( 0x01 << 2 )
#define	RBR_RX_LINE_INTERRUPT 			( RBR_INTERRUPT | RX_LINE_INTERRUPT )
#define	THRE_RX_LINE_INTERRUPT 			( THRE_INTERRUPT | RX_LINE_INTERRUPT)
#define	RBR_THRE_RX_LINE_INTERRUPT 		( RBR_INTERRUPT | THRE_INTERRUPT | RX_LINE_INTERRUPT )
#define	END_OF_AUTO_BAUD_INTERRUPT 		( 0x01 << 8 )
#define	TIME_OUT_AUTO_BAUD_INTERRUPT 	( 0x01 << 9 )

typedef INTERRUPT_SOURCE UART_SOURCE;
typedef FUNCTIONAL_STATE UART_STATE;
typedef INTERRUPT_FORCED UART_INTERRUPT_FORCED;
typedef LEVEL_PRIORITY	 UART_LEVEL_PRIORITY;

typedef enum
{
	DATA_BITS_5,
	DATA_BITS_6,
	DATA_BITS_7,
	DATA_BITS_8,
}DATA_BITS;

typedef enum
{
	BITS_DE_PARADA_1,
	BITS_DE_PARADA_2	/*Tener cuidado, cuando los bits de datos son 5,
	 	 	 	 	 	  en lugar de 2 bits de parada se usa 1 y  medio*/
}STOP_BITS;

typedef enum
{
	SIN_PARIDAD = 0,
	PARIDAD_IMPAR = 1,
	PARIDAD_PAR = 3,
	FORCE_1 = 5,
	FORCE_0 = 7
}UART_PARITY;

typedef enum
{
	NO_BREAK,
	BREAK
}BREAK_TRANSMISSION;

typedef enum
{
	UART_CCLK_DIV_4,
	UART_CCLK_DIV_1,
	UART_CCLK_DIV_2,
	UART_CCLK_DIV_8
}UART_CLK_DIV;

typedef enum
{
	BAUD_ERROR,
	NONE_ERRORS,
	UART_VAL_ERROR,
	CLK_DIV_ERROR,
}UART_ERRORS;

typedef struct
{
	UART_STATE estado;
	UART_INTERRUPT_FORCED forced;
	UART_LEVEL_PRIORITY priority;
}UART_INTERRUPT;

typedef struct
{
	UART_INTERRUPT dataInt;
	uint32_t CClk;
	UART_CLK_DIV cclkDiv;
	uint32_t baudRate;
	DATA_BITS dataBits;
	UART_PARITY paridad;
	STOP_BITS stopBits;
	uint32_t uartInterrupts;
}UART_CONFIG;

void
UART_DefaultInit(UART_SOURCE uartX);

UART_ERRORS
UART_Init(UART_SOURCE uartX,
		  UART_CONFIG uartConfig,
		  void (*pRXFunc)(void),
		  void (*pTXFunc)(void));

void
UART_bitsDeDatos(UART_SOURCE uartX,
				 DATA_BITS bits);

void
UART_bitsDeParada(UART_SOURCE uartX,
				  STOP_BITS bits);

void
UART_setParity(UART_SOURCE uartX,
			   UART_PARITY parity);

void
UART_breakTransmission(UART_SOURCE uartX,
					   BREAK_TRANSMISSION state);

MBOOLEAN
UART_setBaudRate(UART_SOURCE uartX,
				 const uint32_t uartFreq,
				 const uint32_t baudRate);

MBOOLEAN
UART_EsTiempoDeProceso(UART_SOURCE uartX);

MBOOLEAN
UART_TransmitirByte(UART_SOURCE uartX,
					uint8_t data);

uint32_t
UART_TransmitirBufferLong(UART_SOURCE uartX,
					  	  uint8_t *datos,
					  	  uint8_t cantDatos);

uint32_t
UART_TransmitirString(UART_SOURCE uartX,
					  char *string);

uint8_t
UART_DatoRecibido(UART_SOURCE uartX);

#endif /* UART_H_ */

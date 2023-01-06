/*
 * UART.c
 *
 *  Created on: 15/09/2014
 *      Author: Administrador
 */

#include "NVIC.h"
#include "GPIO.h"
#include "My_Types.h"
#include "LPC17xx.h"
#include "UART.h"
#include "uSignals.h"

#define TOTAL_UARTS 4
#define STOP_BIT_REG 2
#define PARITY_BIT_REG 3
#define BREAK_CONTROL_REG 6
#define DLAB_REG 7
#define TOTAL_FDR 72
#define RECEIVELINESTATUS 0x06
#define RECEIVEDATAAVAILABLE 0x04
#define CHARACTERTIMEOUTINDICATOR 0X0C
#define THREINTERRUPT 0x02
#define RECEIVERDATAREADY 0x01
#define OVERRUNERROR 0x02
#define BREAKINTERRUPT (0x01 << 4)
#define UART_VALIDA(x) ((x>=UART_0 && x<=UART_3)?(TRUE):(FALSE))
#define MAX_DAT 200 //esto puede ser cualquier valor

typedef union
{
	uint16_t 	valor;
	struct
	{
		uint8_t LSB;
		uint8_t MSB;
	} DVAL;
}UART_DL;

typedef union
{
	uint8_t FDR_VAL;
	struct
	{
		uint32_t FDR_DIV:4;
		uint32_t FDR_MUL:4;
	} FDR_PARSE;
}UART_DIV;

typedef enum
{
	INT_UART_0,
	INT_UART_1,
	INT_UART_2,
	INT_UART_3
}INT_UART;

typedef enum
{
	PROC_NORMAL,
	PROC_SATURADO,
	PROC_ERROR
}STATUS_PROCESS;

typedef enum
{
	TX,
	RX,
	TX_RX_SEL
}UART_FLOW;

static registro_t *UNLCR[TOTAL_UARTS] = {U0LCR,
										 U1LCR,
										 U2LCR,
										 U3LCR};

static registro_t *UNDLL[TOTAL_UARTS] = {U0DLL,
										 U1DLL,
										 U2DLL,
										 U3DLL};

static registro_t *UNDLM[TOTAL_UARTS] = {U0DLM,
									   	 U1DLM,
									   	 U2DLM,
									   	 U3DLM};

static registro_t *UNIER[TOTAL_UARTS] = {U0IER,
									   	 U1IER,
									   	 U2IER,
									   	 U3IER};

static registro_t *UNTHR[TOTAL_UARTS] = {U0THR,
									   	 U1THR,
									   	 U2THR,
									   	 U3THR};

static registro_t *UNFDR[TOTAL_UARTS] = {U0FDR,
										 U1FDR,
										 U2FDR,
										 U3FDR};

static registro_t *UNFCR[TOTAL_UARTS] = {U0FCR,
										 U1FCR,
										 U2FCR,
										 U3FCR};

const uint8_t TAB_DIV[TOTAL_FDR] =
{
		0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 3, 2, 3,
		1, 4, 3, 2, 3, 4, 1, 5, 4, 3, 5, 2, 5, 3, 4, 5, 6, 7,
		1, 8, 7, 6, 5, 4, 7, 3, 8, 5, 7, 9, 2, 9, 7, 5, 8, 11,
		3, 10, 7, 11, 4, 9, 5, 11, 6, 13, 7, 8, 9, 10, 11, 12, 13, 14
};

const uint8_t TAB_MUL[TOTAL_FDR] =
{
		1, 15, 14, 13, 12, 11, 10, 9, 8, 15, 7, 13, 6, 11, 5, 14, 9, 13,
		4, 15, 11, 7, 10, 13, 3, 14, 11, 8, 13, 5, 12, 7, 9, 11, 13, 15,
		2, 15, 13, 11, 9, 7, 12, 5, 13, 8, 11, 14, 3, 13, 10, 7, 11, 15,
		4, 13, 9, 14, 5, 11, 6, 13, 7, 15, 8, 9, 10, 11, 12, 13, 14, 15
};

const float TAB_FDR[TOTAL_FDR] =
{
		1.000, 1.067, 1.071, 1.077, 1.083, 1.091, 1.100, 1.111, 1.125,
		1.133, 1.143, 1.154, 1.167, 1.182, 1.200, 1.214, 1.222, 1.231,
		1.250, 1.267, 1.273, 1.286, 1.300, 1.308, 1.333, 1.357, 1.364,
		1.375, 1.385, 1.400, 1.417, 1.429, 1.444, 1.455, 1.462, 1.467,
		1.500, 1.533, 1.538, 1.545, 1.556, 1.571, 1.583, 1.600, 1.615,
		1.625, 1.636, 1.643, 1.667, 1.692, 1.700, 1.714, 1.727, 1.733,
		1.750, 1.769, 1.778, 1.786, 1.800, 1.818, 1.833, 1.846, 1.857,
		1.867, 1.875, 1.889, 1.900, 1.909, 1.917, 1.923, 1.929, 1.933
};

static volatile uint32_t uartPClk[TOTAL_UARTS] = {0,0,0,0};
void (*callbackRXUART0)(void) = NULL;
void (*callbackRXUART1)(void) = NULL;
void (*callbackRXUART2)(void) = NULL;
void (*callbackRXUART3)(void) = NULL;
void (*callbackTXUART0)(void) = NULL;
void (*callbackTXUART1)(void) = NULL;
void (*callbackTXUART2)(void) = NULL;
void (*callbackTXUART3)(void) = NULL;

static volatile uint8_t bufferTrama[TOTAL_UARTS][TX_RX_SEL][MAX_DAT];
static volatile uint8_t currDatIng[TOTAL_UARTS][TX_RX_SEL];
static volatile uint8_t currDatEgr[TOTAL_UARTS][TX_RX_SEL];
static volatile MBOOLEAN tiempoDeProcesar[TOTAL_UARTS][TX_RX_SEL];
static volatile STATUS_PROCESS statusProcess[TOTAL_UARTS][TX_RX_SEL];

/*
 * void ingresarDato(uint32_t bufferTx_O_bufferRx, uint8_t dato);
 * */

void
ingresarDato(UART_SOURCE uartX,
			 UART_FLOW flujoRxTx,
			 uint8_t dato);

volatile uint8_t
egresarDato(UART_SOURCE uartX,
			UART_FLOW flujoRxTx);

MBOOLEAN
esTiempoDeProcesar(UART_SOURCE uartX,
				   UART_FLOW flujoRxTx);

void
UART_DefaultInit(UART_SOURCE uartX)
{
	UART_CONFIG configUart;

	configUart.dataInt.estado = UART_ENABLE;
	configUart.cclkDiv = UART_CCLK_DIV_4;
	configUart.baudRate = B9600;
	configUart.CClk = 100 MHz;
	configUart.dataBits = DATA_BITS_8;
	configUart.paridad = SIN_PARIDAD;
	configUart.stopBits = BITS_DE_PARADA_1;
	configUart.uartInterrupts = RBR_THRE_RX_LINE_INTERRUPT;

	UART_Init(uartX,configUart,NULL,NULL);
}

UART_ERRORS
UART_Init(UART_SOURCE uartX,
		  UART_CONFIG uartConfig,
		  void (*pRXFunc)(void),
		  void (*pTXFunc)(void))
{
	volatile uint32_t uartPClkAux;
	uint32_t clriter;

	if(UART_VALIDA(uartX) == TRUE)
	{
		(*(UNLCR[uartX-UART_0])) &= ~(0x01UL << DLAB_REG);

		NVIC_Setting(uartX,(uartConfig.dataInt.estado),(uartConfig.dataInt.forced),(uartConfig.dataInt.priority));

		(*(UNIER[uartX-UART_0])) = uartConfig.uartInterrupts;
		(*(UNFCR[uartX-UART_0])) = 0x07; //habilita la UART, resetea los registros y configura que el RX se active con un solo dato

		switch((uartConfig.cclkDiv))
		{
			case UART_CCLK_DIV_4:
				uartPClkAux = ((uartConfig.CClk)/4);
				break;
			case UART_CCLK_DIV_1:
				uartPClkAux = (uartConfig.CClk);
				break;
			case UART_CCLK_DIV_2:
				uartPClkAux = ((uartConfig.CClk)/2);
				break;
			case UART_CCLK_DIV_8:
				uartPClkAux = ((uartConfig.CClk)/8);
				break;
			default:
				uartPClkAux = 0;
				return CLK_DIV_ERROR;
				break;
		}

		switch (uartX)
		{
			case UART_0:
				PCONP |= (0x01 << 3);
				uartPClk[0] = uartPClkAux;
				PCLKSEL0 &= ~(0x03 << 6);
				PCLKSEL0 |= ((uartConfig.cclkDiv) << 6);
				GPIO_SetPinFunc(uSignals_GetPortNum(nTX0),uSignals_GetPinNum(nTX0),FIRST_ALT_FUNC);
				GPIO_SetPinFunc(uSignals_GetPortNum(nRX0),uSignals_GetPinNum(nRX0),FIRST_ALT_FUNC);
				GPIO_SetResistorMode(uSignals_GetPortNum(nTX0),uSignals_GetPinNum(nTX0),RES_NONE);
				GPIO_SetResistorMode(uSignals_GetPortNum(nRX0),uSignals_GetPinNum(nRX0),RES_NONE);
				callbackRXUART0 = pRXFunc;
				callbackTXUART0 = pTXFunc;
				if((UART_setBaudRate(UART_0,uartPClk[0],uartConfig.baudRate)) == FALSE)
				{
					return BAUD_ERROR;
				}
				break;
			case UART_1:
				PCONP |= (0x01 << 4);
				uartPClk[1] = uartPClkAux;
				PCLKSEL0 &= ~(0x03 << 8);
				PCLKSEL0 |= ((uartConfig.cclkDiv) << 8);
				GPIO_SetPinFunc(uSignals_GetPortNum(nTX1),uSignals_GetPinNum(nTX1),FIRST_ALT_FUNC);
				GPIO_SetPinFunc(uSignals_GetPortNum(nRX1),uSignals_GetPinNum(nRX1),FIRST_ALT_FUNC);
				GPIO_SetResistorMode(uSignals_GetPortNum(nTX1),uSignals_GetPinNum(nTX1),RES_NONE);
				GPIO_SetResistorMode(uSignals_GetPortNum(nRX1),uSignals_GetPinNum(nRX1),RES_NONE);
				callbackRXUART1 = pRXFunc;
				callbackTXUART1 = pTXFunc;
				if((UART_setBaudRate(UART_1,uartPClk[1],uartConfig.baudRate)) == FALSE)
				{
					return BAUD_ERROR;
				}
				break;
			case UART_2:
				PCONP |= (0x01 << 24);
				uartPClk[2] = uartPClkAux;
				PCLKSEL1 &= ~(0x03 << 16);
				PCLKSEL1 |= ((uartConfig.cclkDiv) << 16);
				GPIO_SetPinFunc(PORT_2,PIN_8,SECOND_ALT_FUNC);
				GPIO_SetPinFunc(PORT_2,PIN_9,SECOND_ALT_FUNC);
				GPIO_SetResistorMode(PORT_2,PIN_8,RES_NONE);
				GPIO_SetResistorMode(PORT_2,PIN_9,RES_NONE);
				callbackRXUART2 = pRXFunc;
				callbackTXUART2 = pTXFunc;
				if((UART_setBaudRate(UART_2,uartPClk[2],uartConfig.baudRate)) == FALSE)
				{
					return BAUD_ERROR;
				}
				break;
			default:
				PCONP |= (0x01 << 25);
				uartPClk[3] = uartPClkAux;
				PCLKSEL1 &= ~(0x03 << 18);
				PCLKSEL1 |= ((uartConfig.cclkDiv) << 18);
				GPIO_SetPinFunc(PORT_4,PIN_28,THIRD_ALT_FUNC);
				GPIO_SetPinFunc(PORT_4,PIN_29,THIRD_ALT_FUNC);
				GPIO_SetResistorMode(PORT_4,PIN_28,RES_NONE);
				GPIO_SetResistorMode(PORT_4,PIN_29,RES_NONE);
				callbackRXUART3 = pRXFunc;
				callbackTXUART3 = pTXFunc;
				if((UART_setBaudRate(UART_3,uartPClk[3],uartConfig.baudRate)) == FALSE)
				{
					return BAUD_ERROR;
				}
				break;
		}
		UART_bitsDeDatos(uartX, uartConfig.dataBits);
		UART_setParity(uartX, uartConfig.paridad);
		UART_bitsDeParada(uartX,uartConfig.stopBits);
		for(clriter = 0; clriter < MAX_DAT; clriter++)
		{
			bufferTrama[uartX - UART_0][TX][clriter] = 0x00;
			bufferTrama[uartX - UART_0][RX][clriter] = 0x00;
		}
		currDatIng[uartX - UART_0][TX] = 0x00;
		currDatIng[uartX - UART_0][RX] = 0x00;
		currDatEgr[uartX - UART_0][TX] = 0x00;
		currDatEgr[uartX - UART_0][RX] = 0x00;
		tiempoDeProcesar[uartX - UART_0][TX] = FALSE;
		tiempoDeProcesar[uartX - UART_0][RX] = FALSE;
		statusProcess[uartX - UART_0][TX] = PROC_NORMAL;
		statusProcess[uartX - UART_0][RX] = PROC_NORMAL;
	}
	else
	{
		return UART_VAL_ERROR;
	}

	return NONE_ERRORS;
}

void
UART_bitsDeDatos(UART_SOURCE uartX,
				 DATA_BITS bits)
{
	(*(UNLCR[uartX-UART_0])) &= ~(( uint32_t )0x03UL);
	(*(UNLCR[uartX-UART_0])) |= bits;
}

void
UART_bitsDeParada(UART_SOURCE uartX,
				  STOP_BITS bits)
{
	(*(UNLCR[uartX-UART_0])) &= ~(( uint32_t )( 0x01UL << STOP_BIT_REG ));
	(*(UNLCR[uartX-UART_0])) |= (bits << STOP_BIT_REG);
}

void
UART_setParity(UART_SOURCE uartX,
			   UART_PARITY parity)
{
	(*(UNLCR[uartX-UART_0])) &= ~(( uint32_t )( 0x07UL << PARITY_BIT_REG ));
	(*(UNLCR[uartX-UART_0])) |= (parity << PARITY_BIT_REG);
}

void
UART_breakTransmission(UART_SOURCE uartX,
					   BREAK_TRANSMISSION state)
{
	if(state <= BREAK)
	{
		(*(UNLCR[uartX-UART_0])) &= ~(( uint32_t )( 0x01UL << BREAK_CONTROL_REG ));
		(*(UNLCR[uartX-UART_0])) |= (state << BREAK_CONTROL_REG);
	}
}

MBOOLEAN
UART_setBaudRate(UART_SOURCE uartX,
				 const uint32_t uartFreq,
				 const uint32_t baudRate)
{
	UART_DL config;
	UART_DIV fineConfig;
	volatile uint32_t valorAux;
	MBOOLEAN configurado = TRUE;
	int32_t fdrIter = (TOTAL_FDR/2);
	uint32_t fdrcount = 0;
	float baudRateAux;
	float errorBaud;
	float fr;
	static uint32_t clkFreq = 100000000;

	if(uartFreq != 0)
	{
		clkFreq = uartFreq;
	}
	else
	{
		clkFreq = uartPClk[uartX-UART_0];
	}

	(*(UNLCR[uartX-UART_0])) |= (0x01UL << DLAB_REG);
	if((valorAux = clkFreq/(16 * baudRate)) == 0)
	{
		/*El valor de clk es muy bajo para este baudRate*/
		return FALSE;
	}

	config.valor = ( uint16_t ) valorAux;

	if(((clkFreq)%(16*baudRate)) == 0)
	{
		fineConfig.FDR_PARSE.FDR_DIV = 0;
		fineConfig.FDR_PARSE.FDR_MUL = 1;
	}
	else
	{
		baudRateAux = ((float) clkFreq)/((float)(16*valorAux));
		if(baudRateAux > ((float) baudRate))
		{
			errorBaud = baudRateAux - ((float) baudRate);
		}
		else
		{
			errorBaud = ((float) baudRate) - baudRateAux;
		}

		fineConfig.FDR_PARSE.FDR_DIV = 0;
		fineConfig.FDR_PARSE.FDR_MUL = 1;

		while( ( (errorBaud/((float) baudRate) ) >= 0.011) && ( TRUE == configurado ) )
		{
			if( ( fdrIter < TOTAL_FDR ) && fdrIter >= 0)
			{
				valorAux = clkFreq/((uint32_t)(((float)16) * ((float)baudRate) * TAB_FDR[fdrIter]));
			}
			else
			{
				fineConfig.FDR_PARSE.FDR_DIV = 0;
				fineConfig.FDR_PARSE.FDR_MUL = 1;
				configurado = FALSE;
			}

			fr = clkFreq/(((float)16) * ((float)baudRate) * valorAux);

			if(fr > 1.933)
			{
				if(fdrIter > 0)
				{
					fdrIter--;
				}
				else
				{
					fineConfig.FDR_PARSE.FDR_DIV = 0;
					fineConfig.FDR_PARSE.FDR_MUL = 1;
					configurado = FALSE;
				}
			}
			else
			{
				if(fr < 1.000)
				{
					if(fdrIter < TOTAL_FDR-1)
					{
						fdrIter++;
					}
					else
					{
						fineConfig.FDR_PARSE.FDR_DIV = 0;
						fineConfig.FDR_PARSE.FDR_MUL = 1;
						configurado = FALSE;
					}
				}
				else
				{
					for(fdrcount = 0; (fdrcount < (TOTAL_FDR-1)); fdrcount++)
					{
						if(fr >= TAB_FDR[fdrcount] && fr <= TAB_FDR[fdrcount+1])
						{
							if((fr - TAB_FDR[fdrcount]) > TAB_FDR[fdrcount+1] - fr)
							{
								fineConfig.FDR_PARSE.FDR_DIV = TAB_DIV[fdrcount+1];
								fineConfig.FDR_PARSE.FDR_MUL = TAB_MUL[fdrcount+1];
							}
							else
							{
								fineConfig.FDR_PARSE.FDR_DIV = TAB_DIV[fdrcount];
								fineConfig.FDR_PARSE.FDR_MUL = TAB_MUL[fdrcount];

								if(0 == fdrcount)
								{
									configurado = FALSE;
								}
							}
							config.valor = ( uint16_t ) valorAux;
						}
					}

					baudRateAux = ((float) clkFreq)/(((float)(16*config.valor))*(1+(((float)(fineConfig.FDR_PARSE.FDR_DIV))/(float)(fineConfig.FDR_PARSE.FDR_MUL))));
					if(baudRateAux > ((float) baudRate))
					{
						errorBaud = baudRateAux - ((float) baudRate);
					}
					else
					{
						errorBaud = ((float) baudRate) - baudRateAux;
					}
					if(fdrIter < (TOTAL_FDR/2))
					{
						fdrIter--;
					}
					else
					{
						fdrIter++;
					}
				}
			}
		}
	}

	(*(UNDLL[uartX-UART_0])) = config.DVAL.LSB;
	(*(UNDLM[uartX-UART_0])) = config.DVAL.MSB;
	(*(UNFDR[uartX-UART_0])) = fineConfig.FDR_VAL;

	(*(UNLCR[uartX-UART_0])) &= ~(0x01UL << DLAB_REG);

	return configurado;
}

void
UART0_IRQHandler(void)
{
	uint32_t auxIIR = ((uint32_t) U0IIR);

	while((auxIIR & 0x01) == 0x00)
	{
		switch((auxIIR & 0x0E))
		{
			case RECEIVELINESTATUS:
				/*if(U0LSR & RECEIVERDATAREADY)
				{
					Si se usa fifo completar
				}*/
				/*if(U0LSR & OVERRUNERROR)
				{
					Aviso de trama fallida.
				}
				*/
				/*if(U0LSR & BREAKINTERRUPT)
				{
					reiniciarTrama();
				}*/
				break;
			case RECEIVEDATAAVAILABLE:
				if(callbackRXUART0 != NULL)
				{
					callbackRXUART0();
				}
				else
				{
					if(currDatIng[INT_UART_0][RX] < (MAX_DAT-1))
					{
						currDatIng[INT_UART_0][RX]++;
					}
					else
					{
						currDatIng[INT_UART_0][RX] = 0;
					}

					bufferTrama[INT_UART_0][RX][currDatIng[INT_UART_0][RX]] = ( volatile uint8_t )(*( U0RBR ));
				}
				break;
			case CHARACTERTIMEOUTINDICATOR:
				/*Completar si se usa fifo*/
				break;
			case THREINTERRUPT:
				break;
			default:
				break;
		}

		auxIIR = ((uint32_t) U0IIR);
	}
}

void
UART1_IRQHandler(void)
{
	uint32_t auxIIR = ((uint32_t) U1IIR);

	while((auxIIR & 0x01) == 0x00)
	{
		switch((auxIIR & 0x0E))
		{
			case RECEIVELINESTATUS:
				/*if(U0LSR & RECEIVERDATAREADY)
				{
					Si se usa fifo completar
				}*/
				/*if(U0LSR & OVERRUNERROR)
				{
					Aviso de trama fallida.
				}
				*/
				/*if(U0LSR & BREAKINTERRUPT)
				{
					stopTrama();
				}*/
				break;
			case RECEIVEDATAAVAILABLE:
				if(callbackRXUART1 != NULL)
				{
					callbackRXUART1();
				}
				else
				{
					ingresarDato(UART_1,RX,( volatile uint8_t )(*( U1RBR )));
				}
				break;
			case CHARACTERTIMEOUTINDICATOR:
				/*Completar si se usa fifo*/
				break;
			case THREINTERRUPT:
				(*U1THR) = egresarDato(UART_1, TX);
				break;
			default:
				break;
		}

		auxIIR = ((uint32_t) U1IIR);
	}
}

void
ingresarDato(UART_SOURCE uartX,
			 UART_FLOW flujoRxTx,
			 volatile uint8_t dato)
{
	if( flujoRxTx == TX )
	{
		if((((*U1LSR) >> 0x06) & 0x01) == 0x01)
		{
			(*(UNTHR[uartX - UART_0])) = dato;
			return;
		}
	}

	if(currDatIng[uartX - UART_0][flujoRxTx] == currDatEgr[uartX - UART_0][flujoRxTx])
	{
		if(tiempoDeProcesar[uartX - UART_0][flujoRxTx] != TRUE)
		{
			tiempoDeProcesar[uartX - UART_0][flujoRxTx] = TRUE;
			statusProcess[uartX - UART_0][flujoRxTx] = PROC_NORMAL;
		}
		else
		{
			if(flujoRxTx == TX)
			{
				statusProcess[uartX - UART_0][TX] = PROC_SATURADO;
			}
			else
			{
				statusProcess[uartX - UART_0][RX] = PROC_ERROR;
			}

			return;
		}
	}
	else
	{
		statusProcess[uartX - UART_0][flujoRxTx] = PROC_NORMAL;
	}

	if(currDatIng[uartX - UART_0][flujoRxTx] < (MAX_DAT-1))
	{
		currDatIng[uartX - UART_0][flujoRxTx]++;
	}
	else
	{
		currDatIng[uartX - UART_0][flujoRxTx] = 0;
	}

	bufferTrama[uartX - UART_0][flujoRxTx][currDatIng[uartX - UART_0][flujoRxTx]] = dato;
}

volatile uint8_t
egresarDato(UART_SOURCE uartX,
			UART_FLOW flujoRxTx)
{
	volatile uint8_t dato = 0x00;

	if(esTiempoDeProcesar(uartX,flujoRxTx) == TRUE)
	{
		if(currDatEgr[uartX - UART_0][flujoRxTx] < (MAX_DAT-1))
		{
			currDatEgr[uartX - UART_0][flujoRxTx]++;
		}
		else
		{
			currDatEgr[uartX - UART_0][flujoRxTx] = 0;
		}

		dato = bufferTrama[uartX - UART_0][flujoRxTx][currDatEgr[uartX - UART_0][flujoRxTx]];

		if(currDatEgr[uartX - UART_0][flujoRxTx] == currDatIng[uartX - UART_0][flujoRxTx])
		{
			tiempoDeProcesar[uartX - UART_0][flujoRxTx] = FALSE;
		}
	}

	return dato;
}

MBOOLEAN
esTiempoDeProcesar(UART_SOURCE uartX,
				   UART_FLOW flujoRxTx)
{
	return tiempoDeProcesar[uartX - UART_0][flujoRxTx];
}

volatile STATUS_PROCESS
ingresoDisponible(UART_SOURCE uartX,
				  UART_FLOW flujoRxTx)
{
	return (statusProcess[uartX - UART_0][flujoRxTx]);
}

MBOOLEAN
UART_TransmitirByte(UART_SOURCE uartX,
					uint8_t data)
{
	MBOOLEAN seraEnviado;

	ingresarDato(uartX, TX, data);

	if(PROC_SATURADO == ingresoDisponible(uartX,TX))
	{
		seraEnviado = FALSE;
	}
	else
	{
		seraEnviado = TRUE;
	}

	return seraEnviado;
}

uint32_t
UART_TransmitirBufferLong(UART_SOURCE uartX,
					  	  uint8_t *datos,
					  	  uint8_t cantDatos)
{
	uint32_t i;
	MBOOLEAN transmited = TRUE;

	for(i = 0; ((i < cantDatos) && (TRUE == transmited)) ; i++)
	{
		transmited = UART_TransmitirByte(uartX,datos[i]);
	}

	return i;
}

uint32_t
UART_TransmitirString(UART_SOURCE uartX,
					  char *string)
{
	uint32_t i;
	MBOOLEAN transmited = TRUE;

	for(i = 0; ((string[i] != 0x00) && (TRUE == transmited)) ; i++)
	{
		transmited = UART_TransmitirByte(uartX,(uint8_t)string[i]);
	}

	return i;
}

MBOOLEAN
UART_EsTiempoDeProceso(UART_SOURCE uartX)
{
	return esTiempoDeProcesar(uartX, RX);
}

uint8_t
UART_DatoRecibido(UART_SOURCE uartX)
{
	return (uint8_t) (egresarDato(uartX,RX));
}


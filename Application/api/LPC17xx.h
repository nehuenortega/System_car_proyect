/*
 * LPC1769.h
 */

#ifndef LPC1769_H_
#define LPC1769_H_

#include <stdint.h>

#define     __I     volatile const     /*!< defines 'read only' permissions                 */
#define     __O     volatile           /*!< defines 'write only' permissions                */
#define     __IO    volatile           /*!< defines 'read / write' permissions              */


/******************************************************************************/
/*                Device Specific Peripheral registers structures             */
/******************************************************************************/


/*------------- System Control (SC) ------------------------------------------*/
#define FLASHCFG	(*((uint32_t *)0x400FC000UL)) 	/* Flash access configuration */
#define PLL0CON		(*((uint32_t *)0x400FC080UL))	/* Registro de control del PLL0	*/
#define	PLL0CFG		(*((uint32_t *)0x400FC084UL))	/* Registro de configuracion del PLL0 */
#define	PLL0STAT	(*((uint32_t *)0x400FC088UL))	/* Registro de estado del PLL0 */
#define	PLL0FEED	(*((uint32_t *)0x400FC08CUL))	/* Registro de control del PLL0 */
#define	PLL1CON		(*((uint32_t *)0x400FC0A0UL))	/* Registro de control del PLL1 */
#define	PLL1CFG		(*((uint32_t *)0x400FC0A4UL))	/* Registro de configuracion del PLL1 */
#define	PLL1STAT	(*((uint32_t *)0x400FC0A8UL))	/* Registro de estado del PLL1 */
#define	PLL1FEED	(*((uint32_t *)0x400FC0ACUL))	/* Registro de control del PLL1 */
#define PCONP	    (*((uint32_t *)0x400FC0C4UL))	/* Registro de Control de Alimentación de Periféricos */
#define CCLKCFG		(*((uint32_t *)0x400FC104UL))	/* Registro de configuracion del clock */
#define USBCLKCFG	(*((uint32_t *)0x400FC108UL))	/* Registro de Configuración de Clock de USB */
#define CLKSRCSEL	(*((uint32_t *)0x400FC10CUL))	/* Registro de seleccion del clock */
#define SCS			(*((uint32_t *)0x400FC1A0UL))	/* Registro de control de sistema y registro de status */
#define PCLKSEL0	(*((uint32_t *)0x400FC1A8UL))	/* Registro de Selección de Clock de Periféricos 0 */
#define PCLKSEL1	(*((uint32_t *)0x400FC1ACUL))	/* Registro de Selección de Clock de Periféricos 1 */
#define CLKOUTCFG	(*((uint32_t *)0x400FC1C8UL))	/* Registro de Configuración de Salida de Clock */


/*------------- Pin Connect Block (PINCON) -----------------------------------*/
typedef struct
{
  __IO uint32_t PINSEL0;
  __IO uint32_t PINSEL1;
  __IO uint32_t PINSEL2;
  __IO uint32_t PINSEL3;
  __IO uint32_t PINSEL4;
  __IO uint32_t PINSEL5;
  __IO uint32_t PINSEL6;
  __IO uint32_t PINSEL7;
  __IO uint32_t PINSEL8;
  __IO uint32_t PINSEL9;
  __IO uint32_t PINSEL10;
       uint32_t RESERVED0[5];
  __IO uint32_t PINMODE0;
  __IO uint32_t PINMODE1;
  __IO uint32_t PINMODE2;
  __IO uint32_t PINMODE3;
  __IO uint32_t PINMODE4;
  __IO uint32_t PINMODE5;
  __IO uint32_t PINMODE6;
  __IO uint32_t PINMODE7;
  __IO uint32_t PINMODE8;
  __IO uint32_t PINMODE9;
  __IO uint32_t PINMODE_OD0;
  __IO uint32_t PINMODE_OD1;
  __IO uint32_t PINMODE_OD2;
  __IO uint32_t PINMODE_OD3;
  __IO uint32_t PINMODE_OD4;
  __IO uint32_t I2CPADCFG;
} LPC_PINCON_TypeDef;

/*------------- General Purpose Input/Output (GPIO) --------------------------*/
typedef struct
{
  __IO uint32_t FIODIR;
  	   uint32_t RESERVED0[3];
  __IO uint32_t FIOMASK;
  __IO uint32_t FIOPIN;
  __IO uint32_t FIOSET;
  __O  uint32_t FIOCLR;
} LPC_GPIO_TypeDef;

typedef struct
{
  __I  uint32_t IntStatus;
  __I  uint32_t IO0IntStatR;
  __I  uint32_t IO0IntStatF;
  __O  uint32_t IO0IntClr;
  __IO uint32_t IO0IntEnR;
  __IO uint32_t IO0IntEnF;
       uint32_t RESERVED0[3];
  __I  uint32_t IO2IntStatR;
  __I  uint32_t IO2IntStatF;
  __O  uint32_t IO2IntClr;
  __IO uint32_t IO2IntEnR;
  __IO uint32_t IO2IntEnF;
} LPC_GPIOINT_TypeDef;

typedef struct
{
  __I uint32_t INTSTATR;
  __I uint32_t INTSTATF;
  __IO uint32_t INTCLR;
  __IO uint32_t INTENR;
  __IO  uint32_t INTENF;
} LPC_GPIO_INT_TypeDef;


/*------------- External Interrupt (EINT) --------------------------------------------------*/

#define EXTINT		(*((uint32_t *)0x400FC140UL)) 	/* EINT Flags */
#define EXTMODE		(*((uint32_t *)0x400FC148UL)) 	/* EINT Mode */
#define EXTPOLAR	(*((uint32_t *)0x400FC14CUL)) 	/* EINT Polarity Mode */


/*------------- Interrupt's Vector (NVIC) --------------------------------------------------*/

#define ISER0		(*((uint32_t *)0xE000E100UL))	/*		Interrupt set-enable register		*/
#define ISER1		(*((uint32_t *)0xE000E104UL))	/*		Interrupt set-enable register		*/

#define ICER0		(*((uint32_t *)0xE000E180UL))	/*		Interrupt clear-enable register		*/
#define ICER1		(*((uint32_t *)0xE000E184UL))	/*		Interrupt clear-enable register		*/

#define ISPR0		(*((uint32_t *)0xE000E200UL))	/*		Interrupt set-pending register		*/
#define ISPR1		(*((uint32_t *)0xE000E204UL))	/*		Interrupt set-pending register		*/

#define ICPR0		(*((uint32_t *)0xE000E280UL))	/*		Interrupt clear-pending register	*/
#define ICPR1		(*((uint32_t *)0xE000E284UL))	/*		Interrupt clear-pending register	*/

#define IABR0		(*((uint32_t *)0xE000E300UL))	/*		Interrupt active bit registers		*/
#define IABR1		(*((uint32_t *)0xE000E304UL))	/*		Interrupt active bit registers		*/

#define IPR0		(*((uint32_t *)0xE000E100UL))	/*		Interrupt priority registers		*/

/*------------- System Tick Timer (SYSTICKTMR) --------------------------------------------------*/

typedef struct {
	 __IO uint32_t STCTRL;
	 __IO uint32_t STRELOAD;
	 __IO uint32_t STCURR;
	 __IO uint32_t STCALIB;
}LPC_SYSTICKTMR_Typedef;

#define SYSTICK_TMR	((LPC_SYSTICKTMR_Typedef *) 0xE000E010UL)

/*------------- Timer (TIM) --------------------------------------------------*/

typedef struct {
	 __IO uint32_t IR;
	 __IO uint32_t TCR;
	 __I uint32_t TC;
	 __IO uint32_t PR;
	 __I uint32_t PC;
	 __IO uint32_t MCR;
	 __IO uint32_t MR0;
	 __IO uint32_t MR1;
	 __IO uint32_t MR2;
	 __IO uint32_t MR3;
	 __IO uint32_t CCR;
	 __I uint32_t CR0;
	 __I uint32_t CR1;
     uint32_t RESERVED0[2];
	 __IO uint32_t EMR;
     uint32_t RESERVED1[12];
	 __IO uint32_t CTCR;
}LPC_TMR_Typedef;

#define LPC_TMR0             ((LPC_TMR_Typedef      *) 0x40004000UL    )
#define LPC_TMR1             ((LPC_TMR_Typedef      *) 0x40008000UL    )
#define LPC_TMR2             ((LPC_TMR_Typedef      *) 0x40090000UL    )
#define LPC_TMR3             ((LPC_TMR_Typedef      *) 0x40094000UL    )

/*------------- Pulse-Width Modulation (PWM) ---------------------------------*/

/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/

typedef struct
{
  union {
  __I  uint8_t  RBR;
  __O  uint8_t  THR;
  __IO uint8_t  DLL;
       uint32_t RESERVED0;
  };
  union {
  __IO uint8_t  DLM;
  __IO uint32_t IER;
  };
  union {
  __I  uint32_t IIR;
  __O  uint8_t  FCR;
  };
  __IO uint8_t  LCR;
       uint8_t  RESERVED1[3];
  __IO uint8_t  MCR;
       uint8_t  RESERVED2[3];
  __I  uint8_t  LSR;
       uint8_t  RESERVED3[3];
  __I  uint8_t  MSR;
       uint8_t  RESERVED4[3];
  __IO uint8_t  SCR;
       uint8_t  RESERVED5[3];
  __IO uint32_t ACR;
       uint32_t RESERVED6;
  __IO uint32_t FDR;
       uint32_t RESERVED7;
  __IO uint8_t  TER;
       uint8_t  RESERVED8[27];
  __IO uint8_t  RS485CTRL;
       uint8_t  RESERVED9[3];
  __IO uint8_t  ADRMATCH;
       uint8_t  RESERVED10[3];
  __IO uint8_t  RS485DLY;
       uint8_t  RESERVED11[3];
  __IO uint32_t FIFOLVL;
} LPC_UART1_TypeDef;

#define LPC_UART1             ((LPC_UART1_TypeDef     *) 0x40010000UL    )

/*------------- Serial Peripheral Interface (SPI) ----------------------------*/

/*------------- Synchronous Serial Communication (SSP) -----------------------*/

/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/

typedef struct {
	 __IO uint32_t CONSET;
	 __I uint32_t STAT;
	 __IO uint32_t DAT;
	 __IO uint32_t ADR0;
	 __IO uint32_t SCLH;
	 __IO uint32_t SCLL;
	 __IO uint32_t CONCLR;
	 __IO uint32_t MMCTRL;
	 __IO uint32_t ADR1;
	 __IO uint32_t ADR2;
	 __IO uint32_t ADR3;
	 __IO uint32_t DATA_BUFFER;
	 __IO uint32_t MASK0;
	 __IO uint32_t MASK1;
	 __IO uint32_t MASK2;
	 __IO uint32_t MASK3;
}LPC_I2C_Typedef;

#define LPC_I2C0             (*(LPC_I2C_Typedef      *) 0x4001C000UL    )
#define LPC_I2C1             (*(LPC_I2C_Typedef      *) 0x4005C000UL    )
#define LPC_I2C2             (*(LPC_I2C_Typedef      *) 0x400A0000UL    )

/*------------- Inter IC Sound (I2S) -----------------------------------------*/

/*------------- Repetitive Interrupt Timer (RIT) -----------------------------*/

/*------------- Real-Time Clock (RTC) ----------------------------------------*/

/*------------- Watchdog Timer (WDT) -----------------------------------------*/

/*------------- Analog-to-Digital Converter (ADC) ----------------------------*/

/*------------- Digital-to-Analog Converter (DAC) ----------------------------*/

/*------------- Motor Control Pulse-Width Modulation (MCPWM) -----------------*/

/*------------- Quadrature Encoder Interface (QEI) ---------------------------*/

/*------------- Controller Area Network (CAN) --------------------------------*/

/*------------- General Purpose Direct Memory Access (GPDMA) -----------------*/

/*------------- Universal Serial Bus (USB) -----------------------------------*/

/*------------- Ethernet Media Access Controller (EMAC) ----------------------*/



/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/
#define LPC_GPIO_BASE         (0x2009C000UL)
#define LPC_GPIO0             ((LPC_GPIO_TypeDef      *) 0x2009C000UL    )
#define LPC_GPIO1             ((LPC_GPIO_TypeDef      *) 0x2009C020UL    )
#define LPC_GPIO2             ((LPC_GPIO_TypeDef      *) 0x2009C040UL    )
#define LPC_GPIO3             ((LPC_GPIO_TypeDef      *) 0x2009C060UL    )
#define LPC_GPIO4             ((LPC_GPIO_TypeDef      *) 0x2009C080UL    )
#define LPC_PINCON            ((LPC_PINCON_TypeDef    *) 0x4002C000UL    )

/*                     INTERRUPT                                              */

#define INT_STATUS			  ((uint32_t              *) 0x40028080UL    )		/*   Interrupts Pending   */
#define GPIO_INT0			  ((LPC_GPIO_INT_TypeDef  *) 0x40028084UL    )		/*   Interrupt 0          */
#define GPIO_INT2			  ((LPC_GPIO_INT_TypeDef  *) 0x400280A4UL    )		/*   Interrupt 2		  */



void SystemInit (void);

#endif /* LPC1769_H_ */

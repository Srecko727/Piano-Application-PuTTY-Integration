/*------------------------------------------------------------------------------
  usart.c --
  
  Description:
    Provides some useful definitions regarding the USART system of the
    ATxmega128A1U.
  
  Author(s): Dr. Eric Schwartz, Christopher Crary, Wesley Piard
  Last modified by: Dr. Eric M. Schwartz
  Last modified on: 8 Mar 2023
------------------------------------------------------------------------------*/

/********************************DEPENDENCIES**********************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "usart.h"

/*****************************END OF DEPENDENCIES******************************/

/***********************************MACROS*************************************/

/* At 2 MHz SYSclk, 5 BSEL, -6 BSCALE corresponds to 115200 bps */
#define BSEL     (33)
#define BSCALE   (-1)

/********************************END OF MACROS*********************************/

/*****************************FUNCTION DEFINITIONS*****************************/

char usartd0_in_char(void)
{
	while(!(USARTD0.STATUS & USART_DREIF_bm));
	return USARTD0.DATA;
}

void usartd0_in_string(char * buf)
{
	while(*buf) usartd0_in_char();
}

void usartd0_init(void)
{
  /* Configure relevant TxD and RxD pins. */
	PORTD.OUTSET = PIN3_bm;
	PORTD.DIRSET = PIN3_bm;
	PORTD.DIRCLR = PIN2_bm;

  /* Configure baud rate. */
	USARTD0.BAUDCTRLA = (uint8_t)BSEL;
	USARTD0.BAUDCTRLB = (uint8_t)((BSCALE << 4)|(BSEL >> 8));

  /* Configure remainder of serial protocol. */
  /* (In this example, a protocol with 8 data bits, no parity, and
   *  one stop bit is chosen.) */
	USARTD0.CTRLC =	(USART_CMODE_ASYNCHRONOUS_gc |
					 USART_PMODE_DISABLED_gc  	 |
					 USART_CHSIZE_8BIT_gc)       &
					~USART_SBMODE_bm;
	/*USARTD0.CTRLC =	(USART_CMODE_ASYNCHRONOUS_gc |
					USART_PMODE_ODD_gc  	 |
					USART_CHSIZE_8BIT_gc);*/

  /* Enable receiver and/or transmitter systems. */
	USARTD0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
	
	PMIC.CTRL = 0x01;
	sei();
	
  /* Enable interrupt (optional). */
	 USARTD0.CTRLA = USART_RXCINTLVL_LO_gc; 
}

void usartd0_out_char(char c)
{
	while(!(USARTD0.STATUS & USART_DREIF_bm));
	USARTD0.DATA = c;
}

void usartd0_out_string(const char * str)
{
	while(*str) usartd0_out_char(*(str++));
}

/***************************END OF FUNCTION DEFINITIONS************************/
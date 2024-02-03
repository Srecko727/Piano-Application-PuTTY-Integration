#include <avr/io.h>
#include <avr/interrupt.h>
#include "inits.h"

extern void clock_init(void);


int main(void)
{
	//init channel 0  of daca module
	clock_init();
	dac_init();
	dma_init();
	tcc0_init(63);
	uint8_t index = 0;
			PORTC.OUTSET = 1<<7;
			PORTC.DIRSET = 1<<7;	
			//PORTC.DIRSET = 1<<5;
	
	while(1)
	{
		//enable dma
		DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
	}
}
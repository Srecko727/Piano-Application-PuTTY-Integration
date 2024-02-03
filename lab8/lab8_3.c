#include <avr/io.h>
#include <avr/interrupt.h>
#include "inits.h"

extern void clock_init(void);


int main(void)
{
	//init channel 0  of daca module
	clock_init();
	dac_init();
	tcc0_init(63);
	//probe pin PA3 for DAC1
	dma_init();
	uint8_t index = 0;
	
	while(1)
	{
		/*//wait for tcc0 ovf to be set
		while (!(TCC0.INTFLAGS & TC0_OVFIF_bm));
		//clear ovf flag
		TCC0.INTFLAGS = TC0_OVFIF_bm;
		//ensure the ch0data reg is empty before starting new conversion
		while(!(DACA_STATUS & DAC_CH0DRE_bm));
		//output a sample from lookout table
		DACA.CH0DATA = sine[index++];*/
		DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
	}
}

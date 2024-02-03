#include <avr/io.h>
#include <avr/interrupt.h>
#include "inits.h"
#include "usart.h"

extern void clock_init(void);
volatile char button;
uint8_t switchState = 1;

int main(void)
{
	clock_init();
	usartd0_init();
	
	//init speakers
	PORTC.OUTSET = 1<<7;
	PORTC.DIRSET = 1<<7;
	
	dac_init();
	dma_init();
	
	tcc1_init();
	while(1)
	{
		DMA.CH0.CTRLA |= DMA_CH_ENABLE_bm;
	}
}

ISR(USARTD0_RXC_vect)
{
	cli();
	button = usartd0_in_char();
	switch (button)
	{
		case 'e':
		tcc0_init(119);
		//hold(button);
		break;
		
		case '4':
		tcc0_init(113);
		//hold(button);
		break;
		
		case 'r':
		tcc0_init(106);
		//hold(button);
		break;
		
		case '5':
		tcc0_init(100);
		//hold(button);
		break;
		
		case 't':
		tcc0_init(95);
		//hold(button);
		break;
		
		case 'y':
		tcc0_init(89);
		//hold(button);
		break;
		
		case '7':
		tcc0_init(84);
		//hold(button);
		break;
		
		case 'u':
		tcc0_init(80);
		//hold(button);
		break;
		
		case '8':
		tcc0_init(75);
		//hold(button);
		break;
		
		case 'i':
		tcc0_init(71);
		//hold(button);
		break;
		
		case '9':
		tcc0_init(67);
		//hold(button);
		break;
		
		case 'o':
		tcc0_init(63);
		//hold(button);
		break;
		
		case 'p':
		tcc0_init(60);
		//hold(button);
		break;
		
		case 's':
		if (switchState == 1)
		{
			dma_init_expDecay();
			switchState = 0;
		}
		else
		{
			dma_init();
			switchState = 1;
		}
	}
	TCC1.CTRLA = TC_CLKSEL_DIV1024_gc;
	//button = 0;
	sei();
}
ISR(TCC1_OVF_vect)
{
		TCC0.CTRLA = TC_CLKSEL_OFF_gc;
}
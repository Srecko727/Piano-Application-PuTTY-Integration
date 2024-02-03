#include <avr/io.h>

void dac_init(void);

int main(void)
{
	//init channel 0 of DAC module
	dac_init();
	while(1)
	{
		//ensure the ch0data reg is empty before starting new conversion
		while(!(DACA_STATUS & DAC_CH0DRE_bm));
		//write digital value to the ch0data reg
		//0 = 0V, 0xFFF = VREF
		
		//1.2 = (ch0data/0xfff)*2.5
		//4095*1.2/2.5 = ch0data
		//ch0data = 1965 = 0x7AD
		DACA.CH0DATA = 0x7EA;//0x7AD;
		
	}
}

void dac_init()
{
	//use only channel0
	DACA.CTRLB = DAC_CHSEL_SINGLE_gc;		//single1 is channel1 single is channel0
	//use AREFB (2.5V) data is right adjusted
	DACA.CTRLC = DAC_REFSEL_AREFB_gc;
	//enable channel 0 aswell as overall dac module
	DACA.CTRLA = DAC_CH0EN_bm | DAC_ENABLE_bm;
}
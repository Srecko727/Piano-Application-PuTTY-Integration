#ifndef INITS_H_
#define INITS_H_

#include <avr/io.h> 
#include <avr/interrupt.h>

void dac_init(void);

void hold(char pressed);

void tcc0_init(uint16_t note);

void dma_init(void);

void dma_init_expDecay(void);

#endif /* INITS_H_ */
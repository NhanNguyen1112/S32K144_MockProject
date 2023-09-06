#include "S32K144.h"

volatile char StateLED=0;

void PORTC_IRQHandler(void);

void PORTC_IRQHandler(void)
{
	if(READBIT(PORTC->PCR[PIN12],24))
	{
		SETBIT(PORTC->PCR[PIN12],1,24);
		StateLED=1;
	}
	
	if(READBIT(PORTC->PCR[PIN13],24))
	{
		SETBIT(PORTC->PCR[PIN13],1,24);
		StateLED=2;
	}
}



#include "Lpit.h"

void LPIT0_Ch0_IRQHandler(void);
static volatile unsigned int Count=0;
unsigned int Tick_ms=0;

void LPIT_Init(unsigned int TimerVALUE)
{
	unsigned int TCTRL=0;

  LPIT_CLK_ENABLE(Enable,SPLLDIV2_CLK);
	
  LPIT->MCR = 0x1u;     /* Enable peripheral clock to timers */

  LPIT->MIER = 0x00000001u;    /* Timer 0 Enable interrupt */

  LPIT->TVAL0 = TimerVALUE;      /* Timer 0: 60mhz-> 60.000 = 1ms */ 

	NVIC_SetPriority(LPIT0_Ch0_IRQn,1);
	NVIC_ClearPendingFlag(LPIT0_Ch0_IRQn);
	NVIC_EnableInterrupt(LPIT0_Ch0_IRQn); /* Enable LPIT timer 0 */
	
  TCTRL |= (1u<<0);
  LPIT->TCTRL0 = TCTRL;  /* Timer 0 Enable */

}

void LPIT0_Ch0_IRQHandler(void)
{
	LPIT->MSR |= (1u<<0); /* Timer 0 Clear flag */
	Count++;
  Tick_ms++;
}

void LPIT_Delay_ms(const unsigned int MiliSecond)
{
  while(Count<MiliSecond);
  Count=0;
}



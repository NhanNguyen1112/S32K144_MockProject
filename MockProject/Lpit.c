
#include "Lpit.h"

void LPIT0_Ch0_IRQHandler(void);
static volatile unsigned int Count=0;
unsigned int Tick_ms=0;

/*=================================================================================
                  LPIT TEST
==================================================================================*/

/*
static unsigned int test=0;
static int total=0;
static unsigned int Starttimer=0;
static unsigned int Stoptimer=0;
*/

void MainLPIT_Test(void)
{
  SOSC_Init_8Mhz();
	SPLL_Init(Div_2,Div_2);
	Run_Mode_Clock(SPLLDIV2_CLK, RunDiv_2, RunDiv_2, RunDiv_3);
  //CheckClock();

  LPIT_Init_CH0(60000);

  Gpio_Init();

  while(1)
  {
		Gpio_TogglePin(PortD,LEDBLUE);
		LPIT_CH0_Delay_ms(1000);
    Gpio_TogglePin(PortD,LEDRED);
		LPIT_CH0_Delay_ms(1000);
    Gpio_TogglePin(PortD,LEDGREEN);
    LPIT_CH0_Delay_ms(1000);
		
		// Starttimer=LPIT->CVAL0;
		// for(unsigned int i=0; i<=3000000; i++)
		// {
		// 	test++;
		// }
		// Stoptimer=LPIT->CVAL0;
		
		// total = (int)( (Starttimer - Stoptimer)/60000000 );
		
		// test=0;
  }
}
/*==================================================================================*/

void LPIT_Init_CH0(unsigned int TimerVALUE)
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

void LPIT_CH0_Delay_ms(const unsigned int MiliSecond)
{
  while(Count<MiliSecond);
  Count=0;
}




#include "Softtimer.h"

static volatile unsigned int TimeCountMs;

static Softtimer TIMER[Total_Timer];

void Softtimer_Init(void)
{
	int i=0;
	
	for(i=0;i<Total_Timer;i++)
  {
    TIMER[i].TimerID = 0;
    TIMER[i].Mode = 0;
    TIMER[i].TimeoutValue = 0;
    TIMER[i].Callback = 0;
    TIMER[i].CurrentTime = 0;
  }
	
  TimeCountMs = 0;

  SYSTICK->SYST_RVR = (unsigned int)(60000u-1); /* Set reload value 1ms*/

  SYSTICK->SYST_CVR = (unsigned int)(0u); /* Clear current value */

  SYSTICK->SYST_CSR |= (3u<<0); /* Enable counter & Set external clock & enable INT */
}

/*
* TimerID: 0->Total Timer
* TimeOutValue: 1=100ms
* Mode: ONESHOT / CONTINUE
*/
void Softtimer_StartTimer(unsigned int TimerID,unsigned int TimeoutValue,unsigned char Mode,CALLBACK Event)
{
  TIMER[TimerID].TimerID = TimerID;
  TIMER[TimerID].Mode = Mode;
  TIMER[TimerID].TimeoutValue = TimeoutValue;
  TIMER[TimerID].Callback = Event;
  TIMER[TimerID].CurrentTime = TimeCountMs;
}

void Softtimer_StopTimer(unsigned int TimerID)
{
  TIMER[TimerID].TimeoutValue = 0;
}

void Softtimer_MainFunction(void)
{
  int i;
  for(i=0;i<Total_Timer;i++)
  {
    if(TIMER[i].TimeoutValue != 0)
    {
      if ( (TimeCountMs - TIMER[i].CurrentTime) >= TIMER[i].TimeoutValue )
      {
        if(TIMER[i].Mode==CONTINUE) 
        {
          TIMER[i].Callback();
          TIMER[i].CurrentTime = TimeCountMs;
        } 
        else TIMER[i].Callback();
      }
    }
  }
}

void SysTick_Handler(void)
{
  TimeCountMs++;
}



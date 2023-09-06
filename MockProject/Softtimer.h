
#ifndef __Softtimer__
#define __Softtimer__

#include "S32K144.h"
#include "Systick_Register.h"

#define Total_Timer 3

typedef void (*CALLBACK)(void);

typedef enum 
{
  ONESHOT,
  CONTINUE
}Mode_typedef;

typedef struct Softtimer
{
  unsigned int TimerID;
  unsigned char Mode;
  char dummy[3u];
  unsigned int TimeoutValue;
  unsigned int CurrentTime;
  CALLBACK Callback;
} Softtimer;

void Softtimer_Init(void);
void Softtimer_StartTimer(unsigned int TimerID,unsigned int TimeoutValue,unsigned char Mode,CALLBACK callback);
void Softtimer_StopTimer(unsigned int TimerID);
void Softtimer_MainFunction(void);
void SysTick_Handler(void);

#endif



#ifndef __LED_MAX7219__ 
#define __LED_MAX7219__

#include "S32K144.h"

typedef enum LEDState
{
  LED_OK,
  LED_Timeout
}LEDState_enum;

unsigned char MAX7219_Init(void);
unsigned char LCD_Print(unsigned char Pos, unsigned char Number);
unsigned char LCD_TurnOff(unsigned char Pos);
unsigned char LCD_TwoNumber(unsigned char Pos_1, unsigned char Pos_2, unsigned char Number);
unsigned char LCD_TimeDisplay(unsigned char Hour, unsigned char Minute, unsigned char Second);
unsigned char LCD_DayDisplay(unsigned char Day, unsigned char Month, unsigned char year);

#endif /* __LED_MAX7219__ */



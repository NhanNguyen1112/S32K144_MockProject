#include "LED_MAX7219.h"

/* LED 7-Segment MAX7219 */
unsigned char MAX7219_Init(void)
{
  unsigned char State=LED_OK;
  unsigned short Data=0;

	/* intensity*/
	Data = 0x0A01;
	if( SPI1_Transmit(&Data)==Spi_TimeOut ) State=LED_Timeout;
	
	/* scan limit*/
	Data = 0x0B07;
	if( SPI1_Transmit(&Data)==Spi_TimeOut ) State=LED_Timeout;

	/* Normal Operation */
	Data = 0x0C01;
	if( SPI1_Transmit(&Data)==Spi_TimeOut ) State=LED_Timeout;

	/* Display Test */
	/*SPI1_Send16bit(0x0F01);*/
 
	/* Decode mode */
	Data = 0x09FF;
	if( SPI1_Transmit(&Data)==Spi_TimeOut ) State=LED_Timeout;

	return State;
}

unsigned char LCD_Print(unsigned char Pos, unsigned char Number)
{
  unsigned char State=LED_OK;

  unsigned short Data_Print;
  Data_Print = Number;
  Data_Print = (unsigned short)((Pos<<8) + (Data_Print));
	if( SPI1_Transmit(&Data_Print)==Spi_TimeOut ) State=LED_Timeout;

  return State;
}

unsigned char LCD_TurnOff(unsigned char Pos)
{
  unsigned char State=LED_OK;

  unsigned short Data_Print;
  Data_Print = 0x0F;
  Data_Print |= (Pos<<8);
  if( SPI1_Transmit(&Data_Print)==Spi_TimeOut ) State=LED_Timeout;

  return State;
}

unsigned char LCD_TwoNumber(unsigned char Pos_1, unsigned char Pos_2, unsigned char Number)
{
  unsigned char State=LED_OK;
  unsigned char So_DonVi;
  unsigned char So_Chuc;
	So_DonVi=0;
  So_Chuc=0;

  So_DonVi = (Number%10);
  So_Chuc = (Number/10);

  if( LCD_Print(Pos_1, So_DonVi)==LED_Timeout ) State=LED_Timeout;
  if( LCD_Print(Pos_2, So_Chuc)==LED_Timeout ) State=LED_Timeout;

  return State;
}

unsigned char LCD_TimeDisplay(unsigned char Hour, unsigned char Minute, unsigned char Second)
{
  unsigned char State=LED_OK;

  if( LCD_Print(3,10)==LED_Timeout ) State=LED_Timeout;
  if( LCD_Print(6,10)==LED_Timeout ) State=LED_Timeout;

  if( LCD_TwoNumber(1,2,Second)==LED_Timeout ) State=LED_Timeout;
  if( LCD_TwoNumber(4,5,Minute)==LED_Timeout ) State=LED_Timeout;
  if( LCD_TwoNumber(7,8,Hour)==LED_Timeout ) State=LED_Timeout;

  return State;
}

unsigned char LCD_DayDisplay(unsigned char Day, unsigned char Month, unsigned char year)
{
  unsigned char State=LED_OK;

  if( LCD_Print(3,10)==LED_Timeout ) State=LED_Timeout;
  if( LCD_Print(6,10)==LED_Timeout ) State=LED_Timeout;

  if( LCD_TwoNumber(1,2,year)==LED_Timeout ) State=LED_Timeout;
  if( LCD_TwoNumber(4,5,Month)==LED_Timeout ) State=LED_Timeout;
  if( LCD_TwoNumber(7,8,Day)==LED_Timeout ) State=LED_Timeout;

  return State; 
}


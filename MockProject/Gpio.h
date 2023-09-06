
#ifndef __Gpio__
#define __Gpio__ 

#include "S32K144.h"
#include "Gpio_Register.h"

/*
	PTD0 - BLUE
	PTD15 - RED
	PTD16 - GREEN

	PTC12 - Button 1
	PTC13 - Button 2
*/

extern volatile char StateLED;

#define BUTTON_1 12u
#define BUTTON_2 13u

#define LEDBLUE 	0u
#define LEDRED 		15u
#define LEDGREEN 	16u

void Gpio_Init(void);
void Gpio_GetPinValue(const unsigned int port, unsigned char pin, unsigned int *value);
void Gpio_SetPinValue(const unsigned int port, unsigned char pin, const unsigned int value);
void Gpio_TogglePin(const unsigned int port, unsigned char pin);
void Delay(const unsigned int millis, const char Select);

void Program1(void);
void Program2(void);
void Assignment3_MAIN(void);

#endif



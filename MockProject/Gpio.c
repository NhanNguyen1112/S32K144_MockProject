#include "Gpio.h"

/*
	PTD0 - BLUE
	PTD15 - RED
	PTD16 - GREEN
*/
void Gpio_Init(void)
{
	/* Enable clock port C, D */
	EnableClockPortC(Enable);
	EnableClockPortD(Enable);
	
	/* Set MUX GPIO for LED */
	PORTD->PCR[PIN0] 	|= (0x01u<<8); /*BLUE*/
	PORTD->PCR[PIN15] |= (0x01u<<8); /*RED*/
	PORTD->PCR[PIN16] |= (0x01u<<8); /*GREEN*/
	/* Disable PULL LED */
	PORTD->PCR[PIN0]  &= ~(0x1u<<1); /*BLUE*/
	PORTD->PCR[PIN15] &= ~(0x1u<<1); /*RED*/
	PORTD->PCR[PIN16] &= ~(0x1u<<1); /*GREEN*/
	/* SET GPIO OUTPUT for LED */
	SETBIT(GPIOD->PDDR,1u,LEDRED);
	SETBIT(GPIOD->PDDR,1u,LEDGREEN);
	SETBIT(GPIOD->PDDR,1u,LEDBLUE);
	/* TURN OFF ALL LED */
	SETBIT(GPIOD->PDOR,1u,LEDRED);
	SETBIT(GPIOD->PDOR,1u,LEDGREEN);
	SETBIT(GPIOD->PDOR,1u,LEDBLUE);
	
	/* Set MUX GPIO for BUTTON */ 
	PORTC->PCR[PIN12] &= ~(7u<<8);
	PORTC->PCR[PIN13] &= ~(7u<<8);
	PORTC->PCR[PIN12] |= (0x01u<<8); /*Button 1*/
	PORTC->PCR[PIN13] |= (0x01u<<8); /*Button 2*/
	/* Enable PULL BUTTON */
	PORTC->PCR[PIN12] |= (0x1u<<1);
	PORTC->PCR[PIN13] |= (0x1u<<1);
	/* Set Pull Down BUTTON */
	PORTC->PCR[PIN12] &= ~(0x1u<<0);
	PORTC->PCR[PIN13] &= ~(0x1u<<0);
	/* SET INPUT for Button */
	CLEARBIT(GPIOC->PDDR,1u,BUTTON_1);
	CLEARBIT(GPIOC->PDDR,1u,BUTTON_2);
	
	/* Enable NVIC */
	//NVIC->ISER[1] |= (1u<<29u);

	/* Config interrupt for button 1, 2 */
	//PORTC->PCR[PIN12] |= (0x9u<<16);
	//PORTC->PCR[PIN13] |= (0x9u<<16);
	
}

void Gpio_GetPinValue(const unsigned int port, unsigned char pin, unsigned int *value)
{
	if(port==PortA) 			*value = READBIT(GPIOA->PDIR,pin);
	else if(port==PortB) 	*value = READBIT(GPIOB->PDIR,pin);
	else if(port==PortC) 	*value = READBIT(GPIOC->PDIR,pin);
	else if(port==PortD) 	*value = READBIT(GPIOD->PDIR,pin);
	else 									*value = READBIT(GPIOE->PDIR,pin);
}

void Gpio_SetPinValue(const unsigned int port, unsigned char pin, const unsigned int value)
{
	if(value==HIGH)
	{
		if(port==PortA) 			SETBIT(GPIOA->PDOR,1u,pin);
		else if(port==PortB) 	SETBIT(GPIOB->PDOR,1u,pin);
		else if(port==PortC) 	SETBIT(GPIOC->PDOR,1u,pin);
		else if(port==PortD) 	SETBIT(GPIOD->PDOR,1u,pin);
		else 									SETBIT(GPIOE->PDOR,1u,pin);
	}
	else 
	{
		if(port==PortA) 			CLEARBIT(GPIOA->PDOR,1u,pin);
		else if(port==PortB) 	CLEARBIT(GPIOB->PDOR,1u,pin);
		else if(port==PortC) 	CLEARBIT(GPIOC->PDOR,1u,pin);
		else if(port==PortD) 	CLEARBIT(GPIOD->PDOR,1u,pin);
		else 									CLEARBIT(GPIOE->PDOR,1u,pin);
	}
}

void Gpio_TogglePin(const unsigned int port, unsigned char pin)
{
	if(port==PortA) 		SETBIT(GPIOA->PTOR,1u,pin);
	else if(port==PortB) 	SETBIT(GPIOB->PTOR,1u,pin);
	else if(port==PortC) 	SETBIT(GPIOC->PTOR,1u,pin);
	else if(port==PortD) 	SETBIT(GPIOD->PTOR,1u,pin);
	else 					SETBIT(GPIOE->PTOR,1u,pin);
}



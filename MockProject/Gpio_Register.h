
#ifndef _Gpio_Register_
#define _Gpio_Register_

#include "Gpio.h"

/*===============================================================================*/
/*			Define PORT			*/ 
/*===============================================================================*/
typedef struct 
{
	volatile unsigned int PCR[32u];       
	volatile unsigned int GPCLR;
	volatile unsigned int GPCHR;
	volatile unsigned int GICLR;
	volatile unsigned int GICHR;
	volatile unsigned int ISFR;
	volatile unsigned int DFER;
	volatile unsigned int DFCR;
	volatile unsigned int DFWR;
}PORT_typedef;

#define PORTA_address (0x40049000UL)
#define PORTB_address (0x4004A000UL)
#define PORTC_address (0x4004B000UL)
#define PORTD_address (0x4004C000UL)
#define PORTE_address (0x4004D000UL)

#define PORTA	((PORT_typedef *)PORTA_address)
#define PORTB	((PORT_typedef *)PORTB_address)
#define PORTC	((PORT_typedef *)PORTC_address)
#define PORTD	((PORT_typedef *)PORTD_address)
#define PORTE	((PORT_typedef *)PORTE_address)

/*===============================================================================*/


/*===============================================================================*/
/*			Define GPIO			*/ 
/*===============================================================================*/
typedef struct 
{
	volatile unsigned int PDOR;
	volatile unsigned int PSOR;
	volatile unsigned int PCOR;
	volatile unsigned int PTOR;
	volatile unsigned int PDIR;
	volatile unsigned int PDDR;
	volatile unsigned int PIDR;
}gpio_typedef;

#define GPIOA_base_address (0x400FF000UL)
#define GPIOB_base_address (0x400FF040UL)
#define GPIOC_base_address (0x400FF080UL)
#define GPIOD_base_address (0x400FF0C0UL)
#define GPIOE_base_address (0x400FF100UL)

#define GPIOA	((gpio_typedef *)GPIOA_base_address)
#define GPIOB	((gpio_typedef *)GPIOB_base_address)
#define GPIOC	((gpio_typedef *)GPIOC_base_address)
#define GPIOD	((gpio_typedef *)GPIOD_base_address)
#define GPIOE	((gpio_typedef *)GPIOE_base_address)
/*===============================================================================*/

#endif /* _Gpio_Register_ */



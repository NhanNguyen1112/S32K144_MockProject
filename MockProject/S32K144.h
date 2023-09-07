
#ifndef __S32K144__
#define __S32K144__

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Clock.h"
#include "Nvic.h"
#include "Lpuart.h"
#include "Lpspi.h"
#include "Lpit.h"
#include "Gpio.h"
#include "Softtimer.h"
#include "APP_FUNCTION.h"
#include "String.h"
#include "LED_MAX7219.h"
/*================================================================================================*/

/*==================================================================================================
*                                        DEFINES AND MACROS
==================================================================================================*/
#define SETBIT(PORT,VALUE,BIT) 		( (PORT) |= ( (VALUE)<<(BIT) ) )
#define CLEARBIT(PORT,VALUE,BIT) 	( (PORT) &= ~( (VALUE)<<(BIT) ) )
#define SETALL(PORT) 				( (PORT)|=(0xFFFFFFFF) )
#define CLEARALL(PORT) 				( (PORT)&=(0x00000000) )
#define READBIT(PORT,BIT) 			( (PORT) & (1u<<(BIT)) )
/*================================================================================================*/

/*==================================================================================================
*                                        TYPEDEFS & ENUMS
==================================================================================================*/

typedef unsigned char 	uint8_t;
typedef unsigned short 	uint16_t;
typedef unsigned int 	uint32_t;

typedef enum DigitalState_enum
{
	LOW,
	HIGH
}DigitalState_enum;

typedef enum EnDisable_enum
{
	Disable,
	Enable
}EnDisable_enum;

typedef enum PinMode_enum
{
	OUTPUT,
	INPUT
}PinMode_enum;

typedef enum UpDown_enum
{
	No,
	PullUp,
	PullDown
}UpDown_enum;

typedef enum Port_enum
{
	PortA,
	PortB,
	PortC,
	PortD,
	PortE
}Port_enum;

typedef enum Gpio_enum
{
	GpioA,
	GpioB,
	GpioC,
	GpioD,
	GpioE
}Gpio_enum;

typedef enum PortPin_enum
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7,
	PIN8,
	PIN9,
	PIN10,
	PIN11,
	PIN12,
	PIN13,
	PIN14,
	PIN15,
	PIN16,
	PIN17,
	PIN18,
	PIN19,
	PIN20,
	PIN21,
	PIN22,
	PIN23,
	PIN24,
	PIN25,
	PIN26,
	PIN27,
	PIN28,
	PIN29,
	PIN30,
	PIN31
}PortPin_enum;

/*===============================================================================*/

/*===============================================================================*/
/*			Define SIM			*/ 
/*===============================================================================*/

typedef struct
{
	char dummy[0x4u];
	volatile uint32_t CHIPCTL;
	char dummy1[0x8u];
	volatile uint32_t FTMOPT0;
	volatile uint32_t LPOCLKS;
	char dummy2[0x8u];
	volatile uint32_t ADCOPT;
	volatile uint32_t FTMOPT1;
	volatile uint32_t MISCTRL0;
	volatile uint32_t SDID;
	char dummy3[0x1Cu];
	volatile uint32_t PLATCGC;
	char dummy4[0xCu];
	volatile uint32_t FCFG1;
	char dummy5[0x8u];
	volatile uint32_t UIDH;
	volatile uint32_t UIDMH;
	volatile uint32_t UIDML;
	volatile uint32_t UIDL;
	char dummy6[0x8u];
	volatile uint32_t CLKDIV4;
	volatile uint32_t MISCTRL1;
}SIM_typedef;

#define SIM_BASE_ADDRESS (0x40048000u)
#define SIM ((volatile SIM_typedef *)SIM_BASE_ADDRESS)

/*===============================================================================*/



#endif /* __S32K144__ */


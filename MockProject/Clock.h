
#ifndef __Clock__
#define __Clock__

#include "Clock_Register.h"
#include "S32K144.h"

typedef enum Divide
{
	Div_Disable,
	Div_1,
	Div_2,
	Div_4,
	Div_8,
	Div_16,
	Div_32,
	Div_64
}Divide_enum; 

typedef enum RunModeDiv
{
	RunDiv_1,
	RunDiv_2,
	RunDiv_3,
	RunDiv_4,
	RunDiv_5,
	RunDiv_6,
	RunDiv_7,
	RunDiv_8,
	RunDiv_9,
	RunDiv_10,
	RunDiv_11,
	RunDiv_12,
	RunDiv_13,
	RunDiv_14,
	RunDiv_15,
	RunDiv_16
}RunModeDiv_enum;

typedef enum ClockSelect_enum
{
	NoClock,
	SOSCDIV2_CLK,
	SIRCDIV2_CLK,
	FIRCDIV2_CLK,
	SPLLDIV2_CLK,
	LPO128_CLK
}ClockSelect_enum;

void SOSC_Init_8Mhz(void);
void SPLL_Init(Divide_enum SPLLDIV1, Divide_enum SPLLDIV2);
void Run_Mode_Clock(ClockSelect_enum SPLLCLK, RunModeDiv_enum DIVCORE, RunModeDiv_enum DIVBUS, RunModeDiv_enum DIVSLOW);
void FIRC_Init(Divide_enum FIRCDIV1, Divide_enum FIRCDIV2);
void CheckClock(void);
void EnableClockPortA(const unsigned char Status);
void EnableClockPortB(const unsigned char Status);
void EnableClockPortC(const unsigned char Status);
void EnableClockPortD(const unsigned char Status);
void EnableClockPortE(const unsigned char Status);
void LPIT_CLK_ENABLE(const unsigned char Status, ClockSelect_enum Clock_Seclect);
void UART0_CLK_ENABLE(const unsigned char Status, ClockSelect_enum Clock_Seclect);
void UART1_CLK_ENABLE(const unsigned char Status, ClockSelect_enum Clock_Seclect);
void SPI0_CLK_ENABLE(const unsigned char Status, ClockSelect_enum Clock_Seclect);
void SPI1_CLK_ENABLE(const unsigned char Status, ClockSelect_enum Clock_Seclect);
void SPI2_CLK_ENABLE(const unsigned char Status, ClockSelect_enum Clock_Seclect);

#endif /* __Clock__ */



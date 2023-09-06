
#ifndef __UART_Register__
#define __UART_Register__

#include "Lpuart.h"

typedef struct
{
	volatile unsigned int VERID;
	volatile unsigned int PARAM;
	volatile unsigned int GLOBAL;
	volatile unsigned int PINCFG;
	volatile unsigned int BAUD;
	volatile unsigned int STAT;
	volatile unsigned int CTRL;
	volatile unsigned int DATA;
	volatile unsigned int MATCH;
	volatile unsigned int MODIR;
	volatile unsigned int FIFO;
	volatile unsigned int WATER;
}UART_Typedef;

#define LPUART0_BASE_ADDRESS (0x4006A000u)
#define LPUART1_BASE_ADDRESS (0x4006B000u)
#define LPUART2_BASE_ADDRESS (0x4006C000u)

#define UART0 ((UART_Typedef *) LPUART0_BASE_ADDRESS)
#define UART1 ((UART_Typedef *) LPUART1_BASE_ADDRESS)
#define UART2 ((UART_Typedef *) LPUART2_BASE_ADDRESS)

#endif /* __UART_Register__ */



#ifndef _SPI_Register_
#define _SPI_Register_

#include "Lpspi.h"

typedef struct 
{
	volatile const unsigned int VERID;
	volatile const unsigned int PARAM;
	char dummy0[8];
	volatile unsigned int CR;
	volatile unsigned int SR;
	volatile unsigned int IER;
	volatile unsigned int DER;
	volatile unsigned int CFGR0;
	volatile unsigned int CFGR1;
	char dummy1[8];
	volatile unsigned int DMR0;
	volatile unsigned int DMR1;
	char dummy2[8];
	volatile unsigned int CCR;
	char dummy3[20];
	volatile unsigned int FCR;
	volatile const unsigned int FSR;
	volatile unsigned int TCR;
	volatile unsigned int TDR;
	char dummy5[8];
	volatile const unsigned int RSR;
	volatile const unsigned int RDR;
}SPI_typedef;

#define LPSPI0_base_address (0x4002C000)
#define LPSPI1_base_address (0x4002D000)
#define LPSPI2_base_address (0x4002E000)

#define SPI0 ((SPI_typedef *)LPSPI0_base_address)
#define SPI1 ((SPI_typedef *)LPSPI1_base_address)
#define SPI2 ((SPI_typedef *)LPSPI2_base_address)

#endif /* _SPI_Register_ */





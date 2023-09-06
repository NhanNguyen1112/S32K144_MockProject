
#ifndef _LPIT_Register_
#define _LPIT_Register_

#include "Lpit.h"

/*===============================================================================*/
/*			Define LPIT			*/ 
/*===============================================================================*/

typedef struct
{
	volatile unsigned int VERID;
	volatile unsigned int PARAM;
	volatile unsigned int MCR;
	volatile unsigned int MSR;
	volatile unsigned int MIER;
	volatile unsigned int SETTEN;
	volatile unsigned int CLRTEN;
	unsigned int dummy;
	volatile unsigned int TVAL0;
	volatile unsigned int CVAL0;
	volatile unsigned int TCTRL0;
	unsigned int dummy0;
	volatile unsigned int TVAL1;
	volatile unsigned int CVAL1;
	volatile unsigned int TCTRL1;
	unsigned int dummy1;
	volatile unsigned int TVAL2;
	volatile unsigned int CVAL2;
	volatile unsigned int TCTRL2;
	unsigned int dummy2;
	volatile unsigned int TVAL3;
	volatile unsigned int CVAL3;
	volatile unsigned int TCTRL3;
}LPIT_typdef;

#define LPIT_BASE_ADDRESS 	((unsigned int)0x40037000u)
#define LPIT				((LPIT_typdef*)LPIT_BASE_ADDRESS)

/*===============================================================================*/

#endif



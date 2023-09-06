
#ifndef __Systick_Register__
#define __Systick_Register__

#include "Softtimer.h"

/*===============================================================================*/
/*			Define SYSTICK			*/ 
/*===============================================================================*/
typedef struct
{
	volatile unsigned int SYST_CSR;
	volatile unsigned int SYST_RVR;
	volatile unsigned int SYST_CVR;
	volatile unsigned int SYST_CALIB;
}Systick_typedef;
#define SYSTICK_BASE_ADDRESS  ((unsigned int)0xE000E010u)
#define SYSTICK 							((Systick_typedef*)SYSTICK_BASE_ADDRESS)
/*===============================================================================*/

#endif



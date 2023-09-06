
#ifndef _Clock_Register_
#define _Clock_Register_

#include "Clock.h"

/*===============================================================================*/
/*			Define SCG (Clock)			*/ 
/*===============================================================================*/
typedef struct
{
	volatile unsigned int VERID;
	volatile unsigned int PARAM;
	char dummy0[8u];
	volatile unsigned int CSR;
	volatile unsigned int RCCR;
	volatile unsigned int VCCR;
	volatile unsigned int HCCR;
	volatile unsigned int CLKOUTCNFG;
	char dummy2[220u];

	volatile unsigned int SOSCCSR;
	volatile unsigned int SOSCDIV;
	volatile unsigned int SOSCCFG;
	char dummy3[244u];

	volatile unsigned int SIRCCSR;
	volatile unsigned int SIRCDIV;
	volatile unsigned int SIRCCFG;
	char dummy4[244u];

	volatile unsigned int FIRCCSR;
	volatile unsigned int FIRCDIV;
	volatile unsigned int FIRCCFG;
	char dummy5[756u];

	volatile unsigned int SPLLCSR;
	volatile unsigned int SPLLDIV;
	volatile unsigned int SPLLCFG;
}SCG_typedef;

#define SCG_BASE_ADDRESS (0x40064000u)
#define SCG ((SCG_typedef *)SCG_BASE_ADDRESS)

/*===============================================================================*/


/*===============================================================================*/
/*			Define PCC (Clock)			*/ 
/*===============================================================================*/

#define PCC_ADC0_OFFSET   (0xEC)
#define PCC_ADC1_OFFSET   (0x9C)
#define PCC_LPSPI0_OFFSET (0xB0)
#define PCC_LPSPI1_OFFSET (0xB4)
#define PCC_LPSPI2_OFFSET (0xB8)
#define PCC_LPIT_OFFSET   (0xDC)
#define PCC_PORTA_OFFSET  (0x124)
#define PCC_PORTB_OFFSET  (0x128)
#define PCC_PORTC_OFFSET  (0x12C)
#define PCC_PORTD_OFFSET  (0x130)
#define PCC_PORTE_OFFSET  (0x134)
#define PCC_UART0_OFFSET  (0x1A8)
#define PCC_UART1_OFFSET  (0x1AC)
#define PCC_UART2_OFFSET  (0x1B0)
#define PCC_LPI2C0_OFFSET (0x198)
#define PCC_LPI2C1_OFFSET (0x19C)

#define PCC_base_address (0x40065000u)

#define PCC_ADC0     *((volatile unsigned int *)(PCC_base_address + PCC_ADC0_OFFSET))
#define PCC_ADC1     *((volatile unsigned int *)(PCC_base_address + PCC_ADC1_OFFSET))
#define PCC_LPSPI0   *((volatile unsigned int *)(PCC_base_address + PCC_LPSPI0_OFFSET))
#define PCC_LPSPI1   *((volatile unsigned int *)(PCC_base_address + PCC_LPSPI1_OFFSET))
#define PCC_LPSPI2   *((volatile unsigned int *)(PCC_base_address + PCC_LPSPI2_OFFSET))
#define PCC_LPIT     *((volatile unsigned int *)(PCC_base_address + PCC_LPIT_OFFSET))
#define PCC_PORTA    *((volatile unsigned int *)(PCC_base_address + PCC_PORTA_OFFSET))
#define PCC_PORTB    *((volatile unsigned int *)(PCC_base_address + PCC_PORTB_OFFSET))
#define PCC_PORTC    *((volatile unsigned int *)(PCC_base_address + PCC_PORTC_OFFSET))
#define PCC_PORTD    *((volatile unsigned int *)(PCC_base_address + PCC_PORTD_OFFSET))
#define PCC_PORTE    *((volatile unsigned int *)(PCC_base_address + PCC_PORTE_OFFSET))
#define PCC_UART0    *((volatile unsigned int *)(PCC_base_address + PCC_UART0_OFFSET))
#define PCC_UART1    *((volatile unsigned int *)(PCC_base_address + PCC_UART1_OFFSET))
#define PCC_UART2    *((volatile unsigned int *)(PCC_base_address + PCC_UART2_OFFSET))
#define PCC_LPI2C0   *((volatile unsigned int *)(PCC_base_address + PCC_LPI2C0_OFFSET))
#define PCC_LPI2C1   *((volatile unsigned int *)(PCC_base_address + PCC_LPI2C1_OFFSET))

/*===============================================================================*/

#endif /* Clock_Register */



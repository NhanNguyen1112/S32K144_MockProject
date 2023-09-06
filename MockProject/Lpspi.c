
#include "Lpspi.h"

static void SPI1_GPIO_Config(void)
{
	EnableClockPortB(Enable);

	PORTB->PCR[14] &= ~(7u<<8);
	PORTB->PCR[14] |= (3u<<8); /* ALT 3 */

	PORTB->PCR[15] &= ~(7u<<8);
	PORTB->PCR[15] |= (3u<<8); /* ALT 3 */

	PORTB->PCR[16] &= ~(7u<<8);
	PORTB->PCR[16] |= (3u<<8); /* ALT 3 */

	PORTB->PCR[17] &= ~(7u<<8);
	PORTB->PCR[17] |= (3u<<8); /* ALT 4 */
}

/* Pin number        | Function
* ----------------- |------------------
* PTB14             | LPSPI1_SCK
* PTB15							| LPSPI1_SIN
* PTB16			        | LPSPI1_SOUT
* PTB17			        | LPSPI1_PCS3 
*/
void SPI1_Init(void)
{
	unsigned int TCR=0;

	SPI1_GPIO_Config(); /* Setting SCK/PCS/SOUT/SIN pin */

	SPI1_CLK_ENABLE(Enable,SPLLDIV2_CLK); /* Select SPLLDIV2 */

	SPI1->CR = 2; 	/* Reset Master */
	SPI1->CR = 0; 	/* Disable Module for config */
	
	SPI1->IER = 0; 	/* No use Interrupt */
	SPI1->DER = 0; 	/* No use DMA */

	SPI1->CFGR0 = 0; /* Defaults */	

	SPI1->CCR |= (4u<<24); 	/* SCKPCS = 4+1 =5 */
	SPI1->CCR |= (4u<<16); 	/* PCSSCK = 4+1 =5 */
	SPI1->CCR |= (13u<<0); 	/* SCKDIV = 13+2 = 15 cycles */

	TCR |= (3u<<24); 			/* PCS[3] */	
	TCR &= ~(1u<<31); 		/* CPOL: LOW */
	TCR &= ~(1u<<30); 		/* CPHA: 0 */
	TCR |= (15u<<0); 			/* FRAME SIZE = 15+1 = 16 */
	TCR |= (2u<<27);			/* FRESCALE DIV 4 -> 60/4=15Mhz*/
	SPI1->TCR = TCR;
	
	SPI1->FCR  	|= (3u);      /* TXWATER: Transmit FIFO */
	SPI1->CFGR1 |= (1u<<3u);  /* No Stall if Tx FIFO empty or Rx FIFO full*/

	SPI1->CR |= (1u<<3u);		/* Debug Mode */
	SPI1->CFGR1 |= (1u<<0); /* Master Mode */

	SPI1->CR |= (1u<<0); 	/* Module Enable */
}

void SPI1_Transmit(unsigned short *DataSend)
{
	while( (SPI1->SR & (1u)) == 0 ){} /* Wait for Tx FIFO available */                                 
  SPI1->TDR = *DataSend; /* Transmit data */
}

/*========================================================================================
																MAIN TEST
=========================================================================================*/
void SPI_MAIN_TEST(void)
{
	SOSC_Init_8Mhz();
	SPLL_Init(Div_2,Div_2);
	Run_Mode_Clock(SPLLDIV2_CLK, RunDiv_2, RunDiv_2, RunDiv_3);
  //CheckClock();

	LPIT_Init_CH0(60000);

	SPI1_Init();

	static unsigned short Data=0;
	// /* intensity*/
	Data = 0x0A01;
	SPI1_Transmit(&Data);
	
	// /* scan limit*/
	Data = 0x0B07;
	SPI1_Transmit(&Data);

	// /* Normal Operation */
	Data = 0x0C01;
	SPI1_Transmit(&Data);

	// /* Display Test */
	// //LPSPI1_send_char(0x0F01);
 
	// /* Decode mode */
	Data = 0x09FF;
	SPI1_Transmit(&Data);

	// /* set 1 for led 0 */
	Data = 0x0101;
	SPI1_Transmit(&Data);

	Data = 0x0808;
	SPI1_Transmit(&Data);
	// SPI1_Transmit(0x020F);
	// SPI1_Transmit(0x030F);
	// SPI1_Transmit(0x040F);
	// SPI1_Transmit(0x050F);
	// SPI1_Transmit(0x060F);
	// SPI1_Transmit(0x070F);
	// SPI1_Transmit(0x080F);

	while(1)
	{
		//SPI0_Transmit_16bit(Data);
		
		// while( !(SPI0->SR & (1u<<0)) ) /* wait transmit data is requested */

		// SPI0->TDR = Data;

		// SPI0->SR |= (1u<<0); /* Clear TDF flag */
		
		// SysTickDelay_ms(1000);
	}
}
/*=========================================================================================*/




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

unsigned char SPI1_Transmit(unsigned short *DataSend)
{
	unsigned int TickTime=0;
	unsigned char State=Spi_OK;

	TickTime = Tick_ms;
	while( (SPI1->SR & (1u)) == 0 ) /* Wait for Tx FIFO available */             
	{
		if( (unsigned int)(Tick_ms-TickTime)>=5 )
		{
			State=Spi_TimeOut;
			break;
		}
	}

  SPI1->TDR = *DataSend; /* Transmit data */

	return State;
}



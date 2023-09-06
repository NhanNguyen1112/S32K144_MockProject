
#include "Lpuart.h"

static unsigned char Software_Buffer_Send[UART_BUFFER_SIZE];
static unsigned char Software_Buffer_Read[UART_BUFFER_SIZE];

static unsigned char Transmit_State=0;
static unsigned char Receive_State=0;
static unsigned int LengthBufferSend=0;
static unsigned int LengthBufferRead=0;
static unsigned char Index_Read=0;
static unsigned char Index_Write=0;

static void UART1_GPIO_Config(void)
{
	EnableClockPortC(Enable);
	PORTC->PCR[6] &= ~(7u<<8);
	PORTC->PCR[6] |= (2u<<8); /* ALT 2 */

	PORTC->PCR[7] &= ~(7u<<8);
	PORTC->PCR[7] |= (2u<<8); /* ALT 2 */
}

void Uart_Init (void)
{
  unsigned int BAUD=0;
	unsigned int CTRL=0;

	UART1_GPIO_Config();
	UART1_CLK_ENABLE(Enable,SOSCDIV2_CLK);

	BAUD &= ~(1u<<29); 	/* 7-9bit data */
	BAUD |= (15u<<24); 	/* OSR= 15 */
	BAUD |= (0x34u<<0); /* 8mhz/9600/15+1 ~= 52 */
	BAUD &= ~(1u<<13); 	/* 1 Stop bit */
	UART1->BAUD = BAUD;

	//CTRL |= (1u<<0); 		/* Odd Parity */
	//CTRL &= ~(1u<<0); 	/* Even Parity */
	//CTRL |= (1u<<1); 		/* Parity enable */

	CTRL &= ~(1u<<11); /* 8bit-10bit Data */
	//CTRL |= (1u<<11); /* 7bit Data */

	CTRL &= ~(1u<<4); /* 8bit Data */
	//CTRL |= (1u<<4); /* 9bit Data */

	//CTRL |= (1u<<23); /* TX Enable Interrupt */
	CTRL |= (1u<<21); /* RX Enable Interrupt */

	CTRL |= (1u<<18) | (1u<<19); /* TX & RX enable */
	UART1->CTRL = CTRL;

	NVIC_SetPriority(LPUART1_RxTx_IRQn,0);
	NVIC_ClearPendingFlag(LPUART1_RxTx_IRQn);
	NVIC_EnableInterrupt(LPUART1_RxTx_IRQn);

	Transmit_State=IDLE;
	Receive_State=EMPTY;
}

unsigned char Uart_Transmit ( unsigned char* u8_TxBuffer, unsigned int u4_Length )
{
	unsigned int Count=0;
	unsigned char State=ACCEPT;

	if(Transmit_State == IDLE)
	{
		for(Count=0; Count<u4_Length; Count++)
		{
			Software_Buffer_Send[Count] = *u8_TxBuffer;
			u8_TxBuffer++;
			LengthBufferSend++;
		}
		Transmit_State=BUSY;
	}
	else State=NOT_ACCEPT;

	return State;
}

unsigned char Uart_GetTransmitState ( void )
{
	return Transmit_State;
}

void Uart_TxMainFunction ( void )
{
	static unsigned int idex=0;
	if(Transmit_State == BUSY)
	{
		if( (UART1->STAT & (1u<<23)) && (LengthBufferSend!=0) )
		{
			UART1->DATA = Software_Buffer_Send[idex];
			idex++;
			LengthBufferSend--;
		}
		else 
		{
			idex=0;
			Transmit_State=IDLE;
		}
	}
}

unsigned int Uart_GetReceiveData ( unsigned char * u8_RxBuffer )
{
	static unsigned char LengthCount=0;

	if( (Receive_State == NOT_EMP))
	{
		if(Index_Read != Index_Write)
		{
			u8_RxBuffer[LengthCount] = Software_Buffer_Read[Index_Read];
			LengthCount++;

			if( Index_Read>=(UART_BUFFER_SIZE-1) ) Index_Read=0;
			else Index_Read++;	
		}
		else 
		{
			LengthBufferRead = LengthCount;
			LengthCount=0;
			Receive_State = EMPTY;
		}
	}

	return LengthBufferRead;

}

unsigned char Uart_GetReceiveState ( void )
{
	return Receive_State;
}

void Uart_RxMainFunction ( void )
{
	Software_Buffer_Read[Index_Write] = (unsigned char)(UART1->DATA);
	
	if(Index_Write >= (UART_BUFFER_SIZE-1) ) Index_Write=0;
	else Index_Write++;

	Receive_State = NOT_EMP;
}

void LPUART1_RxTx_IRQHandler(void)
{
	Uart_RxMainFunction();
} 

/*=============================================================================
							        MAIN UART TEST
=============================================================================*/

/*
static unsigned char TestDataSend[5]= {'A','B','C','D','-'};
static unsigned char TestReadData[20];
static unsigned int length=0;

void UART_MAIN_TEST(void)
{
	SOSC_Init_8Mhz();
	SPLL_Init(Div_2,Div_2);
	Run_Mode_Clock(SPLLDIV2_CLK, RunDiv_2, RunDiv_2, RunDiv_3);
  //CheckClock();
	
	Gpio_Init();

	LPIT_Init_CH0(60000);

	Uart_Init();
	
	while(1)
	{

		if( Uart_GetReceiveState() == NOT_EMP )
		{
			length = Uart_GetReceiveData(TestReadData);
		}			
		else 
		{
			if(length!=0)
			{
				Gpio_TogglePin(PortD,LEDBLUE);
				LPIT_CH0_Delay_ms(3000);
				Gpio_TogglePin(PortD,LEDBLUE);

				length=0;
				BufferClear(TestReadData,sizeof(TestReadData));
			}
		}
		
		LPIT_CH0_Delay_ms(2);
		
	}
}
*/

/*=============================================================================*/






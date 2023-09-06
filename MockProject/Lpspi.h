
#ifndef _SPI_
#define _SPI_

#include "S32K144.h"
#include "Lpspi_Register.h"

/* Pin number        | Function
* ----------------- |------------------
* PTB14             | LPSPI1_SCK
* PTB15							| LPSPI1_SIN
* PTB16			        | LPSPI1_SOUT
* PTB17			        | LPSPI1_PCS3 
*/

void SPI_MAIN_TEST(void);

void SPI1_Init(void);
void SPI1_Transmit(unsigned short *Data);

#endif /* _SPI_ */






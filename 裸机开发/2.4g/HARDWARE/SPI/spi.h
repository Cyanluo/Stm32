#ifndef _SPI_H_
#define _SPI_H_

#include "sys.h"

void SPI2_Init(void);
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler);
u8 SPI2_RW_Byte(u8 TxData);


#endif

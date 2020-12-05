#include "spi.h"

void SPI2_Init(void)
{
	SPI_InitTypeDef SPI_Initstruct;
	GPIO_InitTypeDef GPIO_Initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstruct);
	
	SPI_Initstruct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_16;
	SPI_Initstruct.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_Initstruct.SPI_CPOL=SPI_CPOL_Low;
	SPI_Initstruct.SPI_CRCPolynomial=7;
	SPI_Initstruct.SPI_DataSize=SPI_DataSize_8b;
	SPI_Initstruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_Initstruct.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_Initstruct.SPI_Mode=SPI_Mode_Master;
	SPI_Initstruct.SPI_NSS=SPI_NSS_Soft;
	SPI_Init(SPI2,&SPI_Initstruct);
	
	SPI_Cmd(SPI2,ENABLE);
}

//SPI 速度设置函数
//SpeedSet:
//SPI_BaudRatePrescaler_2   2分频   
//SPI_BaudRatePrescaler_8   8分频   
//SPI_BaudRatePrescaler_16  16分频  
//SPI_BaudRatePrescaler_256 256分频 
  
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
  	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;	//设置SPI2速度 
	SPI_Cmd(SPI2,ENABLE); 

}

u8 SPI2_RW_Byte(u8 TxData)
{
	u8 error;
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET)
	{
		error++;
		if(error>200)
			return 0;
	}
	error=0;
	SPI_I2S_SendData(SPI2,TxData);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET)
	{
		error++;
		if(error>200)
			return 0;
	}
	return SPI_I2S_ReceiveData(SPI2);
}





#include "nrf.h"
#include "spi.h"

u8 RX_ADD[RX_ADR_WIDTH]={0x01,0x03,0x05,0x07,0x09};
u8 TX_ADD[TX_ADR_WIDTH]={0x01,0x03,0x05,0x07,0x09};

void Nrf_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG |RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_7 |GPIO_Pin_8;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_Initstruct);
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_Initstruct);
	GPIO_Initstruct.GPIO_Pin = GPIO_Pin_12;				 //PB12上拉 防止W25X的干扰
 	GPIO_Initstruct.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_Initstruct.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_Initstruct);	//初始化指定IO
 	GPIO_SetBits(GPIOB,GPIO_Pin_12);//上拉
	
	GPIO_ResetBits(GPIOG,GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8);
	SPI2_Init();
	
	NRF_CS=1;
	NRF_CE=0;
}

u8 NRF_Write_Reg(u8 reg,u8 val)
{
	u8 status;
	NRF_CS=0;
	status=SPI2_RW_Byte(reg);
	SPI2_RW_Byte(val);
	NRF_CS=1;
	return status;
}

u8 NRF_Read_Reg(u8 reg)
{
	u8 status;
	NRF_CS=0;
	SPI2_RW_Byte(reg);
	status=SPI2_RW_Byte(0xff);
	NRF_CS=1;
	return status;
}

u8 NRF_Read_Buf(u8 reg,u8 *buf,u8 num)
{
	u8 status,i;
	NRF_CS=0;
	status=SPI2_RW_Byte(reg);
	for(i=0;i<num;i++)
	{
		buf[i]=SPI2_RW_Byte(0xff);	
	}
	NRF_CS=1;
	return status;
}

u8 NRF_Write_Buf(u8 reg,u8 *buf,u8 num)
{
	u8 status,i;
	NRF_CS=0;
	status=SPI2_RW_Byte(reg);
	for(i=0;i<num;i++)
	{
		SPI2_RW_Byte(buf[i]);
	}
	NRF_CS=1;
	return status;
}

u8 NRF_Tx_Packet(u8 *buf)
{
	u8 sta;
	SPI2_SetSpeed(SPI_BaudRatePrescaler_8);
	NRF_CE=0;
	NRF_Write_Buf(WR_TX_PLOAD,buf,TX_PLOAD_WIDTH);
	NRF_CE=1;
	while(NRF_IRQ!=0);
	sta=NRF_Read_Reg(STATUS);
	NRF_Write_Reg(NRF_WRITE_REG+STATUS,sta);
	if(sta&MAX_TX)
	{
		NRF_Write_Reg(FLUSH_TX,0xff);
		return MAX_TX;
	}
	if(sta&TX_OK)
	{
		return TX_OK;
	}
	return 0xff;
}

u8 NRF_Rx_Packet(u8 *buf)
{
	u8 sta;
	SPI2_SetSpeed(SPI_BaudRatePrescaler_8);
	sta=NRF_Read_Reg(STATUS);
	NRF_Write_Reg(NRF_WRITE_REG+STATUS,sta);
	if(sta&RX_OK)
	{
		NRF_Read_Buf(RD_RX_PLOAD,buf,RX_PLOAD_WIDTH);
		NRF_Write_Reg(FLUSH_RX,0xff);
		return 1;
	}
	return 0;
}

void NRF_RX_Mode(void)
{
	NRF_CE=0;
	NRF_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADD,RX_ADR_WIDTH);
	NRF_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);
	NRF_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);
	NRF_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);
	NRF_Write_Reg(NRF_WRITE_REG+RF_CH,40);
	NRF_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);
	NRF_Write_Reg(NRF_WRITE_REG+CONFIG,0x0f);
	NRF_CE=1;
}

void NRF_TX_Mode(void)
{
	NRF_CE=0;
	NRF_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,RX_ADD,RX_ADR_WIDTH);
	NRF_Write_Buf(NRF_WRITE_REG+TX_ADDR,TX_ADD,TX_ADR_WIDTH);
	NRF_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);
	NRF_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);
	NRF_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);
	NRF_Write_Reg(NRF_WRITE_REG+RF_CH,40);
	NRF_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);
	NRF_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);
	NRF_CE=1;
}





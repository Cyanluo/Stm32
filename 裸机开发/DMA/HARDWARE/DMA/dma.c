#include "dma.h"

u16 DMA_Count;
DMA_Channel_TypeDef* DMA_Channel;

void DMA_Config(DMA_Channel_TypeDef* channel,u32 padd,u32 sadd,u16 count)
{
	DMA_InitTypeDef DMA_Initstruct;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	
	DMA_DeInit(channel);
	DMA_Initstruct.DMA_BufferSize=count;
	DMA_Initstruct.DMA_DIR=DMA_DIR_PeripheralDST;
	DMA_Initstruct.DMA_M2M=DMA_M2M_Disable;
	DMA_Initstruct.DMA_MemoryBaseAddr=sadd;
	DMA_Initstruct.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA_Initstruct.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA_Initstruct.DMA_Mode=DMA_Mode_Normal;
	DMA_Initstruct.DMA_PeripheralBaseAddr=padd;
	DMA_Initstruct.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA_Initstruct.DMA_PeripheralInc=DMA_MemoryInc_Disable;
	DMA_Initstruct.DMA_Priority=DMA_Priority_Medium;
	DMA_Init(channel,&DMA_Initstruct);
	DMA_Count=count;
	DMA_Channel=channel;
}

void DMA_Enable(DMA_Channel_TypeDef* channel )
{
	DMA_Cmd(channel,DISABLE);
	DMA_SetCurrDataCounter(channel,DMA_Count);
	DMA_Cmd(channel,ENABLE);	
}









#ifndef _DMA_H_
#define _DMA_H_
#include "sys.h"

extern u16 DMA_Count;
extern DMA_Channel_TypeDef* DMA_Channel;

void DMA_Config(DMA_Channel_TypeDef* channel,u32 padd,u32 sadd,u16 count);
void DMA_Enable(DMA_Channel_TypeDef* channel);

#endif

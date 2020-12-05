#ifndef _KEYSCAN_H_
#define _KEYSCAN_H_

#include"stm32f10x.h"

#define KEY_0_DW  1
#define KEY_1_DW  2
#define KEY_2_DW  3
#define KEY_3_DW  4

#define KEY_0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define KEY_1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define KEY_2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define KEY_3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

void Key_Init(void);
u8 KeyScan(u8);

#endif

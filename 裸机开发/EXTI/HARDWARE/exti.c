#include "stm32f10x.h"
#include "exti.h"

void Exti_Init(void)
{
	NVIC_InitTypeDef NVIC_Initstruct;
	EXTI_InitTypeDef EXTI_Initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);	//外部中断与端口映射
	
    EXTI_Initstruct.EXTI_Line=EXTI_Line4 | EXTI_Line3 | EXTI_Line2 ;
	EXTI_Initstruct.EXTI_LineCmd=ENABLE;
	EXTI_Initstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initstruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Initstruct);		
	EXTI_Initstruct.EXTI_Line=EXTI_Line0 ;
	EXTI_Initstruct.EXTI_LineCmd=ENABLE;
	EXTI_Initstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initstruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_Initstruct);//外部中断初始化
	
	NVIC_Initstruct.NVIC_IRQChannel=EXTI0_IRQn ; 
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstruct);
	NVIC_Initstruct.NVIC_IRQChannel=EXTI2_IRQn ; 
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstruct);
	NVIC_Initstruct.NVIC_IRQChannel=EXTI3_IRQn ; 
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstruct);
	NVIC_Initstruct.NVIC_IRQChannel=EXTI4_IRQn ; 
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstruct);
		
}


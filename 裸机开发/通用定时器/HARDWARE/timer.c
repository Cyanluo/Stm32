#include "timer.h"
#include "LED.h"

void Timer3_Init(u16 pre,u16 count)
{
	NVIC_InitTypeDef NVIC_Initstruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitstruct.TIM_Period=count;
	TIM_TimeBaseInitstruct.TIM_Prescaler=pre;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitstruct);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
	NVIC_Initstruct.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Initstruct);
}


void TIM3_IRQHandler()
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		LED1=!LED1;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}




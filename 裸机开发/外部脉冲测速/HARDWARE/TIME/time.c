#include "time.h"

void Tim6_Init(u16 pre,u16 val)
{
	NVIC_InitTypeDef NVIC_Initstruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	
	TIM_DeInit(TIM6);
	TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Down;
	TIM_TimeBaseInitstruct.TIM_Period=val;
	TIM_TimeBaseInitstruct.TIM_Prescaler=pre;
	TIM_TimeBaseInit(TIM6,&TIM_TimeBaseInitstruct);
	
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	
	NVIC_Initstruct.NVIC_IRQChannel=TIM6_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstruct);
	TIM_Cmd(TIM6,ENABLE);
}




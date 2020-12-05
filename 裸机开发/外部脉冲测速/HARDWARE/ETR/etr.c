#include "etr.h"


void ETR3_Init(u16 pre,u16 val)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
	GPIO_InitTypeDef GPIO_Initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_Initstruct);
	
	TIM_DeInit(TIM3);
	TIM_ETRClockMode2Config(TIM3,TIM_ExtTRGPSC_OFF,TIM_ExtTRGPolarity_NonInverted,5);
	
	TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitstruct.TIM_Period=val;
	TIM_TimeBaseInitstruct.TIM_Prescaler=pre;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitstruct);
	TIM_SetCounter(TIM3,0);
	
	TIM_Cmd(TIM3,ENABLE);
}








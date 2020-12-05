#include "pwm_timer3_2.h"

void PWM_Timer3_2_Init(u16 add,u16 pre)
{
	TIM_OCInitTypeDef TIM_OCInitstruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
	GPIO_InitTypeDef GPIO_Initstruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 ,ENABLE );
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_5;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstruct);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE);
	
	TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitstruct.TIM_Period=add;
	TIM_TimeBaseInitstruct.TIM_Prescaler=pre;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitstruct);
	
	TIM_OCInitstruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitstruct.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OCInitstruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitstruct.TIM_Pulse=800;
	TIM_OC2Init(TIM3,&TIM_OCInitstruct);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_Cmd(TIM3,ENABLE);
}









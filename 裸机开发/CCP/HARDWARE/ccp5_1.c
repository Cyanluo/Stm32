#include "ccp5_1.h"

void CCP5_1_Init(u16 add,u16 pre)
{
	NVIC_InitTypeDef NVIC_Initstruct;
	TIM_ICInitTypeDef TIM_ICInitstruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitstruct;
	GPIO_InitTypeDef GPIO_Initstruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	TIM_TimeBaseInitstruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitstruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitstruct.TIM_Period=add;
	TIM_TimeBaseInitstruct.TIM_Prescaler=pre;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitstruct);
	
	TIM_ICInitstruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitstruct.TIM_ICFilter=0x00;
	TIM_ICInitstruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitstruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitstruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM5,&TIM_ICInitstruct);
	
	TIM_ITConfig(TIM5,TIM_IT_Update |TIM_IT_CC1,ENABLE);
	
	NVIC_Initstruct.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Initstruct);
	
	TIM_Cmd(TIM5,ENABLE);
}

u16 ccp_cap_val;//捕获计数器当前值
u8 ccp_cap_sta;//位7置1表示捕获上升沿，位6置1表示捕获下降沿，后六位表示定时器溢出次数

void TIM5_IRQHandler()
{
	if((ccp_cap_sta&(1<<6))==0)//数据还未读走或还未成功捕获
	{
		if(TIM_GetITStatus(TIM5,TIM_IT_CC1)==SET)
		{
			if(ccp_cap_sta&(1<<7))//成功捕获下降沿
			{
				ccp_cap_sta|=1<<6;//下降沿标志置位
				ccp_cap_val=TIM_GetCapture1(TIM5);
				TIM_OC1PolarityConfig(TIM5,TIM_OCPolarity_High);//反转捕获级性
			}
			else
			{
				ccp_cap_val=0;
				ccp_cap_sta=0;
				ccp_cap_sta|=1<<7;
				TIM_SetCounter(TIM5,0);
				TIM_OC1PolarityConfig(TIM5,TIM_OCPolarity_Low);
			}
		}
		if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET)
		{
			if(ccp_cap_sta&(1<<7))//捕获还未完成
			{
				if((ccp_cap_sta&(0x3f))>64)//高电平太长
				{
					ccp_cap_sta|=1<<6;//强制结束
					ccp_cap_val=0xffff;
					TIM_OC1PolarityConfig(TIM5,TIM_OCPolarity_High);//反转捕获级性
				}
				else
					ccp_cap_sta++;
			}
		}
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update |TIM_IT_CC1);//清除中断标志
}








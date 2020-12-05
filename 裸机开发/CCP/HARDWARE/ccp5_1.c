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

u16 ccp_cap_val;//�����������ǰֵ
u8 ccp_cap_sta;//λ7��1��ʾ���������أ�λ6��1��ʾ�����½��أ�����λ��ʾ��ʱ���������

void TIM5_IRQHandler()
{
	if((ccp_cap_sta&(1<<6))==0)//���ݻ�δ���߻�δ�ɹ�����
	{
		if(TIM_GetITStatus(TIM5,TIM_IT_CC1)==SET)
		{
			if(ccp_cap_sta&(1<<7))//�ɹ������½���
			{
				ccp_cap_sta|=1<<6;//�½��ر�־��λ
				ccp_cap_val=TIM_GetCapture1(TIM5);
				TIM_OC1PolarityConfig(TIM5,TIM_OCPolarity_High);//��ת������
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
			if(ccp_cap_sta&(1<<7))//����δ���
			{
				if((ccp_cap_sta&(0x3f))>64)//�ߵ�ƽ̫��
				{
					ccp_cap_sta|=1<<6;//ǿ�ƽ���
					ccp_cap_val=0xffff;
					TIM_OC1PolarityConfig(TIM5,TIM_OCPolarity_High);//��ת������
				}
				else
					ccp_cap_sta++;
			}
		}
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update |TIM_IT_CC1);//����жϱ�־
}








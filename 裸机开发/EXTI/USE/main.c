#include "stm32f10x.h"
#include "LED_J.h"
#include "BEEP.h"
#include "keyscan.h"
#include "exti.h"

int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	LED_init();
	beep_init();
	Key_Init();
	Exti_Init();
	while(1);
}

void EXTI0_IRQHandler()
{
	delay_ms(10);
	if(EXTI_GetITStatus(EXTI_Line0))
	{
		BEEP=~BEEP;
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI2_IRQHandler()
{
	delay_ms(10);
	if(EXTI_GetITStatus(EXTI_Line2))
	{
		LED1=~LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line2);
}	

void EXTI3_IRQHandler()
{
	delay_ms(10);
	if(EXTI_GetITStatus(EXTI_Line3))
	{
		LED2=~LED2;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}

void EXTI4_IRQHandler()
{
	delay_ms(10);
	if(EXTI_GetITStatus(EXTI_Line4))
	{
		LED2=~LED2;
		LED1=~LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}


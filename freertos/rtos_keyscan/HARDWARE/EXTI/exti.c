#include "exti.h"
#include "sys.h"
#include "FreeRTOS.h"
#include "task.h"
#include "key.h"
#include "delay.h"
extern TaskHandle_t LED1Task_Handler;

void EXTI_init(void)
{
	NVIC_InitTypeDef NVIC_Initstruct;
	EXTI_InitTypeDef EXTI_Initstruct;
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_Initstruct.EXTI_Line=EXTI_Line0;
	EXTI_Initstruct.EXTI_LineCmd=ENABLE;
	EXTI_Initstruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Initstruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_Initstruct);
	
	NVIC_Initstruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=5;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_Initstruct);
}

void EXTI0_IRQHandler()
{
	u8 yeidrequest;
	if(EXTI_GetITStatus(EXTI_Line0)==SET)
	{
		delay_xms(20);
		if(key_up==1)
		{	
			yeidrequest=xTaskResumeFromISR(LED1Task_Handler);
			if(yeidrequest==pdTRUE)
			{
				portYIELD_FROM_ISR(yeidrequest);
			}
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}







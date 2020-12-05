#include"LED.h"
#include"stm32f10x.h" 

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_struct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_struct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_struct.GPIO_Pin=GPIO_Pin_5;
	GPIO_struct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB,&GPIO_struct);	
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	
	GPIO_struct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_struct.GPIO_Pin=GPIO_Pin_5;
	GPIO_struct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOE,&GPIO_struct);
	GPIO_SetBits(GPIOE,GPIO_Pin_5);
}

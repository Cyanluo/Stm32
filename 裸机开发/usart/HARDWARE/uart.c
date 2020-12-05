#include "uart.h"

void Usart1_Init(void)
{
	GPIO_InitTypeDef GPIO_Initstruct;
	USART_InitTypeDef USART_Initstruct;
	NVIC_InitTypeDef NVIC_Initstruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	USART_Initstruct.USART_BaudRate=9600;
	USART_Initstruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Initstruct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_Initstruct.USART_Parity=USART_Parity_No;
	USART_Initstruct.USART_StopBits=USART_StopBits_1;
	USART_Initstruct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_Initstruct);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1,ENABLE);
	
	NVIC_Initstruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_Initstruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Initstruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Initstruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_Initstruct);
}

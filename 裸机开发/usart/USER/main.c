#include "uart.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	Usart1_Init();
	while(1);
}

void USART1_IRQHandler(void)
{
	u16 data;
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
	{
		data=USART_ReceiveData(USART1);
		USART_SendData(USART1,data);
	}
}


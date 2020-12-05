#include"stm32f10x.h"
#include"LED_J.h"
#include"BEEP.h"

int main(void)
{
	delay_init();
	LED_init();
	beep_init();
	while(1)
	{
//		GPIOB->ODR&=~(1<<5);
//		GPIOE->ODR&=~(1<<5);
		
//		GPIOB->BRR=1<<5;
//		GPIOE->BRR=1<<5;
		
		LED1=1;
		LED2=0;
		BEEP=1;
		
		delay_ms(1000);
		
//		GPIOB->ODR|=1<<5;
//		GPIOE->ODR|=1<<5;
		
//		GPIOB->BSRR=1<<5;
//		GPIOE->BSRR=1<<5;
		
		LED1=0;
		LED2=1;
		BEEP=0;
		
		delay_ms(1000);
	}
}

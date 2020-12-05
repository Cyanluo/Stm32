#include "stm32f10x.h"
#include "LED_J.h"

void LED_init(void)
{
	RCC->APB2ENR|=1<<3;
	RCC->APB2ENR|=1<<6;
	
	GPIOB->CRL&=0xff0fffff;
	GPIOB->CRL|=0x00300000;
	GPIOE->CRL&=0xff0fffff;
	GPIOE->CRL|=0x00300000;
	
	GPIOB->BSRR=1<<5;
	GPIOE->BSRR=1<<5;
	
//	GPIOB->ODR|=1<<5;
//	GPIOE->ODR|=1<<5;
}

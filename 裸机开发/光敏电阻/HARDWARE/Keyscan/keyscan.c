#include "keyscan.h"
#include "delay.h"

void Key_Init(void)
{
	GPIO_InitTypeDef gpio_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA,ENABLE);
	
	gpio_init.GPIO_Mode=GPIO_Mode_IPU;
	gpio_init.GPIO_Pin=GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Init(GPIOE,&gpio_init);
	
	gpio_init.GPIO_Mode=GPIO_Mode_IPD;
	gpio_init.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA,&gpio_init);
	
}

u8 KeyScan(u8 mode)
{
	static u8 key_up=1;
	if(mode==0)
		key_up=1;
	if(key_up&&(KEY_0==0||KEY_1==0||KEY_2==0||KEY_3==1))
	{
		delay_ms(3);
		key_up=0;
		if(KEY_0==0)
			return KEY_0_DW;
		else if(KEY_1==0)
			return KEY_1_DW;
		else if(KEY_2==0)
			return KEY_2_DW;
		else if(KEY_3==1)
			return KEY_3_DW;
		else
			key_up=1;
	}
	else if(KEY_0==1&&KEY_1==1&&KEY_2==1&&KEY_3==0)
		key_up=1;
	return 0;
	
		
}

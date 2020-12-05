#include"key.h"
#include"delay.h"

void key_init(void)
{
	GPIO_InitTypeDef GPIO_Initstruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOE,ENABLE);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_Initstruct);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOE,&GPIO_Initstruct);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOE,&GPIO_Initstruct);
	
	GPIO_Initstruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Initstruct.GPIO_Pin=GPIO_Pin_4;
	GPIO_Initstruct.GPIO_Speed=GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOE,&GPIO_Initstruct);
}

u8 key_scan(u8 mode)
{
	static u8 memary=1;
	delay_init();
	if(mode==0)
		memary=1;
	if(memary==1)
	{
		if(key0==0||key1==0||key2==0||key_up==1)
		{
			memary=0;
			delay_ms(5);
			if(key0==0||key1==0||key2==0||key_up==1)
			{
				if(key0==0) return KEY0_DOWN;
				else if(key1==0) return KEY1_DOWN;
				else if(key2==0) return KEY2_DOWN;
				else if(key_up==1) return KEY_UP_DOWN;
			}else
				memary=1;
		}
	}else if(key0==1&&key1==1&&key2==1&&key_up==0)
				memary=1;
	return 0;
}












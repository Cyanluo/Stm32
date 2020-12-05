#include"stm32f10x.h"
#include"LED.h"
#include"delay.h"
#include"timer.h"

int main(void)
{
	LED_init();
	delay_init();
	Timer3_Init(2999,23999);
	TIM_Cmd(TIM3,ENABLE);
	while(1)
	{
		LED0=!LED0;
		delay_ms(500);
	}
}


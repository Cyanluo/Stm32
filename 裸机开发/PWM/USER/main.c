#include"stm32f10x.h"
#include"LED.h"
#include"delay.h"
#include"timer.h"
#include"pwm_timer3_2.h"

int main(void)
{
	u16 pwm=0;
	LED_init();
	delay_init();
	PWM_Timer3_2_Init(1000,0);
	while(1)
	{
		for(pwm=0;pwm<1000;pwm++)
		{
			TIM_SetCompare2(TIM3,pwm);
			delay_ms(1);
		}	
		
		for(pwm=1000;pwm>0;pwm--)
		{
			TIM_SetCompare2(TIM3,pwm);
			delay_ms(1);
		}
	}
}


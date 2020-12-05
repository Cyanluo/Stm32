#include"stm32f10x.h"
#include"LED.h"
#include"delay.h"
#include"ccp5_1.h"
#include"pwm_timer3_2.h"
#include"usart.h"

extern u16 ccp_cap_val;//捕获计数器当前值
extern u8 ccp_cap_sta;//位7置1表示捕获上升沿，位6置1表示捕获下降沿，后六位表示定时器溢出次数


int main(void)
{
//	u16 pwm=0;
	u32 temp;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_init();
	delay_init();
	uart_init(115200);
	CCP5_1_Init(0xffff,71);//每计一次数1us
	PWM_Timer3_2_Init(1000,0);
	while(1)
	{
/*		for(pwm=0;pwm<1000;pwm++)
		{
			TIM_SetCompare2(TIM3,pwm);
			delay_ms(1);
		}	
		
		for(pwm=1000;pwm>0;pwm--)
		{
			TIM_SetCompare2(TIM3,pwm);
			delay_ms(1);
		}*/
		TIM_SetCompare2(TIM3,TIM_GetCapture2(TIM3)+1);
		if(TIM_GetCapture2(TIM3)>=1000)
			TIM_SetCompare2(TIM3,0);
		delay_ms(1);
		
		if(ccp_cap_sta&(1<<6))
		{
			temp=65536*(ccp_cap_sta&0x3f);
			temp+=ccp_cap_val;
			printf("WIDTH:%d us\r\n",temp);
			ccp_cap_sta=0;
		}
	}
}


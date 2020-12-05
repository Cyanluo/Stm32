#include"stm32f10x.h"
#include"LED.h"
#include"delay.h"
#include"time.h"
#include"etr.h"
#include"speed.h"
#include"lcd.h"
#include"usart.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_init();
	delay_init();
	uart_init(115200);//串口初始化
	ETR3_Init(0,0xffff);//外部脉冲计数
	Tim6_Init(7199,4999);	//0.5s进中断
	LCD_Init();
	POINT_COLOR=BLUE;
	LCD_ShowString(90,200,200,16,24,"speed=  .   m/s");
	LCD_ShowString(90,250,200,16,24,"count=");
	POINT_COLOR=BLACK;
	while(1)
	{		
		printf("count=%f\r\n",speed.L_speed);
		delay_ms(200);
		LED0=0;
		LED1=1;
		delay_ms(200);
		LED1=0;
	}
}

void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update)==SET)
	{
		LED0=1;
		Get_Speed();//更新速度
	}
}

#include "speed.h"
#include "lcd.h"

SPEED speed;

void Get_Speed(void)
{
	float len;
	TIM_Cmd(TIM6,DISABLE);
	TIM_Cmd(TIM3,DISABLE);
	speed.L_count=TIM_GetCounter(TIM3);//���¼���ֵ
	LCD_ShowxNum(162,250,speed.L_count,3,24,0);//��ʾ����ֵ
	TIM_SetCounter(TIM3,0);
	len=(speed.L_count/20.0)*(2*3.14*radius);//����·��xxcm
	speed.L_speed=len*2/100;//�����ٶ�m/s
	LCD_ShowxNum(162,200,(u8)speed.L_speed,2,24,0);
	LCD_ShowxNum(198,200,(u8)(speed.L_speed*1000)%1000,3,24,0);
	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	TIM_Cmd(TIM6,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
}

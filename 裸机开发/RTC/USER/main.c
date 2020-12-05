#include"stm32f10x.h"
#include"LED.h"
#include"delay.h"
#include"lcd.h"
#include"keyscan.h"
#include"rtc.h"
#include"usart.h"

int main(void)
{
	u8 key,flag=0;
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Key_Init();
	beep_init();
	uart_init(115200);
	RTC_Init();
	LCD_Init();
    POINT_COLOR=RED;//设置字体为红色 	
	RTC_Alarm_Set(2019,10,6,18,5,30);
	while(1)
	{
		LCD_ShowNum(105,162,calendar.hour,2,24);
		LCD_ShowChar(130,162,':',24,0);	
		LCD_ShowNum(140,162,calendar.min,2,24);
		LCD_ShowChar(165,162,':',24,0);	
		LCD_ShowNum(175,162,calendar.sec,2,24);
		switch(calendar.week)
			{
				case 0:
					LCD_ShowString(115,120,200,16,24,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(115,120,200,16,24,"Monday   ");
					break;
				case 2:
					LCD_ShowString(115,120,200,16,24,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(115,120,200,16,24,"Wednesday");
					break;
				case 4:
					LCD_ShowString(115,120,200,16,24,"Thursday ");
					break;
				case 5:
					LCD_ShowString(115,120,200,16,24,"Friday   ");
					break;
				case 6:
					LCD_ShowString(115,120,200,16,24,"Saturday ");
					break;  
			}
			LCD_ShowNum(105,200,calendar.w_year,4,16);									  
			LCD_ShowNum(158,200,calendar.w_month,2,16);									  
			LCD_ShowNum(180,200,calendar.w_date,2,16);
		key=KeyScan(1);
		if(key)
		{
			switch(key)
			{
				case KEY_3_DW :
				if(flag==0)	
				{
					RTC_ITConfig(RTC_IT_SEC |RTC_IT_ALR,DISABLE);
					flag=1;
				}
				else
				{
					RTC_Set(2019,10,6,calendar.hour,calendar.min ,calendar.sec);
					RTC_ITConfig(RTC_IT_SEC |RTC_IT_ALR,ENABLE);
					flag=0;
				}break;
				case KEY_2_DW :
					calendar.hour++;break;
				case KEY_1_DW :
					calendar.min++;break;
				case KEY_0_DW :
					calendar.sec++;break;
			}
		}
	}
}









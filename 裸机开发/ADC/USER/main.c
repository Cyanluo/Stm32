#include "uart.h"
#include "delay.h"
#include "dma.h"
#include "lcd.h"
#include "keyscan.h"
#include "adc.h"

int main(void)
{
	u16 val;
	ADC1_Init();
	delay_init();
	Usart1_Init(115200);
	LCD_Init();
	LCD_ShowString(90,100,250,16,24,"VOL: .V");
	while(1)
	{
		val=Get_Average_Val(ADC_Channel_1,8);
		val=val*(3.3/4096)*100;
		LCD_ShowxNum(138,100,val/100,1,24,0);
		LCD_ShowxNum(162,100,val%100,2,24,0x80);
		delay_ms(200);
	}
}
	


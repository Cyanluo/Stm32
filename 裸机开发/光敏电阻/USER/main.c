#include "uart.h"
#include "delay.h"
#include "dma.h"
#include "lcd.h"
#include "keyscan.h"
#include "adc.h"
#include "light_sensor.h"

int main(void)
{
	u16 val=0;
	ADC3_Init();
	delay_init();
	Usart1_Init(115200);
	LCD_Init();
	LCD_ShowString(90,100,300,16,24,"LIGHT:");
	while(1)
	{
		val=Get_Light_Val();
		LCD_ShowxNum(170,100,val,2,24,0);
		delay_ms(200);
	}
}
	


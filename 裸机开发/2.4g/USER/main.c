#include"stm32f10x.h"
#include"LED.h"
#include"delay.h"
#include"nrf.h"
#include"usart.h"
#include"lcd.h"

u8 RX_Buf[5];
u8 TX_Buf[]="12345";

int main(void)
{
	u8 sta;
	u8 count;
	LED_init();
	delay_init();
	Nrf_Init();
	uart_init(115200);
	LCD_Init();
	while(1)
	{
		NRF_RX_Mode();
		sta=NRF_Rx_Packet(&count);
//		LCD_ShowString(89,159,259,16,24,RX_Buf);
		LCD_ShowxNum(90,159,count,3,24,0);
//		NRF_TX_Mode();
//		sta=NRF_Tx_Packet(TX_Buf);
		LCD_ShowxNum(90,200,sta,1,24,0);
		LED0=1;
		delay_ms(300);
		LED0=0;
		delay_ms(300);
	}
}


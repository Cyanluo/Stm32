#include"stm32f10x.h"
#include"LED_J.h"
#include"BEEP.h"
#include"keyscan.h"
#include"spi.h"
#include"w25qxx.h"
#include"lcd.h"
#include"usart.h"


u8 Send_Buf[100]="spi text";
u8 Receive_Buf[100];
int main(void)
{
	u8 key;
	W25q_Init();
	delay_init();
	LED_init();
	beep_init();
	Key_Init();
	uart_init(115200);
	LCD_Init();
	while(1)
	{	
		key=KeyScan(1);
		if(key)
		{
			switch(key)
			{
				case KEY_0_DW : 
					W25q_Wr_Check(Send_Buf,5,sizeof(Send_Buf));
				LCD_ShowString(100,159,250,16,24,Send_Buf);break;
				case KEY_1_DW :
					W25q_Re_Page(Receive_Buf,6,sizeof(Send_Buf));
				LCD_ShowString(100,200,250,16,24,Receive_Buf);break;
				case KEY_2_DW :					
					BEEP=1;
					delay_ms(500);
					BEEP=0;
					break;
				case KEY_3_DW :
					BEEP=0;break;
			}
		}
	}
}


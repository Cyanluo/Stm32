#include"stm32f10x.h"
#include"LED_J.h"
#include"BEEP.h"
#include"keyscan.h"

int main(void)
{
	u8 key;
	
	delay_init();
	LED_init();
	beep_init();
	Key_Init();
	while(1)
	{	
		key=KeyScan(1);
		if(key)
		{
			switch(key)
			{
				case KEY_0_DW : 
					LED1=0;break;
				case KEY_1_DW :
					LED1=1;break;
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


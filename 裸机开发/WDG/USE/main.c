#include "stm32f10x.h"
#include "LED_J.h"
#include "BEEP.h"
#include "keyscan.h"
#include "wdg.h"


int main(void)
{
//	u8 key;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init();
	LED_init();
	beep_init();
	Key_Init();
//	IWDG_Init(4,625);
	
	LED1=0;
	delay_ms(300);

	WDOG_Init(WWDG_Prescaler_8,0X7F,0X5F);
	while(1)
	{	
/*		key=KeyScan(0);
		if(key)
		{
			switch(key)
			{
				case KEY_3_DW :Feed_IDog();
			}					
		}*/
		LED1=1;
	}
}


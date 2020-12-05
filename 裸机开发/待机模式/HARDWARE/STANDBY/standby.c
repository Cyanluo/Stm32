#include "standby.h"
#include "keyscan.h"
#include "delay.h"

void Standby_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR,ENABLE);
	PWR_WakeUpPinCmd(ENABLE);
	PWR_EnterSTANDBYMode();
}

u8 calctime(void)
{
	u8 t;
	while(KEY_3)
	{
		delay_ms(15);
		t++;
		if(t>=200)
		{
			return 1;
		}
	}
	return 0;
}





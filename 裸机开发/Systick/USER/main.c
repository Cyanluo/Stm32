#include "systick.h"
#include "BEEP.h"

int main(void)
{
	u32 judge;
	beep_init();
	while(1)
	{
		SysTick_Init_Time(50,SYS_ms);
		SysTick_Run();
		do
		{
			judge=Judge_Finish();
		}while(judge==SYS_NO);
		SysTick_Stop();
		BEEP=1;
		SysTick_Init_Time(50,SYS_ms);
		SysTick_Run();
		do
		{
			judge=Judge_Finish();
		}while(judge==SYS_NO);
		SysTick_Stop();
		BEEP=0;
	}
}

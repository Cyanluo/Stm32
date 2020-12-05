#include "systick.h"

void SysTick_Init_Time(u32 time,u8 usoms)//usoms为SYS_ms或者SYS_us
{
	u32 count;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//HCLK/8
	if(usoms==SYS_ms)
		count=SystemCoreClock/8000;
	if(usoms==SYS_us)
		count=SystemCoreClock/8000000;
	SysTick->LOAD=count*time;//装载数据
	SysTick->VAL=0x00;//清空计数器
}

void SysTick_Run(void)		
{
	SysTick->CTRL|=1;//开启定时器
}

void SysTick_Stop(void)
{
	SysTick->CTRL&=~1;//关闭定时器
	SysTick->VAL=0x00;
}

u32 SysTick_Current(void)
{
	u32 val;
	val=SysTick->VAL;//读当前数值
	return val;
}

u8 Judge_Finish(void)
{
	u32 flag;
	flag=SysTick->CTRL&(1<<16);//读标志位
	if(flag==0)
		return SYS_NO;
	if(flag!=0)
		return SYS_YES;
	return 0;
}





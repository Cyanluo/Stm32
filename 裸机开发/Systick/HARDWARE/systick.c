#include "systick.h"

void SysTick_Init_Time(u32 time,u8 usoms)//usomsΪSYS_ms����SYS_us
{
	u32 count;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//HCLK/8
	if(usoms==SYS_ms)
		count=SystemCoreClock/8000;
	if(usoms==SYS_us)
		count=SystemCoreClock/8000000;
	SysTick->LOAD=count*time;//װ������
	SysTick->VAL=0x00;//��ռ�����
}

void SysTick_Run(void)		
{
	SysTick->CTRL|=1;//������ʱ��
}

void SysTick_Stop(void)
{
	SysTick->CTRL&=~1;//�رն�ʱ��
	SysTick->VAL=0x00;
}

u32 SysTick_Current(void)
{
	u32 val;
	val=SysTick->VAL;//����ǰ��ֵ
	return val;
}

u8 Judge_Finish(void)
{
	u32 flag;
	flag=SysTick->CTRL&(1<<16);//����־λ
	if(flag==0)
		return SYS_NO;
	if(flag!=0)
		return SYS_YES;
	return 0;
}





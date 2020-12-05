#include "wdg.h"
#include "LED_J.h"
#include "BEEP.h"

u8  NEW_rlr=0x7f;

void IWDG_Init(u8 pre,u16 rlr)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(pre);//time=(4*2^pre)*rlr/40 (ms)
	IWDG_SetReload(rlr);
	IWDG_ReloadCounter();
	IWDG_Enable();
}

void Feed_IDog()
{
	IWDG_ReloadCounter();
}

void WWDG_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    //WWDG中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占2，子优先级3，组2	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	 //抢占2，子优先级3，组2	
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);//NVIC初始化
}

  void WDOG_Init(u32 pre,u8 rlr,u8 windowdata)
{
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);
	
	NEW_rlr=rlr&NEW_rlr;
	WWDG_SetPrescaler(pre);	
	WWDG_SetWindowValue(windowdata);
	WWDG_Enable(NEW_rlr);
	WWDG_ClearFlag();
	
	WWDG_NVIC_Init();
	
	WWDG_EnableIT();
}

void Feed_WDog(u8 count)
{
	WWDG_Enable(count);
}

void WWDG_IRQHandler(void)
{
	Feed_WDog(NEW_rlr);
	LED2=!LED2;
	WWDG_ClearFlag();
}










#ifndef _WDG_H_
#define _WDG_H_

#include "stm32f10x.h"

void IWDG_Init(u8 pre,u16 rlr);
void Feed_IDog(void);

//void WWDG_Init(u8 tr,u8 wr,u32 fprer);
void WDOG_Init(u32 pre,u8 rlr,u8 windowdata);
void Feed_WDog(u8 count);

#endif

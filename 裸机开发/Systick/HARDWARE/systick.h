#ifndef _SYSTICK_H_
#define _SYSTICK_H_

#include "stm32f10x.h"

#define SYS_ms    0
#define SYS_us    1 
#define SYS_YES   0
#define SYS_NO    1

void SysTick_Init_Time(u32 time,u8 usoms);  //
void SysTick_Run(void);
void SysTick_Stop(void);
u32 SysTick_Current(void);
u8 Judge_Finish(void);


#endif

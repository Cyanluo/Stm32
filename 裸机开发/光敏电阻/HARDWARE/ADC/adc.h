#ifndef _ADC_H_
#define _ADC_H_
#include "sys.h"

void ADC1_Init(void);
void ADC3_Init(void);
u16 Get_Adc(u8 ch);
u16 Get_Average_Val(u8 ch,u8 cn);
u16 Get_Adc3(u8 ch);

#endif

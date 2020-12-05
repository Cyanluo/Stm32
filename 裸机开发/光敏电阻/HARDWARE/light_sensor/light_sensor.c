#include "light_sensor.h"

u16 Get_Light_Val(void)
{
	u16 i,val;
	for(i=0;i<10;i++)
	{
		val+=Get_Adc3(ADC_Channel_6);
	}
	val/=10;
	if(val>4000)
		val=4000;
	val=val/40;
	return 100-val;
}


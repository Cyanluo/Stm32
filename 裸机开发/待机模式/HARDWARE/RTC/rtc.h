#ifndef _RTC_H_
#define _RTC_H_
#include "BEEP.h"
#include "sys.h"

typedef struct 
{
	vu8 hour;
	vu8 min;
	vu8 sec;			
	//公历日月年周
	vu16 w_year;
	vu8  w_month;
	vu8  w_date;
	vu8  week;		 
}_calendar_obj;	

extern _calendar_obj calendar;	//日历结构体


u8 RTC_Init(void);

u8 Is_Leap_Year(u16 year);

u8 RTC_Get(void);

u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);

u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);

u8 RTC_Get_Week(u16 year,u8 month,u8 day);

#endif

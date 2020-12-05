#ifndef _SPEED_H_
#define _SPEED_H_
#include "sys.h"
#define radius 3   //轮半径cm
typedef struct
{
	u16 L_count;//脉冲计数值
	float L_speed;//速度（m/s）
}SPEED;

extern SPEED speed;
void Get_Speed(void);//更新SPEED结构体

#endif

#ifndef _SPEED_H_
#define _SPEED_H_
#include "sys.h"
#define radius 3   //�ְ뾶cm
typedef struct
{
	u16 L_count;//�������ֵ
	float L_speed;//�ٶȣ�m/s��
}SPEED;

extern SPEED speed;
void Get_Speed(void);//����SPEED�ṹ��

#endif

#ifndef _KEY_
#define _KEY_
#include "sys.h"

#define key0   		PEin(4)
#define key1   		PEin(3)
#define key2  		PEin(2)
#define key_up 		PAin(0)
#define	KEY0_DOWN   1
#define KEY1_DOWN   2
#define KEY2_DOWN   3
#define KEY_UP_DOWN 4

void key_init(void);
u8 key_scan(u8 mode);//0 可重复触发 1 不可重复

#endif

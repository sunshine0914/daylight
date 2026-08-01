#ifndef __IN_KEY_H__
#define __IN_KEY_H__

#include "public.h"

sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;


#define K1_PRESS 1
#define K2_PRESS 2
#define K3_PRESS 3
#define K4_PRESS 4
#define K_UNPRESS 0

u8 	key_scan(void);
void  key_press_function();


#endif
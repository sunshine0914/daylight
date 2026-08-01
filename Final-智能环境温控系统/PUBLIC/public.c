#include "public.h"
u8 page=0;
u8 page_change=1;
u8 set_temp=35;
u8  num=20;
u8 max_temper=30;
u8 min_temper=20;

void Delay10us(u16 t)		//@11.0592MHz
{
    while(t--);	
}


void Delay1ms(u16 t)		//@11.0592MHz
{
	u16 i,j;
	for(i=t;i>0;i--)
		for(j=110;j>0;j--);
}

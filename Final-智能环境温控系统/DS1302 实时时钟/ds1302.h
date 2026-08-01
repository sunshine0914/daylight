#ifndef __DS1302_H__
#define __DS1302_H__

#include "public.h"

sbit DS1302_RST=P3^5;
sbit DS1302_CLK=P3^6;
sbit DS1302_IO =P3^4;

extern u8 gWRITE_RTC_ADDR [7];
extern u8 gREAD_RTC_ADDR [7];
extern u8 gDS1302_TIME [7]; 

void ds1302_write_byte(u8 add,u8 dat);
u8 ds1302_read_byte(u8 add);
void ds1302_init(void);
void ds1302_read_time(void);

u8 BCD_DEC(u8 val);
u8 DEC_BCD(u8 val) ;


#endif
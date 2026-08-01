#ifndef __DS18B20_H__
#define __DS18B20_H__

#include "public.h"

sbit DS18B20_PORT=P3^7;


void ds18b20_reset(void);
u8 ds18b20_check(void);
u8 ds18b20_init(void);
void ds18b20_write_byte(u8 dat);
u8 ds18b20_read_bit(void);
u8 ds18b20_read_byte(void);
float ds18b20_read_temperture(void);
void ds18b20_start(void);


#endif
#ifndef __PUBLIC_H__
#define __PUBLIC_H__
#include <intrins.h>
#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;

void Delay10us(u16 t);
void Delay1ms(u16 t);

#define max_temper_add  0x00
#define min_temper_add  0x01

extern  u8  page;
extern u8  num;
extern u8 page_change;
extern u8  set_temp;
extern u8 max_temper;
extern u8 min_temper;
#endif
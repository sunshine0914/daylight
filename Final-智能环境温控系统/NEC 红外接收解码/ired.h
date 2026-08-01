#ifndef __IRED_H__
#define __IRED_H__
#include "public.h"
#include "buzzer_fan.h"
#include "bus.h"
#include "at24c02.h"
extern u8 gired_data[4];
extern bit ir_rec_ok;
extern u8 ir_key_code;

sbit  IRED=P3^2;

void ired_init(void);
u8 IR_ReadKey(void);
u8 IRED_Key(void);
void ired_function();
#endif
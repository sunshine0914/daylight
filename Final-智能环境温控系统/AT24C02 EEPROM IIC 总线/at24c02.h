#ifndef __AT24C02_H__
#define __AT24C02_H__

#include "public.h"
#include "iic.h"
void at24c02_write_one_byte(u8 add,u8 dat);
u8 at24c02_read_byte(u8 add);
#endif
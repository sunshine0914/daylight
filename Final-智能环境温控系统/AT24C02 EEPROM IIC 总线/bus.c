#include "bus.h"
#include "at24c02.h"

void bus_init(void)
{
	u8 buf_max;//高温放在0x00
	u8 buf_min;//低温放在0x01

	Delay1ms(20); 

    buf_max=at24c02_read_byte(max_temper_add);
	buf_min=at24c02_read_byte(min_temper_add);

	if(buf_max==0xff&&buf_min==0xff)
	{
		at24c02_write_one_byte(0x00,30);
		at24c02_write_one_byte(0x01,20);

		max_temper=30;
		min_temper=20;
	}
	else
	{
		max_temper=buf_max;
		min_temper=buf_min;
	}
}

void bus_save_param(void)
{
	at24c02_write_one_byte(0x00,max_temper);
	at24c02_write_one_byte(0x01,min_temper);
}
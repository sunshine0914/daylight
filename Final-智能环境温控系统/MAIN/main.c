#include "public.h"
#include "lcd1602.h"
#include "in_key.h"
#include "ds18b20.h"
#include "buzzer_fan.h"
#include "bus.h"
#include "at24c02.h"
#include "ds1302.h"
#include "ired.h"
#define EEPROM_ADDRESS	0

void main()

{
	u8 i = 1;
	u16 inter;
	int buf;
	int temp_value;
	u8 temp_buf[6];
	u8 sec,min,hour;
	u8 time_buf[9];

    ired_init();

	LCD1602_init();

	ds18b20_init();

	bus_init();

	ds1302_init();//由于不含纽扣电池所有就没用保持时间的功能
	
	ds18b20_read_temperture();
    ds18b20_read_temperture();
	
    buzzer_fan_init();

	while (1)
	{
		i++;


		if(i>1000)
		{
			i=0;
		}
		if (i % 23 == 0) 
		{
			temp_value = ds18b20_read_temperture() * 10;
		}
		if(i % 300==0)
		{
			ds1302_read_time();
		}
		buf = temp_value;

		if (buf < 0)
		{
			buf = -buf;
			temp_buf[0] = '-';
		}
		else temp_buf[0] = '+';


		temp_buf[1] = buf / 100 + '0';// 十位
		temp_buf[2] = buf % 100 / 10 + '0';// 个位
		temp_buf[3] = '.';
		temp_buf[4] = buf % 100 % 10 + '0';// 小数点后一位
		temp_buf[5] = '\0';


		key_press_function();
		ired_function();


		if (page_change == 1)
		{
			LCD1602_user_clear();
			page_change = 0;
		}

		if (page == 0)
		{

			sec  = BCD_DEC(gDS1302_TIME[0]);
			min  = BCD_DEC(gDS1302_TIME[1]);
			hour = BCD_DEC(gDS1302_TIME[2]);

			time_buf[0] = hour / 10 + '0';
			time_buf[1] = hour % 10 + '0';
			time_buf[2] = ':';
			time_buf[3] = min / 10 + '0';
			time_buf[4] = min % 10 + '0';
			time_buf[5] = ':';
			time_buf[6] = sec / 10 + '0';
			time_buf[7] = sec % 10 + '0';
			time_buf[8] = '\0';


			LCD1602_show_string(0, 0, "TIME:");
			LCD1602_show_string(5, 0, time_buf);

			LCD1602_show_string(0, 1, "TEMP:");
			LCD1602_show_string(5, 1, temp_buf);


			if(temp_value>=max_temper*10)
			{
				fan_work();
				inter = (600 - temp_value)/10;
				if(inter < 10) inter = 10; 
			    beep_alarm(inter);
			}
			else if(temp_value<=min_temper*10)
			{
				fan_nowork();
				beep_alarm(10);
			}
			else
			{
				fan_nowork();
				BEEP=0;
			} 
		}
		else
		{
			LCD1602_show_string(0, 0, "MAX T:");
			LCD1602_WriteNum(6, 0, max_temper);
			LCD1602_show_string(9, 0, "C");

			LCD1602_show_string(0, 1, "MIN T:");
			LCD1602_WriteNum(6, 1, min_temper);
			LCD1602_show_string(9, 1, "C");

		}
	}
}





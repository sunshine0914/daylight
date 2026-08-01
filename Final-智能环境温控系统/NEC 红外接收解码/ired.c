#include "ired.h"

u8 gired_data[4];
bit ir_rec_ok=0;
u8 ir_key_code=0;

void ired_init(void)
{
	IT0 = 1;
	EX0 = 1;
	EA = 1;
	IRED = 1;
    ir_rec_ok = 0;
    ir_key_code = 0;
	gired_data[1] = gired_data[2] = gired_data[3] = gired_data[0] = 0;
}


void ired(void) interrupt 0
{
	u8 i = 0;
	u8 j = 0;
	u16 time_cnt = 0;
	u8 ired_high_time = 0;
	if (IRED == 0)
	{
		time_cnt = 1000;
		while ((!IRED) && (time_cnt))
		{
			Delay10us(1);
			time_cnt--;
			if (time_cnt == 0)return;
		}

		if (IRED)
		{
			time_cnt = 500;
			while (IRED&& time_cnt)
			{
				Delay10us(1);
				time_cnt--;
				if (time_cnt == 0)return;
			}
			for (i = 0; i < 4; i++)
			{
				for (j = 0; j < 8; j++)
				{
					time_cnt = 600;
					while (IRED == 0 && time_cnt)
					{
						Delay10us(1);
						time_cnt--;
						if (time_cnt == 0) return;
					}
					time_cnt = 20;
					while (IRED)
					{
						Delay10us(10);
						ired_high_time++;
						if (ired_high_time > 20)return;
					}
					gired_data[i] >>= 1;
					if (ired_high_time >= 8)
					{
						gired_data[i] |= 0x80;
					}
					ired_high_time = 0;
				}
			}
		}
		if (gired_data[2] != ~gired_data[3])
		{
			for (i = 0; i < 4; i++)
			{
				gired_data[i] = 0;
			}
			return;
		}
		ir_key_code = gired_data[2];
        ir_rec_ok = 1; 
		
	}
}

u8 IRED_Key(void)
{
	u8 temp=0;
	if(ir_rec_ok==1)
	{
		temp=ir_key_code;
		ir_rec_ok=0;
	}
	return temp;
}

void ired_function(void)
{
	u8 key = IRED_Key();
	if(key == 0)
	{
		return;		// 没有按键按下，直接返回
	}

	switch(key)
	{		
		case 0x0c:
		 if(page==1&&max_temper<60)
		 {
			max_temper++;
		 }
			break;
		case 0x18:
		if(page==1&&max_temper>min_temper)
		 {
			max_temper--;
		 }
			break;
		case 0x5e:
		if(page==1)
		 {
			max_temper=30;
			if(max_temper <= min_temper)min_temper = max_temper - 1;
		 }
			break;
		case 0x08:
		if(page==1&&min_temper<max_temper)
		 {
			min_temper++;
		 }
			break;
		case 0x1c:
		if(page==1&&min_temper>0)
		 {
			min_temper--;
		 }
			break;
		case 0x5a:
		if(page==1)
		 {
			min_temper=20;if(min_temper >= max_temper)max_temper = min_temper + 1;
		 }
			break;
		case 0x19:
			page=0;
			page_change=1;
			break;
		case 0x0d:
			page=1;
			page_change=1;
			break;
		case 0x42:
			fan_work();
			break;
		case 0x52:
			fan_nowork();
			break;
		case 0x4a:
			beep_alarm(700);
			break;
		case 0x16:
			bus_save_param();
			break;
		default:
		    break;
	}
}































#include "buzzer_fan.h"

void buzzer_fan_init(void)
{
    BEEP = 0;
    buzzer_fan_port  = 0;
}


void beep_alarm(u16 stop_time)
{
	BEEP = 1;
	Delay10us(700);
	BEEP = 0; 
	Delay10us(stop_time);
}


void fan_work()
{
	buzzer_fan_port=1;
}
void fan_nowork()
{
	buzzer_fan_port=0;
}
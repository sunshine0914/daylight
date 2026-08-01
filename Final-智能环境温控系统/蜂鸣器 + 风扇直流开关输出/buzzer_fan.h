#ifndef __BUZZER_FAN_H__
#define __BUZZER_FAN_H__

#include "public.h"

sbit buzzer_fan_port=P1^0;
sbit BEEP=P2^5;

void beep_alarm(u16 stop_time);
void fan_work(void);
void fan_nowork(void);
void buzzer_fan_init(void);
#endif
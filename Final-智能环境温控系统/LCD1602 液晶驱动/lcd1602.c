#include "lcd1602.h"

void LCD1602_write_cmd(u8 cmd)
{
    LCD1602_RS =0;
	LCD1602_RW=0;
	LCD1602_EN=0;
	Delay10us(1);
	LCD1602_PORT=cmd;
	Delay1ms(1);
	LCD1602_EN=1;
	Delay1ms(1);
	LCD1602_EN=0; 
}


void LCD1602_write_dat(u8 dat)
{
	LCD1602_RS=1;
	LCD1602_RW=0;
	LCD1602_EN=0;
	Delay10us(1);
	LCD1602_PORT=dat;
	Delay1ms(1);
	LCD1602_EN=1;
	Delay1ms(1);
	LCD1602_EN=0; 
}

void LCD1602_init(void)
{
     Delay1ms(20);
	 LCD1602_write_cmd(0x38);
	 LCD1602_write_cmd(0x0C);
	 LCD1602_write_cmd(0x06);
	 LCD1602_write_cmd(0x01);
}

void LCD1602_user_clear(void)
{
	LCD1602_write_cmd(0x01);
}

void LCD1602_SET_ADDRESS(u8 x,u8 y)
{
	if(y==0)
	{
		x|=0x80;
	}
	else
	{
		x|=0xC0;
	}
	
	LCD1602_write_cmd(x);	
}

void LCD1602_show_string(u8 x,u8 y,u8* str)
{
	u8 i=0;
	LCD1602_SET_ADDRESS(x,y);
	
	while(1)
	{
     	if(*(str+i)=='\0') break;
		LCD1602_write_dat(*(str+i));
		i++;
	}
}

void LCD1602_WriteNum(u8 x,u8 y,u8 dat)//只能显示0到99的s
{
    u8 i,j;
    i = dat / 10;
    j  = dat % 10;
    LCD1602_SET_ADDRESS(x,y);
    if(i != 0) LCD1602_write_dat(i + '0');
    LCD1602_write_dat(j + '0');
}

 























































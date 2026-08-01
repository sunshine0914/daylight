#ifndef __LCD1602_H__
#define __LCD1602_H__

#include "public.h"

sbit LCD1602_RS = P2^6;   // 寄存器选择引脚：0=指令，1=数据
sbit LCD1602_RW = P2^5;   // 读写选择：0=写操作，1=读操作
sbit LCD1602_EN = P2^7;   // 使能引脚

#define LCD1602_PORT  P0 

void LCD1602_write_cmd(u8 cmd);
void LCD1602_write_dat(u8 dat); 
void LCD1602_init(void);
void LCD1602_user_clear(void);
void LCD1602_SET_ADDRESS(u8 x,u8 y);
void LCD1602_show_string(u8 x,u8 y,u8* str);
void LCD1602_WriteNum(u8 x,u8 y,u8 dat);

#endif
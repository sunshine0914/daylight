#include "ds1302.h"

u8 gWRITE_RTC_ADDR[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c}; //秒分时日月周年
u8 gREAD_RTC_ADDR[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d}; //秒分时日月周年

u8 gDS1302_TIME[7]={0x47,0x51,0x13,0x03,0x07,0x06,0x21};

void ds1302_write_byte(u8 add,u8 dat)
{
	u8 i=0;

	DS1302_RST=0;
	Delay10us(1);
	DS1302_CLK=0;
	Delay10us(1);
	DS1302_RST=1;
	Delay10us(1);

	for(i=0;i<8;i++)
	{
		DS1302_IO=add&0x01;
		add>>=1;
	    DS1302_CLK=1;
		Delay10us(1);
		DS1302_CLK=0;
		Delay10us(1);
	}

	for(i=0;i<8;i++)
	{
		DS1302_IO=dat&0x01;
		dat>>=1;
	    DS1302_CLK=1;
		Delay10us(1);
		DS1302_CLK=0;
		Delay10us(1);
	}
	
}

u8 ds1302_read_byte(u8 add)
{
	u8 i=0;
	u8 temp=0;
	u8 value=0;

	DS1302_RST=0;
	Delay10us(1);
	DS1302_CLK=0;
	Delay10us(1);
	DS1302_RST=1;
	Delay10us(1);


	for(i=0;i<8;i++)
	{
		DS1302_IO=add&0x01;
		add>>=1;
	    DS1302_CLK=1;
		Delay10us(1);
		DS1302_CLK=0;
		Delay10us(1);
	}

	for(i=0;i<8;i++)
	{
		temp=DS1302_IO;
		value=(temp<<7)|(value>>1);

		DS1302_CLK=1;
		Delay10us(1);
		DS1302_CLK=0;
		Delay10us(1);
	}



	DS1302_CLK=1;
	Delay10us(1);
	DS1302_IO=0;
	Delay10us(1);
	DS1302_IO=1;
	Delay10us(1);

	 return value;
}

void ds1302_init(void)
{
	u8 i=0;
	
	ds1302_write_byte(0x8e,0x00);//关闭写保护

	for(i=0;i<7;i++)
	{
		ds1302_write_byte(gWRITE_RTC_ADDR[i],gDS1302_TIME[i]);
	}
	ds1302_write_byte(0x8e,0x80);//开启

}

void ds1302_read_time(void)
{
	 u8 i=0;

	 for(i=0;i<7;i++)
	 {
	 	gDS1302_TIME[i]=ds1302_read_byte(gREAD_RTC_ADDR[i]);
	 }
}

u8 BCD_DEC(u8 val)
{
	return (val>>4)*10+(val & 0x0f);
}

u8 DEC_BCD(u8 val)
{
	return ((val/10)<<4)|(val%10);
}
#include <REGX52.H>

sbit DS1302_SCLK=P3^6;

void Timer0_Init(void)   //10us进一次中断
{
	TMOD&=0xF0;
	TMOD|=0x01;
	TL0=0x91;
	TH0=0xFF;
	
	ET0=1;
	EA=1;
	PT0=0;
    TR0=1;	
}

void Timer0_Routine(void)   interrupt 1
{
	DS1302_SCLK=1;
	DS1302_SCLK=0;
}

/**
 ****************************************************************************************************
 * @file        main.c
 * @author      jna
 * @date        2025-09-25
 * @brief       DS1302实时时钟-DS1302底层通信+读写时间封装
 * @email       2944309620@qq.com
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:STC89C52开发板
 *
 ****************************************************************************************************
 */
#include <REGX52.H>
#include "Delay.h"
#include "DS1302_Reg.h"
#include "LCD1602.h"

sbit DS1302_IO=P3^4;
sbit DS1302_CE=P3^5;
sbit DS1302_SCLK=P3^6;

void DS1302_Init(void)  //根据数据手册初始化时序
{
	DS1302_CE=0;
	DS1302_SCLK=0;
} 

void SCLK_H(void)		//时钟高电平表示
{
	DS1302_SCLK=1;
	Delay10us();		//延时也可以去掉,只要满足2MHz以下即可
}

void SCLK_L(void)		//时钟低电平表示
{
	DS1302_SCLK=0;
	Delay10us();		//延时也可以去掉,只要满足2MHz以下即可
}

/*  
  * @brief  发送1字节数据
  * @param  Address 命令字  Data 待发数据
  * @retval 无
*/
void DS1302_Send_Byte(unsigned char Address,unsigned char Data)
{
	unsigned char i;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{
		DS1302_IO=(Address&(0x01<<i));
	    SCLK_H();	
		SCLK_L();
	}
	
	for(i=0;i<8;i++)
	{
		DS1302_IO=Data&(0x01<<i);
		SCLK_H();
		SCLK_L();
	}
	DS1302_CE=0;
}

/*  
  * @brief  接收1字节数据
  * @param  Address 命令字
  * @retval Data 接收的1字节数据
*/
unsigned char DS1302_Read_Byte(unsigned char Address)
{
	unsigned char i,Data=0x00;
	DS1302_CE=1;
	for(i=0;i<8;i++)
	{		
		DS1302_IO=(Address&(0x01<<i));
	    SCLK_H();			
		SCLK_L();	
	}
	
	for(i=0;i<8;i++)
	{
		SCLK_H();
		if(DS1302_IO==1){Data|=(0x01<<i);}	
		SCLK_L();	
	}
	DS1302_CE=0;
	DS1302_IO=0;
	return Data;
}

/*  
  * @brief  关闭写保护
  * @param  Data 待发数据
  * @retval 无
*/
void DS1302_WriteOK(unsigned char Data)
{
	DS1302_Send_Byte(WP,Data);
}

/*  
  * @brief  写秒
  * @param  Data 待发数据
  * @retval 无
*/
void DS1302_WriteSeconds(unsigned char Data)
{
	DS1302_Send_Byte(Write_Seconds,Data);
}

/*  
  * @brief  读秒
  * @param  无
  * @retval Seconds 秒数
*/
unsigned char DS1302_ReadSeconds(void)
{
	unsigned char Data=0x00,Seconds=0;
	Data=DS1302_Read_Byte(Read_Seconds);
	Seconds+=Data&0x0F;  //读低4位秒数(是多少就是多少秒)
	Seconds+=((Data&0x70)>>4)*10; //第4-第6位单位为10秒,这里要x10
	return Seconds;
}

/*  
  * @brief  写分钟
  * @param  Data 待发数据
  * @retval 无
*/
void DS1302_WriteMinutes(unsigned char Data)
{
	DS1302_Send_Byte(Write_Minutes,Data);
}

/*  
  * @brief  读分钟
  * @param  无
  * @retval Minutes 分钟
*/
unsigned char DS1302_ReadMinutes(void)
{
	unsigned char Data=0x00,Minutes=0;
	Data=DS1302_Read_Byte(Read_Minutes);
	Minutes+=Data&0x0F;
	Minutes+=((Data&0x70)>>4)*10;
	return Minutes;
}

void DS1302_WriteHours(unsigned char Data)  //写小时
{
	DS1302_Send_Byte(Write_Hours,Data);
	if((Data&0x80)!=0)
	{
		if((Data&0x20)!=0)
		{
			LCD_ShowString(1,10,"PM");
		}		
		else
		{
			LCD_ShowString(1,10,"AM");
		}
	}
}

unsigned char DS1302_ReadHours(void)   //读小时		24小时制度
{
	unsigned char Data=0x00,Hours=0;
	Data=DS1302_Read_Byte(Read_Hours);
	Hours+=Data&0x0F;
	Hours+=((Data&0x30)>>4)*10;  //与上同理,见详情见DS1302数据手册
	return Hours;
}

unsigned char DS1302_ReadHours_12(void)   //读小时		12小时制度
{
	unsigned char Data=0x00,Hours=0;
	Data=DS1302_Read_Byte(Read_Hours);
	Hours+=Data&0x0F;
	Hours+=((Data&0x10)>>4)*10;  //与上同理,见详情见DS1302数据手册
	return Hours;
}

void DS1302_WriteYears(unsigned char Data)  //写年
{
	DS1302_Send_Byte(Write_Years,Data);
}

unsigned char DS1302_ReadYears(void) 	//读年
{
	unsigned char Data=0x00,Years=0;
	Data=DS1302_Read_Byte(Read_Years);
	Years+=Data&0x0F;
	Years+=((Data&0xF0)>>4)*10;
	return Years;
}

void DS1302_WriteMonths(unsigned char Data)  //写月
{
	DS1302_Send_Byte(Write_Months,Data);
}

unsigned char DS1302_ReadMonths(void) //读月
{
	unsigned char Data=0x00,Months=0;
	Data=DS1302_Read_Byte(Read_Months);
	Months+=Data&0x0F;
	Months+=((Data&0x10)>>4)*10;
	return Months;
}

void DS1302_WriteDates(unsigned char Data)  //写号
{
	DS1302_Send_Byte(Write_Dates,Data);
}

unsigned char DS1302_ReadDates(void) 	//读号
{
	unsigned char Data=0x00,Dates=0;
	Data=DS1302_Read_Byte(Read_Dates);
	Dates+=Data&0x0F;
	Dates+=((Data&0x30)>>4)*10;
	return Dates;
}

/*  
  * @brief  设置时间
  * @param  Year 年(0-99) Month月(1-12) Day 日(1-31) Hour 时(0-23) Minute 分(0-59) Second 秒(0-59)
  * @retval 无
*/
void DS1302_SetTime(unsigned char Year,unsigned char Month,unsigned char Day,
					unsigned char Hour,unsigned char Minute,unsigned char Second)
{
	DS1302_Init();
	DS1302_WriteOK(0x00);   //关闭写保护
	
	DS1302_WriteYears(Year);
	DS1302_WriteMonths(Month);
	DS1302_WriteDates(Day);
	
	DS1302_WriteHours(Hour);
	DS1302_WriteMinutes(Minute);
	DS1302_WriteSeconds(Second);
	
	DS1302_WriteOK(0x80);   //开启写保护
}

/*  
  * @brief  读时间 24时制
  * @param  Year 年(0-99) Month月(1-12) Day 日(1-31) Hour 时(0-23) Minute 分(0-59) Second 秒(0-59)
  * @retval 无
*/
void DS1302_ReadTime(unsigned char *Year,unsigned char *Month,unsigned char *Day,
					unsigned char *Hour,unsigned char *Minute,unsigned char *Second)
{
	*Year=DS1302_ReadYears();
	*Month=DS1302_ReadMonths();
	*Day=DS1302_ReadDates();
	*Hour=DS1302_ReadHours();
	*Minute=DS1302_ReadMinutes();
	*Second=DS1302_ReadSeconds();
}

/*  
  * @brief  读时间 12小时制
  * @param  Year 年(0-99) Month月(1-12) Day 日(1-31) Hour 时(0-23) Minute 分(0-59) Second 秒(0-59)
  * @retval 无
*/
void DS1302_ReadTime_12(unsigned char *Year,unsigned char *Month,unsigned char *Day,
					unsigned char *Hour,unsigned char *Minute,unsigned char *Second)
{
	*Year=DS1302_ReadYears();
	*Month=DS1302_ReadMonths();
	*Day=DS1302_ReadDates();
	*Hour=DS1302_ReadHours_12();
	*Minute=DS1302_ReadMinutes();
	*Second=DS1302_ReadSeconds();
}

/**
 ****************************************************************************************************
 * @file        DS18B20.c
 * @author      jna
 * @date        2025-10-08
 * @brief       DS18B20测温度(初始化,发送命令)
 * @email       2944309620@qq.com
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:STC89C52开发板
 *
 ****************************************************************************************************
 */

#include <REGX52.H>
#include "DS18B20_Command.h"
#include "DS18B20_Communication.h"
#include "INTRINS.h"
#include "LCD1602.h"

#define DS18B20_IO  P3_7

/*Receive_Data用于存储DS18B20中9字节的数据
Write_Scratchpad用于设置高低温触发器,分辨率
Receive_ROMCode用于存储DS18B20的特定64位ROM编码
*/
//高温报警24度,低温报警0度,12位
unsigned char Receive_Data[9]={0},Write_Scratchpad[3]={0x1B,0x00,0x7F},  
			  Receive_ROMCode[8]={0};   

/*  
    * @brief  DS18B20初始化序列,对应数据手册流程图第一步
    * @param  无
    * @retval 无
*/           			  
void DS18B20_InitSequence(void)
{
	unsigned char i;
	DS18B20_IO=0;
	
	i = 227;
	while (--i);  //延时500us
	
	DS18B20_IO=1;
	
	i = 43;
	while (--i);  //延时100us
	
	
	i = 227;
	while (--i);  //延时500us	
	
//	i = 43;  //延时350us  只要满足One-Wire协议时序要求都可以
//	while (--i);
}

/*  
    * @brief  DS18B20发送ROM命令,对应数据手册流程图第二步
    * @param  Command,要发送的是何种命令
    * @retval 无
*/
void DS18B20_Master_Tx_RomCommand(unsigned char Command)
{
	unsigned char m,i,j,Byte=0x00,Flag=1;
	DS18B20_Master_Tx_Byte(Command);
	if(Command==SKIP_ROM)
	{
		;
	}
	else if(Command==READ_ROM)   //读DS18B20的64位代码
	{
		for(m=0;m<8;m++)
		{
			for(j=0;j<8;j++)
			{
				DS18B20_IO=0;
				_nop_();  //延时6微秒
				DS18B20_IO=1;
				_nop_();  //延时6微秒			
				
				if(DS18B20_IO==1)
				{
					Byte|=(0x01<<j);
				}
				if(j==7)
				{
					Receive_ROMCode[m]=Byte;
					Byte=0x00;
				}
				i = 25;
			    while (--i);  //延时60us
			}
		}
	}
	else if(Command==MATCH_ROM)
	{
		;//待续
	}
	else if(Command==SEARCH_ROM)
	{
		;//待续
	}
	else if(Command==ALARM_SEARCH)   //温度报警,LED灯亮
	{
		DS18B20_IO=0;
		_nop_();  //延时6微秒
		DS18B20_IO=1;
		_nop_();  //延时6微秒

		if(DS18B20_IO==0)
		{
			P2_0=0;
		}
		else
		{
			P2_0=1;
		}
	}
}

/*  
    * @brief  DS18B20发送功能命令,对应数据手册流程图第三步
    * @param  Command,要发送的是何种命令
    * @retval 无
*/
void DS18B20_Master_Tx_FunctionCommand(unsigned char Command)
{
	unsigned char Flag=1,i,j,m,Byte=0x00;
	DS18B20_Master_Tx_Byte(Command);
	if(Command==CONVERT_T)
	{
		while(Flag)  //发送读取时隙,直到DS18B20温度转换完成
		{
			DS18B20_IO=0;
			_nop_();  //延时6微秒
			DS18B20_IO=1;
			_nop_();  //延时6微秒
			
			if(DS18B20_IO==1)
			{
				Flag=0;	
			}
			
			i = 25;
			while (--i);  //延时60us
		}

	}
	else if(Command==COPY_SCRATCHPAD)
	{
		while(Flag)  //发送读取时隙,直到数据复制完成
		{
			DS18B20_IO=0;
			_nop_();  //延时6微秒
			DS18B20_IO=1;
			_nop_();  //延时6微秒
			
			if(DS18B20_IO==1)
			{
				Flag=0;	
			}
			
			i = 25;
			while (--i);  //延时60us
		}
	}
	else if(Command==READ_POWER_SUPPLY)
	{
		DS18B20_IO=0;
		_nop_();  //延时6微秒
		DS18B20_IO=1;
		_nop_();  //延时6微秒
		
		if(DS18B20_IO==1)
		{
			Flag=0;	   //表明是外部电源供电
		}
		LCD_ShowNum(1,16,Flag,1);
	}
	else if(Command==RECALL_EEPROM)
	{
		;//上电自动进行,待续
	}
	else if(Command==READ_SCRATCHPAD)  //读存储器数据
	{
		for(m=0;m<9;m++)
		{
			for(j=0;j<8;j++)
			{
				DS18B20_IO=0;
				_nop_();  //延时6微秒
				DS18B20_IO=1;
				_nop_();  //延时6微秒			
				
				if(DS18B20_IO==1)
				{
					Byte|=(0x01<<j);
				}
				if(j==7)
				{
					Receive_Data[m]=Byte;
					Byte=0x00;
				}
				i = 25;
			    while (--i);  //延时60us
			}
		}
	}
	else if(Command==WRITE_SCRATCHPAD)
	{
		DS18B20_Master_Tx_Byte(Write_Scratchpad[0]);
		DS18B20_Master_Tx_Byte(Write_Scratchpad[1]);
		DS18B20_Master_Tx_Byte(Write_Scratchpad[2]);
	}
}


/*  
    * @brief  DS18B20获取温度值(十进制形式)
    * @param  无
    * @retval Temp,即得到的温度值
*/
float DS18B20_GetTemperature(void)
{
	float Temp;
	Temp=Receive_Data[0];
	Temp/=16;
		
	
	Temp+=((Receive_Data[1]&0x07)*16);
	
	if(((Receive_Data[1])&0xF8)!=0)  //根据手册高5位全为1时为负
	{
		Temp=-Temp;
	}
	
	return Temp;
}



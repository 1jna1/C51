/**
 ****************************************************************************************************
 * @file        main.c
 * @author      jna
 * @date        2025-09-26
 * @brief       AT24C02数据存储
 * @email       2944309620@qq.com
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:STC89C52开发板
 *
 ****************************************************************************************************
 */
#include <REGX52.H>
#include "LCD1602.h"
#include "AT24C02.h"
#include "Delay.h"

void main()
{
	unsigned char code Data[]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};	//要存入的数据
	unsigned char Data1,Data2,Data3,Data4,Data5,Data6,Data7,Data8;  //为了读出写入的数据进行显示
	LCD_Init();
	AT24C02_PageWriteData(0x01,Data);  //按页写数据,把Data数组中的数据写入AT24C02中
	Data1=AT24C02_ReadData(0x00);	
	Data2=AT24C02_ReadData(0x01);
	Data3=AT24C02_ReadData(0x02);
	Data4=AT24C02_ReadData(0x03);
	Data5=AT24C02_ReadData(0x04);
	Data6=AT24C02_ReadData(0x05);
	Data7=AT24C02_ReadData(0x06);
	Data8=AT24C02_ReadData(0x07);
	LCD_ShowHexNum(1,1,Data1,2);
	LCD_ShowHexNum(1,4,Data2,2);
	LCD_ShowHexNum(1,7,Data3,2);
	LCD_ShowHexNum(1,10,Data4,2);
	LCD_ShowHexNum(2,1,Data5,2);
	LCD_ShowHexNum(2,4,Data6,2);
	LCD_ShowHexNum(2,7,Data7,2);
	LCD_ShowHexNum(2,10,Data8,2);
	while(1)
	{
		
	}
}


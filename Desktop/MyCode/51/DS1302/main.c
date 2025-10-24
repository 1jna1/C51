/**
 ****************************************************************************************************
 * @file        main.c
 * @author      jna
 * @date        2025-09-25
 * @brief       DS1302实时时钟
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
#include "DS1302.h"
#include "Delay.h"
#include "DS1302_Reg.h"

void main()
{
	unsigned char Year=0,Month=0,Date=0,Hour=0,Minute=0,Second=0;
	LCD_Init();
	
	DS1302_SetTime(0x25,0x09,0x25,0x23,0x59,0x56);  //参数分别表示年月日时分秒,在这里即可修改时间
	
	LCD_ShowString(2,3,":");
	LCD_ShowString(2,6,":");
	LCD_ShowString(1,3,"-");
	LCD_ShowString(1,6,"-");
		
	while(1)		
	{
		DS1302_ReadTime(&Year,&Month,&Date,&Hour,&Minute,&Second);  //去读取时间存放在变量里
		LCD_ShowNum(1,1,Year,2);
		LCD_ShowNum(1,4,Month,2);
		LCD_ShowNum(1,7,Date,2);
		LCD_ShowNum(2,7,Second,2); 
		LCD_ShowNum(2,4,Minute,2);
		LCD_ShowNum(2,1,Hour,2);
	}
}


/**
 ****************************************************************************************************
 * @file        main.c
 * @author      jna
 * @date        2025-10-08
 * @brief       DS18B20测温度
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
#include "DS18B20.h"
#include "DS18B20_Command.h"

void main()
{
	float Temp;  //存放测量到的温度值
	LCD_Init();
	LCD_ShowString(1,1,"Temperature:");
	LCD_ShowString(2,4,".");	
	
	//根据手册要求,主设备访问从设备
	DS18B20_InitSequence();
	DS18B20_Master_Tx_RomCommand(SKIP_ROM);
	DS18B20_Master_Tx_FunctionCommand(WRITE_SCRATCHPAD);   //设置高低温触发器、分辨率
	
	while(1)
	{
		DS18B20_InitSequence();
		DS18B20_Master_Tx_RomCommand(SKIP_ROM);
		DS18B20_Master_Tx_FunctionCommand(CONVERT_T);  //温度转换
		
		DS18B20_InitSequence();
		DS18B20_Master_Tx_RomCommand(SKIP_ROM);
		DS18B20_Master_Tx_FunctionCommand(READ_SCRATCHPAD);  //读取DS18B20所有字节数据
				
	
		Temp=DS18B20_GetTemperature();   //获取温度值
		
		LCD_ShowSignedNum(2,1,Temp,2);
		LCD_ShowNum(2,5,(unsigned int)((Temp-(unsigned char)Temp)*10000)%10000,4);  //显示温度
		
		
		DS18B20_InitSequence();
		DS18B20_Master_Tx_RomCommand(ALARM_SEARCH);	  //搜索触发温度报警的DS18B20
	}
}


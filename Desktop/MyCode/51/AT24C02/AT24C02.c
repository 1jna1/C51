/**
 ****************************************************************************************************
 * @file        main.c
 * @author      jna
 * @date        2025-09-26
 * @brief       AT24C02数据存储-读写数据
 * @email       2944309620@qq.com
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:STC89C52开发板
 *
 ****************************************************************************************************
 */
 
#include <REGX52.H>
#include "I2C.h"
#include "Delay.h"

#define AT24C02_ADDRESS  0xA0   //器件地址(手册中有,每个型号器件地址要求不一样)

void Delay(unsigned int xms);

/*  
  * @brief  按页写数据
  * @param  Reg_Address 页地址 *Data 要写的数据的地址
  * @retval 无
*/
void AT24C02_PageWriteData(unsigned char Reg_Address,unsigned char *Data)  //按页写数据
{
	unsigned char i;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(Reg_Address);
	I2C_ReceiveAck();
	for(i=0;i<8;i++)
	{
		I2C_SendByte(Data[i]);
		I2C_ReceiveAck();
	}
	I2C_Stop();
	Delay(5);  //这里的Delay根据数据手册要求此时AT24C02进入写周期
}

/*  
  * @brief  按字节写数据
  * @param  Reg_Address 字地址 Data 要写的数据
  * @retval 无
*/
void AT24C02_WriteData(unsigned char Reg_Address,unsigned char Data)  //按字节写数据
{
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(Reg_Address);
	I2C_ReceiveAck();
	I2C_SendByte(Data);
	I2C_ReceiveAck();
	I2C_Stop();
	Delay(5);  //这里的Delay根据数据手册要求此时AT24C02进入写周期
}

/*  
  * @brief  按顺序读字节数据
  * @param  Reg_Address 要读的寄存器地址
  * @retval Data 读到的数据
*/
unsigned char AT24C02_ReadData(unsigned char Reg_Address)  
{
	unsigned char Data;
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS);
	I2C_ReceiveAck();
	I2C_SendByte(Reg_Address);
	I2C_ReceiveAck();
	
	I2C_Start();
	I2C_SendByte(AT24C02_ADDRESS|0x01);
	I2C_ReceiveAck();
	Data=I2C_ReadByte();
	I2C_SendAck(1);
	I2C_Stop();
	return Data;
}

//也可以一下子读8位数据,后面需要继续进行完善

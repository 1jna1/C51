/**
 ****************************************************************************************************
 * @file        main.c
 * @author      jna
 * @date        2025-09-26
 * @brief       AT24C02数据存储-底层I2C通信
 * @email       2944309620@qq.com
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:STC89C52开发板
 *
 ****************************************************************************************************
 */

#include <REGX52.H>

sbit SCL=P2^1;
sbit SDA=P2^0;

void SCL_W(unsigned char Bit)
{
	SCL=Bit;
}

void SDA_W(unsigned char Bit)
{
	SDA=Bit;
}

unsigned char SDA_R(void)
{
	unsigned char Bit;
	Bit=SDA;
	return Bit;
}

void I2C_Start(void)
{
	SDA_W(1);
	SCL_W(1);
	SDA_W(0);
	SCL_W(0);
}

void I2C_Stop(void)
{
	SDA_W(0);
	SCL_W(1);
	SDA_W(1);
}

void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		SDA_W(Byte&(0x80>>i));
		SCL_W(1);
		SCL_W(0);
	}
}

unsigned char I2C_ReadByte(void)
{
	unsigned char i,Data=0x00;
	SDA_W(1);
	for(i=0;i<8;i++)
	{
		SCL_W(1);
		if(SDA_R()==1)
		{
			Data|=(0x80>>i);
		}
		SCL_W(0);
	}
	return Data;
}

void I2C_SendAck(unsigned char Bit)
{
	SDA_W(Bit);
	SCL_W(1);
	SCL_W(0);
}

unsigned char I2C_ReceiveAck(void)
{
	unsigned char Ack;
	SDA_W(1);
	SCL_W(1);
	Ack=SDA_R();
	SCL_W(0);
	return Ack;
}

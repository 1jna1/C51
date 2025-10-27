/**
 ****************************************************************************************************
 * @file        DS18B20_Communication.c
 * @author      jna
 * @date        2025-10-08
 * @brief       DS18B20测温度(底层通信,发1,0,发送字节数据)
 * @email       2944309620@qq.com
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:STC89C52开发板
 *
 ****************************************************************************************************
 */
#include <REGX52.H>

#define DS18B20_IO  P3_7

/*  
    * @brief  DS18B20发送1
    * @param  无
    * @retval 无
*/ 
void DS18B20_MasterWrite_1(void)
{
	unsigned char i;	
	
	DS18B20_IO=0;
	
	i = 2;
	while (--i);  //延时10us
	
	DS18B20_IO=1;
	
	i = 29;
	while (--i);  //延时70us
}

/*  
    * @brief  DS18B20发送0
    * @param  无
    * @retval 无
*/
void DS18B20_MasterWrite_0(void)
{
	unsigned char i;
	
	DS18B20_IO=0;
	
	i = 29;
	while (--i);  //延时70us
	
	DS18B20_IO=1;
	
}

/*  
    * @brief  DS18B20发送1字节
    * @param  Byte,要发送的字节数据
    * @retval 无
*/
void DS18B20_Master_Tx_Byte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if((Byte&(0x01<<i))!=0){DS18B20_MasterWrite_1();}
		else {DS18B20_MasterWrite_0();}
	}
}

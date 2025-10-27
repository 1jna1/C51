#ifndef __DS18B20_H__
#define __DS18B20_H__

extern unsigned char Receive_Data[9],Receive_ROMCode[8];

unsigned char DS18B20_InitSequence(void);
void DS18B20_Master_Tx_RomCommand(unsigned char Command);
void DS18B20_Master_Tx_FunctionCommand(unsigned char Command);

float DS18B20_GetTemperature(void);

#endif

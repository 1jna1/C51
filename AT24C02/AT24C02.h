#ifndef __AT24C02_H__
#define __AT24C02_H__

void AT24C02_WriteData(unsigned char Reg_Address,unsigned char Data);
void AT24C02_PageWriteData(unsigned char Reg_Address,unsigned char *Data);
unsigned char AT24C02_ReadData(unsigned char Reg_Address);

#endif

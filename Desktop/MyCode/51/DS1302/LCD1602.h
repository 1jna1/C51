#ifndef __LCD1602_H__
#define __LCD1602_H__

void Delay1ms(void);
unsigned char LCD_ReadState(void);
unsigned char LCD_ReadData(void);
void LCD_WriteCommand(unsigned char Command);
void LCD_WriteData(unsigned char Data);
void LCD_Init(void);
void LCD_ShowChar(unsigned char line,unsigned char column,unsigned char character);
void LCD_ShowString(unsigned char line,unsigned char column,unsigned char *string);
void LCD_ShowNum(unsigned char line,unsigned char column,unsigned int number,unsigned char count);
void LCD_ShowSignedNum(unsigned char line,unsigned char column,int number,unsigned char count);
void LCD_ShowHexNum(unsigned char line,unsigned char column,unsigned int number,unsigned char count);
void LCD_ShowBinNum(unsigned char line,unsigned char column,unsigned int number,unsigned char length);

#endif

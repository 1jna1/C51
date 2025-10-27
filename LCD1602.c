#include <REGX52.H>
#include <INTRINS.H>
#include <math.h>

#define Data_Port  P0

sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_E=P2^7;

void Delay1ms(void)	//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

unsigned char LCD_ReadState(void)
{
	unsigned char State;
	LCD_RS=0;
	LCD_RW=1;
	Delay1ms();
	LCD_E=1;
	State=Data_Port;
	LCD_E=0;
	Delay1ms();
	return State;
}

unsigned char LCD_ReadData(void)
{
	unsigned char Data;
	LCD_RS=1;
	LCD_RW=1;
	Delay1ms();
	LCD_E=1;
	Data=Data_Port;
	LCD_E=0;
	Delay1ms();
	return Data;
}

void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;
	LCD_RW=0;
	Delay1ms();
	Data_Port=Command;
	LCD_E=1;
	Delay1ms();
	LCD_E=0;
	Delay1ms();
}

void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;
	LCD_RW=0;
	Delay1ms();
	Data_Port=Data;
	LCD_E=1;
	Delay1ms();
	LCD_E=0;
	Delay1ms();
}

void LCD_Init(void)
{
	LCD_WriteCommand(0x38);
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x06);
	LCD_WriteCommand(0x01);
}

void LCD_Setcursor(unsigned char line,unsigned char column)
{
	if(line==1)
	{
		LCD_WriteCommand(0x80+(column-1));
	}
	else
	{
		LCD_WriteCommand(0x80+(column-1+0x40));
	}
}

void LCD_ShowChar(unsigned char line,unsigned char column,unsigned char character)
{
	LCD_Setcursor(line,column);
	LCD_WriteData(character);
}

void LCD_ShowString(unsigned char line,unsigned char column,unsigned char *string)
{
	unsigned char i=0;
	LCD_Setcursor(line,column);
	for(i=0;string[i]!='\0';i++)
	{
		LCD_WriteData(string[i]);
	}
}

void LCD_ShowNum(unsigned char line,unsigned char column,unsigned int number,unsigned char count)
{
	unsigned char temp,i;
	LCD_Setcursor(line,column);
	for(i=count;i>0;i--)
	{
		temp=number/pow(10,i-1);
		LCD_WriteData(temp+0x30);
		number-=temp*pow(10,i-1);
	}
}

void LCD_ShowSignedNum(unsigned char line,unsigned char column,int number,unsigned char count)
{
	unsigned char temp,i;
	LCD_Setcursor(line,column);
	if(number>=0)
	{
		LCD_WriteData('+');
		for(i=count;i>0;i--)
		{
			temp=number/pow(10,i-1);
			LCD_WriteData(temp+0x30);
			number-=temp*pow(10,i-1);
		}
	}
	else
	{
		int num=-number;
		LCD_WriteData('-');
		for(i=count;i>0;i--)
		{
			temp=num/pow(10,i-1);
			LCD_WriteData(temp+0x30);
			num-=temp*pow(10,i-1);
		}
	}

}

void LCD_ShowHexNum(unsigned char line,unsigned char column,unsigned int number,unsigned char count)
{
	unsigned char temp,i,j;
	LCD_Setcursor(line,column);	
	for(i=count-1;i>0;i--)
	{
		temp=number/pow(16,i);
		if(temp>=10&&temp<=15)
		{
			LCD_WriteData(temp-10+'A');
		}
		else if(temp>=0&&temp<10)
		{
			LCD_WriteData(temp+'0');
		}
		number-=temp*pow(16,i);
		if(number>=10&&number<=15)
		{
			LCD_WriteData(number-10+'A');
		}
		else if(number>=0&&number<10)
		{
			LCD_WriteData(number+'0');
		}
	}
	if(count==1)
	{
		if(number>=10&&number<=15)
		{
			LCD_WriteData(number-10+'A');
		}
		else if(number>=0&&number<10)
		{
			LCD_WriteData(number+'0');
		}
	}
		
}

void LCD_ShowBinNum(unsigned char line,unsigned char column,unsigned int number,unsigned char length)
{
	unsigned char i,temp;
	LCD_Setcursor(line,column);	
	for(i=length;i>0;i--)
	{
		temp=number/pow(2,i-1);
		LCD_WriteData(temp+'0');
	    number-=temp*pow(2,i-1);
	}
}

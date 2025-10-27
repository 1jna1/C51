#include <REGX52.H>

void Delay10us(void)	//@11.0592MHz  延时10us
{
	unsigned char data i;

	i = 2;
	while (--i);
}

void Delay(unsigned int xms)	//@11.0592MHz
{
	unsigned char data i, j;

	while(xms--)
	{
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);		
	}

}


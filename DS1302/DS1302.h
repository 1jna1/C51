#ifndef __DS1302_H__
#define __DS1302_H__

unsigned char DS1302_ReadSeconds(void);
unsigned char DS1302_ReadMinutes(void);
unsigned char DS1302_ReadHours(void);
unsigned char DS1302_ReadHours_12(void);
unsigned char DS1302_ReadYears(void);
unsigned char DS1302_ReadMonths(void);
unsigned char DS1302_ReadDates(void);

//主函数调用该两个函数即可设置时间,读取时间,其余底层通信可不用管(已封装好)

//注意:使用12小时制度写Hour时 0x xxxx xxxx 最高位(最左边)给1  从左往右数第3位给1表示下午,给0表示上午
//具体看手册

/*  
  * @brief  设置时间
  * @param  Year 年(0-99) Month月(1-12) Day 日(1-31) Hour 时(0-23) Minute 分(0-59) Second 秒(0-59)
  * @retval 无
*/
void DS1302_SetTime(unsigned char Year,unsigned char Month,unsigned char Day,
					unsigned char Hour,unsigned char Minute,unsigned char Second);

/*  
  * @brief  读时间
  * @param  Year 年(0-99) Month月(1-12) Day 日(1-31) Hour 时(0-23) Minute 分(0-59) Second 秒(0-59)
  * @retval 无
*/
void DS1302_ReadTime(unsigned char *Year,unsigned char *Month,unsigned char *Day,
					unsigned char *Hour,unsigned char *Minute,unsigned char *Second);

/*  
  * @brief  读时间 12小时制
  * @param  Year 年(0-99) Month月(1-12) Day 日(1-31) Hour 时(0-23) Minute 分(0-59) Second 秒(0-59)
  * @retval 无
*/
void DS1302_ReadTime_12(unsigned char *Year,unsigned char *Month,unsigned char *Day,
					unsigned char *Hour,unsigned char *Minute,unsigned char *Second);

#endif

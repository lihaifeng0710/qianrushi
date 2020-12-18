#include "timeStamp.h"
//#include "stdio.h"

void transformToDateString(uint_64 timeStamp ,char *dateString);
void transformToDate(uint_64 timeStamp ,uint_64 **dateArry);
void intToString(uint_64 num,uint_8* str,uint_8 len);

//=====================================================================
//函数名称：timeChange
//函数返回：无
//参数说明：ticks：时间戳
//       time：解析后的日期，例:19700101000000(1970-01-01 00:00:00)
//功能概要：时间戳转成字符表示日期
//=====================================================================
void timeChange(uint_64 ticks,uint_8 *curtime)
{
	//62135625600000                 1970年之前的毫秒数      东八区，减8小时
	transformToDateString(ticks*1000+62135625600000-28800*1000,curtime);
}

//将64位时间戳转化为时间字符串
void transformToDateString(uint_64 timeStamp ,char *dateString)
{
    uint_64 year ,month ,day ,hour ,minute ,second ,milliSecond;
    uint_64 *intp[] = {&year ,&month ,&day ,&hour ,&minute ,&second ,&milliSecond };

    transformToDate(timeStamp ,intp);

	intToString(year,dateString,4);
	dateString[4] = '-';
	intToString(month,dateString+5,2);
	dateString[7] = '-';
	intToString(day+1,dateString+8,2);
	dateString[10] = ' ';
	intToString(hour,dateString+11,2);
	dateString[13] = ':';
	intToString(minute,dateString+14,2);
	dateString[16] = ':';
	intToString(second,dateString+17,2);
	dateString[19] = 0;
}

//将64位时间戳转化为时间数组
void transformToDate(uint_64 timeStamp ,uint_64 **dateArry)
{
    uint_64 low ,high ,mid ,t;
    uint_64 year ,month ,day ,hour ,minute ,second ,milliSecond;
    uint_64 daySum[] = {0 ,31 ,59 ,90 ,120 ,151 ,181 ,212 ,243 ,273 ,304 ,334 ,365};
    uint_64 milOfDay = 24 * 3600 * 1000;
    uint_64 milOfHour = 3600 * 1000;

    /*防止超过9999-12-31 23:59:59:999*/
    if(timeStamp > 315537897599999) {
        timeStamp = 315537897599999;
    }

    low = 1;
    high = 9999;

    while(low <= high)
    {
        mid = (low+high)>>1;
        t = ((mid-1) * 365 + (mid-1)/4 - (mid-1)/100 + (mid-1)/400) * milOfDay;

        if(t == timeStamp)
        {
            low = mid + 1;
            break;
        }
        else if(t < timeStamp)
            low = mid + 1;
        else
            high = mid - 1;
    }
    year = low-1;
    uint_64 cc;
    uint_64 aa,bb;
    cc = (year-1) * 365;
    cc += (year-1)/4;
    aa = (year-1)/100;
    bb = (year-1)/400 ;

    cc -= aa;
    cc += bb;

    timeStamp -= cc* milOfDay;

    int isLeapYear = ((year&3) == 0 && year%100!=0) || year%400 == 0;

    for(month = 1 ;(daySum[month] + ((isLeapYear && month > 1) ? 1 : 0)) * milOfDay <= timeStamp && month < 13 ;month ++) {
        if(isLeapYear && month > 1)
            ++daySum[month];
    }
    timeStamp -= daySum[month-1] * milOfDay;

    day = timeStamp / milOfDay;
    timeStamp -= day * milOfDay;

    hour = timeStamp / milOfHour;
    timeStamp -= hour * milOfHour;

    minute = timeStamp / 60000;
    timeStamp -= minute * 60000;

    second = timeStamp / 1000;
    milliSecond = timeStamp % 1000;

    *dateArry[0] = year;
    *dateArry[1] = month;
    *dateArry[2] = day;
    *dateArry[3] = hour;
    *dateArry[4] = minute;
    *dateArry[5] = second;
    *dateArry[6] = milliSecond;
}


void intToString(uint_64 num,uint_8* str,uint_8 len)
{
	uint_8 i;
	uint_8 remainder; //余数
	uint_64 divisor;  //除数

	divisor = num;
	for(i = 0;i < len;i++)
	{
		remainder = divisor % 10;
		divisor = divisor / 10;
		str[len-i-1] = remainder + '0';
	}
}

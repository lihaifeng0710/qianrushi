/*
 * valueType.c
 *
 *  Created on: 2018年5月9日
 *      Author: 13341
 */
#include "valueType.h"

//=====================================================================
//函数名称：IntConvertToStr
//函数返回：无
//参数说明：num：待转换为字符串的数字；str：字符串转换完成后存储的位置；
//功能概要：将指定进制的整型数转为字符串
//=====================================================================
uint_8 *IntConvertToStr(int_32 num,uint_8 *buf)
{
	char *str;
	int temp;
	int sign = 0;                          //标记num的符号
    char *p;
     str = buf;
     p = str;
	  /*负数的话取绝对值并改变标记*/
	  if (num < 0)
	  {
			 num = 0 - num;
			 sign = 1;
	  }
	  /*把数从低位放进字符串*/
	  do
	  {
			 temp = num % 10;    //取num的最后一位
			 *p = temp + '0';
			 p++;
	  }while ((num /= 10) != 0);
	  /*是负数的时候添加‘-’*/
	  if (sign == 1)
	  {
			*(p++) = '-';
	  }
	   /*给字符串的末尾添加 ''/0*/
	  *p = '\0';
	  p--;
	  /*字符串逆置*/
	  while(str < p)
	  {
		   *str = *str + *p;
		   *p = *str - *p;
		   *str = *str - *p;
		   str++;
		   p--;
	  }
	  return buf;
}

//=====================================================================
//函数名称：DoubleConvertToStr
//函数返回：无
//参数说明：num：待转换为字符串的数字；n:保留小数位数；str：字符串转换完成后存储的位置；
//功能概要：将指定进制的浮点数型数转为字符串
//=====================================================================
uint_8 *DoubleConvertToStr(double num,int_32 n,uint_8 *buf)
{
    int     sumI;
    float   sumF;
    int     sign = 0;
    int     temp;
    int     count = 0;
    char *p;
    char *pp;
    char * str;
    str = buf;
    p = str;
    if(num < 0)
    {
        sign = 1;
        num = 0 - num;
    }
    sumI = (int)num;    //sumI is the part of int
    sumF = num - sumI;  //sumF is the part of float
    do
    {
        temp = sumI % 10;
        *(str++) = temp + '0';
    }while((sumI = sumI /10) != 0);
    if(sign == 1)
    {
        *(str++) = '-';
    }
    pp = str;
    pp--;
    while(p < pp)
    {
        *p = *p + *pp;
        *pp = *p - *pp;
        *p = *p -*pp;
        p++;
        pp--;
    }
    *(str++) = '.';     //point
    do
    {
        temp = (int)(sumF*10);
        *(str++) = temp + '0';

        if((++count) == n)
            break;

        sumF = sumF*10 - temp;

    }while(!(sumF > -0.000001 && sumF < 0.000001));
    *str = '\0';
    return buf;
}

//=====================================================================
//函数名称：ArrayCopy
//函数返回：无
//参数说明：dest：复制后存放的数组；source：被复制的数组；len:复制的长度
//功能概要：从源数组复制指定长度的内容到目标数组
//=====================================================================
void ArrayCopy(uint_8 * dest,uint_8*source,uint_16 len)
{
	uint_16 i = 0;
	for(i=0;i<len;i++)
		dest[i]=source[i];
}

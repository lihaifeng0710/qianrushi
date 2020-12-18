/*
 * valueType.c
 *
 *  Created on: 2018��5��9��
 *      Author: 13341
 */
#include "valueType.h"

//=====================================================================
//�������ƣ�IntConvertToStr
//�������أ���
//����˵����num����ת��Ϊ�ַ��������֣�str���ַ���ת����ɺ�洢��λ�ã�
//���ܸ�Ҫ����ָ�����Ƶ�������תΪ�ַ���
//=====================================================================
uint_8 *IntConvertToStr(int_32 num,uint_8 *buf)
{
	char *str;
	int temp;
	int sign = 0;                          //���num�ķ���
    char *p;
     str = buf;
     p = str;
	  /*�����Ļ�ȡ����ֵ���ı���*/
	  if (num < 0)
	  {
			 num = 0 - num;
			 sign = 1;
	  }
	  /*�����ӵ�λ�Ž��ַ���*/
	  do
	  {
			 temp = num % 10;    //ȡnum�����һλ
			 *p = temp + '0';
			 p++;
	  }while ((num /= 10) != 0);
	  /*�Ǹ�����ʱ����ӡ�-��*/
	  if (sign == 1)
	  {
			*(p++) = '-';
	  }
	   /*���ַ�����ĩβ��� ''/0*/
	  *p = '\0';
	  p--;
	  /*�ַ�������*/
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
//�������ƣ�DoubleConvertToStr
//�������أ���
//����˵����num����ת��Ϊ�ַ��������֣�n:����С��λ����str���ַ���ת����ɺ�洢��λ�ã�
//���ܸ�Ҫ����ָ�����Ƶĸ���������תΪ�ַ���
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
//�������ƣ�ArrayCopy
//�������أ���
//����˵����dest�����ƺ��ŵ����飻source�������Ƶ����飻len:���Ƶĳ���
//���ܸ�Ҫ����Դ���鸴��ָ�����ȵ����ݵ�Ŀ������
//=====================================================================
void ArrayCopy(uint_8 * dest,uint_8*source,uint_16 len)
{
	uint_16 i = 0;
	for(i=0;i<len;i++)
		dest[i]=source[i];
}

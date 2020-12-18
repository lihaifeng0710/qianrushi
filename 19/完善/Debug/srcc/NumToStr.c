
#include "NumToStr.h"

//=====================================================================
//�������ƣ�NumToStr_int
//�������أ�ת����ɺ����õ����ַ����׵�ַ����'\0'��β
//����˵����x����ת��Ϊ�ַ��������֣�
//         buf���ַ���ת����ɺ�洢��λ�ã�
//���ܸ�Ҫ��������תΪ�ַ���
//=====================================================================
uint8_t *NumToStr_int(int32_t x,char *buf)
{
	char *str,*p;
	int temp,sign;
	
	sign= 0;              //��Ƿ���
	str = buf;
     p = str;
	  //�����Ļ�ȡ����ֵ���ı���
	  if (x < 0)
	  {
			 x = 0 - x;
			 sign = 1;
	  }
	  //�����ӵ�λ�Ž��ַ���
	  do
	  {
			 temp = x % 10;    //ȡx�����һλ
			 *p = temp + '0';
			 p++;
	  }while ((x /= 10) != 0);
	  //�Ǹ�����ʱ����ӡ�-��
	  if (sign == 1)
	  {
			*(p++) = '-';
	  }
	  //���ַ�����ĩβ��� \0
	  *p = '\0';
	  p--;
	  //�ַ�������
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

//================================================================
//�������ƣ�NumToStr_float
//�������أ�ת����ɺ����õ����ַ����׵�ַ����'\0'��β
//����˵����x����ת����˫���ȸ�������
//          m��ת������С����λ����
//          buf���ַ���ת����ɺ�洢��λ�ã�
//���ܸ�Ҫ����������תΪ�ַ���
//=================================================================
char *NumToStr_float(float x,int num,char *buf)
{
    int    sumI,sign,temp,count; 
    float  sumF;
    char *p;
    char *pp;
    char *str;
    //
    str = buf;
    p = str;
    //
    sign = 0;
    count = 0;
    //
    if(x < 0)
    {
        sign = 1;
        x = 0 - x;
    }
    sumI = (int)x;    //sumI is the part of int
    sumF = x - sumI;  //sumF is the part of float
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

        if((++count) == num)
            break;

        sumF = sumF*10 - temp;

    }while(!(sumF > -0.000001 && sumF < 0.000001));
    *str = '\0';
    return buf;
}

//======================================================================
//�ļ����ƣ�user.h��userͷ�ļ���
//������λ��SD-Arm(sumcu.suda.edu.cn)
//���¼�¼��20181201-20200221
//��Ҫ˵��������gpio.h�ļ���ʵ�ֶԾ���Ӧ�ñ�̣������Ƕ�����״̬�ȱ��
//======================================================================
#ifndef USER_H   //��ֹ�ظ����壨USER_H ��ͷ��
#define USER_H

//��1�����̶����ļ�����
#include "printf.h"
#include "gec.h"
#include "gpio.h"
#include "tm1637.h"
#include "ws2812.h"
#include "adlx345.h"
#include "adc.h"
//��2�����䶯��ָʾ�ƶ˿ڼ����Ŷ��塪����ʵ��ʹ�õ����ŸĶ�
//ָʾ�ƶ˿ڼ����Ŷ���
#define  LIGHT_RED    (PTA_NUM|5)  //��ƣ��������ţ�GEC_56
#define  LIGHT_GREEN  (PTA_NUM|12)  //�̵ƣ��������ţ�GEC_55
#define  LIGHT_BLUE   (PTA_NUM|13)  //���ƣ��������ţ�GEC_54

//��״̬�궨�壨�������ư���Ӧ�������ƽ��Ӳ���ӷ�������
#define  LIGHT_ON       0    //����
#define  LIGHT_OFF      1    //�ư�

//��3�����䶯��UART����ģ�鶨��
#define UART_Debug   2  //UART_2   //���ڳ�����£��޷���ʹ��
#define UART_User    0  //UART_2   //�û�����
#define UART_UE      1  //UART_1   //�û�����
//��4�����Ķ����жϷ������궨��
#define UART_User_Handler   UART0_IRQHandler  //�û������жϺ���
#define UART_UE_Handler UART1_IRQHandler

//�ʵƶ˿ڼ����Ŷ���
#define COLORLIGHT  (PTE_NUM|29)      //�������ţ�GEC_6  (WJ6)
//������ģ�鶨��
#define BEEF (PTC_NUM|4)      //�������ţ�GEC_22  (WJ5)
//�����ģ�鶨��
#define MOTOR (PTC_NUM|2)      //�������ţ�GEC_38  (WJ1)
//�����ģ�鶨��
#define TM1637_CLK  (PTB_NUM|0)    //�������ţ�GEC_49  (WJ4)
#define TM1637_DIO  (PTB_NUM|1)    //�������ţ�GEC_48  
//����ѭ����ģ�鶨��
#define RAY_RIGHT (PTD_NUM|6)     //�Ҳ����Ѱ���������������ţ�GEC_15   (WJ7)
#define RAY_LEFT (PTD_NUM|7)      //������Ѱ���������������ţ�GEC_16
//�������ģ�鶨��
#define RAY_HUMAN (PTD_NUM|6)          //�������ţ�GEC_15    ��WJ7��
//Buttonģ�鶨�弰���Ŷ���
#define Button1 (PTB_NUM|17)
#define Button2 (PTB_NUM|16)
#define Button3 (PTC_NUM|3)
#define Button4 (PTC_NUM|0)
//(7)����������ADCͨ����
#define  ADCSound  (7|1<<8)   //PTD_NUM|6��ADC0_SE7b
//(8)���ٶȴ�����ʹ�õ�I2Cģ�鶨��
#define i2cAcceleration 0    //SDA���ţ�GEC_46��PTB_NUM|3����SCL���ţ� GEC_47��PTB_NUM|2��  (WJ3)
#endif    //��ֹ�ظ����壨USER_H ��β��

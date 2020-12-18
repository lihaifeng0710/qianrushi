//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================

#include "includes.h"   //������ͷ�ļ�


int main(void)
{
	//1. ����������ʹ�õı���
	uint_32  mRuncount;     //��ѭ��������
	//2. �����ж�
	DISABLE_INTERRUPTS;

	//3. ��ʼ������ģ��
	light_init(RUN_LIGHT_RED, LIGHT_OFF);  //��Ƴ�ʼ��
	light_init(RUN_LIGHT_BLUE, LIGHT_OFF);  //���Ƴ�ʼ��
	light_init(RUN_LIGHT_GREEN, LIGHT_ON);  //�̵Ƴ�ʼ��
	uart_init(UART_0,MCGIRCLK, 9600);    //����0ʱ��MCGIRCLK(4000Khz)
	uart_init (UART_1,BUSCLK, 9600);     //����1��2ʹ������ʱ��24000Khz
	uart_init (UART_2,BUSCLK, 9600);     //������ʹ��9600
	uart_send_string(UART_0, "Hello Uart_0!\r\n"); //���ڷ��ͳ�ʼ����ʾ
	uart_send_string(UART_1, "Hello Uart_1!\r\n");
	uart_send_string(UART_2, "Hello Uart_2!\r\n");
	//4. ���йر�������ֵ
	mRuncount=0;            //��ѭ��������
	//5. ʹ��ģ���ж�
	uart_enable_re_int(UART_0);   //ʹ�ܴ���0�����ж�
	uart_enable_re_int(UART_1);   //ʹ�ܴ���1�����ж�
	uart_enable_re_int(UART_2);   //ʹ�ܴ���2�����ж�
	//6. �����ж�
	ENABLE_INTERRUPTS;
    
	//������ѭ��
	//��ѭ����ʼ==================================================================
	for(;;)
	{

		//����ָʾ�ƣ�RUN_LIGHT����˸---------------------------------------------
		mRuncount++;					   //��ѭ������������+1
		if (mRuncount >= RUN_COUNTER_MAX)  //��ѭ�����������������趨�ĺ곣��
		{
			mRuncount=0;				   //��ѭ����������������
			//if(uart_re1=='1')
			//light_change(RUN_LIGHT_BLUE);  //��ɫ����ָʾ�ƣ�RUN_LIGHT_BLUE��״̬�仯

			//else if(uart_re1=='2')
			//light_change(RUN_LIGHT_GREEN);  //��ɫ����ָʾ�ƣ�RUN_LIGHT_BLUE��״̬�仯
			//else
			//light_change(RUN_LIGHT_RED);  //��ɫ����ָʾ�ƣ�RUN_LIGHT_BLUE��״̬�仯

		}
		//���¼����û�����--------------------------------------------------------
	}//��ѭ��end_for
	//��ѭ������==================================================================
}


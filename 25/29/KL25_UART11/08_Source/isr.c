//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================�жϺ�����������===============================
//����0�����жϷ�������
void isr_uart0_re(void)
{
    //uint_8 ch;
    //uint_8 flag = 1;
	flag = 1;
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_0, &flag);
    if (0 == flag)
    {
        uart_send1(UART_0, ch);
    }
    
    ENABLE_INTERRUPTS;
}


//����1�����жϷ�������
void isr_uart1_re(void)
{
    //uint_8 ch;
    //uint_8 flag = 1;
	flag = 1;
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_1, &flag);//2����1�ڷ�
    if (0 == flag)
    {
        uart_send1(UART_1, ch);
    }
    //if(ch=='1')
    //{
    //	light_init(RUN_LIGHT_BLUE, LIGHT_OFF);  //�̵Ƴ�ʼ��
    //	light_init(RUN_LIGHT_RED, LIGHT_ON);  //�̵Ƴ�ʼ��
    //	light_init(RUN_LIGHT_GREEN, LIGHT_OFF);  //�̵Ƴ�ʼ��
    //}
    //else
    //{
    //	light_init(RUN_LIGHT_BLUE, LIGHT_OFF);  //�̵Ƴ�ʼ��
    //	light_init(RUN_LIGHT_RED, LIGHT_OFF);  //�̵Ƴ�ʼ��
    //	light_init(RUN_LIGHT_GREEN, LIGHT_OFF);  //�̵Ƴ�ʼ��
    //}

 
    ENABLE_INTERRUPTS;
}

//����2�����жϷ�������
void isr_uart2_re(void)
{
    //uint_8 ch;
    //uint_8 flag = 1;
	flag = 1;
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_2, &flag);//2����1�ڷ�
    if (0 == flag)
    {
        uart_send1(UART_1, ch);
    }
        
    ENABLE_INTERRUPTS;
}



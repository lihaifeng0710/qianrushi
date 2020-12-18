//===========================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================����===============================
//����1�����жϷ�������
void isr_uart1_re(void)
{
    uint_16 ch;
    uint_8 flag = 1;
    static int i=0;
    
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_TEST, &flag);

	if(i==0)
		my[0]=ch-'0';
	else if(i==1)
		my[1]=ch-'0';
	else if(i==2)
		my[2]=ch-'0';
	else
		my[3]=ch-'0';
	if(i==3)
		VReference=1000*my[0]+100*my[1]+10*my[2]+my[3];
	i++;
	if(i==4)
		i=0;
    if (0 == flag)
    {
        uart_send1(UART_TEST, ch);
    }
    
    ENABLE_INTERRUPTS;
}




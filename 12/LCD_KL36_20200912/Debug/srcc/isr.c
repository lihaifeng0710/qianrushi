//=====================================================================
//�ļ����ƣ�isr.c���жϴ������Դ�ļ���
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�20170801-20191020
//�����������ṩ�жϴ�������̿��
//=====================================================================
#include "includes.h"
//======================================================================
//�жϷ���������ƣ�UART_USER_Handler
//����������UART_USE�����յ�һ���ֽڴ���
//��    �ܣ��յ�һ���ֽڣ�ֱ�ӷ��ظ��ֽ�
//��    ע�����뱾����󣬿�ʹ��uart_get_re_int�������ٽ����жϱ�־�ж�
//          ��1-��UART�����жϣ�0-û��UART�����жϣ�
//======================================================================
void UART_User_Handler(void)
{
	uint8_t ch;
	uint8_t flag;
	int i;
	DISABLE_INTERRUPTS;      //�����ж�
	//------------------------------------------------------------------
	//����һ���ֽ�
	ch = uart_re1(UART_User, &flag);   //���ý���һ���ֽڵĺ�����������ж�λ
	if(flag)   //������
	{
		uart_send1(UART_User,ch);//�ط����յ����ֽ�
	}
	wdog_feed();
		
        
	if(ch=='O')
	{
		gpio_set(LIGHT_RED,LIGHT_ON);  
		gpio_set(LIGHT_GREEN,LIGHT_OFF);
		gpio_set(LIGHT_BLUE,LIGHT_OFF);            
		printf(" LIGHT_RED:ON--\n");   //��������Ƶ�״̬
		LCD_ShowString(160,216,BLACK,GRAY,"       ");
		LCD_ShowString(160,216,RED,GRAY,"OPEN");
		for (i=30;i>2;i=i-2)LCD_DrawCircle(120,275,i,RED);
	}
	else if (ch=='C')
	{
		gpio_set(LIGHT_RED,LIGHT_OFF);  
		gpio_set(LIGHT_GREEN,LIGHT_OFF);
		gpio_set(LIGHT_BLUE,LIGHT_OFF);            
		printf(" LIGHT_RED:OFF--\n");   //��������Ƶ�״̬
		LCD_ShowString(160,216,BLACK,GRAY,"       ");
		LCD_ShowString(160,216,RED,GRAY,"CLOSE");
		for (i=30;i>2;i=i-2)LCD_DrawCircle(120,275,i,WHITE);
	}

	wdog_feed();
	
	//------------------------------------------------------------------
	ENABLE_INTERRUPTS;       //�����ж�
}

void TIMER_USER_Handler()
{
     
    DISABLE_INTERRUPTS;
	timer_clear_int(TIMER_USER);
//	printf("==\r\n");
   
    ENABLE_INTERRUPTS;   //�����ж�
}

/*
 ֪ʶҪ�أ�
 1.���ļ��е��жϴ��������õľ�������豸��װ�õľ��幹�����ڸ���оƬ
 ʱ��ֻ�豣֤�豸�Ĺ����ӿ�һ�£����ɱ�֤���ļ�������жϴ����������κ�
 ���ģ��Ӷ��ﵽоƬ�޹��Ե�Ҫ��
 */

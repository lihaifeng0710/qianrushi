//=====================================================================
//�ļ����ƣ�isr.c���жϴ������Դ�ļ���
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�20170801-20191020
//�����������ṩ�жϴ�������̿��
//=====================================================================
#include "includes.h"
#include <string.h>
//�ڲ���������
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer);

//======================================================================
//�жϷ���������ƣ�UART_USER_Handler
//����������UART_USE�����յ�һ���ֽڴ���
//��    �ܣ��յ�һ���ֽڣ�ֱ�ӷ��ظ��ֽ�
//��    ע�����뱾����󣬿�ʹ��uart_get_re_int�������ٽ����жϱ�־�ж�
//          ��1-��UART�����жϣ�0-û��UART�����жϣ�
//======================================================================
void UART_User_Handler(void)
{

    uint8_t ch,flag,N;
    DISABLE_INTERRUPTS;               //�����ж�
    //-----------------------------------------------------------------------
    ch = uart_re1(UART_User, &flag);   //���ý���һ���ֽڵĺ�����������ж�λ
    //�����ڲ�����CreateFrame������֡
   // uart_send1(UART_User,ch);//�ط����յ����ֽڡ�
    if(CreateFrame(ch,g_uart_recvBuf)!=0)    //��֡�ɹ�
    {
    	uart_sendN(UART_User,length,g_uart_recvBuf+1);
//        for(int i=1;i<=length;i++)
//        {
//            uart_send1(UART_User,g_uart_recvBuf[i]);
//        }

        gpio_set(LIGHT_BLUE,LIGHT_ON);
        //N = g_uart_recvBuf[0]-'0';
        //printf("%d",N);
    	//uart_sendN(UART_User,g_uart_recvBuf,N);

    }
    
   	
	ENABLE_INTERRUPTS;       //�����ж�
	
	
}


//�ڲ����ú���

//===========================================================================
//�������ƣ�CreateFrame
//���ܸ�Ҫ���齨����֡��������֡���ݼ��뵽����֡��
//����˵����Data��         ����֡����
//          buffer:        ����֡����
//�������أ���֡״̬    0-��֡δ�ɹ���1-��֡�ɹ�
//��ע��ʮ����������֡��ʽ
//               ֡ͷ        + ���ݳ���         + ��Ч����    +  ֡β
//           FrameHead   +   len       + ��Ч����    + FrameTail
//===========================================================================

static uint8_t frameLen=0;    //֡�ļ�����
uint8_t frameFlag;            //��֡״̬

//���֡ͷ��o��b��֡�ܳ���4(open/blue)
//���֡ͷ��c��g��֡�ܳ���5(close/green)
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer)
{
    frameFlag=0;            //��֡״̬��ʼ��
    //���ݾ�̬����frameLen��֡
    switch(frameLen)
    {
        case 0:    //��һ������
        {
            length=(Data-'0')+48;
            frameLen++;
            frameFlag=0;        //��֡��ʼ
            break;
        }
        default:    //�������
        {
            //���ݳ��Ƚ������µ�����ֱ��֡βǰһλ
            if(frameLen>=1 && frameLen<=(length-1))
            {
                buffer[frameLen]=Data;
                frameLen++;
                break;
            }

            //����ĩβ������ִ��
            if(frameLen>=(length))
            {
                buffer[frameLen]=Data;     //��֡β���뻺����
                frameFlag=1;    //��֡�ɹ�
                frameLen=0    ;     //������0��׼��������֡
                break;
            }
        }
    }     //switch_END
    return frameFlag;                 //������֡״̬
}

/*
 ֪ʶҪ�أ�
 1.���ļ��е��жϴ��������õľ�������豸��װ�õľ��幹�����ڸ���оƬ
 ʱ��ֻ�豣֤�豸�Ĺ����ӿ�һ�£����ɱ�֤���ļ�������жϴ����������κ�
 ���ģ��Ӷ��ﵽоƬ�޹��Ե�Ҫ��
 */

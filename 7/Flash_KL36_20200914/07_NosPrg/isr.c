//=====================================================================
//�ļ����ƣ�isr.c���жϴ������Դ�ļ���
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�20170801-20191020
//�����������ṩ�жϴ�������̿��
//=====================================================================
#include "includes.h"

//����ʹ�õ����ڲ�����
//isr.cʹ�õ��ڲ�����������
void SecAdd1(uint8_t *p);
//======================================================================
//�жϷ���������ƣ�UART_User_Handler
//����������UART_USE�����յ�һ���ֽڴ���
//��    �ܣ��յ�һ���ֽڣ�ֱ�ӷ��ظ��ֽ�
//��    ע�����뱾����󣬿�ʹ��uart_get_re_int�������ٽ����жϱ�־�ж�
//          ��1-��UART�����жϣ�0-û��UART�����жϣ�
//======================================================================
void UART_User_Handler(void)
{
    uint8_t ch,h;
	uint8_t flag;
    uint8_t flashRead[1024];    //flash��ȡ����
    uint8_t *addr;
    addr=(uint8_t*)Address;

	DISABLE_INTERRUPTS;      //�����ж�
	//------------------------------------------------------------------
	//����һ���ֽ�
	ch = uart_re1(UART_User, &flag);   //���ý���һ���ֽڵĺ�����������ж�λ
	if(flag)   //������
	{
		uart_send1(UART_User,ch);//�ط����յ����ֽ�
		switch(ch)
		{
		 case '?'://�������
			 uart_send_string(UART_User," ����,��ȡ,д���ʽ����:\r\n");
			 uart_send_string(UART_User," ��    �� E��62����\r\n");
			 uart_send_string(UART_User," ��    ȡ R���߼���ַ����62����0�ֽڿ�ʼ�ĵ�ַ��ȡ30�ֽڳ�������\r\n");
			 uart_send_string(UART_User," ��    ȡ A�������ַ�����Ӻ궨��addr��ֱַ�Ӷ�ȡ30�ֽڵ�����\r\n");
			 uart_send_string(UART_User," д    �� W����62����0�ֽڿ�ʼ�ĵ�ַд��30�ֽڳ����ַ���\r\n");
			break;
		//��Flash�߼���ַ
		case 'R':
		case 'r':
			flash_read_logic(flashRead,63,Offset,CNT);
			flag=0;
//				flag=flash_isempty(addr,CNT);
			if(flag)
			{
				uart_send_string(UART_User,"Selected area is empty!\n");
			}
			else
			{
				uart_sendN(UART_User,30,flashRead);
				uart_send_string(UART_User,"\n");
			}

			break;
		//��Flash�����ַ
		case 'A':
		case 'a':
			flash_read_physical(flashRead,Address,CNT);
//				flag=flash_isempty(addr,CNT);
			flag=0;
			if(flag)
			{
				uart_send_string(UART_User,"Selected area is empty!\n");
			}
			else
			{
				uart_sendN(UART_User,30,flashRead);
				uart_send_string(UART_User,"\n");
			}
			break;
		//дFlash
		case 'W':
		case 'w':
			flash_erase(63); //��������
			h=flash_write(63,Offset,CNT,Content);
			if(!h)
			{
				uart_send_string(UART_User,"Write OK��\n");
			}
			else
			{
				uart_send_string(UART_User,"Write Error��\n");
			}
			break;
		//����Flash����
		case 'E':
		case 'e':
			h=flash_erase(63); //��������
			if(!h)
			{
				uart_send_string(UART_User,"Erase OK��\n");
			}
			else
			{
				uart_send_string(UART_User,"Erase Error��\n");
			}
			break;

		default:
			break;
		}
	}
	//------------------------------------------------------------------
	ENABLE_INTERRUPTS;       //�����ж�
}

//=====================================================================
//�������ƣ�SYSTICK_USER_Handler��SysTick��ʱ���жϴ������
//����˵������
//�������أ���
//���ܸ�Ҫ����1��ÿ10ms�жϴ���������һ�Σ���2���ﵽһ��ʱ��������+1
//           ���򣬼��㡰ʱ���֡��롱
//�ر���ʾ����1��ʹ��ȫ�ֱ����ֽ�������gTime[3]���ֱ�洢��ʱ���֡��롱
//          ��2��ע�����о�̬������ʹ��
//=====================================================================
//void SYSTICK_USER_Handler()

void SysTick_Handler()
{
	static uint8_t SysTickCount = 0;
	SysTickCount++;    //Tick��Ԫ+1
	wdog_feed();      //���Ź���ι����
	if (SysTickCount >= 100)
	{
		SysTickCount = 0;
		SecAdd1(gTime);
	}
}



//===========================================================================
//�������ƣ�SecAdd1
//�������أ���
//����˵����*p:Ϊָ��һ��ʱ��������p[3]
//���ܸ�Ҫ���뵥Ԫ+1��������ʱ�ֵ�Ԫ��00:00:00-23:59:59)
//===========================================================================
void SecAdd1(uint8_t *p)
{
	*(p+2)+=1;         //��+1
	if(*(p+2)>=60)     //�����
	{
		*(p+2)=0;       //����
		*(p+1)+=1;      //��+1
		if(*(p+1)>=60)  //�����
		{
			*(p+1)=0;    //���
			*p+=1;       //ʱ+1
			if(*p>=24)   //ʱ���
			{
				*p=0;      //��ʱ
			}
		}
	}
}


/*
 ֪ʶҪ�أ�
 1.���ļ��е��жϴ��������õľ�������豸��װ�õľ��幹�����ڸ���оƬ
 ʱ��ֻ�豣֤�豸�Ĺ����ӿ�һ�£����ɱ�֤���ļ�������жϴ����������κ�
 ���ģ��Ӷ��ﵽоƬ�޹��Ե�Ҫ��
 */

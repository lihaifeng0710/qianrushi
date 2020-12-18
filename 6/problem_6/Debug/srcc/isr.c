//=====================================================================
//�ļ����ƣ�isr.c���жϴ������Դ�ļ���
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�20170801-20191020
//�����������ṩ�жϴ�������̿��
//=====================================================================
#include "includes.h"

//����ʹ�õ����ڲ�����
//isr.cʹ�õ��ڲ�����������
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer);

//======================================================================
//�жϷ���������ƣ�UART_User_Handler
//����������UART_USE�����յ�һ���ֽڴ���
//��    �ܣ��յ�һ���ֽڣ�ֱ�ӷ��ظ��ֽ�
//��    ע�����뱾����󣬿�ʹ��uart_get_re_int�������ٽ����жϱ�־�ж�
//          ��1-��UART�����жϣ�0-û��UART�����жϣ�
//======================================================================
void UART_User_Handler(void)
{
    uint8_t ch,h,a,b,c;
	uint8_t flag;
    uint8_t flashRead[1024];    //flash��ȡ����
    uint8_t *addr;
    uint8_t buf[1024];
    addr=(uint8_t*)Address;

	DISABLE_INTERRUPTS;      //�����ж�
	//------------------------------------------------------------------
	//����һ���ֽ�
	ch = uart_re1(UART_User, &flag);   //���ý���һ���ֽڵĺ�����������ж�λ
	if(CreateFrame(ch,g_uart_recv)!=0)   //��֡�ɹ�
	{
		int i=0;
		uart_send_string(UART_User,"��֡�ɹ���\n");
//		for(int i=0;i<(sizeof(g_uart_recv)/sizeof(g_uart_recv[0]));i++)
//			uart_send1(UART_User,g_uart_recv[i]);
		//�����������������
		//--------------���������ʼ--------------
		a=empty[1]-empty[0]-1;
		b=empty[2]-empty[1]-1;
		c=empty[3]-empty[2]-1;
		if(a==1)
		{
			sector=g_uart_recv[2]-'0';
			if(b==1)
			{
				offset=g_uart_recv[4]-'0';
				if(c==1)
				{
					cnt=g_uart_recv[6]-'0';
					for(int i=8;i<8+cnt;i++)
					{
						buf[i-8]=g_uart_recv[i];
					}
				}
				else if(c==2)
				{
					int m=g_uart_recv[6]-'0';
					int n=g_uart_recv[7]-'0';
					cnt=m*10+n;
					for(int i=9;i<9+cnt;i++)
					{
						buf[i-9]=g_uart_recv[i];
					}
				}
			}
			else if(b==2)
			{
				int m=g_uart_recv[4]-'0';
				int n=g_uart_recv[5]-'0';
				offset=m*10+n;
				if(c==1)
				{
					cnt=g_uart_recv[7]-'0';
					for(int i=9;i<9+cnt;i++)
					{
						buf[i-9]=g_uart_recv[i];
					}
				}
				else if(c==2)
				{
					m=g_uart_recv[7]-'0';
					n=g_uart_recv[8]-'0';
					cnt=m*10+n;
					for(int i=10;i<10+cnt;i++)
					{
						buf[i-10]=g_uart_recv[i];
					}
				}
			}
		}
		else if(a==2)
		{
			int m=g_uart_recv[2]-'0';
			int n=g_uart_recv[3]-'0';
			sector=m*10+n;
			if(b==1)
			{
				offset=g_uart_recv[5]-'0';
				if(c==1)
				{
					cnt=g_uart_recv[7]-'0';
					for(int i=9;i<9+cnt;i++)
					{
						buf[i-9]=g_uart_recv[i];
					}
					//uart_send1(UART_User,sector);
				}
				else if(c==2)
				{
					m=g_uart_recv[7]-'0';
					n=g_uart_recv[8]-'0';
					cnt=m*10+n;
					for(int i=10;i<10+cnt;i++)
					{
						buf[i-10]=g_uart_recv[i];
					}
				}
			}
			else if(b==2)
			{
				m=g_uart_recv[5]-'0';
				n=g_uart_recv[6]-'0';
				offset=m*10+n;
				if(c==1)
				{
					cnt=g_uart_recv[8]-'0';
					for(int i=10;i<10+cnt;i++)
					{
						buf[i-10]=g_uart_recv[i];
					}
				}
				else if(c==2)
				{
					m=g_uart_recv[8]-'0';
					n=g_uart_recv[9]-'0';
					cnt=m*10+n;
					for(int i=11;i<11+cnt;i++)
					{
						buf[i-11]=g_uart_recv[i];
					}
				}
			}
		}
		//--------------�����������--------------
		
		//����������flash����
		switch(g_uart_recv[0])
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
			flag=0;
			flag=flash_isempty(sector,cnt);
			if(flag)
			{
				uart_send_string(UART_User,"Selected area is empty!\n");
			}
			else
			{
				flash_read_logic(flashRead,sector,offset,cnt);
				uart_sendN(UART_User,cnt,flashRead);
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
			flash_erase(sector); //��������
			h=flash_write(sector,offset,cnt,buf);
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
			h=flash_erase(sector); //��������
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
#define Nul    (0x20)       //�ո�     
static uint8_t frameLen=0;    //֡�ļ�����
uint8_t frameFlag;            //��֡״̬
static uint8_t flag_empt=0;
static uint8_t vol1=100;
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer)
{
	frameFlag=0;            //��֡״̬��ʼ��
    //���ݾ�̬����frameLen��֡
    switch(frameLen)
    {
        case 0:    //��һ������
        {
            buffer[0]=Data;
            frameLen++;
            frameFlag=0;        //��֡��ʼ
            break;
        }
        default:
        {
        	if(Data==Nul)
        	{
        		buffer[frameLen]=Data;
        		empty[flag_empt]=frameLen;
        		flag_empt++;
        		frameLen++;
        		break;
        	}
        	else if(flag_empt==4)			//�ڵ��ĸ��ո�
        	{
				int n=buffer[frameLen-2]-'0';		//�����ֽ���
				vol1=n+frameLen-1;			//�ַ�������
				buffer[frameLen]=Data;
				frameLen++;
				flag_empt++;			//ˢ��flag_empt����ֹ�´�ִ�иô����
				break;
        	}
        	else
			{
				if(frameLen<vol1)			//����֡βǰ
        		{
					buffer[frameLen]=Data;
        			frameLen++;
        			break;
				}
				else
				{
					buffer[frameLen]=Data;	//��֡β
					frameFlag=1;		//��֡���
					frameLen=0;		//���㣬Ϊ��һ����֡��׼��
					vol1=100;			//���㣬Ϊ��һ����֡��׼��
					flag_empt=0;	//���㣬Ϊ��һ����֡��׼��
					break;
				}
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

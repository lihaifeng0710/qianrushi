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
//�жϷ���������ƣ�UART_USER_Handler
//����������UART_USE�����յ�һ���ֽڴ���
//��    �ܣ��յ�һ���ֽڣ�ֱ�ӷ��ظ��ֽ�
//��    ע�����뱾����󣬿�ʹ��uart_get_re_int�������ٽ����жϱ�־�ж�
//          ��1-��UART�����жϣ�0-û��UART�����жϣ�
//======================================================================
void UART_User_Handler(void)
{
    uint8_t ch;
	uint8_t flag,mFlag;
    uint32_t i;
    uint16_t yushu;
    int  count,setnum;
    uint8_t a;
    uint16_t len;
    uint8_t flashRead[2048];


	DISABLE_INTERRUPTS;      //�����ж�
	//------------------------------------------------------------------
	//����һ���ֽ�
	//��1������һ���ֽ�
	ch = uart_re1(UART_User, &flag);   //���ý���һ���ֽڵĺ�����������ж�λ

	if(flag==0)  goto UARTA_IRQHandler_Exit;     //��û�гɹ��������ݣ�ֱ���˳�
	//��2��������֡���򣬶Խ��յ���������֡
	gcRecvLen = emuart_recv(ch,gcRecvBuf);         //��֡���������֡���ʱ���ط�0֡��
	if(gcRecvLen == 0) goto UARTA_IRQHandler_Exit;//δ��ֱ֡���˳���ֱ���˳�

    //printf("Enter Isr....\n");
    if(gcRecvBuf[0]==11&&strncmp((char *)(gcRecvBuf+1),"auart?",6) == 0)
    {
        uart_send_string(UART_User,"Yes,I am an emuart!!");                   //����λ�����֣�ȷ��ͨ�Ź�ϵ
        uart_send_string(UART_User,(uint8_t *)MCU_TYPE);
    }
//��������⣺��flashRead�̶���1024
	if(gcRecvBuf[0]!=0xFF)
    {

		   switch(gcRecvBuf[0])
		   {
		        case'r':
		        	len=(gcRecvBuf[4]<<8)|gcRecvBuf[5];
					flash_read_logic(flashRead,gcRecvBuf[1],(gcRecvBuf[2]<<8)|gcRecvBuf[3],len);
					mFlag=1;
					for(i=0;i<len;i++)   //�п�
					{
					   if(flashRead[i]!=0xFF)
					   {
						   mFlag=0;
						   break;
					   }
					}

					if(mFlag==1)
						uart_send_string(UART_User," selected area is empty1\n");
					else
						uart_sendN(UART_User,len,flashRead);

//					uart_sendN(UART_User,gcRecvBuf[4],gcRecvBuf);
					//��ԭ��־��������������
					memset(gcRecvBuf,0xFF,gcRecvBuf[5]);
					mFlag=1;
					 break;

				case'a':

					flash_read_physical(flashRead,(gcRecvBuf[1]<<24)|(gcRecvBuf[2]<<16)|(gcRecvBuf[3]<<8)|gcRecvBuf[4],gcRecvBuf[5]);
//					uart_sendN(UART_User,gcRecvBuf[5],flashRead);
					mFlag=1;
					for(i=0;i<gcRecvBuf[5];i++)   //�п�
					{
					   if(flashRead[i]!=0xFF)
					   {
						   mFlag=0;
						   break;

					   }
					}
					if(mFlag==1)
						uart_send_string(UART_User," selected area is empty2\n");
					else
					    uart_sendN(UART_User,gcRecvBuf[5],flashRead);


					//��ԭ��־��������������
					memset(gcRecvBuf,0xFF,gcRecvBuf[5]);
					mFlag=1;

				 break;
				case 'w':
					mFlag=flash_erase(gcRecvBuf[1]);
					mFlag=flash_write(gcRecvBuf[1], (gcRecvBuf[2]<<8)|gcRecvBuf[3],gcRecvBuf[4],&gcRecvBuf[5]);

					if(mFlag==0)
						uart_send_string(UART_User,"Write OK��!\n");
					else
						uart_send_string(UART_User,"Write error��!\n");

//					uart_sendN(UART_User,gcRecvBuf[5],gcRecvBuf);

					memset(gcRecvBuf,0xFF,gcRecvBuf[5]);
					mFlag=1;

				 break;
				case 'W':
					mFlag=flash_erase(gcRecvBuf[1]);
					len=(gcRecvBuf[4]<<8)|gcRecvBuf[5];
					mFlag=flash_write(gcRecvBuf[1], (gcRecvBuf[2]<<8)|gcRecvBuf[3],len,&gcRecvBuf[6]);

					if(mFlag==0)
						uart_send_string(UART_User,"Write OK��!\n");
					else
						uart_send_string(UART_User,"Write error��!\n");

//					uart_sendN(UART_User,gcRecvBuf[5],gcRecvBuf);

					memset(gcRecvBuf,0xFF,gcRecvBuf[6]);
					mFlag=1;

				 break;
				case 'e':
					mFlag=flash_erase(gcRecvBuf[1]);
//					uart_sendN(UART_User,gcRecvBuf[5],gcRecvBuf);

					if(mFlag==0)
						uart_send_string(UART_User,"erase OK��!\n");
					else
						uart_send_string(UART_User,"erase error��!\n");


					//��ԭ��־��������������
					memset(gcRecvBuf,0xFF,gcRecvBuf[5]);
					mFlag=1;
				 break;
				case 'x':
					//mFlag=flash_erase(gcRecvBuf[1]);
					len=(gcRecvBuf[4]<<8)|gcRecvBuf[5];
					mFlag=flash_write(gcRecvBuf[1], (gcRecvBuf[2]<<8)|gcRecvBuf[3],len,&gcRecvBuf[6]);
					
					if(mFlag==0)
						uart_send_string(UART_User,"Write OK��!\n");
					else
						uart_send_string(UART_User,"Write error��!\n");

//					uart_sendN(UART_User,gcRecvBuf[5],gcRecvBuf);

					memset(gcRecvBuf,0xFF,gcRecvBuf[6]);
					mFlag=1;

				 break;
		        case'q':

		        	len=(gcRecvBuf[4]<<8)|gcRecvBuf[5];
		        	setnum=len/1024;  //ƫ�Ƶ�������
		        	yushu=len-1024*setnum;
		        	for(count=0;count<setnum;count++) //��������  ִ����1�κ� ��ס
		        	{
		        		printf("%d \n",setnum);
						flash_read_logic(flashRead,gcRecvBuf[1]+count,(gcRecvBuf[2]<<8)|gcRecvBuf[3],1024);
						mFlag=1;
						for(i=0;i<len;i++)   //�п�
						{
						   if(flashRead[i]!=0xFF)
						   {
							   mFlag=0;
							   break;
						   }
						}
						if(mFlag==1)
							uart_send_string(UART_User," selected area is empty3\n");
						else
						{
							uart_sendN(UART_User,1024,flashRead);
							printf("121111111\n");
						}
	//					uart_sendN(UART_User,gcRecvBuf[4],gcRecvBuf);
						//��ԭ��־��������������
						//memset(flashRead,0xFF,1024);
						//mFlag=1;

		        	}
		        	if(yushu >0)  //������಻��һ�������Ĳ���
		        	{
		        		flash_read_logic(flashRead,gcRecvBuf[1]+count,(gcRecvBuf[2]<<8)|gcRecvBuf[3],yushu);
						mFlag=1;
						for(i=0;i<len;i++)   //�п�
						{
						   if(flashRead[i]!=0xFF)
						   {
							   mFlag=0;
							   break;
						   }
						}
						if(mFlag==1)
							uart_send_string(UART_User," selected area is empty3\n");
						else
						{
							uart_sendN(UART_User,yushu,flashRead);
							printf("2222222\n");
							
						}
	//					uart_sendN(UART_User,gcRecvBuf[4],gcRecvBuf);
						//��ԭ��־��������������
						//memset(flashRead,0xFF,1024);
						//mFlag=1;
		        	}
		        	memset(gcRecvBuf,0xFF,len);
		        	mFlag=1;
		        	break;
				 default:
					 //uart_send_string(UART_User,(uint8_t *)MCU_TYPE);
					 uart_send_string(UART_User,"default test!\n");
					 break;
		   }

    }
	UARTA_IRQHandler_Exit:
	gcRecvLen = 0;  //�ָ�����״̬

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

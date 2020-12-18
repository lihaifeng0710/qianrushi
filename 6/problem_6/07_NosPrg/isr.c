//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"

//声明使用到的内部函数
//isr.c使用的内部函数声明处
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer);

//======================================================================
//中断服务程序名称：UART_User_Handler
//触发条件：UART_USE串口收到一个字节触发
//功    能：收到一个字节，直接返回该字节
//备    注：进入本程序后，可使用uart_get_re_int函数可再进行中断标志判断
//          （1-有UART接收中断，0-没有UART接收中断）
//======================================================================
void UART_User_Handler(void)
{
    uint8_t ch,h,a,b,c;
	uint8_t flag;
    uint8_t flashRead[1024];    //flash读取内容
    uint8_t *addr;
    uint8_t buf[1024];
    addr=(uint8_t*)Address;

	DISABLE_INTERRUPTS;      //关总中断
	//------------------------------------------------------------------
	//接收一个字节
	ch = uart_re1(UART_User, &flag);   //调用接收一个字节的函数，清接收中断位
	if(CreateFrame(ch,g_uart_recv)!=0)   //组帧成功
	{
		int i=0;
		uart_send_string(UART_User,"组帧成功！\n");
//		for(int i=0;i<(sizeof(g_uart_recv)/sizeof(g_uart_recv[0]));i++)
//			uart_send1(UART_User,g_uart_recv[i]);
		//接下来进行语义分析
		//--------------语义分析开始--------------
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
		//--------------语义分析结束--------------
		
		//接下来进行flash操作
		switch(g_uart_recv[0])
		{
		 case '?'://命令帮助
			 uart_send_string(UART_User," 擦除,读取,写入格式如下:\r\n");
			 uart_send_string(UART_User," 擦    除 E：62扇区\r\n");
			 uart_send_string(UART_User," 读    取 R（逻辑地址）：62扇区0字节开始的地址读取30字节长度数据\r\n");
			 uart_send_string(UART_User," 读    取 A（物理地址）：从宏定义addr地址直接读取30字节的数据\r\n");
			 uart_send_string(UART_User," 写    入 W：向62扇区0字节开始的地址写入30字节长度字符串\r\n");
			break;
		//读Flash逻辑地址
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
		//读Flash物理地址
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
		//写Flash
		case 'W':
		case 'w':
			flash_erase(sector); //擦除扇区
			h=flash_write(sector,offset,cnt,buf);
			if(!h)
			{
				uart_send_string(UART_User,"Write OK！\n");
			}
			else
			{
				uart_send_string(UART_User,"Write Error！\n");
			}
			break;
		//擦除Flash测试
		case 'E':
		case 'e':
			h=flash_erase(sector); //擦除扇区
			if(!h)
			{
				uart_send_string(UART_User,"Erase OK！\n");
			}
			else
			{
				uart_send_string(UART_User,"Erase Error！\n");
			}
			break;

		default:
			break;
		}
	}
	//------------------------------------------------------------------
	ENABLE_INTERRUPTS;       //开总中断
}

//=====================================================================
//函数名称：SYSTICK_USER_Handler（SysTick定时器中断处理程序）
//参数说明：无
//函数返回：无
//功能概要：（1）每10ms中断触发本程序一次；（2）达到一秒时，调用秒+1
//           程序，计算“时、分、秒”
//特别提示：（1）使用全局变量字节型数组gTime[3]，分别存储“时、分、秒”
//          （2）注意其中静态变量的使用
//=====================================================================
//void SYSTICK_USER_Handler()
#define Nul    (0x20)       //空格     
static uint8_t frameLen=0;    //帧的计数器
uint8_t frameFlag;            //组帧状态
static uint8_t flag_empt=0;
static uint8_t vol1=100;
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer)
{
	frameFlag=0;            //组帧状态初始化
    //根据静态变量frameLen组帧
    switch(frameLen)
    {
        case 0:    //第一个数据
        {
            buffer[0]=Data;
            frameLen++;
            frameFlag=0;        //组帧开始
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
        	else if(flag_empt==4)			//在第四个空格处
        	{
				int n=buffer[frameLen-2]-'0';		//计算字节数
				vol1=n+frameLen-1;			//字符串长度
				buffer[frameLen]=Data;
				frameLen++;
				flag_empt++;			//刷新flag_empt，防止下次执行该代码段
				break;
        	}
        	else
			{
				if(frameLen<vol1)			//到达帧尾前
        		{
					buffer[frameLen]=Data;
        			frameLen++;
        			break;
				}
				else
				{
					buffer[frameLen]=Data;	//存帧尾
					frameFlag=1;		//组帧完成
					frameLen=0;		//归零，为下一次组帧做准备
					vol1=100;			//归零，为下一次组帧做准备
					flag_empt=0;	//归零，为下一次组帧做准备
					break;
				}
        	}
        }
    }     //switch_END
    return frameFlag;                 //返回组帧状态
}

/*
 知识要素：
 1.本文件中的中断处理函数调用的均是相关设备封装好的具体构件，在更换芯片
 时，只需保证设备的构件接口一致，即可保证本文件的相关中断处理函数不做任何
 更改，从而达到芯片无关性的要求。
 */

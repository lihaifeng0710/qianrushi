//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"

//声明使用到的内部函数
//isr.c使用的内部函数声明处
void SecAdd1(uint8_t *p);
//======================================================================
//中断服务程序名称：UART_User_Handler
//触发条件：UART_USE串口收到一个字节触发
//功    能：收到一个字节，直接返回该字节
//备    注：进入本程序后，可使用uart_get_re_int函数可再进行中断标志判断
//          （1-有UART接收中断，0-没有UART接收中断）
//======================================================================
void UART_User_Handler(void)
{
    uint8_t ch,h;
	uint8_t flag;
    uint8_t flashRead[1024];    //flash读取内容
    uint8_t *addr;
    addr=(uint8_t*)Address;

	DISABLE_INTERRUPTS;      //关总中断
	//------------------------------------------------------------------
	//接收一个字节
	ch = uart_re1(UART_User, &flag);   //调用接收一个字节的函数，清接收中断位
	if(flag)   //有数据
	{
		uart_send1(UART_User,ch);//回发接收到的字节
		switch(ch)
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
			flash_erase(63); //擦除扇区
			h=flash_write(63,Offset,CNT,Content);
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
			h=flash_erase(63); //擦除扇区
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

void SysTick_Handler()
{
	static uint8_t SysTickCount = 0;
	SysTickCount++;    //Tick单元+1
	wdog_feed();      //看门狗“喂狗”
	if (SysTickCount >= 100)
	{
		SysTickCount = 0;
		SecAdd1(gTime);
	}
}



//===========================================================================
//函数名称：SecAdd1
//函数返回：无
//参数说明：*p:为指向一个时分秒数组p[3]
//功能概要：秒单元+1，并处理时分单元（00:00:00-23:59:59)
//===========================================================================
void SecAdd1(uint8_t *p)
{
	*(p+2)+=1;         //秒+1
	if(*(p+2)>=60)     //秒溢出
	{
		*(p+2)=0;       //清秒
		*(p+1)+=1;      //分+1
		if(*(p+1)>=60)  //分溢出
		{
			*(p+1)=0;    //清分
			*p+=1;       //时+1
			if(*p>=24)   //时溢出
			{
				*p=0;      //清时
			}
		}
	}
}


/*
 知识要素：
 1.本文件中的中断处理函数调用的均是相关设备封装好的具体构件，在更换芯片
 时，只需保证设备的构件接口一致，即可保证本文件的相关中断处理函数不做任何
 更改，从而达到芯片无关性的要求。
 */

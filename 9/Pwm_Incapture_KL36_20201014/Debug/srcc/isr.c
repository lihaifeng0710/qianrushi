//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"
#include <string.h>
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
void UART_User_Handler(void){
	uint8_t ch;
	uint8_t flag;
	DISABLE_INTERRUPTS;      //关总中断
	//------------------------------------------------------------------
	//接收一个字节
	ch = uart_re1(UART_User, &flag);   //调用接收一个字节的函数，清接收中断位
	if(flag)   //有数据
	{
		level=ch;
		uart_send1(UART_User,ch);//回发接收到的字节
		uart_send1(UART_User,level);//回发接收到的字节
		uart_send_string(UART_User,"接收成功");
		
	}
	//------------------------------------------------------------------
	ENABLE_INTERRUPTS;       //开总中断
}


//=====================================================================
//函数名称：TIMER_USER_Handler（TIMERB定时器中断处理程序）
//参数说明：无
//函数返回：无
//功能概要：（1）每20ms中断触发本程序一次；（2）达到一秒时，调用秒+1
//           程序，计算“时、分、秒”
//特别提示：（1）使用全局变量字节型数组gTime[3]，分别存储“时、分、秒”
//        （2）注意其中静态变量的使用
//=====================================================================
void TIMER_USER_Handler(void)
{
	DISABLE_INTERRUPTS;                        //关总中断
	//------------------------------------------------------------------
	//（在此处增加功能）
	//申请一个静态的计数器值
	static uint8_t TimerCount = 0;
	//获取当前时钟溢出标志位
	if(timer_get_int(TIMER_USER))
	{
		TimerCount++;           //计数器累加
		if (TimerCount >= 50)
		{
			TimerCount = 0;    //时钟计数器清零
			SecAdd1(gTime);    //时间显示累加
		}
		timer_clear_int(TIMER_USER);    //清时钟溢出标志位
	}
	//------------------------------------------------------------------
	ENABLE_INTERRUPTS;                        //开总中断
}

//=====================================================================
//函数名称：INCAP_USER_Handler（输入捕捉中断处理程序）
//参数说明：无
//函数返回：无
//功能概要：（1）每次捕捉到上升沿或者下降沿触发该程序；
//       （2）每次触发都会上传当前捕捉到的上位机程序
//=====================================================================
void INCAP_USER_Handler(void)
{
	uint16_t val;
	DISABLE_INTERRUPTS;     //关总中断
	//------------------------------------------------------------------
	//（在此处增加功能）
	if(cap_get_flag(INCAP_USER))
	{
		
		val = get_incapture_value(INCAP_USER);
		printf("输入捕捉值%d\r\n",val);
		cap_clear_flag(INCAP_USER); //清中断
	}
	//------------------------------------------------------------------
	ENABLE_INTERRUPTS;     //关总中断
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

//===========================================================================
//文件名称：isr.c
//功能概要： 中断底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================
#include "includes.h"

//========================中断函数服务例程===============================
//串口0接收中断服务例程
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


//串口1接收中断服务例程
void isr_uart1_re(void)
{
    //uint_8 ch;
    //uint_8 flag = 1;
	flag = 1;
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_1, &flag);//2口收1口发
    if (0 == flag)
    {
        uart_send1(UART_1, ch);
    }
    //if(ch=='1')
    //{
    //	light_init(RUN_LIGHT_BLUE, LIGHT_OFF);  //绿灯初始化
    //	light_init(RUN_LIGHT_RED, LIGHT_ON);  //绿灯初始化
    //	light_init(RUN_LIGHT_GREEN, LIGHT_OFF);  //绿灯初始化
    //}
    //else
    //{
    //	light_init(RUN_LIGHT_BLUE, LIGHT_OFF);  //绿灯初始化
    //	light_init(RUN_LIGHT_RED, LIGHT_OFF);  //绿灯初始化
    //	light_init(RUN_LIGHT_GREEN, LIGHT_OFF);  //绿灯初始化
    //}

 
    ENABLE_INTERRUPTS;
}

//串口2接收中断服务例程
void isr_uart2_re(void)
{
    //uint_8 ch;
    //uint_8 flag = 1;
	flag = 1;
    DISABLE_INTERRUPTS;
    
    ch = uart_re1(UART_2, &flag);//2口收1口发
    if (0 == flag)
    {
        uart_send1(UART_1, ch);
    }
        
    ENABLE_INTERRUPTS;
}



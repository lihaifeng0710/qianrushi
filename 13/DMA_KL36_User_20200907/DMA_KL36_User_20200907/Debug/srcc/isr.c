//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"
//======================================================================
//中断服务程序名称：UART_USER_Handler
//触发条件：UART_USE串口收到一个字节触发
//功    能：收到一个字节，直接返回该字节
//备    注：进入本程序后，可使用uart_get_re_int函数可再进行中断标志判断
//          （1-有UART接收中断，0-没有UART接收中断）
//======================================================================
void UART_User_Handler(void)
{
	uint8_t ch;
	uint8_t flag;
	printf("成功4\n");
	DISABLE_INTERRUPTS;      //关总中断
	//------------------------------------------------------------------
	//接收一个字节
	/*ch = uart_re1(UART_User , &flag);
	if(flag){
	    uart_send1(UART_User , ch);
	
	}*/
	printf("成功3\n");
	for(uint32_t i = 0 ; i < 6000 * 5 ; i++);
	dma_read(DMA_CH0,(uint32_t)gDmaRecBuf,10);//请求DMA进行传输数据
	printf("成功2\n");
	gDmaRecFlag=1;//标志位置位
	uart_IdleIrq_clear(UART_User);//清中断标志位
	//------------------------------------------------------------------
	ENABLE_INTERRUPTS;       //开总中断
}


/*
 知识要素：
 1.本文件中的中断处理函数调用的均是相关设备封装好的具体构件，在更换芯片
 时，只需保证设备的构件接口一致，即可保证本文件的相关中断处理函数不做任何
 更改，从而达到芯片无关性的要求。
 */

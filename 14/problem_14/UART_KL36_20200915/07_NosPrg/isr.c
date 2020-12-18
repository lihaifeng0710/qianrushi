//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"
#include <string.h>
//内部函数声明
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer);

//======================================================================
//中断服务程序名称：UART_USER_Handler
//触发条件：UART_USE串口收到一个字节触发
//功    能：收到一个字节，直接返回该字节
//备    注：进入本程序后，可使用uart_get_re_int函数可再进行中断标志判断
//          （1-有UART接收中断，0-没有UART接收中断）
//======================================================================
void UART_User_Handler(void)
{

    uint8_t ch,flag,N;
    DISABLE_INTERRUPTS;               //关总中断
    //-----------------------------------------------------------------------
    ch = uart_re1(UART_User, &flag);   //调用接收一个字节的函数，清接收中断位
    //调用内部函数CreateFrame进行组帧
   // uart_send1(UART_User,ch);//回发接收到的字节、
    if(CreateFrame(ch,g_uart_recvBuf)!=0)    //组帧成功
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
    
   	
	ENABLE_INTERRUPTS;       //开总中断
	
	
}


//内部调用函数

//===========================================================================
//函数名称：CreateFrame
//功能概要：组建数据帧，将待组帧数据加入到数据帧中
//参数说明：Data：         待组帧数据
//          buffer:        数据帧变量
//函数返回：组帧状态    0-组帧未成功，1-组帧成功
//备注：十六进制数据帧格式
//               帧头        + 数据长度         + 有效数据    +  帧尾
//           FrameHead   +   len       + 有效数据    + FrameTail
//===========================================================================

static uint8_t frameLen=0;    //帧的计数器
uint8_t frameFlag;            //组帧状态

//如果帧头是o或b则帧总长是4(open/blue)
//如果帧头是c或g则帧总长是5(close/green)
uint8_t CreateFrame(uint8_t Data,uint8_t * buffer)
{
    frameFlag=0;            //组帧状态初始化
    //根据静态变量frameLen组帧
    switch(frameLen)
    {
        case 0:    //第一个数据
        {
            length=(Data-'0')+48;
            frameLen++;
            frameFlag=0;        //组帧开始
            break;
        }
        default:    //其他情况
        {
            //根据长度接收余下的数据直到帧尾前一位
            if(frameLen>=1 && frameLen<=(length-1))
            {
                buffer[frameLen]=Data;
                frameLen++;
                break;
            }

            //若是末尾数据则执行
            if(frameLen>=(length))
            {
                buffer[frameLen]=Data;     //将帧尾存入缓冲区
                frameFlag=1;    //组帧成功
                frameLen=0    ;     //计数清0，准备重新组帧
                break;
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

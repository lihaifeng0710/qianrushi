//=====================================================================
//文件名称：isr.c（中断处理程序源文件）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：20170801-20191020
//功能描述：提供中断处理程序编程框架
//=====================================================================
#include "includes.h"

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

    uint8_t ch,flag;
    DISABLE_INTERRUPTS;               //关总中断
    //-----------------------------------------------------------------------
    ch = uart_re1(UART_User, &flag);   //调用接收一个字节的函数，清接收中断位
    //调用内部函数CreateFrame进行组帧
   // uart_send1(UART_User,ch);//回发接收到的字节
    if(CreateFrame(ch,g_uart_recvBuf)!=0)    //组帧成功
    {
    	uart_send_string(UART_User,"组帧成功！\n");
    	if(g_uart_recvBuf[0]=='H'&&g_uart_recvBuf[1]=='e'&&g_uart_recvBuf[2]=='l'&&g_uart_recvBuf[3]=='l'&&g_uart_recvBuf[4]=='o')
		{
			uart_send_string(UART_User,"open!\n");
			gpio_set(LIGHT_BLUE,LIGHT_ON);
		}
		else if(g_uart_recvBuf[0]!='H'&&g_uart_recvBuf[1]!='e'&&g_uart_recvBuf[2]!='l'&&g_uart_recvBuf[3]!='l'&&g_uart_recvBuf[4]!='o')
		{
			uart_send_string(UART_User,"close!\n");
			gpio_set(LIGHT_BLUE,LIGHT_OFF);
		}
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
//Hello帧头帧尾
#define FrameHead1    (0x48)       //帧头     ASCII码对应H
#define FrameTail1    (0x6F)       //帧尾     ASCII码对应o

static uint8_t frameLen=0;    //帧的计数器
uint8_t frameFlag;            //组帧状态
uint8_t length=5;


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
        default:    //其他情况
        {
            //根据长度接收余下的数据直到帧尾前一位
            if(frameLen>=1 && frameLen<=(length-2))
            {
                buffer[frameLen]=Data;
                frameLen++;
                break;
            }

            //若是末尾数据则执行
            if(frameLen>=(length-1))
            {
                if ((Data==FrameTail1))    //若是帧尾
                {
                    buffer[frameLen]=Data;     //将帧尾存入缓冲区
                    frameFlag=1;    //组帧成功
                }
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

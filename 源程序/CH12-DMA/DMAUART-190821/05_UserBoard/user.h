//======================================================================
//文件名称：user.h（用户程序头文件）
//制作单位：苏大arm技术中心(sumcu.suda.edu.cn)
//更新记录：2018.12：1.0，2019.1：A.10
//概要说明：本文件用于在使用GEC芯片进行硬件板设计时存放用户板部分引脚定义，
//          GEC引脚具有的功能在gec.h文件中
//======================================================================

#ifndef USER_H   //防止重复定义（开始）
#define USER_H
#include"gec.h"
#include"uecom.h"
#include"printf.h"


//======================================================================
//指示灯端口及引脚定义
#define  LIGHT_RED    GPIOA_2    //红灯，所在引脚：GEC_56（PTA_NUM|5）
#define  LIGHT_GREEN  GPIOA_1  //绿灯， 所在引脚：GEC_55（PTA_NUM|12）
#define  LIGHT_BLUE   GPIOA_0    //蓝灯， 所在引脚：GEC_54（PTA_NUM|13）
//灯状态宏定义（灯的亮暗对应的逻辑电平，由物理硬件接法决定）
#define  LIGHT_ON     0     //灯亮
#define  LIGHT_OFF    1     //灯暗

//UART模块定义
#define UART_USER   UARTA   //TX引脚：GEC_10；RX引脚：GEC_8

//DMA模块定义
#define DMA_SEND  DMA_CH0

#endif//防止重复定义（结尾）

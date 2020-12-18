//======================================================================
//文件名称：user.h（user头文件）
//制作单位：SD-Arm(sumcu.suda.edu.cn)
//更新记录：20181201-20200221
//概要说明：包含gpio.h文件，实现对具体应用编程，而不是对引脚状态等编程
//======================================================================
#ifndef USER_H   //防止重复定义（USER_H 开头）
#define USER_H

//（1）【固定】文件包含
#include "printf.h"
#include "gec.h"
#include "gpio.h"
#include "tm1637.h"
#include "ws2812.h"
#include "adlx345.h"
#include "adc.h"
//（2）【变动】指示灯端口及引脚定义—根据实际使用的引脚改动
//指示灯端口及引脚定义
#define  LIGHT_RED    (PTA_NUM|5)  //红灯，所在引脚：GEC_56
#define  LIGHT_GREEN  (PTA_NUM|12)  //绿灯，所在引脚：GEC_55
#define  LIGHT_BLUE   (PTA_NUM|13)  //蓝灯，所在引脚：GEC_54

//灯状态宏定义（灯亮、灯暗对应的物理电平由硬件接法决定）
#define  LIGHT_ON       0    //灯亮
#define  LIGHT_OFF      1    //灯暗

//（3）【变动】UART可用模块定义
#define UART_Debug   2  //UART_2   //用于程序更新，无法被使用
#define UART_User    0  //UART_2   //用户串口
#define UART_UE      1  //UART_1   //用户串口
//（4）【改动】中断服务函数宏定义
#define UART_User_Handler   UART0_IRQHandler  //用户串口中断函数
#define UART_UE_Handler UART1_IRQHandler

//彩灯端口及引脚定义
#define COLORLIGHT  (PTE_NUM|29)      //所在引脚：GEC_6  (WJ6)
//蜂鸣器模块定义
#define BEEF (PTC_NUM|4)      //所在引脚：GEC_22  (WJ5)
//振动马达模块定义
#define MOTOR (PTC_NUM|2)      //所在引脚：GEC_38  (WJ1)
//数码管模块定义
#define TM1637_CLK  (PTB_NUM|0)    //所在引脚：GEC_49  (WJ4)
#define TM1637_DIO  (PTB_NUM|1)    //所在引脚：GEC_48  
//红外循迹器模块定义
#define RAY_RIGHT (PTD_NUM|6)     //右侧红外寻迹传感器所在引脚：GEC_15   (WJ7)
#define RAY_LEFT (PTD_NUM|7)      //左侧红外寻迹传感器所在引脚：GEC_16
//人体红外模块定义
#define RAY_HUMAN (PTD_NUM|6)          //所在引脚：GEC_15    （WJ7）
//Button模块定义及引脚定义
#define Button1 (PTB_NUM|17)
#define Button2 (PTB_NUM|16)
#define Button3 (PTC_NUM|3)
#define Button4 (PTC_NUM|0)
//(7)声音传感器ADC通道号
#define  ADCSound  (7|1<<8)   //PTD_NUM|6，ADC0_SE7b
//(8)加速度传感器使用的I2C模块定义
#define i2cAcceleration 0    //SDA引脚：GEC_46（PTB_NUM|3）；SCL引脚： GEC_47（PTB_NUM|2）  (WJ3)
#endif    //防止重复定义（USER_H 结尾）

//============================================================================
//文件名称：wdog.h
//功能概要：K60 看门狗驱动程序头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2011-11-13  V1.0   初始版本
//          2011-12-20  V1.1   规范排版
//          2011-12-27  V1.2   使用构件命名规范重新为函数命名，
//                             隐藏wdog_unlock为内部函数
//=================苏州大学飞思卡尔嵌入式中心2012=========================


#ifndef __WDOG_H__
#define __WDOG_H__

//1 头文件    
#include "mcu.h"
#include "string.h"

#define TIMEOUT1  1    //32ms
#define TIMEOUT2  2    //256ms
#define TIMEOUT3  3    //1024ms

#define ENABLE_WDOG	   1      //设置是否开启看门狗

//=========================================================================
//功能概要：启动看门狗模块
//参数说明：无
//函数返回：无
//默认时钟选择LPO，而不选择BUS
//选择总线时钟，复位时间可以是0.17ms、1.36ms、5.46ms
//选择LPO时钟，复位时间可以是32ms、256ms、1024ms
//=========================================================================
void wdog_start(uint32_t timeout);

//=========================================================================
//功能概要：禁用看门狗模块
//参数说明：无
//=========================================================================
void wdog_stop();

//=========================================================================
//功能概要：喂狗，清看门狗计数器
//参数说明：无
//函数返回：无
//=========================================================================
void wdog_feed(void);


#endif 

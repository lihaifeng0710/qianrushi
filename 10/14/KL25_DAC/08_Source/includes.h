//============================================================================
//文件名称：includes.h
//功能概要：应用工程总头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//版本更新：2012-11-12  V2.0
//============================================================================

#ifndef _INCLUDES_H
#define _INCLUDES_H

#include "common.h"
#include "gpio.h"
#include "uart.h"
#include  "dac.h"
#include "light.h"  

//定义全局变量
uint_16  my[4];//
uint_16  VReference;           //DAC参考数字量
//定义系统时钟、总线时钟
#define  core_clk_khz      48000   //芯片内核时钟频率，kHz
#define  bus_clk_khz       24000   //芯片总线时钟频率，Khz

//定义小灯闪烁频率
#define RUN_COUNTER_MAX   1000000ul 

//定义使用的调试号
#define UART_TEST UART_1

#endif

/*
 * core.h
 *
 *  Created on: 2019年7月1日
 *      Author: 阿拉丁
 */

#ifndef _MCU_H_
#define _MCU_H_
 // 包含芯片头文件
#include "MKL36Z4.h"
#include "core_cm0plus.h"
#include "core_cmFunc.h"
#include "core_cmInstr.h"
#include "system_MKL36Z4.h"

//(1)中断设置
#define IRQ_MAX           32     // 可设置中断最大个数
#define IRQ_PRIOR_MAX     3      // 可设置最大中断优先级
#define ENABLE_INTERRUPTS        __enable_irq()             // 开总中断()
#define DISABLE_INTERRUPTS       __disable_irq()            // 关总中断()
#define NOP 				     __asm ("NOP")              // 无操作
#define DisableIRQ(irq)          NVIC_DisableIRQ(irq)       // 禁止irq中断
#define EnableIRQ(irq)           NVIC_EnableIRQ(irq)        // 打开irq中断
#define SetPriority(irq, prio)   NVIC_SetPriority(irq, prio)  // 设置irq中断优先级

//(2)复位发生标志位判断
#define IS_PIN_RESET_OCCURED        BGET(RCM_SRS0_PIN_SHIFT,RCM_SRS0)    // 按键复位
#define IS_POWERON_RESET_OCCURED    BGET(RCM_SRS0_POR_SHIFT, RCM_SRS0)   // 上电复位
#define IS_WDOG_RESET_OCCURED       BGET(RCM_SRS0_WDOG_SHIFT, RCM_SRS0)  // 看门狗复位

//(3)定义系统使用的时钟频率
#define  SYSTEM_CLK       SystemCoreClock          // 芯片系统时钟频率(HZ)
#define  SYSTEM_CLK_KHZ   SystemCoreClock/1000     // 芯片系统时钟频率(KHz)
#define  BUS_CLK_KHZ      SYSTEM_CLK_KHZ/2         // 芯片总线时钟频率(KHz)
#define  SYSTEM_CLK_MS    (48000 / 10)             // 1ms所需时钟频率(HZ)
#define  SYSTEM_CLK_US    (48000 / 1000 / 11)      // 1us所需时钟频率(HZ)


#define MCUTYPE    "[MKL36Z64]"            //MCU型号（10字节）
#define SECTORNUM  64                      //MCU扇区总数
#define SECTORSIZE 0x400                   //扇区大小
#define STACKTOP   0x20001800              //栈顶
#define __MCU_FLASH_ADDR_START__  0x00000000//MCU的FLASH起始地址
#define __MCU_FLASH_ADDR_LENGTH__ 0x00010000//MCU的FLASH长度
#define __MCU_RAM_ADDR_START__   0x1FFFF800	//MCU的RAM起始地址
#define __MCU_RAM_ADDR_LENGTH__  0x00002000	//MCU的RAM长度

#endif /* _MCU_H_ */

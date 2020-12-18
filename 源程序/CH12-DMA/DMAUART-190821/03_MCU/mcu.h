/*
 * core.h
 *
 *  Created on: 2019��7��1��
 *      Author: ������
 */

#ifndef _MCU_H_
#define _MCU_H_
 // ����оƬͷ�ļ�
#include "MKL36Z4.h"
#include "core_cm0plus.h"
#include "core_cmFunc.h"
#include "core_cmInstr.h"
#include "system_MKL36Z4.h"

//(1)�ж�����
#define IRQ_MAX           32     // �������ж�������
#define IRQ_PRIOR_MAX     3      // ����������ж����ȼ�
#define ENABLE_INTERRUPTS        __enable_irq()             // �����ж�()
#define DISABLE_INTERRUPTS       __disable_irq()            // �����ж�()
#define NOP 				     __asm ("NOP")              // �޲���
#define DisableIRQ(irq)          NVIC_DisableIRQ(irq)       // ��ֹirq�ж�
#define EnableIRQ(irq)           NVIC_EnableIRQ(irq)        // ��irq�ж�
#define SetPriority(irq, prio)   NVIC_SetPriority(irq, prio)  // ����irq�ж����ȼ�

//(2)��λ������־λ�ж�
#define IS_PIN_RESET_OCCURED        BGET(RCM_SRS0_PIN_SHIFT,RCM_SRS0)    // ������λ
#define IS_POWERON_RESET_OCCURED    BGET(RCM_SRS0_POR_SHIFT, RCM_SRS0)   // �ϵ縴λ
#define IS_WDOG_RESET_OCCURED       BGET(RCM_SRS0_WDOG_SHIFT, RCM_SRS0)  // ���Ź���λ

//(3)����ϵͳʹ�õ�ʱ��Ƶ��
#define  SYSTEM_CLK       SystemCoreClock          // оƬϵͳʱ��Ƶ��(HZ)
#define  SYSTEM_CLK_KHZ   SystemCoreClock/1000     // оƬϵͳʱ��Ƶ��(KHz)
#define  BUS_CLK_KHZ      SYSTEM_CLK_KHZ/2         // оƬ����ʱ��Ƶ��(KHz)
#define  SYSTEM_CLK_MS    (48000 / 10)             // 1ms����ʱ��Ƶ��(HZ)
#define  SYSTEM_CLK_US    (48000 / 1000 / 11)      // 1us����ʱ��Ƶ��(HZ)


#define MCUTYPE    "[MKL36Z64]"            //MCU�ͺţ�10�ֽڣ�
#define SECTORNUM  64                      //MCU��������
#define SECTORSIZE 0x400                   //������С
#define STACKTOP   0x20001800              //ջ��
#define __MCU_FLASH_ADDR_START__  0x00000000//MCU��FLASH��ʼ��ַ
#define __MCU_FLASH_ADDR_LENGTH__ 0x00010000//MCU��FLASH����
#define __MCU_RAM_ADDR_START__   0x1FFFF800	//MCU��RAM��ʼ��ַ
#define __MCU_RAM_ADDR_LENGTH__  0x00002000	//MCU��RAM����

#endif /* _MCU_H_ */

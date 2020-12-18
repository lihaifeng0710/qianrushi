

#ifndef SYSINIT_H
#define SYSINIT_H

#include "common.h"
#include "vectors.h"

//����ϵͳʱ�ӡ�����ʱ��
#define  MCGFLL_CLK_KHZ         48000    //FLL���ʱ��Ƶ�ʣ�kHz
#define  MCGPLL_CLK_KHZ         48000    //PLL���ʱ��Ƶ�ʣ�kHz
#define  CORE_CLK_KHZ   MCGPLL_CLK_KHZ   //оƬ�ں�ʱ��Ƶ�ʣ�kHz
#define  BUS_CLK_KHZ             24000   //оƬ����ʱ��Ƶ�ʣ�Khz
#define  MCGIR_CLK_KHZ           4000    //�ڲ��ο�ʱ��Ƶ�ʣ�kHz

//===========================================================================
//�������ƣ�sys_init
//�������أ���
//����˵������ 
//���ܸ�Ҫ��(1)KL25��EXTAL(40)��XTAL(41)��8Mhz�ⲿ���񣬲���PLL/FLL���ʱ��Ƶ
//             ��48MHz,�ں�ʱ��48MHz������ʱ��24MHz���ڲ��ο�ʱ��4MHz��
//          (2)������ЩƵ�ʣ�sys_init.h����Ӧ�ĺ곣��������Թ����ʱʹ��
//===========================================================================
void sys_init(void);

#endif 

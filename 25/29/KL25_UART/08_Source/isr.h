//===========================================================================
//文件名称：isr.h
//功能概要： 中断底层驱动构件头文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2012-11-12   V1.0
//===========================================================================

#ifndef _ISR_H   //防止重复定义（ISR_H  开头)
#define _ISR_H

//===============用户中断向量表注册表=====================
//1 注册串口0中断向量
#ifdef VECTOR_028
	#undef VECTOR_028
	extern void isr_uart0_re(void);
	#define VECTOR_028  isr_uart0_re
#endif
	
//2 注册串口1中断向量
#ifdef VECTOR_029
	#undef VECTOR_029
	extern void isr_uart1_re(void);
	#define VECTOR_029  isr_uart1_re
#endif
	
//3 注册串口2中断向量
#ifdef VECTOR_030
	#undef VECTOR_030
	extern void isr_uart2_re(void);
	#define VECTOR_030  isr_uart2_re
#endif	
	

#endif   //防止重复定义（ 结尾)

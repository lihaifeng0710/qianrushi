//===========================================================================
//�ļ����ƣ�isr.h
//���ܸ�Ҫ�� �жϵײ���������ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//===========================================================================

#ifndef _ISR_H   //��ֹ�ظ����壨ISR_H  ��ͷ)
#define _ISR_H

//===============�û��ж�������ע���=====================
//1 ע�ᴮ��0�ж�����
#ifdef VECTOR_028
	#undef VECTOR_028
	extern void isr_uart0_re(void);
	#define VECTOR_028  isr_uart0_re
#endif
	
//2 ע�ᴮ��1�ж�����
#ifdef VECTOR_029
	#undef VECTOR_029
	extern void isr_uart1_re(void);
	#define VECTOR_029  isr_uart1_re
#endif
	
//3 ע�ᴮ��2�ж�����
#ifdef VECTOR_030
	#undef VECTOR_030
	extern void isr_uart2_re(void);
	#define VECTOR_030  isr_uart2_re
#endif	
	

#endif   //��ֹ�ظ����壨 ��β)

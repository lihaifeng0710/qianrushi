//===========================================================================
//�ļ����ƣ�vectors.h
//���ܸ�Ҫ�������ж�������ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2013-02-22V1.2;2013-05-08V2.0(WYH)  
//===========================================================================
#ifndef VECTORS_H   //��ֹ�ظ����壨 ��ͷ)
#define VECTORS_H


 //���塰vector_entry��Ϊ����ָ�����ͣ������ͺ�������ֵΪ��void�����������Ϊ��void��
typedef void (*vector_entry)(void);  

extern void startup(void);     //�ڡ�startup.c"�ļ���
#define BOOT_START startup     //�Ա�ʹ��BOOT_START������Ϊ�����������

extern void NOS_isrDummy(void); //DEFAULT_VECTOR�����ڡ�vectors.c����
#define DEFAULT_VECTOR  NOS_isrDummy

#define VECTOR_002    DEFAULT_VECTOR
#define VECTOR_003    DEFAULT_VECTOR
#define VECTOR_004    DEFAULT_VECTOR
#define VECTOR_005    DEFAULT_VECTOR
#define VECTOR_006    DEFAULT_VECTOR
#define VECTOR_007    DEFAULT_VECTOR
#define VECTOR_008    DEFAULT_VECTOR
#define VECTOR_009    DEFAULT_VECTOR
#define VECTOR_010    DEFAULT_VECTOR
#define VECTOR_011    DEFAULT_VECTOR
#define VECTOR_012    DEFAULT_VECTOR
#define VECTOR_013    DEFAULT_VECTOR
#define VECTOR_014    DEFAULT_VECTOR
#define VECTOR_015    DEFAULT_VECTOR
#define VECTOR_016    DEFAULT_VECTOR
#define VECTOR_017    DEFAULT_VECTOR
#define VECTOR_018    DEFAULT_VECTOR
#define VECTOR_019    DEFAULT_VECTOR
#define VECTOR_020    DEFAULT_VECTOR
#define VECTOR_021    DEFAULT_VECTOR
#define VECTOR_022    DEFAULT_VECTOR
#define VECTOR_023    DEFAULT_VECTOR
#define VECTOR_024    DEFAULT_VECTOR
#define VECTOR_025    DEFAULT_VECTOR
#define VECTOR_026    DEFAULT_VECTOR
#define VECTOR_027    DEFAULT_VECTOR
#define VECTOR_028    DEFAULT_VECTOR
#define VECTOR_029    DEFAULT_VECTOR
#define VECTOR_030    DEFAULT_VECTOR
#define VECTOR_031    DEFAULT_VECTOR
#define VECTOR_032    DEFAULT_VECTOR
#define VECTOR_033    DEFAULT_VECTOR
#define VECTOR_034    DEFAULT_VECTOR
#define VECTOR_035    DEFAULT_VECTOR
#define VECTOR_036    DEFAULT_VECTOR
#define VECTOR_037    DEFAULT_VECTOR
#define VECTOR_038    DEFAULT_VECTOR
#define VECTOR_039    DEFAULT_VECTOR
#define VECTOR_040    DEFAULT_VECTOR
#define VECTOR_041    DEFAULT_VECTOR
#define VECTOR_042    DEFAULT_VECTOR
#define VECTOR_043    DEFAULT_VECTOR
#define VECTOR_044    DEFAULT_VECTOR
#define VECTOR_045    DEFAULT_VECTOR
#define VECTOR_046    DEFAULT_VECTOR
#define VECTOR_047    DEFAULT_VECTOR

#include "isr.h"   //�����ж�������

  
#endif  //��ֹ�ظ�����(��β)

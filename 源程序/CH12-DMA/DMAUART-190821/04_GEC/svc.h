//======================================================================
//文件名称：svc.h（svc头文件）
//版权所有：苏大arm技术中心(sumcu.suda.edu.cn)
//版本更新：2018-10 V1.0
//功能描述：包括所有bios_fun_point，用于存放用户接口函数指针数组首地址。
//======================================================================

#ifndef _SVC_H_
#define _SVC_H_

void **  bios_fun_point;   //用于存放函数指针数组地址。
//已经发生中断
#define IS_IRQ_MODE()        (__get_IPSR() != 0U)
//已经关中断
#define IS_IRQ_MASKED()      (__get_PRIMASK() != 0U)

#define SVC_ArgR(n,a) \
register uint32_t __r##n __ASM("r"#n) = (uint32_t)a

#define SVC_RegF "r6"

#define SVC_ArgF(f) \
register uint32_t __rf   __ASM(SVC_RegF) = (uint32_t)f

#define SVC_ArgN(n) \
register uint32_t __r##n __ASM("r"#n)

#define SVC_In0 "r"(__rf)
#define SVC_In1 "r"(__rf),"r"(__r0)
#define SVC_In2 "r"(__rf),"r"(__r0),"r"(__r1)
#define SVC_In3 "r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2)
#define SVC_In4 "r"(__rf),"r"(__r0),"r"(__r1),"r"(__r2),"r"(__r3)

#define SVC_Out0
#define SVC_Out1 "=r"(__r0)
#define SVC_Out2 "=r"(__r0),"=r"(__r1)

#define SVC_CL0
#define SVC_CL1 "r1"
#define SVC_CL2 "r0","r1"

#define SVC_Call1(in, out, cl)                                                 \
	 uint_8 is_irq_masked; \
	 is_irq_masked = 0; \
	 if ( IS_IRQ_MASKED()) {                \
	        __ASM volatile ("cpsie i" : : : "memory");\
	        is_irq_masked = 1; \
           }\
     __ASM volatile ("svc 1" : out : in : cl);\
     if(is_irq_masked) \
	      __ASM volatile ("cpsid i" : : : "memory");

//===========================
//__asm__(汇编语句模板: 输出部分: 输入部分: 破坏描述部分)

#define SVC_ArgSP(a) \
 __ASM volatile("sub  sp,#4":::"sp"); \
 __ASM volatile("str %0,[sp,#0]"::"r"(a):"sp");

#define SVC_AddSP(n)  \
 __asm volatile (" add sp,%0"::"r"(n):"sp");\

#define SVC1_INIT(f,t,nf)         \
__attribute__((always_inline))            \
__STATIC_INLINE t f (void) {     \
	 __asm volatile (" push {r4,r6}":::"memory");\
	  SVC_ArgF(nf);\
	  SVC_ArgN(0);                         \
	  SVC_Call1(SVC_In1, SVC_Out1, SVC_CL1);     \
	  __asm volatile (" pop {r4,r6}":::"r4","r6");\
     return (t) __r0;             \
	}

#endif    /* 04_GEC_SVC_H_ */

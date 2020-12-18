#include "sysinit.h"

//===========================================================================
//函数名称：sys_init
//函数返回：无
//参数说明：无 
//功能概要：(1)KL25的EXTAL(40)、XTAL(41)接8Mhz外部晶振，产生PLL/FLL输出时钟频
//             率48MHz,内核时钟48MHz，总线时钟24MHz，内部参考时钟4MHz。
//          (2)对于这些频率，sys_init.h有相应的宏常量定义可以供编程时使用
//===========================================================================
void sys_init(void)  
{
    uint_32 i = 0;
    uint_8 temp_reg = 0;

 //1.首先从FEI模式过渡到FBE模式
    
    //C2= 0x1C，因为我们的核心板上采用了外部晶振为8Mhz，属于高频率范围，
    //C2[RANGE]设置为0b01；C2[HGO]设为1以配置晶振来进行高增益操作；因为
    //正在使用的外部参考时钟源是晶振，所以C2[EREFS]设置为1。
    MCG_C2 = (MCG_C2_RANGE0(1) | MCG_C2_EREFS0_MASK);
    //C1 = 0x90 ，C1[CLKS]设置为2’b10，以便选择作为系统时钟源的外部参考时钟。
    //C1[FRDIV]设置为3'b011，对应256分频,因为8MHz/256=31.25kHz在由FLL要求的
    //31.25kHz至39.0625 kHz频率范围内。C1[IREFS]清除为0，选择外部参考时钟和
    //外部晶振。
    MCG_C1 = (MCG_C1_CLKS(2) | MCG_C1_FRDIV(3));
    //需要等到S[OSCINIT]被置位外部晶振才能使用
    for (i = 0 ; i < 20000 ; i++)
    {
        //如果S[OSCINIT]在循环结束之前被置位就跳出循环
        if (MCG_S & MCG_S_OSCINIT0_MASK) break;
    }
    //等待参考时钟状态位清0
    for (i = 0 ; i < 2000 ; i++)
    {
        //如果IREFST在循环结束之前被清0就跳出循环
        if (!(MCG_S & MCG_S_IREFST_MASK)) break;
    }
    //等待时钟状态位以显示时钟源为外部参考时钟
    for (i = 0 ; i < 2000 ; i++)
    {
        //如果CLKST显示外部时钟被选择，在循环结束之前就跳出循环
        if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x2) break;
    }
 //2.现在处于FBE状态，使能时钟监视器，由FBE直接转换为PBE模式
    MCG_C6 |= MCG_C6_CME0_MASK;
    //配置PLL为2分频
    MCG_C5 |= MCG_C5_PRDIV0(1); 
    //配置MCG_C6 以设置PLL倍频因子并且时能PLL，PLLS位被置位来时能PLL，MCGOUT时钟源仍然是外部参考时钟          
    temp_reg = MCG_C6; //存储当前C6的值（因为CME0位之前被置位了）
    temp_reg &= ~MCG_C6_VDIV0_MASK; //将VDIV清0
    temp_reg |= MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0); // 重新写值到VDIV 并且时能PLL
    MCG_C6 = temp_reg; // 更新MCG_C6的值
    // 等待PLLST状态位被置
    for (i = 0 ; i < 2000 ; i++)
    {
        //如果PLLST在循环结束之前被置位就跳出循环
        if (MCG_S & MCG_S_PLLST_MASK) break;
    }
    //等待LOCK位被置
    for (i = 0 ; i < 4000 ; i++)
    {
        //如果LOCK在循环结束之前被置位就跳出循环
        if (MCG_S & MCG_S_LOCK0_MASK) break;
    }
  //3.现在处于PBE模式。最后，PBE模式转换成PEE模式
    // 设置核心时钟分频器2分频
    //设置总线时钟分频器2分频 (总线时钟的时钟源是核心时钟)
    SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(1) | SIM_CLKDIV1_OUTDIV4(1) );
    //清CLKS来打开CLKS多路复用器来选择PLL作为MCGCLKOUT
    MCG_C1 &= ~MCG_C1_CLKS_MASK;
    // 等待时钟状态位更新
    for (i = 0 ; i < 2000 ; i++)
    {
        //如果CLKST在循环结束之前等于3就跳出循环
        if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x3) break;
    }
  //4.现在处于PEE模式
}






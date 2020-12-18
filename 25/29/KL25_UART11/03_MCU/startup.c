
#include "common.h"
#include "sysinit.h"

extern int main(void);

//声明内部函数
static void vector_init(void);
static void m_zero_fill_bss(void);
static void m_data_seg_init(void);
static void sys_pin_enable_port(void);


//看门狗WDOG(COP)宏定义
#define WDOG_DISABLE() {SIM_COPC = 0x00u;}  //禁用看门狗
//COP使用LPO时钟，COP在2^10个LPO时钟周期后延时
#define WDOG_ENABLE() {SIM_COPC |= SIM_COPC_COPT_MASK;} //使能看门狗


// 系统上电启动程序
 void startup(void)
{
	 WDOG_DISABLE();       //禁用看门狗
        //WDOG_ENABLE();        使能看门狗  
	vector_init();          //复制中断向量表至RAM
	m_zero_fill_bss ();     //清零未初始化BSS数据段
	m_data_seg_init ();     //将ROM中的初始化数据拷贝到RAM中
	sys_init();             //初始化系统时钟
	sys_pin_enable_port();  //使能端口时钟
	main();                 //进入主函数
	while(1);               //永久循环（主函数内永久循环，含有执行不到该语句）          
}

//-------------------------------------------------------------------------------

//拷贝中断向量表
void vector_init(void)
{
	extern char __VECTOR_RAM[];
	extern char __vector_table[];
	uint_32 n;
	
	if (__VECTOR_RAM != __vector_table)
	{
	    for (n = 0; n < 0x410; n++)
	        __VECTOR_RAM[n] = __vector_table[n];
	}
	//Point the VTOR to the new copy of the vector table 
      SCB_VTOR=(uint_32)__VECTOR_RAM;
}

// 初始化BSS段
void m_zero_fill_bss(void)
{
	extern char __START_BSS[];
    extern char __END_BSS[];

    uint_8 *bss_start = (uint_8 *)__START_BSS;
    uint_8 *bss_end   = (uint_8 *)__END_BSS;
    uint_32 n = bss_end - bss_start;
    
    while (n--)
    	*bss_start++ = 0;
}

//复制ROM数据至RAM
void m_data_seg_init(void)
{
	extern char __START_DATA[];
	extern char __END_DATA[];
	extern char __START_DATA_ROM[];
	
	uint_8 *data_start = (uint_8 *)__START_DATA;
	uint_8 *data_end   = (uint_8 *)__END_DATA;
	uint_8 *data_rom_start = (uint_8 *)__START_DATA_ROM;
	uint_32 n = data_end - data_start;
	
	while (n--)
	    *data_start++ = *data_rom_start++;
}

//使能端口时钟
void sys_pin_enable_port(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK
			  | SIM_SCGC5_PORTB_MASK
			  | SIM_SCGC5_PORTC_MASK
			  | SIM_SCGC5_PORTD_MASK
			  | SIM_SCGC5_PORTE_MASK; 
}

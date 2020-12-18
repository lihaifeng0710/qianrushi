//===========================================================================
//文件名称：vectors.c
//功能概要：定义中断向量表源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2013-02-22V1.2;2013-05-08V2.0(WYH) 
//===========================================================================

#include "vectors.h"

extern unsigned long __BOOT_STACK_ADDRESS;   //在"intflash.ld“文件中定义

// KL25中断向量表
__attribute__ ((section (".vectortable"))) vector_entry rom_vector[] = 
{
    (vector_entry)(&__BOOT_STACK_ADDRESS),   //0x00  0x00000000-ivINT_Initial_Stack_Pointer
    BOOT_START,         // 0x01  0x00000004 - ivINT_Initial_Program_Counter used 
    VECTOR_002,         // 0x02  0x00000008   -2   ivINT_NMI 
    VECTOR_003,         // 0x03  0x0000000C   -1   ivINT_Hard_Fault
    VECTOR_004,         // 0x04  0x00000010 - ivINT_Reserved4 
    VECTOR_005,         // 0x05  0x00000014 - ivINT_Reserved5 
    VECTOR_006,         // 0x06  0x00000018 - ivINT_Reserved6 
    VECTOR_007,         // 0x07  0x0000001C - ivINT_Reserved7 
    VECTOR_008,         // 0x08  0x00000020 - ivINT_Reserved8 
    VECTOR_009,         // 0x09  0x00000024 - ivINT_Reserved9 
    VECTOR_010,         // 0x0A  0x00000028 - ivINT_Reserved10
    VECTOR_011,         // 0x0B  0x0000002C - ivINT_SVCall    
    VECTOR_012,         // 0x0C  0x00000030 - ivINT_Reserved12
    VECTOR_013,         // 0x0D  0x00000034 - ivINT_Reserved13
    VECTOR_014,         // 0x0E  0x00000038 - ivINT_PendableSrvReq 
    VECTOR_015,         // 0x0F  0x0000003C - ivINT_SysTick   
	// Cortex external interrupt vectors 
	VECTOR_016,         // 0x10  0x00000040 - ivINT_DMA0                        
	VECTOR_017,         // 0x11  0x00000044 - ivINT_DMA1                        
	VECTOR_018,         // 0x12  0x00000048 - ivINT_DMA2                        
	VECTOR_019,         // 0x13  0x0000004C - ivINT_DMA3                        
	VECTOR_020,         // 0x14  0x00000050 - ivINT_DMA4                        
	VECTOR_021,         // 0x15  0x00000054 - ivINT_DMA5                        
	VECTOR_022,         // 0x16  0x00000058 - ivINT_DMA6                        
	VECTOR_023,         // 0x17  0x0000005C - ivINT_DMA7                        
	VECTOR_024,         // 0x18  0x00000060 - ivINT_DMA8                        
	VECTOR_025,         // 0x19  0x00000064 - ivINT_DMA9                        
	VECTOR_026,         // 0x1A  0x00000068 - ivINT_DMA10                       
	VECTOR_027,         // 0x1B  0x0000006C - ivINT_DMA11                       
	VECTOR_028,         // 0x1C  0x00000070 - ivINT_DMA12                       
	VECTOR_029,         // 0x1D  0x00000074 - ivINT_DMA13                       
	VECTOR_030,         // 0x1E  0x00000078 - ivINT_DMA14                       
	VECTOR_031,         // 0x1F  0x0000007C - ivINT_DMA15                       
	VECTOR_032,         // 0x20  0x00000080 - ivINT_DMA_Error                   
	VECTOR_033,         // 0x21  0x00000084 - ivINT_MCM                         
	VECTOR_034,         // 0x22  0x00000088 - ivINT_FTFL                        
	VECTOR_035,         // 0x23  0x0000008C - ivINT_Read_Collision              
	VECTOR_036,         // 0x24  0x00000090 - ivINT_LVD_LVW                     
	VECTOR_037,         // 0x25  0x00000094 - ivINT_LLW                         
	VECTOR_038,         // 0x26  0x00000098 - ivINT_Watchdog                    
	VECTOR_039,         // 0x27  0x0000009C - ivINT_RNG                         
	VECTOR_040,         // 0x28  0x000000A0 - ivINT_I2C0                        
	VECTOR_041,         // 0x29  0x000000A4 - ivINT_I2C1                        
	VECTOR_042,         // 0x2A  0x000000A8 - ivINT_SPI0                        
	VECTOR_043,         // 0x2B  0x000000AC - ivINT_SPI1                        
	VECTOR_044,         // 0x2C  0x000000B0 - ivINT_SPI2                        
	VECTOR_045,         // 0x2D  0x000000B4 - ivINT_CAN0_ORed_Message_buffer    
	VECTOR_046,         // 0x2E  0x000000B8 - ivINT_PORT                        
	VECTOR_047          // 0x2F  0x000000BC - ivINT_PORT                        
};

void NOS_isrDummy(void)
{
}

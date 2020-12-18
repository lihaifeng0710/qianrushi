//=====================================================================
//文件名称：dma.h
//功能概要：dma底层驱动构件头文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：  2019-05-09  V2.0
//适用芯片：KL25、KL26、KL36
//=====================================================================

#ifndef _DMA_H_
#define _DMA_H_
#include"mcu.h"
#include"gec.h"
#include"includes.h"
//#include"uart.h"
//DMA模式
#define DMA_MODE_NORMAl  0  //普通模式
#define DMA_MODE_PERIODIC 1 //周期模式
//DMA传输宽度
#define DMA_TRANS_WIDTH_BIT32 (0x00) //DMA传输宽度为32位
#define DMA_TRANS_WIDTH_BIT8  (0x01) //DMA传输宽度为8位
#define DMA_TRANS_WIDTH_BIT16 (0x02) //DMA传输宽度为16位
//DMA源地址模数大小
#define DMA_MODULE_DISABLE    (0)//禁用模块
#define DMA_MODULO_BYTE_16    (1)
#define DMA_MODULO_BYTE_32    (2)
#define DMA_MODULO_BYTE_64    (3)
#define DMA_MODULO_BYTE_128   (4)
#define DMA_MODULO_BYTE_256   (5)
#define DMA_MODULO_BYTE_512   (6)
#define DMA_MODULO_BYTE_1K    (7)
#define DMA_MODULO_BYTE_2K    (8)
#define DMA_MODULO_BYTE_4K    (9)
#define DMA_MODULO_BYTE_8K    (10)
#define DMA_MODULO_BYTE_16K   (11)
#define DMA_MODULO_BYTE_32K   (12)
#define DMA_MODULO_BYTE_64K   (13)
#define DMA_MODULO_BYTE_128K  (14)
#define DMA_MODULO_BYTE_256K  (15)
//源地址偏移量开关
#define DMA_SRC_ADDR_OFFSET_ON  (1)
#define DMA_SRC_ADDR_OFFSET_OFF (0)
//目标地址偏移量开关
#define DMA_DST_ADDR_OFFSET_ON  (1)
#define DMA_DST_ADDR_OFFSET_OFF (0)

//DMA请求源
typedef enum DMA_sources
{
    Channel_Disabled    = 0,
    DMA_UART0_Rx            = 2,
    DMA_UART0_Tx            = 3,
    DMA_UART1_Rx            = 4,
    DMA_UART1_Tx            = 5,
    DMA_UART2_Rx            = 6,
    DMA_UART2_Tx            = 7,
	/*        I2S            */
	DMA_I2S0_Rx             = 14,
    DMA_I2S0_Tx             = 15,
    /*        SPI            */
    DMA_SPI0_Rx             = 16,
    DMA_SPI0_Tx             = 17,
    DMA_SPI1_Rx             = 18,
    DMA_SPI1_Tx             = 19,
    /*        I2C            */
    DMA_I2C0                = 22,
    DMA_I2C1                = 23,
    /*        TPM            */
    DMA_TPM0_CH0            = 24,
    DMA_TPM0_CH1            = 25,
    DMA_TPM0_CH2            = 26,
    DMA_TPM0_CH3            = 27,
    DMA_TPM0_CH4            = 28,
    DMA_TPM0_CH5            = 29,
    DMA_TPM1_CH0            = 32,
    DMA_TPM1_CH1            = 33,
    DMA_TPM2_CH0            = 34,
    DMA_TPM2_CH1            = 35,
    /*     ADC/DAC/CMP    */
    DMA_ADC0                = 40,
    DMA_CMP0                = 42,
    DMA_DAC0                = 45,
    DMA_Port_A              = 49,
	DMA_Port_C              = 51,
    DMA_Port_D              = 52,
    DMA_TPM0_OVERFLOW            = 54,
    DMA_TPM1_OVERFLOW            = 55,
    DMA_TPM2_OVERFLOW            = 56,
    DMA_TSI                 = 57,
    DMA_Always_EN1          = 60,
    DMA_Always_EN2          = 61,
    DMA_Always_EN3          = 62,
    DMA_Always_EN4          = 63,
} DMA_sources;

//定义DMA通道状态
typedef enum {
	DMAChannelIdle,			//通道空闲
	DMAChannelStarting,		//通道正在启动
	DMAChannelExecuting,	//通道正在执行
	DMAChannelDone			//通道完成主循环
} DMAChannelState;

//==========================================================================
//函数名称: dma_init
//函数返回: 无
//参数说明:  UART_DMA 范围：见gec.h中定义
//         src_addr:源地址
//         trans_cnt：DMA传输的数据长度
//功能概要: 初始化DMA的UART功能
//==========================================================================
void dma_init(uint8_t UART_DMA);

//==========================================================================
//函数名称: dma_send
//函数返回: 无
//参数说明:
//参数说明:  UART_DMA 范围：见gec.h中定义
//         src_addr:源地址
//         trans_cnt：DMA传输的数据长度
//功能概要:  使用DMA通道进行串口发送，串口号UART。
//==========================================================================
void dma_send(uint8_t UART_DMA,uint32_t src_addr,uint32_t trans_cnt);

//==========================================================================
//函数名称: dma_read1
//函数返回: 无
//参数说明:  UART_DMA UART_DMA模块号，可用参数可参见gec.h文件
//         src_addr：目标地址
//         buffLength：DMA传输的数据长度
//功能概要:  使用DMA通道进行串口发送，串口号UART。
//==========================================================================
void dma_read(uint8_t UART_DMA,uint32_t src_addr,uint32_t trans_cnt);

void uart_IdleIrq_enable(uint8_t uartNo);

void uart_IdleIrq_clear(uint8_t uartNo);

#endif /* 05_DRIVER_DMA_DMA_H_ */

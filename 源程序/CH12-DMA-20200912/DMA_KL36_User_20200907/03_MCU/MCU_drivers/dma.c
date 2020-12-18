//=====================================================================
//文件名称：dma.c
//功能概要：dma底层驱动构件源文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：  2019-05-09  V2.0
//适用芯片：KL25、KL26、KL36
//=====================================================================
#include"dma.h"

//==========================================================================
//函数名称: dma_init
//函数返回: 无
//参数说明:  ch ：DMA通道号，可用参数可参见gec.h文件
//功能概要: 初始化DMA功能
//==========================================================================
void dma_init(uint8_t ch)
{

	//开启DMA和DMAMUX模块时钟门
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	DMAMUX0_CHCFG(ch) = 0x00;
	//清通道中断与错误标志
	if((DMA_DSR_BCR(ch)&DMA_DSR_BCR_DONE_MASK)==DMA_DSR_BCR_DONE_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_BES_MASK)==DMA_DSR_BCR_BES_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_BED_MASK)==DMA_DSR_BCR_BED_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_CE_MASK)==DMA_DSR_BCR_CE_MASK)
		DMA_DSR_BCR(ch)|=DMA_DSR_BCR_DONE_MASK;
	//清除DMA控制寄存器
	DMA_DCR(ch)=0x00;
	DMA_DCR(ch) |= (DMA_DCR_SSIZE(1)		//配置源地址数据长度为8位
				| DMA_DCR_DSIZE(1)		//目的地址数据长度为8位
				| DMA_DCR_D_REQ_MASK	//BCR到0时外设请求清除
				| DMA_DCR_DINC_MASK		//目的地址允许增加
				| DMA_DCR_CS_MASK		//每次请求都会产生一次读写传输
				| DMA_DCR_ERQ_MASK		//允许外设请求
				//| DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK	//允许异步请求
	);
	//DMA通道使能
	DMAMUX0_CHCFG(ch)|=(DMAMUX_CHCFG_ENBL_MASK);
}

//==========================================================================
//函数名称: dma_read
//函数返回: 无
//参数说明:  SrcAddress 源地址
//         DstAddress：目标地址
//         DataLength：DMA传输的数据长度
//功能概要:  使用DMA通道进行串口发送，串口号UART。
//==========================================================================
void dma_read(uint8_t SrcAddress, uint8_t DstAddress, uint8_t DataLength)
{
	DMA_SAR0 = SrcAddress;
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(DataLength);
	DMA_DAR0 = DstAddress;


}

//======================================================================
//函数名称：dma_clear
//参数说明：ch:
//函数返回：清通道中断与错误标志
//======================================================================
void dma_clear(uint8_t ch)
{
	if((DMA_DSR_BCR(ch)&DMA_DSR_BCR_DONE_MASK)==DMA_DSR_BCR_DONE_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_BES_MASK)==DMA_DSR_BCR_BES_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_BED_MASK)==DMA_DSR_BCR_BED_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_CE_MASK)==DMA_DSR_BCR_CE_MASK)
		DMA_DSR_BCR(ch)|=DMA_DSR_BCR_DONE_MASK;

}


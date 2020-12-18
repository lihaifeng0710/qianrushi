//=====================================================================
//文件名称：dma.c
//功能概要：dma底层驱动构件源文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：  2019-05-09  V2.0
//适用芯片：KL25、KL26、KL36
//=====================================================================
#include"dma.h"

//DMA各通道中断请求号
static const IRQn_Type dma_irq_table[] = {
DMA0_IRQn,  DMA1_IRQn,  DMA2_IRQn,  DMA3_IRQn,
};
IRQn_Type table_irq_uart[3] = {UART0_IRQn, UART1_IRQn, UART2_IRQn};

//==========================================================================
//函数名称: dma_init
//函数返回: 无
//参数说明:  UART_DMA ：UART_DMA模块号，可用参数可参见gec.h文件
//         src_addr:源地址
//         trans_cnt：DMA传输的数据长度
//功能概要: 初始化DMA的UART功能
//==========================================================================
void dma_init(uint_8 UART_DMA)
{
	uint_8 UART,chSend,chRe; //串口模块和通道
	//解析UART_DMA
	if(UART_DMA==0)
	{
		UART=0;//串口0
		chSend=0;  //DMA通道0
		chRe = 1;
	}
	//开启DMA和DMAMUX模块时钟门
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	//使能UART_x的DMA发送
	if(UART_DMA==0)
	{
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;    //启动串口0时钟
		UART0_C5|= UART_C4_TDMAS_MASK;//使能UART0的TDMA
		UART0_C5|= UART_C4_RDMAS_MASK;//使能UART0的RDMA
		UART0_C2|= UART_C2_TIE_MASK;  //使能UART0发送中断
		UART0_C2|= UART_C2_RIE_MASK;  //使能UART0接收中断
		UART0_C2&= ~UART_C2_TCIE_MASK;  //禁用UART0发送完成中断
		DMAMUX0_CHCFG(chSend)|=DMA_UART0_Tx<<DMAMUX_CHCFG_SOURCE_SHIFT;
		DMAMUX0_CHCFG(chRe)|=DMA_UART0_Rx<<DMAMUX_CHCFG_SOURCE_SHIFT;
	}

    //清发送通道中断与错误标志
    if((DMA_DSR_BCR(chSend)&DMA_DSR_BCR_DONE_MASK)==DMA_DSR_BCR_DONE_MASK||
    		(DMA_DSR_BCR(chSend)&DMA_DSR_BCR_BES_MASK)==DMA_DSR_BCR_BES_MASK||
			(DMA_DSR_BCR(chSend)&DMA_DSR_BCR_BED_MASK)==DMA_DSR_BCR_BED_MASK||
			(DMA_DSR_BCR(chSend)&DMA_DSR_BCR_CE_MASK)==DMA_DSR_BCR_CE_MASK)
    	DMA_DSR_BCR(chSend)|=DMA_DSR_BCR_DONE_MASK;
    //清接收通道中断与错误标志
    if((DMA_DSR_BCR(chRe)&DMA_DSR_BCR_DONE_MASK)==DMA_DSR_BCR_DONE_MASK||
    		(DMA_DSR_BCR(chRe)&DMA_DSR_BCR_BES_MASK)==DMA_DSR_BCR_BES_MASK||
			(DMA_DSR_BCR(chRe)&DMA_DSR_BCR_BED_MASK)==DMA_DSR_BCR_BED_MASK||
			(DMA_DSR_BCR(chRe)&DMA_DSR_BCR_CE_MASK)==DMA_DSR_BCR_CE_MASK)
    	DMA_DSR_BCR(chRe)|=DMA_DSR_BCR_DONE_MASK;

	DMA_DCR(chSend)=0x00;
	DMA_DCR(chRe)=0x00;
	//默认不接收该通道的DMA请求
	DMA_DCR(chSend)&=~DMA_DCR_ERQ_MASK;
	DMA_DCR(chRe)&=~DMA_DCR_ERQ_MASK;
	//暂时关闭该DMA通道，并设置该通道的请求源，默认触发模式为正常模式
	DMAMUX0_CHCFG(chSend)&=~(DMAMUX_CHCFG_ENBL_MASK);
	DMAMUX0_CHCFG(chRe)&=~(DMAMUX_CHCFG_ENBL_MASK);
	//DMA模式为普通模式
	DMAMUX0_CHCFG(chSend)&=~DMAMUX_CHCFG_TRIG_MASK;
	DMAMUX0_CHCFG(chRe)&=~DMAMUX_CHCFG_TRIG_MASK;
    //关闭自动清除ERQ位
	DMA_DCR(chSend)&=~DMA_DCR_D_REQ_MASK;
	DMA_DCR(chRe)&=~DMA_DCR_D_REQ_MASK;
	//设置源地址和目标地址的模数大小和数据宽度
	DMA_DCR(chSend)|=  (DMA_MODULE_DISABLE     <<DMA_DCR_SMOD_SHIFT)
			      |(DMA_TRANS_WIDTH_BIT8   <<DMA_DCR_SSIZE_SHIFT)
			      |(DMA_MODULE_DISABLE    <<DMA_DCR_DMOD_SHIFT)
			      |(DMA_TRANS_WIDTH_BIT8  <<DMA_DCR_DSIZE_SHIFT)
				  |(DMA_DCR_CS_MASK);

	DMA_DCR(chRe)|=  (DMA_MODULE_DISABLE     <<DMA_DCR_SMOD_SHIFT)
			      |(DMA_TRANS_WIDTH_BIT8   <<DMA_DCR_SSIZE_SHIFT)
			      |(DMA_MODULE_DISABLE    <<DMA_DCR_DMOD_SHIFT)
			      |(DMA_TRANS_WIDTH_BIT8  <<DMA_DCR_DSIZE_SHIFT)
				  |(DMA_DCR_CS_MASK);
	//设置传输时源地址偏移
	DMA_DCR(chSend)|=DMA_DCR_SINC_MASK;
	DMA_DCR(chRe)&=~DMA_DCR_SINC_MASK;
	//设置传输时目标地址不偏移
	DMA_DCR(chSend)&=~DMA_DCR_DINC_MASK;
	DMA_DCR(chRe)|=DMA_DCR_DINC_MASK;
	//字节数计数寄存器设置
	DMA_DSR_BCR(chSend)&=~DMA_DSR_BCR_BCR_MASK;
	DMA_DSR_BCR(chRe)&=~DMA_DSR_BCR_BCR_MASK;
//	DMA_DSR_BCR(ch)|=trans_cnt<<DMA_DSR_BCR_BCR_SHIFT;
	//使能该DMA通道
//	DMAMUX0_CHCFG(chSend)|=(DMAMUX_CHCFG_ENBL_MASK);
//	DMAMUX0_CHCFG(chRe)|=(DMAMUX_CHCFG_ENBL_MASK);
	return;
}


//==========================================================================
//函数名称: dma_send
//函数返回: 无
//参数说明:  UART_DMA UART_DMA模块号，可用参数可参见gec.h文件
//         src_addr:源地址
//         trans_cnt：DMA传输的数据长度
//功能概要:  使用DMA通道进行串口发送，串口号UART。
//==========================================================================
void dma_send(uint_8 UART_DMA,uint_32 src_addr,uint_32 trans_cnt)
{
	uint_32 dest_addr;//目标地址
	uint_32 count;
	count=0;
	uint_8 UART,ch; //串口模块和通道
	//解析UART_DMA
	if(UART_DMA==0)
	{
		UART=0;//串口0
		ch=0;  //DMA通道0
	}
	//判断传输数目参数是否合法
	if((trans_cnt&0xFFF00000)>0) trans_cnt=0xFFFFF;
	//目的地址
	dest_addr=UART0_BASE+0x7;
	//设置目标地址
	DMA_DAR(ch)=dest_addr;
	//清中断与错误标志
	DMA_DSR_BCR(ch)|=DMA_DSR_BCR_DONE_MASK;
	//暂时关闭该DMA通道，并设置该通道的请求源，默认触发模式为正常模式
	DMA_DCR(ch)&=~DMA_DCR_ERQ_MASK;
	DMAMUX0_CHCFG(ch)&=~(DMAMUX_CHCFG_ENBL_MASK);
	//设置源地址
	DMA_SAR(ch)=src_addr;
	//字节数计数寄存器设置
	DMA_DSR_BCR(ch)&=~DMA_DSR_BCR_BCR_MASK;
	DMA_DSR_BCR(ch)|=trans_cnt<<DMA_DSR_BCR_BCR_SHIFT;
	//使能该DMA通道
	DMAMUX0_CHCFG(ch)|=(DMAMUX_CHCFG_ENBL_MASK);
	DMA_DCR(ch)|=DMA_DCR_ERQ_MASK;
}
//==========================================================================
//函数名称: dma_read
//函数返回: 无
//参数说明:  UART_DMA UART_DMA模块号，可用参数可参见gec.h文件
//         src_addr：目标地址
//         buffLength：DMA传输的数据长度
//功能概要:  使用DMA通道进行串口发送，串口号UART。
//==========================================================================
void dma_read(uint_8 UART_DMA,uint_32 src_addr,uint_32 trans_cnt)
{
	uint_32 dest_addr;//目标地址
	uint_32 count;
	uint_8 UART,ch; //串口模块和通道
	//解析UART_DMA
	if(UART_DMA==0)
	{
		UART=0;//串口0
		ch=1;  //DMA通道0
		dest_addr=UART0_BASE+0x7;
	}
	//判断传输数目参数是否合法
	if((trans_cnt&0xFFF00000)>0) trans_cnt=0xFFFFF;
	//目的地址
//	dest_addr=UART0_BASE+0x7;
	//设置目标地址
	DMA_DAR(ch)=src_addr;
	//设置源地址
	DMA_SAR(ch)=dest_addr;
	//清中断与错误标志
	DMA_DSR_BCR(ch)|=DMA_DSR_BCR_DONE_MASK;
	//暂时关闭该DMA通道，并设置该通道的请求源，默认触发模式为正常模式
	DMA_DCR(ch)&=~DMA_DCR_ERQ_MASK;
	DMAMUX0_CHCFG(ch)&=~(DMAMUX_CHCFG_ENBL_MASK);
	//字节数计数寄存器设置
	DMA_DSR_BCR(ch)&=~DMA_DSR_BCR_BCR_MASK;
	DMA_DSR_BCR(ch)|=trans_cnt<<DMA_DSR_BCR_BCR_SHIFT;
	//使能该DMA通道
	DMAMUX0_CHCFG(ch)|=(DMAMUX_CHCFG_ENBL_MASK);
	DMA_DCR(ch)|=DMA_DCR_ERQ_MASK;
}

//======================================================================
//函数名称：uart_IdleIrq_enable
//参数说明：uartNo:
//函数返回：无
//======================================================================
void uart_IdleIrq_enable(uint_8 uartNo)
{
    UART0_MemMapPtr uartch_0=UART0_BASE_PTR; //获取UART0基地址
//    UART_MemMapPtr uartch_1_2 = UART_ARR[uartNo-1]; //获取UART1或者2基地址
    //判断传入串口号参数是否有误，有误直接退出
    if(0 == uartNo)
    {
    	UART0_C2_REG(uartch_0) |= UART0_C2_ILIE_MASK;     //开放UART空闲中断
    	UART0_S1_REG(uartch_0) |= 0x10;
    }
//    else
//    {
//        UART_C2_REG(uartch_1_2) |= UART0_C2_ILIE_MASK;    //开放UART空闲中断
//        UART2_S1_REG(uartch_0) |= 0x10;
//    }
    NVIC_EnableIRQ(table_irq_uart[uartNo]);    //开中断控制器IRQ中断
}

//======================================================================
//函数名称：uart_IdleIrq_clear
//参数说明：uartNo:
//函数返回：无
//======================================================================
void uart_IdleIrq_clear(uint_8 uartNo)
{
    UART0_MemMapPtr uartch_0=UART0_BASE_PTR; //获取UART0基地址
//    UART_MemMapPtr uartch_1_2 = UART_ARR[uartNo-1]; //获取UART1或者2基地址
    //判断传入串口号参数是否有误，有误直接退出
    if(0 == uartNo)
    {
    	//清空闲线标志
    	UART0_S1_REG(UART0_BASE_PTR) |= 0x10;
    }
    else
    {
    	//Uart1\2
    }
    //
}

//======================================================================
//函数名称：dma_enable
//参数说明：dmaNo:
//函数返回：无
//======================================================================
 void dma_enable(uint_8 UART_DMA)
{
	uint_8 UART,chSend,chRe; //串口模块和通道
	//解析UART_DMA
	if(UART_DMA==0)
	{
		UART=0;//串口0
		chSend=0;  //DMA通道0
		chRe = 1;  //DMA通道1
	}
//	DMA_DCR(chSend)|=DMA_DCR_EINT_MASK;
	DMA_DCR(chRe)|=DMA_DCR_EINT_MASK;
//	NVIC_EnableIRQ(DMA0_IRQn);    //开中断控制器IRQ中断
	NVIC_EnableIRQ(DMA1_IRQn);    //开中断控制器IRQ中断
}

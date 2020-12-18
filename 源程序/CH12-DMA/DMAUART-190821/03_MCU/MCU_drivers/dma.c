//=====================================================================
//�ļ����ƣ�dma.c
//���ܸ�Ҫ��dma�ײ���������Դ�ļ�
//������λ�����ݴ�ѧǶ��ʽϵͳ���������о���(sumcu.suda.edu.cn)
//��    ����  2019-05-09  V2.0
//����оƬ��KL25��KL26��KL36
//=====================================================================
#include"dma.h"

//DMA��ͨ���ж������
static const IRQn_Type dma_irq_table[] = {
DMA0_IRQn,  DMA1_IRQn,  DMA2_IRQn,  DMA3_IRQn,
};
IRQn_Type table_irq_uart[3] = {UART0_IRQn, UART1_IRQn, UART2_IRQn};

//==========================================================================
//��������: dma_init
//��������: ��
//����˵��:  UART_DMA ��UART_DMAģ��ţ����ò����ɲμ�gec.h�ļ�
//         src_addr:Դ��ַ
//         trans_cnt��DMA��������ݳ���
//���ܸ�Ҫ: ��ʼ��DMA��UART����
//==========================================================================
void dma_init(uint_8 UART_DMA)
{
	uint_8 UART,chSend,chRe; //����ģ���ͨ��
	//����UART_DMA
	if(UART_DMA==0)
	{
		UART=0;//����0
		chSend=0;  //DMAͨ��0
		chRe = 1;
	}
	//����DMA��DMAMUXģ��ʱ����
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	//ʹ��UART_x��DMA����
	if(UART_DMA==0)
	{
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;    //��������0ʱ��
		UART0_C5|= UART_C4_TDMAS_MASK;//ʹ��UART0��TDMA
		UART0_C5|= UART_C4_RDMAS_MASK;//ʹ��UART0��RDMA
		UART0_C2|= UART_C2_TIE_MASK;  //ʹ��UART0�����ж�
		UART0_C2|= UART_C2_RIE_MASK;  //ʹ��UART0�����ж�
		UART0_C2&= ~UART_C2_TCIE_MASK;  //����UART0��������ж�
		DMAMUX0_CHCFG(chSend)|=DMA_UART0_Tx<<DMAMUX_CHCFG_SOURCE_SHIFT;
		DMAMUX0_CHCFG(chRe)|=DMA_UART0_Rx<<DMAMUX_CHCFG_SOURCE_SHIFT;
	}

    //�巢��ͨ���ж�������־
    if((DMA_DSR_BCR(chSend)&DMA_DSR_BCR_DONE_MASK)==DMA_DSR_BCR_DONE_MASK||
    		(DMA_DSR_BCR(chSend)&DMA_DSR_BCR_BES_MASK)==DMA_DSR_BCR_BES_MASK||
			(DMA_DSR_BCR(chSend)&DMA_DSR_BCR_BED_MASK)==DMA_DSR_BCR_BED_MASK||
			(DMA_DSR_BCR(chSend)&DMA_DSR_BCR_CE_MASK)==DMA_DSR_BCR_CE_MASK)
    	DMA_DSR_BCR(chSend)|=DMA_DSR_BCR_DONE_MASK;
    //�����ͨ���ж�������־
    if((DMA_DSR_BCR(chRe)&DMA_DSR_BCR_DONE_MASK)==DMA_DSR_BCR_DONE_MASK||
    		(DMA_DSR_BCR(chRe)&DMA_DSR_BCR_BES_MASK)==DMA_DSR_BCR_BES_MASK||
			(DMA_DSR_BCR(chRe)&DMA_DSR_BCR_BED_MASK)==DMA_DSR_BCR_BED_MASK||
			(DMA_DSR_BCR(chRe)&DMA_DSR_BCR_CE_MASK)==DMA_DSR_BCR_CE_MASK)
    	DMA_DSR_BCR(chRe)|=DMA_DSR_BCR_DONE_MASK;

	DMA_DCR(chSend)=0x00;
	DMA_DCR(chRe)=0x00;
	//Ĭ�ϲ����ո�ͨ����DMA����
	DMA_DCR(chSend)&=~DMA_DCR_ERQ_MASK;
	DMA_DCR(chRe)&=~DMA_DCR_ERQ_MASK;
	//��ʱ�رո�DMAͨ���������ø�ͨ��������Դ��Ĭ�ϴ���ģʽΪ����ģʽ
	DMAMUX0_CHCFG(chSend)&=~(DMAMUX_CHCFG_ENBL_MASK);
	DMAMUX0_CHCFG(chRe)&=~(DMAMUX_CHCFG_ENBL_MASK);
	//DMAģʽΪ��ͨģʽ
	DMAMUX0_CHCFG(chSend)&=~DMAMUX_CHCFG_TRIG_MASK;
	DMAMUX0_CHCFG(chRe)&=~DMAMUX_CHCFG_TRIG_MASK;
    //�ر��Զ����ERQλ
	DMA_DCR(chSend)&=~DMA_DCR_D_REQ_MASK;
	DMA_DCR(chRe)&=~DMA_DCR_D_REQ_MASK;
	//����Դ��ַ��Ŀ���ַ��ģ����С�����ݿ��
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
	//���ô���ʱԴ��ַƫ��
	DMA_DCR(chSend)|=DMA_DCR_SINC_MASK;
	DMA_DCR(chRe)&=~DMA_DCR_SINC_MASK;
	//���ô���ʱĿ���ַ��ƫ��
	DMA_DCR(chSend)&=~DMA_DCR_DINC_MASK;
	DMA_DCR(chRe)|=DMA_DCR_DINC_MASK;
	//�ֽ��������Ĵ�������
	DMA_DSR_BCR(chSend)&=~DMA_DSR_BCR_BCR_MASK;
	DMA_DSR_BCR(chRe)&=~DMA_DSR_BCR_BCR_MASK;
//	DMA_DSR_BCR(ch)|=trans_cnt<<DMA_DSR_BCR_BCR_SHIFT;
	//ʹ�ܸ�DMAͨ��
//	DMAMUX0_CHCFG(chSend)|=(DMAMUX_CHCFG_ENBL_MASK);
//	DMAMUX0_CHCFG(chRe)|=(DMAMUX_CHCFG_ENBL_MASK);
	return;
}


//==========================================================================
//��������: dma_send
//��������: ��
//����˵��:  UART_DMA UART_DMAģ��ţ����ò����ɲμ�gec.h�ļ�
//         src_addr:Դ��ַ
//         trans_cnt��DMA��������ݳ���
//���ܸ�Ҫ:  ʹ��DMAͨ�����д��ڷ��ͣ����ں�UART��
//==========================================================================
void dma_send(uint_8 UART_DMA,uint_32 src_addr,uint_32 trans_cnt)
{
	uint_32 dest_addr;//Ŀ���ַ
	uint_32 count;
	count=0;
	uint_8 UART,ch; //����ģ���ͨ��
	//����UART_DMA
	if(UART_DMA==0)
	{
		UART=0;//����0
		ch=0;  //DMAͨ��0
	}
	//�жϴ�����Ŀ�����Ƿ�Ϸ�
	if((trans_cnt&0xFFF00000)>0) trans_cnt=0xFFFFF;
	//Ŀ�ĵ�ַ
	dest_addr=UART0_BASE+0x7;
	//����Ŀ���ַ
	DMA_DAR(ch)=dest_addr;
	//���ж�������־
	DMA_DSR_BCR(ch)|=DMA_DSR_BCR_DONE_MASK;
	//��ʱ�رո�DMAͨ���������ø�ͨ��������Դ��Ĭ�ϴ���ģʽΪ����ģʽ
	DMA_DCR(ch)&=~DMA_DCR_ERQ_MASK;
	DMAMUX0_CHCFG(ch)&=~(DMAMUX_CHCFG_ENBL_MASK);
	//����Դ��ַ
	DMA_SAR(ch)=src_addr;
	//�ֽ��������Ĵ�������
	DMA_DSR_BCR(ch)&=~DMA_DSR_BCR_BCR_MASK;
	DMA_DSR_BCR(ch)|=trans_cnt<<DMA_DSR_BCR_BCR_SHIFT;
	//ʹ�ܸ�DMAͨ��
	DMAMUX0_CHCFG(ch)|=(DMAMUX_CHCFG_ENBL_MASK);
	DMA_DCR(ch)|=DMA_DCR_ERQ_MASK;
}
//==========================================================================
//��������: dma_read
//��������: ��
//����˵��:  UART_DMA UART_DMAģ��ţ����ò����ɲμ�gec.h�ļ�
//         src_addr��Ŀ���ַ
//         buffLength��DMA��������ݳ���
//���ܸ�Ҫ:  ʹ��DMAͨ�����д��ڷ��ͣ����ں�UART��
//==========================================================================
void dma_read(uint_8 UART_DMA,uint_32 src_addr,uint_32 trans_cnt)
{
	uint_32 dest_addr;//Ŀ���ַ
	uint_32 count;
	uint_8 UART,ch; //����ģ���ͨ��
	//����UART_DMA
	if(UART_DMA==0)
	{
		UART=0;//����0
		ch=1;  //DMAͨ��0
		dest_addr=UART0_BASE+0x7;
	}
	//�жϴ�����Ŀ�����Ƿ�Ϸ�
	if((trans_cnt&0xFFF00000)>0) trans_cnt=0xFFFFF;
	//Ŀ�ĵ�ַ
//	dest_addr=UART0_BASE+0x7;
	//����Ŀ���ַ
	DMA_DAR(ch)=src_addr;
	//����Դ��ַ
	DMA_SAR(ch)=dest_addr;
	//���ж�������־
	DMA_DSR_BCR(ch)|=DMA_DSR_BCR_DONE_MASK;
	//��ʱ�رո�DMAͨ���������ø�ͨ��������Դ��Ĭ�ϴ���ģʽΪ����ģʽ
	DMA_DCR(ch)&=~DMA_DCR_ERQ_MASK;
	DMAMUX0_CHCFG(ch)&=~(DMAMUX_CHCFG_ENBL_MASK);
	//�ֽ��������Ĵ�������
	DMA_DSR_BCR(ch)&=~DMA_DSR_BCR_BCR_MASK;
	DMA_DSR_BCR(ch)|=trans_cnt<<DMA_DSR_BCR_BCR_SHIFT;
	//ʹ�ܸ�DMAͨ��
	DMAMUX0_CHCFG(ch)|=(DMAMUX_CHCFG_ENBL_MASK);
	DMA_DCR(ch)|=DMA_DCR_ERQ_MASK;
}

//======================================================================
//�������ƣ�uart_IdleIrq_enable
//����˵����uartNo:
//�������أ���
//======================================================================
void uart_IdleIrq_enable(uint_8 uartNo)
{
    UART0_MemMapPtr uartch_0=UART0_BASE_PTR; //��ȡUART0����ַ
//    UART_MemMapPtr uartch_1_2 = UART_ARR[uartNo-1]; //��ȡUART1����2����ַ
    //�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
    if(0 == uartNo)
    {
    	UART0_C2_REG(uartch_0) |= UART0_C2_ILIE_MASK;     //����UART�����ж�
    	UART0_S1_REG(uartch_0) |= 0x10;
    }
//    else
//    {
//        UART_C2_REG(uartch_1_2) |= UART0_C2_ILIE_MASK;    //����UART�����ж�
//        UART2_S1_REG(uartch_0) |= 0x10;
//    }
    NVIC_EnableIRQ(table_irq_uart[uartNo]);    //���жϿ�����IRQ�ж�
}

//======================================================================
//�������ƣ�uart_IdleIrq_clear
//����˵����uartNo:
//�������أ���
//======================================================================
void uart_IdleIrq_clear(uint_8 uartNo)
{
    UART0_MemMapPtr uartch_0=UART0_BASE_PTR; //��ȡUART0����ַ
//    UART_MemMapPtr uartch_1_2 = UART_ARR[uartNo-1]; //��ȡUART1����2����ַ
    //�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
    if(0 == uartNo)
    {
    	//������߱�־
    	UART0_S1_REG(UART0_BASE_PTR) |= 0x10;
    }
    else
    {
    	//Uart1\2
    }
    //
}

//======================================================================
//�������ƣ�dma_enable
//����˵����dmaNo:
//�������أ���
//======================================================================
 void dma_enable(uint_8 UART_DMA)
{
	uint_8 UART,chSend,chRe; //����ģ���ͨ��
	//����UART_DMA
	if(UART_DMA==0)
	{
		UART=0;//����0
		chSend=0;  //DMAͨ��0
		chRe = 1;  //DMAͨ��1
	}
//	DMA_DCR(chSend)|=DMA_DCR_EINT_MASK;
	DMA_DCR(chRe)|=DMA_DCR_EINT_MASK;
//	NVIC_EnableIRQ(DMA0_IRQn);    //���жϿ�����IRQ�ж�
	NVIC_EnableIRQ(DMA1_IRQn);    //���жϿ�����IRQ�ж�
}

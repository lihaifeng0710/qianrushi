//=====================================================================
//�ļ����ƣ�dma.c
//���ܸ�Ҫ��dma�ײ���������Դ�ļ�
//������λ�����ݴ�ѧǶ��ʽϵͳ���������о���(sumcu.suda.edu.cn)
//��    ����  2019-05-09  V2.0
//����оƬ��KL25��KL26��KL36
//=====================================================================
#include"dma.h"

//==========================================================================
//��������: dma_init
//��������: ��
//����˵��:  ch ��DMAͨ���ţ����ò����ɲμ�gec.h�ļ�
//���ܸ�Ҫ: ��ʼ��DMA����
//==========================================================================
void dma_init(uint8_t ch)
{

	//����DMA��DMAMUXģ��ʱ����
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	DMAMUX0_CHCFG(ch) = 0x00;
	//��ͨ���ж�������־
	if((DMA_DSR_BCR(ch)&DMA_DSR_BCR_DONE_MASK)==DMA_DSR_BCR_DONE_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_BES_MASK)==DMA_DSR_BCR_BES_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_BED_MASK)==DMA_DSR_BCR_BED_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_CE_MASK)==DMA_DSR_BCR_CE_MASK)
		DMA_DSR_BCR(ch)|=DMA_DSR_BCR_DONE_MASK;
	//���DMA���ƼĴ���
	DMA_DCR(ch)=0x00;
	DMA_DCR(ch) |= (DMA_DCR_SSIZE(1)		//����Դ��ַ���ݳ���Ϊ8λ
				| DMA_DCR_DSIZE(1)		//Ŀ�ĵ�ַ���ݳ���Ϊ8λ
				| DMA_DCR_D_REQ_MASK	//BCR��0ʱ�����������
				| DMA_DCR_DINC_MASK		//Ŀ�ĵ�ַ��������
				| DMA_DCR_CS_MASK		//ÿ�����󶼻����һ�ζ�д����
				| DMA_DCR_ERQ_MASK		//������������
				//| DMA_DCR_EINT_MASK
				| DMA_DCR_EADREQ_MASK	//�����첽����
	);
	//DMAͨ��ʹ��
	DMAMUX0_CHCFG(ch)|=(DMAMUX_CHCFG_ENBL_MASK);
}

//==========================================================================
//��������: dma_read
//��������: ��
//����˵��:  SrcAddress Դ��ַ
//         DstAddress��Ŀ���ַ
//         DataLength��DMA��������ݳ���
//���ܸ�Ҫ:  ʹ��DMAͨ�����д��ڷ��ͣ����ں�UART��
//==========================================================================
void dma_read(uint8_t SrcAddress, uint8_t DstAddress, uint8_t DataLength)
{
	DMA_SAR0 = SrcAddress;
	DMA_DSR_BCR0 = DMA_DSR_BCR_BCR(DataLength);
	DMA_DAR0 = DstAddress;


}

//======================================================================
//�������ƣ�dma_clear
//����˵����ch:
//�������أ���ͨ���ж�������־
//======================================================================
void dma_clear(uint8_t ch)
{
	if((DMA_DSR_BCR(ch)&DMA_DSR_BCR_DONE_MASK)==DMA_DSR_BCR_DONE_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_BES_MASK)==DMA_DSR_BCR_BES_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_BED_MASK)==DMA_DSR_BCR_BED_MASK||
			(DMA_DSR_BCR(ch)&DMA_DSR_BCR_CE_MASK)==DMA_DSR_BCR_CE_MASK)
		DMA_DSR_BCR(ch)|=DMA_DSR_BCR_DONE_MASK;

}


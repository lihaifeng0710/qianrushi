//============================================================================
//�ļ����ƣ�dac.c
//���ܸ�Ҫ��KL25 DAC�ײ����������ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2013-04-7   V1.0    
//============================================================================

#include "dac.h"  //����DAC��������ͷ�ļ�   


//================================�ڲ�����======================================
//============================================================================
//�������ƣ�dac_set_buffer
//�������أ����õĻ�������Сֵ
//����˵����dacx_base_ptr��DACx��ָ��      
//       dacindex�������ţ�0,1
//       buffval������ֵ:0~4095
//���ܸ�Ҫ������DACx������
//============================================================================ 
int dac_set_buffer( DAC_MemMapPtr dacx_base_ptr, uint_8 dacindex, int buffval);


//============================================================================
//�������ƣ�dac_init
//�������أ���
//����˵����RefVoltage���ο���ѹѡ�� 0=VREFH��1=VDDA 
//���ܸ�Ҫ����ʼ��DACģ���趨
//============================================================================
void dac_init(uint_8 RefVoltage)
{
    SIM_SCGC6 |=SIM_SCGC6_DAC0_MASK;   //ʹ��DAC0ʱ��
    
    //����DAC0_C0�Ĵ���
    if( 1== RefVoltage)    
    	DAC0_C0 |=  DAC_C0_DACRFS_MASK;   //ѡ��VDDA�ο���ѹ3.3V 
    else if( 0 == RefVoltage)    
    	DAC0_C0 &= ~DAC_C0_DACRFS_MASK;   //ѡ��VREFH�ο���ѹ3.3V      

    DAC0_C0 |= DAC_C0_DACTRGSEL_MASK;     //�������
    //���������Ч���߹���ģʽ���������õ��жϽ�ֹ,�������ö��жϽ�ֹ��
    DAC0_C0 &= ~( DAC_C0_DACSWTRG_MASK | DAC_C0_LPEN_MASK | DAC_C0_DACBBIEN_MASK | DAC_C0_DACBTIEN_MASK);  
    
   //����DAC0_C1�Ĵ���	  
   //DMA���� ,��������ģʽ
    DAC0_C1 &= ~( DAC_C1_DMAEN_MASK | DAC_C1_DACBFEN_MASK | DAC_C1_DACBFMD_MASK );                               
    //ʹ��DAC0ģ�� 
    DAC0_C0 |= DAC_C0_DACEN_MASK;      
}
    
//============================================================================
//�������ƣ�dac_convert
//����˵����data: ������ ��Χ��0~4095��
//���ܸ�Ҫ��ִ��DACת��
//============================================================================   
void dac_convert(uint_16 data)
{
    dac_set_buffer(DAC0_BASE_PTR, 0, data);
}

//================================�ڲ�����======================================
//============================================================================
//�������ƣ�dac_set_buffer
//�������أ����õĻ�������Сֵ
//����˵����dacx_base_ptr��DACx��ָ��      
//       dacindex�������ţ�0,1
//       buffval������ֵ:0~4095
//���ܸ�Ҫ������DACx������
//============================================================================ 
int dac_set_buffer( DAC_MemMapPtr dacx_base_ptr, uint_8 dacindex, int buffval)
{
    int temp = 0; 
    //���û��������ֽ�
    DAC_DATL_REG(dacx_base_ptr, dacindex)  =   (buffval&0x0ff); 
    //���û��������ֽ�
    DAC_DATH_REG(dacx_base_ptr, dacindex)  =   (buffval&0xf00) >>8;                                
    temp =( DAC_DATL_REG(dacx_base_ptr, dacindex)|
    		( DAC_DATH_REG(dacx_base_ptr, dacindex)<<8));   
    return temp ;
}
 

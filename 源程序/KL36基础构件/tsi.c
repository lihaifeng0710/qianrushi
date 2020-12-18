//=====================================================================
//�ļ����ƣ�tsi.c
//���ܸ�Ҫ��tsi�ײ���������Դ�ļ�
//������λ�����ݴ�ѧǶ��ʽϵͳ���������о���(sumcu.suda.edu.cn)
//��    ����  2019-05-09  V2.0
//����оƬ��KL25��KL26��KL36
//=====================================================================
#include "tsi.h"

//=====================================================================
//�������ƣ�tsi_init                                                  
//���ܸ�Ҫ����ʼ��TSIģ�� ,
//����˵����chnlIDs:TSIģ����ʹ�õ�ͨ���ţ������ò����ɲμ�gec.h�ļ�
//     threshold:��ֵ
//�������أ� ��
//=====================================================================
void tsi_init(uint8_t chnlID,uint32_t threshold)
{
    //����TSIʱ��
    BSET(SIM_SCGC5_TSI_SHIFT,SIM_SCGC5);
    BSET(SIM_SCGC5_PORTA_SHIFT,SIM_SCGC5);

    //ͨ���ţ�0=PTB0�ţ�1=PTA0�ţ�2=PTA1�ţ�3=PTA2�ţ�4=PTA3�ţ�5=PTA4�ţ�
    //      6=PTB1�ţ�7=PTB2�ţ�8=PTB3�ţ�9=PTB16�ţ�10=PTB17�ţ�11=PTB18�ţ�
    //      12=PTB19�ţ�13=PTC0�ţ�14=PTC1�ţ�15=PTC2��
    //(����1��2��3��4��5�����������ŵ�Ĭ�Ϲ��ܼ�ΪTSIͨ��)
    switch(chnlID)   //chnlID��ȡֵΪ0~15
    {
    case 0:
    	PORTB_PCR0 &= ~PORT_PCR_MUX_MASK; //ͨ��0ʹ��
        break;
    case 1:
    	PORTA_PCR0 &= ~PORT_PCR_MUX_MASK; //ͨ��1ʹ��
        break;
    case 2:
        PORTA_PCR1 &= ~PORT_PCR_MUX_MASK; //ͨ��2ʹ��
        break;
    case 3:
        PORTA_PCR2 &= ~PORT_PCR_MUX_MASK; //ͨ��3ʹ��
        break;
    case 4:
        PORTA_PCR3 &= ~PORT_PCR_MUX_MASK; //ͨ��4ʹ��
        break;
    case 5:
        PORTA_PCR4 &= ~PORT_PCR_MUX_MASK; //ͨ��5ʹ��
        break;
    case 6:
    	PORTB_PCR1 &= ~PORT_PCR_MUX_MASK; //ͨ��6ʹ��
        break;
    case 7:
    	PORTB_PCR2 &= ~PORT_PCR_MUX_MASK; //ͨ��7ʹ��
        break;
    case 8:
        PORTB_PCR3 &= ~PORT_PCR_MUX_MASK; //ͨ��8ʹ��
        break;
    case 9:
        PORTB_PCR16 &= ~PORT_PCR_MUX_MASK; //ͨ��9ʹ��
        break;
    case 10:
        PORTB_PCR17 &= ~PORT_PCR_MUX_MASK; //ͨ��10ʹ��
        break;
    case 11:
        PORTB_PCR18 &= ~PORT_PCR_MUX_MASK; //ͨ��11ʹ��
        break;
    case 12:
    	PORTB_PCR19 &= ~PORT_PCR_MUX_MASK; //ͨ��12ʹ��
        break;
    case 13:
    	PORTC_PCR0 &= ~PORT_PCR_MUX_MASK; //ͨ��13ʹ��
        break;
    case 14:
        PORTC_PCR1 &= ~PORT_PCR_MUX_MASK; //ͨ��14ʹ��
        break;
    case 15:
        PORTC_PCR2 &= ~PORT_PCR_MUX_MASK; //ͨ��15ʹ��
        break;
    }

    BSET(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);//TSI�ж�ʹ��
    
    BSET(TSI_GENCS_STPE_SHIFT,TSI0_GENCS);//TSI�ڵ͹���ģʽ������
    
    //�Ĵ���TSI0_GENCS��REFCHRGλ��λ4�����ο�������ŵ����Ϊ8uA
    TSI0_GENCS |= (TSI_GENCS_REFCHRG(4)
        | TSI_GENCS_DVOLT(0)//�Ĵ���TSI0_GENCS��DVOLTλΪ00��ʾ��ֵ��ѹ
                    //Vp=1.33V����ֵ��ѹVm=0.30V ����ֵ��ֵ֮��Dv=1.03V
            | TSI_GENCS_EXTCHRG(6)//�缫������ŵ����ֵ32uA
        | TSI_GENCS_PS(2)     //�缫����4��Ƶ
        | TSI_GENCS_NSCN(11)  //ÿ���缫ɨ��4��
    );
    
//  BCLR(TSI_GENCS_ESOR_SHIFT,TSI0_GENCS);  //���ó�����ֵ�����ж�
    BSET(TSI_GENCS_ESOR_SHIFT,TSI0_GENCS);  //��
  //BCLR(TSI_GENCS_STM_SHIFT,TSI0_GENCS); //�������ɨ��
    BSET(TSI_GENCS_STM_SHIFT,TSI0_GENCS);
    
    //��Խֵ��־λ��ɨ�����λ
    //������ֵ��λ��EOSFΪ1���ó�ɨ�����״̬
    BSET(TSI_GENCS_OUTRGF_SHIFT,TSI0_GENCS);
    BSET(TSI_GENCS_EOSF_SHIFT,TSI0_GENCS);
    
    //ѡ��ͨ��
    TSI0_DATA &= ~TSI_DATA_TSICH_MASK;
    TSI0_DATA |= (TSI_DATA_TSICH(chnlID)); 
    //TSIģ��ʹ��
    BSET(TSI_GENCS_TSIEN_SHIFT,TSI0_GENCS);
    //������ֵ
    TSI0_TSHD = threshold;
}


//=====================================================================
//�������ƣ�tsi_get_value
//���ܸ�Ҫ����ȡTSIͨ���ļ���ֵ                                                  
//����˵������                               
//�������أ���ȡTSIͨ���ļ���ֵ                                                                
//=====================================================================
uint16_t tsi_get_value(void)
{

    uint16_t value;      
    BCLR(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);          //��TSI�ж�  
    BSET(TSI_DATA_SWTS_SHIFT,TSI0_DATA);
    while(!(TSI0_GENCS & TSI_GENCS_EOSF_MASK));       //�ȴ�ɨ�����   
    BSET(TSI_GENCS_EOSF_SHIFT,TSI0_GENCS);            //д1��0ɨ�������־λ
    value =  (TSI0_DATA & TSI_DATA_TSICNT_MASK);      //��ȡ�����Ĵ����е�ֵ
    BSET(TSI_GENCS_OUTRGF_SHIFT,TSI0_GENCS);          //д1��0��ֵ��־λ
    BSET(TSI_GENCS_EOSF_SHIFT,TSI0_GENCS);               //��ɨ�������־λ
    BSET(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);          //��TSI�ж�   
    return value; 
}


//=====================================================================
//�������ƣ�tsi_set_threshold1                                                  
//���ܸ�Ҫ���趨ָ��ͨ������ֵ                                                  
//����˵����     low:   �趨��ֵ����   ��     ȡֵ��ΧΪ0~65535                                 
//         high:  �趨��ֵ����   ��    ȡֵ��ΧΪ0~65535
//�������أ� ��                                                             
//=====================================================================
void tsi_set_threshold(uint16_t low, uint16_t high)
{
    uint32_t thresholdValue;
    //��16λΪ���ޣ���16λΪ����
    thresholdValue = high;
    thresholdValue = (thresholdValue<<16)|low;
    TSI0_TSHD = thresholdValue;
}


//=====================================================================
//�������ƣ�tsi_enable_re_int
//���ܸ�Ҫ����TSI�ж�,�ر��������ɨ��,���жϿ�����IRQ�ж�
//����˵������
//�������أ���
//=====================================================================
void tsi_enable_re_int(void)
{
    //��TSI�ж�,�ر��������ɨ��
    BSET(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);
    BSET(TSI_GENCS_STM_SHIFT,TSI0_GENCS);
    NVIC_EnableIRQ((IRQn_Type)26); //���жϿ�����IRQ�ж�
}

//=====================================================================
//�������ƣ�tsi_disable_re_int
//����˵������
//�������أ���
//���ܸ�Ҫ����TSI�ж�,���������ɨ��,���жϿ�����IRQ�ж�
//=====================================================================
void tsi_disable_re_int(void)
{
    //��TSI�ж�,���������ɨ��
    BCLR(TSI_GENCS_TSIIEN_SHIFT,TSI0_GENCS);
    BCLR(TSI_GENCS_STM_SHIFT,TSI0_GENCS);
    //��ֹ�жϿ�����IRQ�ж�
    NVIC_DisableIRQ((IRQn_Type)26);
}

//=====================================================================
//�������ƣ�tsi_softsearch
//���ܸ�Ҫ������һ�����ɨ��
//����˵������
//�������أ���
//=====================================================================
void tsi_softsearch(void)
{
    BCLR(TSI_GENCS_STM_SHIFT,TSI0_GENCS);
    //TSI0_GENCS &= ~TSI_GENCS_STM_MASK;    //�����������
    BSET(TSI_DATA_SWTS_SHIFT,TSI0_DATA);
    //TSI0_DATA |= TSI_DATA_SWTS_MASK;     //��ʼһ�����ɨ��
}


//=====================================================================
//�������ƣ�tsi_search
//���ܸ�Ҫ������һ��tsiɨ��
//����˵������
//�������أ���
//=====================================================================
void tsi_search(void)
{
	BSET(TSI_GENCS_TSIEN_SHIFT,TSI0_GENCS);   //����һ��TSIɨ��
}

//=====================================================================
//�������ƣ�tsi_get_int
//���ܸ�Ҫ����ȡtsi�жϱ�־
//����˵������
//�������أ�1=���жϲ�����0=û���жϲ���
//=====================================================================
uint8_t tsi_get_int(void)
{
	if(TSI0_GENCS & TSI_GENCS_OUTRGF_MASK)
		return 1;
	else
		return 0;
}

//=====================================================================
//�������ƣ�tsi_clear_int
//���ܸ�Ҫ�����tsi�жϱ�־
//����˵������
//�������أ���
//=====================================================================
void tsi_clear_int(void)
{
	TSI0_GENCS |=  TSI_GENCS_OUTRGF_MASK;     //д1����ó�ֵ�ж�λ
	BCLR(TSI_GENCS_TSIEN_SHIFT,TSI0_GENCS);   //���TSI�ж�
}

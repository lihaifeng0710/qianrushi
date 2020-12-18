
#include "gec.h"

void  BIOS_API_Init();
void Int_Handler_init();

void  BIOS_API_Init()  
{
     bios_fun_point=svc1_init();  //��ȡBIOS��API�ӿڱ��׵�ַ
     Int_Handler_init();          //�û��жϴ����������ʼ��
}
//======================================================================
//�������ƣ�Int_Handler_init
//�������أ���
//����˵������
//���ܸ�Ҫ���û��жϴ����������ʼ������Ӧ���жϴ�������̴���isr.c�ļ���
//======================================================================
void Int_Handler_init()    //�û��жϴ����������ʼ��
{
	setVector(PORTA_IRQn,(uint_32)&GPIOA_Handler);
	setVector(PORTC_PORTD_IRQn,(uint_32)&GPIOB_Handler);
	setVector(UART0_IRQn,(uint_32)&UARTA_Handler);
	setVector(LPTMR0_IRQn,(uint_32)&TIMERA_Handler);
	setVector(TPM1_IRQn,(uint_32)&TIMERB_Handler);
	setVector(SPI0_IRQn,(uint_32)&SPIA_Handler);
	setVector(SPI1_IRQn,(uint_32)&SPIB_Handler);
	setVector(I2C0_IRQn,(uint_32)&I2CA_Handler);
	setVector(I2C1_IRQn,(uint_32)&I2CB_Handler);
	setVector(TSI0_IRQn,(uint_32)&TSI_Handler);
	setVector(TPM0_IRQn,(uint_32)&INCAP_Handler);

}

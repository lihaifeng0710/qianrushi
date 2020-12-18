
#include "gec.h"

void  BIOS_API_Init();
void Int_Handler_init();

void  BIOS_API_Init()  
{
     bios_fun_point=svc1_init();  //获取BIOS中API接口表首地址
     Int_Handler_init();          //用户中断处理程序名初始化
}
//======================================================================
//函数名称：Int_Handler_init
//函数返回：无
//参数说明：无
//功能概要：用户中断处理程序名初始化，对应的中断处理程序编程处在isr.c文件中
//======================================================================
void Int_Handler_init()    //用户中断处理程序名初始化
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

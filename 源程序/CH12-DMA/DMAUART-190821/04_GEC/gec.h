//======================================================================
//�ļ����ƣ�gec.h��GECоƬ����ͷ�ļ���
//������λ���մ�arm��������(sumcu.suda.edu.cn)
//���¼�¼��2018.12��1.0��2019.2��A.12
//��Ҫ˵�������ļ�ΪGEC���ŵĹ�������
//======================================================================

#ifndef GEC_H    //��ֹ�ظ����壨��ʼ��
#define GEC_H

#include "gpio.h"
#include "uart.h"
#include "flash.h"
#include "mcu.h"

void  BIOS_API_Init();
//======================================================================
//�������ƣ�Int_Handler_init
//�������أ���
//����˵������
//���ܸ�Ҫ�������û������жϵ�ISR��������ISRִ�д����isr.c�ж���
//======================================================================
void Int_Handler_init();

//�����̶�����жϷ�������----------------------------------------------------
void  __attribute__((weak)) GPIOA_Handler(void);   //GPIOA�ж�
void  __attribute__((weak)) GPIOB_Handler(void);   //GPIOB�ж�
void  __attribute__((weak)) UARTA_Handler(void);   //UART0�����ж�
void  __attribute__((weak)) I2CA_Handler(void);    //I2C0�����ж�
void  __attribute__((weak)) I2CB_Handler(void);    //I2C1�����ж�
void  __attribute__((weak)) SPIA_Handler(void);    //SPI0�����ж�
void  __attribute__((weak)) SPIB_Handler(void);    //SPI1�����ж�
void  __attribute__((weak)) INCAP_Handler(void);   //TPM0��ʱ��
void  __attribute__((weak)) TIMERA_Handler(void);  //LPTMR0
void  __attribute__((weak)) TIMERB_Handler(void);  //TPM1��ʱ��
void  __attribute__((weak)) TSI_Handler(void);     //TSI�����ж�
//----------------------------------------------------------------------

//===========================================================
//��0��GEC���������ڲ�MCU��KL36�����Ŷ�Ӧ��ϵ
//�й�����
#define  GND          0XFFFF    //��
#define  P5V          0XFFFE    //5V��Դ
#define  P3V3         0XFFFD    //3V3��Դ
#define  GNSS_ANT     0XFFFC    //����/GPS������������
#define  MAIN_ANT     0XFFFB    //��ͨ��ģ����������
#define  DBG_TXD      0XFFFA    //��ͨ��ģ����Դ��������������
#define  DBG_RXD      0XFFF9    //��ͨ��ģ����Դ���������������
#define  SWD_DIO      0XFFF8    //SWD����������������
#define  SWD_CLK      0XFFF7    //SWDʱ���ź���������
//�˿ںŵ�ַƫ�����궨��
#define PTA_NUM     (0<<8)
#define PTB_NUM     (1<<8)
#define PTC_NUM     (2<<8)
#define PTD_NUM     (3<<8)
#define PTE_NUM     (4<<8)
//GEC���Ŷ���
#define  GEC_1     GND
#define  GEC_2     PTE_NUM|25
#define  GEC_3     PTE_NUM|31
#define  GEC_4     PTE_NUM|30
#define  GEC_5     PTE_NUM|24
#define  GEC_6     PTE_NUM|29
#define  GEC_7     PTE_NUM|23
#define  GEC_8     PTE_NUM|21     //UART0_RX
#define  GEC_9     GND
#define  GEC_10    PTE_NUM|20     //UART0_TX

#define  GEC_11    PTE_NUM|19
#define  GEC_12    PTE_NUM|18
#define  GEC_13    PTE_NUM|17     //UART2_RX
#define  GEC_14    PTE_NUM|16     //UART2_TX
#define  GEC_15    PTD_NUM|6
#define  GEC_16    PTD_NUM|7
#define  GEC_17    GND
#define  GEC_18    GNSS_ANT
#define  GEC_19    GND
#define  GEC_20    GND

#define  GEC_21    PTD_NUM|5
#define  GEC_22    PTD_NUM|4
#define  GEC_23    PTD_NUM|3
#define  GEC_24    PTD_NUM|2
#define  GEC_25    PTD_NUM|1
#define  GEC_26    GND
#define  GEC_27    PTD_NUM|0
#define  GEC_28    PTC_NUM|7
#define  GEC_29    PTC_NUM|6
#define  GEC_30    PTC_NUM|5

#define  GEC_31    PTC_NUM|4
#define  GEC_32    GND
#define  GEC_33    MAIN_ANT
#define  GEC_34    GND
#define  GEC_35    GND
#define  GEC_36    P3V3
#define  GEC_37    PTC_NUM|3
#define  GEC_38    PTC_NUM|2   //GPIOC_13/I2CB_SDA
#define  GEC_39    PTC_NUM|1   //GPIOC_14/I2CB_SCL
#define  GEC_40    PTC_NUM|0

#define  GEC_41    PTB_NUM|19
#define  GEC_42    PTB_NUM|18
#define  GEC_43    GND
#define  GEC_44    PTB_NUM|17
#define  GEC_45    PTB_NUM|16
#define  GEC_46    PTB_NUM|3   //GPIOB_14/I2CA��SDA����
#define  GEC_47    PTB_NUM|2   //GPIOB_15/I2CA��SCL����
#define  GEC_48    PTB_NUM|1
#define  GEC_49    PTB_NUM|0
#define  GEC_50    DBG_TXD

#define  GEC_51    GND
#define  GEC_52    GND
#define  GEC_53    DBG_RXD
#define  GEC_54    PTA_NUM|13
#define  GEC_55    PTA_NUM|12
#define  GEC_56    PTA_NUM|5
#define  GEC_57    PTA_NUM|4   //NMI��������
#define  GEC_58    SWD_DIO
#define  GEC_59    PTA_NUM|2
#define  GEC_60    GND

#define  GEC_61    PTA_NUM|1
#define  GEC_62    SWD_CLK
#define  GEC_63    GND
#define  GEC_64    P3V3
#define  GEC_65    GND
#define  GEC_66    P5V
#define  GEC_67    P5V
#define  GEC_68    GND

//��1��GPIO����
//GPIOAģ�飨�����жϹ��ܣ���ӦKL36��A��-WYH-190213�˶�
#define  GPIOA_0    GEC_54   //PTA_NUM|13
#define  GPIOA_1    GEC_55   //PTA_NUM|12
#define  GPIOA_2    GEC_56   //PTA_NUM|5
#define  GPIOA_3    GEC_59   //PTA_NUM|2
#define  GPIOA_4    GEC_61   //PTA_NUM|1
//GPIOBģ�飨�����жϹ��ܣ�-��ӦKL36��C�ڡ�D��WYH-190213�˶�
#define  GPIOB_0    GEC_15   //PTD_NUM|6
#define  GPIOB_1    GEC_16   //PTD_NUM|7

#define  GPIOB_2    GEC_21   //PTD_NUM|5
#define  GPIOB_3    GEC_22   //PTD_NUM|4
#define  GPIOB_4    GEC_23   //PTD_NUM|3
#define  GPIOB_5    GEC_24   //PTD_NUM|2
#define  GPIOB_6    GEC_25   //PTD_NUM|1

#define  GPIOB_7    GEC_27   //PTD_NUM|0
#define  GPIOB_8    GEC_28   //PTC_NUM|7
#define  GPIOB_9    GEC_29   //PTC_NUM|6
#define  GPIOB_10   GEC_30   //PTC_NUM|5
#define  GPIOB_11   GEC_31   //PTC_NUM|4

#define  GPIOB_12   GEC_37   //PTC_NUM|3
#define  GPIOB_13   GEC_38   //PTC_NUM|2
#define  GPIOB_14   GEC_39   //PTC_NUM|1
#define  GPIOB_15   GEC_40   //PTC_NUM|0

//GPIOCģ�飨���жϹ��ܣ�-��ӦKL36��E�ڡ�B��WYH-190213�˶�
#define  GPIOC_0    GEC_2   //PTE_NUM|25
#define  GPIOC_1    GEC_3   //PTE_NUM|31
#define  GPIOC_2    GEC_4
#define  GPIOC_3    GEC_5
#define  GPIOC_4    GEC_6
#define  GPIOC_5    GEC_7
#define  GPIOC_6    GEC_11
#define  GPIOC_7    GEC_12
#define  GPIOC_8    GEC_41
#define  GPIOC_9    GEC_42
#define  GPIOC_10   GEC_44
#define  GPIOC_11   GEC_45
#define  GPIOC_12   GEC_46
#define  GPIOC_13   GEC_47
#define  GPIOC_14   GEC_48
#define  GPIOC_15   GEC_49


//��2��UART����
//UARTģ�鶨��
#define UARTA  0  //TX���ţ� GEC_10��RX���ţ� GEC_8
#define UARTB  1  //δ����������ʹ�ã�
#define UARTC  2  //TX���ţ� GEC_14��RX���ţ� GEC_13

//��3��ADC���Ŷ���-WYH
//ͨ��ѡ��
#define MUXSEL_A     0    //ѡ��˿ڵ�Aͨ��
#define MUXSEL_B     1    //ѡ��˿ڵ�Bͨ��
//ADCͨ������              ͨ����|ͨ����<<8
//�������Ŷ���
//ADC_PIN1��ADC_PIN2���Ժϳ�һ���������
#define ADC_PIN0  (0|MUXSEL_A<<8)     //�������ţ�GEC_10��PTE_NUM|20����ADC0_DP0/SE0
#define ADC_PIN1  (4|MUXSEL_A<<8)     //�������ţ�GEC_8��PTE_NUM|21���� ADC0_DM0/SE4a
//ADC_PIN3��ADC_PIN4���Ժϳ�һ���������
#define ADC_PIN2  (1|MUXSEL_A<<8)     //�������ţ�GEC_45��PTE_NUM|16����ADC0_DP1/SE1
#define ADC_PIN3  (5|MUXSEL_A<<8)     //�������ţ�GEC_44��PTE_NUM|17����ADC0_DM1/SE5a
//ADC_PIN5��ADC_PIN6���Ժϳ�һ���������
#define ADC_PIN4  (2|MUXSEL_A<<8)     //�������ţ�GEC_12��PTE_NUM|18����ADC0_DP2/SE2
#define ADC_PIN5  (6|MUXSEL_A<<8)     //�������ţ�GEC_11��PTE_NUM|19����ADC0_DM2/SE6a
//����ֻ�ܵ�������
#define ADC_PIN6   (7|MUXSEL_A<<8)    //�������ţ�GEC_7��PTE_NUM|23����ADC0_DM3/SE7a
#define ADC_PIN7   (4|MUXSEL_B<<8)    //�������ţ�GEC_6��PTE_NUM|29����ADC0_SE4b
#define ADC_PIN8   (6|MUXSEL_B<<8)    //�������ţ�GEC_21��PTD_NUM|5����ADC0_SE6b
#define ADC_PIN9  (7|MUXSEL_B<<8)    //�������ţ�GEC_15��PTD_NUM|6����ADC0_SE7b
#define ADC_PIN10  (11|MUXSEL_A<<8)   //�������ţ�GEC_38��PTC_NUM|2����ADC0_SE11
#define ADC_PIN11  (14|MUXSEL_A<<8)   //�������ţ�GEC_40��PTC_NUM|0����ADC0_SE14
#define ADC_PIN12  (15|MUXSEL_A<<8)   //�������ţ�GEC_39��PTC_NUM|1����ADC0_SE15
#define ADC_PIN13  (13|MUXSEL_A<<8)   //�������ţ�GEC_46��PTB_NUM|3����ADC0_SE13
#define ADC_PIN14  (12|MUXSEL_A<<8)   //�������ţ�GEC_47��PTB_NUM|2����ADC0_SE12
#define ADC_PIN15  (9 |MUXSEL_A<<8)   //�������ţ�GEC_48��PTB_NUM|1����ADC0_SE9
#define ADC_PIN16  (8 |MUXSEL_A<<8)   //�������ţ�GEC_49��PTB_NUM|0����ADC0_SE8
#define ADC_PIN17  (26|MUXSEL_A<<8)   //оƬ�Դ��¶ȴ����� ����δ����


//��4��SPIģ������-WYH
//SS���ţ� GEC_31��PTC_NUM|4����SCK���ţ� GEC_30��PTC_NUM|5����
//MOSI���ţ� GEC_29��PTC_NUM|6����MISO���ţ� GEC_28��PTC_NUM|7��
#define SPIA  0
//SS���ţ� GEC_22��PTD_NUM|4����SCK���ţ� GEC_21��PTD_NUM|5��
//MOSI���ţ� GEC_15��PTD_NUM|6����MISO���ţ� GEC_16(PTD_NUM|7)
#define SPIB  1

//��5��I2Cģ������-WYH
//I2Cģ�鶨��
#define I2CA  0   //SDA���ţ�GEC_46��PTB_NUM|3����SCL���ţ� GEC_47��PTB_NUM|2��
#define I2CB  1   //SDA���ţ�GEC_38��PTC_NUM|2����SCL���ţ� GEC_39��PTC_NUM|1��

//TPM0����PWM��INCAP��OUTCMP
//��6���������PWM����-WYH
#define  PWM_PIN0  GEC_39  //GEC_39��PTC_NUM|1��
#define  PWM_PIN1  GEC_38  //GEC_38��PTC_NUM|2��
#define  PWM_PIN2  GEC_37  //GEC_37��PTC_NUM|3��
#define  PWM_PIN3  GEC_23  //GEC_23��PTD_NUM|3��
#define  PWM_PIN4  GEC_22  //GEC_22��PTD_NUM|4��
#define  PWM_PIN5  GEC_21  //GEC_21��PTD_NUM|5��
//��7�����벶׽INCAP����-WYH
#define  INCAP_PIN0  GEC_39  //GEC_39��PTC_NUM|1��
#define  INCAP_PIN1  GEC_38  //GEC_38��PTC_NUM|2��
#define  INCAP_PIN2  GEC_37  //GEC_37��PTC_NUM|3��
#define  INCAP_PIN3  GEC_23  //GEC_23��PTD_NUM|3��
#define  INCAP_PIN4  GEC_22  //GEC_22��PTD_NUM|4��
#define  INCAP_PIN5  GEC_21  //GEC_21��PTD_NUM|5��
//��8������Ƚ�OUTCMP����-WYH
#define  OUTCMP_PIN0  GEC_39  //GEC_39��PTC_NUM|1��
#define  OUTCMP_PIN1  GEC_38  //GEC_38��PTC_NUM|2��
#define  OUTCMP_PIN2  GEC_37  //GEC_37��PTC_NUM|3��
#define  OUTCMP_PIN3  GEC_23  //GEC_23��PTD_NUM|3��
#define  OUTCMP_PIN4  GEC_22  //GEC_22��PTD_NUM|4��
#define  OUTCMP_PIN5  GEC_21  //GEC_21��PTD_NUM|5��

//��9��TSIͨ������������˵��
#define TSI_PIN0   13   //�������ţ�GEC_40��PTC_NUM|0��
#define TSI_PIN1   12   //�������ţ�GEC_41��PTB_NUM|19��
#define TSI_PIN2   11   //�������ţ�GEC_42��PTB_NUM|18��
#define TSI_PIN3   10   //�������ţ�GEC_44��PTB_NUM|17��
#define TSI_PIN4    9   //�������ţ�GEC_45��PTB_NUM|16��
#define TSI_PIN5    8   //�������ţ�GEC_46��PTB_NUM|3��
#define TSI_PIN6    7   //�������ţ�GEC_47��PTB_NUM|2��
#define TSI_PIN7    6   //�������ţ�GEC_48��PTB_NUM|1��
#define TSI_PIN8    0   //�������ţ�GEC_49��PTB_NUM|0��
#define TSI_PIN9    3   //�������ţ�GEC_59��PTA_NUM|2��
#define TSI_PIN10   2   //�������ţ�GEC_61��PTA_NUM|1��

//����Ӳ����Ӧ��ģ��
//��10����ʱ������
//timer
#define TIMERA  0   //LPTMR
//TPM
#define TIMERB  1   //TPM1


//��11��DMAͨ������
#define DMA_CH0  0  //ͨ��0  ��ӦUARTA
#define DMA_CH1  1  //ͨ��1  ��ӦUARTA
#define DMA_CH2  2  //ͨ��2  ��ӦUARTA
#define DMA_CH3  3  //ͨ��3  ��ӦUARTA


#endif  //��ֹ�ظ����壨��β��


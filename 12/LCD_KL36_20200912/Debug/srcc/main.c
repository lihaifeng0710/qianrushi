//======================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ��SD-ARM��sumcu.suda.edu.cn��
//�汾���£�
//�����������������̵�<01_Doc>�ļ�����Readme.txt�ļ�
//======================================================================
#define GLOBLE_VAR
#include "includes.h"      //������ͷ�ļ�

//----------------------------------------------------------------------
//����ʹ�õ����ڲ�����
//main.cʹ�õ��ڲ�����������
float TempRegression(uint16_t AD);
//----------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̣��μ���壩
int main(void)
{
    //��1��======�������֣���ͷ��==========================================
    //��1.1������main����ʹ�õľֲ�����
    uint32_t mMainLoopCount;  //��ѭ����������
    uint8_t  mFlag;           //�Ƶ�״̬��־
    uint8_t i;
    float temperature;
    uint16_t light;
    uint16_t mcu_temp_AD;
    float mcu_temp;
    uint16_t bat_AD;
    float bat_V;
    char temp[6];
    uint8_t mag;
    uint16_t AD_CAL1;
	uint16_t AD_CAL2;
    
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;
    wdog_feed();
    printf("����User��main...\n");
    
    //��1.3����������ʹ�õľֲ���������ֵ
    mMainLoopCount=0;    //��ѭ����������
    mFlag='R';           //�Ƶ�״̬��־
    //��1.4����ȫ�ֱ�������ֵ
    
    //��1.5���û�����ģ���ʼ��
    wdog_start(3);	  //�������Ź�
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);          //��ʼ����� 'R'
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);        //��ʼ���̵� 'G'
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);         //��ʼ������ 'B'
    gpio_init(PIN_MAG,GPIO_INPUT,1);     
    wdog_feed();
    printf("LCD��ʼ��...");
    LCD_Init();
    printf("�ɹ�\n");
    uart_init(UART_User,115200);
    adc_init(AD_LIGHT,0);
    adc_init(AD_TEMP,0);
    adc_init(AD_MCU_TEMP,0);
    wdog_feed();
//    adc_init(AD_BAT,0);

    //��1.6��ʹ��ģ���ж�
    uart_enable_re_int(UART_User);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;
    
    //��1.8������LCD�����еĺ���
    
    printf("���«��ʾ��LCD��Ļ����...");
    LCD_aotu(2,2,238,318,0);
    LCD_aotu(4,40,236,80,1);
    LCD_ShowString(72,20,RED,GRAY,(char *)"AHL-MCU-KL36");
    LCD_ShowString(68,52,RED,GRAY,(char *)"Hardware-Test");
  	wdog_feed();
    LCD_ShowString(8,88,BLACK,GRAY,(char *)"MCU_Tmp:");
    //LCD_ShowString(140,88,BLACK,GRAY,(char *)"BAT:      V");
    LCD_aotu(4,106,236,116,1);
    LCD_ShowString(8,120,BLACK,GRAY,(char *)"Round_Tmp:");
    LCD_aotu(4,138,236,148,1);
    LCD_ShowString(8,152,BLACK,GRAY,(char *)"Brightness:");
    LCD_aotu(4,170,236,180,1);
    LCD_ShowString(8,184,BLACK,GRAY,(char *)"Magnetism:");
    LCD_aotu(4,202,236,212,1);
    LCD_ShowString(8,216,BLACK,GRAY,(char *)"Tri-coloured light:");
    wdog_feed();                                         
    
    LCD_aotu(4,234,236,316,1);
    printf("���\n");
//     while(1){}
    //��1��======�������֣���β��==========================================

    //��2��======��ѭ�����֣���ͷ��========================================
    for(;;)   //for(;;)����ͷ��
    {
    	wdog_feed();
        //��2.1����ѭ����������+1
        mMainLoopCount++;
        //��2.2��δ�ﵽ��ѭ�������趨ֵ������ѭ��
        if (mMainLoopCount<=0x1fffff)  continue;
        //��2.3���ﵽ��ѭ�������趨ֵ��ִ��������䣬���еƵ���������
        //��2.3.1�����ѭ����������
        mMainLoopCount=0; 
        
        temperature = TempRegression(adc_read(AD_TEMP));
        mcu_temp_AD = adc_read(AD_MCU_TEMP);
//        bat_AD = adc_read(AD_BAT);
//        bat_V = (float)(bat_AD*66.0/4096.0);
        light = adc_read(AD_LIGHT);
        printf(" mcu_temp��%d--\n",mcu_temp_AD);
        mcu_temp = (float)(25.0-(mcu_temp_AD*0.05-719)/1.715);
//        mcu_temp = (float)(60+(70*((float)(mcu_temp_AD) - AD_CAL1))/(AD_CAL2 - AD_CAL1));
//        
        mag = gpio_get(PIN_MAG);
        LCD_ShowString(136,120,BLACK,GRAY,"        ");
        LCD_ShowString(136,152,BLACK,GRAY,"        ");
        LCD_ShowString(84,88,BLACK,GRAY,"     ");
        LCD_ShowString(180,88,BLACK,GRAY,"    ");
        wdog_feed();
        LCD_ShowString(136,120,GREEN,GRAY,(char *)NumToStr_float(temperature,1,temp));
        LCD_ShowString(84,88,GREEN,GRAY,(char *)NumToStr_float(mcu_temp,1,temp));
//        LCD_ShowString(180,88,GREEN,GRAY,(char *)NumToStr_float(bat_V,1,temp));
        LCD_ShowString(136,152,GREEN,GRAY,(char *)NumToStr_float(light/10.0,1,temp));
        if(mag == 1)  LCD_ShowString(136,184,RED,GRAY,"N");
        else LCD_ShowString(136,184,GREEN,GRAY,"Y");
        wdog_feed();
        printf(" ������%d--\n",mag);
        printf(" �����¶ȣ�%d--\n",(int)temperature); 
        printf(" ���գ�%d--\n",light);
        printf(" MCU�¶ȣ�%4.1lf--\n",mcu_temp);
//        printf(" bat_V��%4.1lf V--\n",bat_V);
        
    }  //for(;;)��β
    //��2��======��ѭ�����֣���β��========================================
}   //main��������β��


//======����Ϊ���������õ��Ӻ���===========================================
float TempRegression(uint16_t tmpAD)
{
    float v1,v2,S,T;
    v1 = ((float)tmpAD*3300)/65535;   //ADֵ��Ϊ�������ѹ(mV)
    v2=3300 - v1;                    //��ѹ�������˵�ѹ(mV)
    S = v1/v2;                       //��ѹ��
    T = (1/(log(S)/3950.0 + (1/(273.15 + 25)))) - 273.15 + 0.5;
    return T;
}



//=========================================================================
/*
֪ʶҪ�أ�
��1��main.c��һ��ģ�壬���ļ����д�������漰�����Ӳ���ͻ�����ͨ�����ù���
ʵ�ֶ�Ӳ���ĸ�Ԥ��
��2�����ļ��жԺ�GLOBLE_VAR�����˶��壬�����ڰ���"includes.h"ͷ�ļ�ʱ���ᶨ
��ȫ�ֱ������������ļ��а���"includes.h"ͷ�ļ�ʱ��
����ʱ���Զ�����extern
*/



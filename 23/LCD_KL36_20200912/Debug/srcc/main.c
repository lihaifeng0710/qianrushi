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
void Test_Digitaltube();
void main_Dly_ms(uint32_t ms);
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
        if (mMainLoopCount<=20)  continue;
        //��2.3���ﵽ��ѭ�������趨ֵ��ִ��������䣬���еƵ���������
        //��2.3.1�����ѭ����������
        mMainLoopCount=0; 
        wdog_feed();
	
        wdog_feed();
    
        wdog_feed();



     
        

        uint8_t mString[30];
        uint8_t xyzData[6];         //x��y��z����ǣ���ռ�����ֽ�
        uint16_t xdata,ydata,zdata; //x�����
        uint8_t checkdata;          //ADLX345����֤����,��ȷ����Ϊ0xe5
        adlx345_init(i2cAcceleration,0x0B,0x08,0x08,0x80,0x00,0x00,0x05);//��ʼ��ADLX345(J2�˿�) 
        adlx345_read1(0x00,&checkdata);    //��ȡadxl345У������
        adlx345_init(0,0x0B,0x08,0x08,0x80,0x00,0x00,0x05);//��ʼ��ADLX345(J2�˿�)
        adlx345_read1(0x00,&checkdata);    //��ȡadxl345У������
        main_Dly_ms(5);
        adlx345_readN(0x32,xyzData,6);		   //����Ǵ�������ֵ
        
        xdata = (xyzData[1]<<8)+xyzData[0];    //x�������
        ydata = (xyzData[3]<<8)+xyzData[2];    //y�������
        zdata = (xyzData[5]<<8)+xyzData[4];    //z�������
        printf("���x�������:%d\r\n\r\n",xdata);             //���x�������
        printf("���y�������:%d\r\n\r\n",ydata);             //���y�������
        printf("���z�������:%d\n\r\n\r\n",zdata);           //���z�������

       // if(xdata<=10000)

        char a1[10];
        char a2[10];
        char a3[10];
        
        sprintf(a1,"%d",xdata);
        sprintf(a2,"%d",ydata);
        sprintf(a3,"%d",zdata);
        
        uart_send_string(UART_User, a1);
        uart_send1(UART_User, '.');
        uart_send_string(UART_User, a2);
        uart_send1(UART_User, '.');
        uart_send_string(UART_User, a3);
        uart_send1(UART_User, '\n');
        


        
        

	    // uart_send_string(UART_User, "����оƬ�¶�");
		// uart_send1 (UART_User ,a+'0');
		// uart_send1 (UART_User ,b+'0');
		// uart_send1(UART_User, '.');
		// uart_send1 (UART_User ,c+'0');
		// uart_send1 (UART_User ,d+'0');
		// uart_send1(UART_User, '\n');
		
		
        
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







void main_Dly_ms(uint32_t ms)
{
    for(uint32_t i= 0; i < (6000*ms); i++) __asm("nop");
}

//====================================================================
/*
֪ʶҪ�أ�
��1��main.c��һ��ģ�壬���ļ����д�������漰�����Ӳ���ͻ�����ͨ�����ù���
ʵ�ֶ�Ӳ���ĸ�Ԥ��
��2�����ļ��б��С����䡿�ĵط�Ϊϵͳ��������������������Ŀ�޹أ�����ɾ����
��3�����ļ��жԺ�GLOBLE_VAR�����˶��壬�����ڰ���"includes.h"ͷ�ļ�ʱ���ᶨ
��ȫ�ֱ������������ļ��а���"includes.h"ͷ�ļ�ʱ��
����ʱ���Զ�����extern
*/



//====================================================================
//�ļ����ƣ�main.c��Ӧ�ù�����������
//����ṩ��SD-Arm��sumcu.suda.edu.cn��
//�汾���£�2017.08, 2020.06
//�����������������̵�<01_Doc>�ļ�����Readme.txt�ļ�
//====================================================================

#define GLOBLE_VAR
#include "includes.h"      //������ͷ�ļ�

//----------------------------------------------------------------------
//����ʹ�õ����ڲ�����
//main.cʹ�õ��ڲ�����������
void Test_Lantern();
void main_Dly_ms(uint32_t ms);
//----------------------------------------------------------------------
//��������һ������¿�����Ϊ����Ӵ˿�ʼ���У�ʵ�������������̼���壩
int main(void)
{
    //��1��======�������֣���ͷ��==========================================
    //��1.1������main����ʹ�õľֲ�����
    uint32_t mMainLoopCount;  //��ѭ��ʹ�õļ�¼��ѭ����������
    uint8_t  mFlag;            //��ѭ��ʹ�õ���ʱ����
    
    //��1.2�������䡿�����ж�
    DISABLE_INTERRUPTS;

    
    //��1.3����������ʹ�õľֲ���������ֵ
    mMainLoopCount = 0;     //��ѭ��ʹ�õļ�¼��ѭ����������
    mFlag='A';              //��ѭ��ʹ�õ���ʱ����������״̬��־
    
    //��1.4����ȫ�ֱ�������ֵ
    
    //��1.5���û�����ģ���ʼ��
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //��ʼ������
    //uart_init(UART_User,115200);
    
    //��1.6��ʹ��ģ���ж�
    //uart_enable_re_int(UART_User);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;
    
    printf("-----------------------------------------------------\r\n"); 
    printf("���«��ʾ���ʵƲ���ʵ�� \r\n");
    printf("  �� ������˸\n");
    printf("  �� UART_Debug���ڣ�������115200��������ʵ���ʾ��Ϣ \r\n");
    printf("----------------------------------------------------\r\n"); 
    
    
    //��1��======�������֣���β��==========================================
    
    //��2��======��ѭ�����֣���ͷ��=========================================
    for(;;)     //for(;;)����ͷ��
    {
        
        //��2.1����ѭ������+1�����ж��Ƿ�С���ض�����
        mMainLoopCount++;                         //+1
        if (mMainLoopCount<=6556677)  continue;   //���С���ض�����������ѭ��
        Test_Lantern();
        //��2.2����ѭ�����������ض���������״̬�����л��������ƻ���˸��
        mMainLoopCount=0;      //����ѭ������
        //�л���״̬
        if (mFlag=='A')   //����״̬��־Ϊ'A'
        {
            gpio_set(LIGHT_BLUE,LIGHT_ON);   //���õơ�����
            printf("���ƣ���\r\n\r\n");           //ͨ�����Դ�������Ƶ�״̬
            mFlag='L';                        //�ı�״̬��־
        }
        else                   //����,����״̬��־��Ϊ'A'    
        {
            gpio_set(LIGHT_BLUE,LIGHT_OFF);  //���õơ�����  
            printf("���ƣ���\r\n\r\n");           //ͨ�����Դ�������Ƶ�״̬
            mFlag='A';                        //�ı�״̬��־
        }	
    }     //for(;;)��β
    //��2��======��ѭ�����֣���β��========================================
}

//======����Ϊ���������õ��Ӻ�����Ŵ�=====================================
//=====================================================================
//�������ƣ�Test_Lantern
//�������أ���
//����˵������
//���ܸ�Ҫ�����Բʵƴ���������
//=====================================================================
void Test_Lantern()
{	
    //��1�����Բʵ�
    //һ�ֲʵ���ɫռ3���ֽڣ���grb˳��
    uint8_t grbw[12]={0xFF,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF};
    uint8_t rwgb[12]={0x00,0xFF,0x00,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0xFF};
    uint8_t black[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};


    uint8_t test1_1[12]={0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t test1_2[12]={0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
    uint8_t test1_3[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,};
    uint8_t test1_4[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,};

    uint8_t test2_1[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t test2_2[12]={0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
    uint8_t test2_3[12]={0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,};
    uint8_t test2_4[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,};

    uint8_t test3_1[12]={0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t test3_2[12]={0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,};
    uint8_t test3_3[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,};
    uint8_t test3_4[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,};

    uint8_t test4_1[12]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
    uint8_t test4_2[12]={0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,};
    uint8_t test4_3[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,};
    uint8_t test4_4[12]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,};


    static char OutputCtl=0;
    OutputCtl++;
    if (OutputCtl>=5) OutputCtl=1;
    WS_Init(COLORLIGHT);




    gpio_init(Button1,GPIO_OUTPUT,0);
	gpio_init(Button2,GPIO_OUTPUT,1);
	gpio_init(Button3,GPIO_INPUT,0);
	gpio_pull(Button3,1);
	gpio_init(Button4,GPIO_INPUT,0);
	gpio_pull(Button4,1);
    if (gpio_get(Button3)==0)
	{
		printf("��һ����ˮ��\r\n\r\n");
        switch (OutputCtl)
        {
        case 1:
        	WS_SendOnePix(COLORLIGHT,test1_1,4);
            printf("---------1--------\r\n\r\n");
            break;
        case 2:
            WS_SendOnePix(COLORLIGHT,test1_3,4);
            printf("---------2---------\r\n\r\n");
            break;
        case 3:
            WS_SendOnePix(COLORLIGHT,test1_4,4);
            printf("---------3----------\r\n\r\n");
            break;
        case 4:
        	WS_SendOnePix(COLORLIGHT,test1_2,4);
            printf("----------4---------\r\n\r\n");
            break;
        default:
	        break;
	    }
    }
    if (gpio_get(Button4)==0)
	{
		printf("�ڶ�����ˮ��\r\n\r\n");
        switch (OutputCtl)
        {
        case 1:
        	WS_SendOnePix(COLORLIGHT,test2_1,4);
            printf("---------1--------\r\n\r\n");
            break;
        case 2:
            WS_SendOnePix(COLORLIGHT,test2_3,4);
            printf("---------2---------\r\n\r\n");
            break;
        case 3:
            WS_SendOnePix(COLORLIGHT,test2_4,4);
            printf("---------3----------\r\n\r\n");
            break;
        case 4:
        	WS_SendOnePix(COLORLIGHT,test2_2,4);
            printf("----------4---------\r\n\r\n");
            break;
        default:
	        break;
	    }
    }

    gpio_init(Button1,GPIO_OUTPUT,1);
	gpio_init(Button2,GPIO_OUTPUT,0);
	gpio_init(Button3,GPIO_INPUT,0);
	gpio_pull(Button3,1);
	gpio_init(Button4,GPIO_INPUT,0);
	gpio_pull(Button4,1);

    if (gpio_get(Button3)==0)
	{
		printf("��������ˮ��\r\n\r\n");
        switch (OutputCtl)
        {
        case 1:
        	WS_SendOnePix(COLORLIGHT,test3_1,4);
            printf("---------1--------\r\n\r\n");
            break;
        case 2:
            WS_SendOnePix(COLORLIGHT,test3_3,4);
            printf("---------2---------\r\n\r\n");
            break;
        case 3:
            WS_SendOnePix(COLORLIGHT,test3_4,4);
            printf("---------3----------\r\n\r\n");
            break;
        case 4:
        	WS_SendOnePix(COLORLIGHT,test3_2,4);
            printf("----------4---------\r\n\r\n");
            break;
        default:
	        break;
	    }
	}
	if (gpio_get(Button4)==0)
	{
		printf("�ڶ�����ˮ��\r\n\r\n");
        switch (OutputCtl)
        {
        case 1:
        	WS_SendOnePix(COLORLIGHT,test4_1,4);
            printf("---------1--------\r\n\r\n");
            break;
        case 2:
            WS_SendOnePix(COLORLIGHT,test4_3,4);
            printf("---------2---------\r\n\r\n");
            break;
        case 3:
            WS_SendOnePix(COLORLIGHT,test4_4,4);
            printf("---------3----------\r\n\r\n");
            break;
        case 4:
        	WS_SendOnePix(COLORLIGHT,test4_2,4);
            printf("----------4---------\r\n\r\n");
            break;
        default:
	        break;
	    }
	}

	        
    
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



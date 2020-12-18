//======================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：SD-ARM（sumcu.suda.edu.cn）
//版本更新：
//功能描述：见本工程的<01_Doc>文件夹下Readme.txt文件
//======================================================================
#define GLOBLE_VAR
#include "includes.h"      //包含总头文件

//----------------------------------------------------------------------
//声明使用到的内部函数
//main.c使用的内部函数声明处
float TempRegression(uint16_t AD);
//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程，参见书稿）
int main(void)
{
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    uint32_t mMainLoopCount;  //主循环次数变量
    uint8_t  mFlag;           //灯的状态标志
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
    
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;
    wdog_feed();
    printf("进入User的main...\n");
    
    //（1.3）给主函数使用的局部变量赋初值
    mMainLoopCount=0;    //主循环次数变量
    mFlag='R';           //灯的状态标志
    //（1.4）给全局变量赋初值
    
    //（1.5）用户外设模块初始化
    wdog_start(3);	  //启动看门狗
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);          //初始化红灯 'R'
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);        //初始化绿灯 'G'
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);         //初始化蓝灯 'B'
    gpio_init(PIN_MAG,GPIO_INPUT,1);     
    wdog_feed();
    printf("LCD初始化...");
    LCD_Init();
    printf("成功\n");
    uart_init(UART_User,115200);
    adc_init(AD_LIGHT,0);
    adc_init(AD_TEMP,0);
    adc_init(AD_MCU_TEMP,0);
    wdog_feed();
//    adc_init(AD_BAT,0);

    //（1.6）使能模块中断
    uart_enable_re_int(UART_User);
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;
    
    //（1.8）调用LCD构件中的函数
    
    printf("金葫芦提示：LCD屏幕版面...");
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
    printf("完成\n");
//     while(1){}
    //（1）======启动部分（结尾）==========================================

    //（2）======主循环部分（开头）========================================
    for(;;)   //for(;;)（开头）
    {
    	wdog_feed();
        //（2.1）主循环次数变量+1
        mMainLoopCount++;
        //（2.2）未达到主循环次数设定值，继续循环
        if (mMainLoopCount<=0x1fffff)  continue;
        //（2.3）达到主循环次数设定值，执行下列语句，进行灯的亮暗处理
        //（2.3.1）清除循环次数变量
        mMainLoopCount=0; 
        
        temperature = TempRegression(adc_read(AD_TEMP));
        mcu_temp_AD = adc_read(AD_MCU_TEMP);
//        bat_AD = adc_read(AD_BAT);
//        bat_V = (float)(bat_AD*66.0/4096.0);
        light = adc_read(AD_LIGHT);
        printf(" mcu_temp：%d--\n",mcu_temp_AD);
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
        printf(" 磁力：%d--\n",mag);
        printf(" 环境温度：%d--\n",(int)temperature); 
        printf(" 光照：%d--\n",light);
        printf(" MCU温度：%4.1lf--\n",mcu_temp);
//        printf(" bat_V：%4.1lf V--\n",bat_V);
        
    }  //for(;;)结尾
    //（2）======主循环部分（结尾）========================================
}   //main函数（结尾）


//======以下为主函数调用的子函数===========================================
float TempRegression(uint16_t tmpAD)
{
    float v1,v2,S,T;
    v1 = ((float)tmpAD*3300)/65535;   //AD值变为采样点电压(mV)
    v2=3300 - v1;                    //分压电阻两端电压(mV)
    S = v1/v2;                       //分压比
    T = (1/(log(S)/3950.0 + (1/(273.15 + 25)))) - 273.15 + 0.5;
    return T;
}



//=========================================================================
/*
知识要素：
（1）main.c是一个模板，该文件所有代码均不涉及具体的硬件和环境，通过调用构件
实现对硬件的干预。
（2）本文件中对宏GLOBLE_VAR进行了定义，所以在包含"includes.h"头文件时，会定
义全局变量，在其他文件中包含"includes.h"头文件时，
编译时会自动增加extern
*/



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
void Test_Digitaltube();
void main_Dly_ms(uint32_t ms);
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
        if (mMainLoopCount<=20)  continue;
        //（2.3）达到主循环次数设定值，执行下列语句，进行灯的亮暗处理
        //（2.3.1）清除循环次数变量
        mMainLoopCount=0; 
        wdog_feed();
	
        wdog_feed();
    
        wdog_feed();



     
        

        uint8_t mString[30];
        uint8_t xyzData[6];         //x、y、z轴倾角，均占两个字节
        uint16_t xdata,ydata,zdata; //x轴倾角
        uint8_t checkdata;          //ADLX345的验证数据,正确接收为0xe5
        adlx345_init(i2cAcceleration,0x0B,0x08,0x08,0x80,0x00,0x00,0x05);//初始化ADLX345(J2端口) 
        adlx345_read1(0x00,&checkdata);    //读取adxl345校验数据
        adlx345_init(0,0x0B,0x08,0x08,0x80,0x00,0x00,0x05);//初始化ADLX345(J2端口)
        adlx345_read1(0x00,&checkdata);    //读取adxl345校验数据
        main_Dly_ms(5);
        adlx345_readN(0x32,xyzData,6);		   //读倾角传感器数值
        
        xdata = (xyzData[1]<<8)+xyzData[0];    //x方向倾角
        ydata = (xyzData[3]<<8)+xyzData[2];    //y方向倾角
        zdata = (xyzData[5]<<8)+xyzData[4];    //z方向倾角
        printf("输出x方向倾角:%d\r\n\r\n",xdata);             //输出x方向倾角
        printf("输出y方向倾角:%d\r\n\r\n",ydata);             //输出y方向倾角
        printf("输出z方向倾角:%d\n\r\n\r\n",zdata);           //输出z方向倾角

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
        


        
        

	    // uart_send_string(UART_User, "这是芯片温度");
		// uart_send1 (UART_User ,a+'0');
		// uart_send1 (UART_User ,b+'0');
		// uart_send1(UART_User, '.');
		// uart_send1 (UART_User ,c+'0');
		// uart_send1 (UART_User ,d+'0');
		// uart_send1(UART_User, '\n');
		
		
        
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







void main_Dly_ms(uint32_t ms)
{
    for(uint32_t i= 0; i < (6000*ms); i++) __asm("nop");
}

//====================================================================
/*
知识要素：
（1）main.c是一个模板，该文件所有代码均不涉及具体的硬件和环境，通过调用构件
实现对硬件的干预。
（2）本文件中标有【不变】的地方为系统保留，此类代码与具体项目无关，不宜删除。
（3）本文件中对宏GLOBLE_VAR进行了定义，所以在包含"includes.h"头文件时，会定
义全局变量，在其他文件中包含"includes.h"头文件时，
编译时会自动增加extern
*/



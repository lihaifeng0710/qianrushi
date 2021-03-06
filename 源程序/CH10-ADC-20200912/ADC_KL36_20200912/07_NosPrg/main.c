//====================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：SD-Arm（sumcu.suda.edu.cn）
//版本更新：2017.08, 2020.05
//功能描述：见本工程的<01_Doc>文件夹下Readme.txt文件
//====================================================================

#define GLOBLE_VAR
#include "includes.h"      //包含总头文件

//----------------------------------------------------------------------
//声明使用到的内部函数
//main.c使用的内部函数声明处
//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程见书稿）
int main(void)
{
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
	uint16_t mcu_temp_AD;			 //温度值
    uint8_t  mFlag;          //主循环使用的临时变量
    uint8_t  mSec;	         //记当前秒的值
    float temperature;
    float mcu_temp;
    //（1.2）【不变】关总中断
    DISABLE_INTERRUPTS;
    wdog_stop();
    
    //（1.3）给主函数使用的局部变量赋初值
    mFlag='A';              //主循环使用的临时变量：蓝灯状态标志
    
    //（1.4）给全局变量赋初值
   	//"时分秒"缓存初始化(00:00:00)
   	gTime[0] = 0;       //时
   	gTime[1] = 0;	  	//分
   	gTime[2] = 0;	  	//秒
   	mSec = gTime[2];	//记住当前秒的值
    //（1.5）用户外设模块初始化
   	gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //初始化蓝灯
   	systick_init(10);      //设置systick为10ms中断
   	uart_init(UART_User,115200);
   	uart_init(UART_Debug,115200);
  	adc_init(AD_BOARD_TEMP,0);        //初始化ADC
  	adc_init(AD_MCU_TEMP,0);        //初始化ADC

    //（1.6）使能模块中断
    uart_enable_re_int(UART_Debug);
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;
    printf("------------------------------------------------------\n");
    printf("金葫芦提示：AD实例 \n");
    printf("  ① 蓝灯闪烁\n");
   	printf("  ② 每秒读取一次温度传感器的AD采集值，并通过串口输出 \n");
   	printf("  ③ 通过上位机串口程序配合串口中断主动获取AD采集值 \n");
   	printf("  ④ 以字符串的形式输出采集的数据更加直观  \n");
   	printf("  ⑤ 试着编写高级语言程序，将采集的数据以图表、曲线等形式表现出来 \n");
    printf("------------------------------------------------------\n");


    //（1）======启动部分（结尾）==========================================
    
    //（2）======主循环部分（开头）=========================================
    for(;;)     //for(;;)（开头）
    {
    	__asm("NOP");
        if (gTime[2] == mSec)  continue;
   		mSec=gTime[2];
        //以下是1秒到的处理，灯的状态切换（这样灯每秒闪一次）
        //切换灯状态
        if (mFlag=='A')   //若灯状态标志为'A'
        {
            gpio_set(LIGHT_BLUE,LIGHT_ON);   //设置灯“亮”
            mFlag='L';                        //改变状态标志
        }
        else                   //否则,若灯状态标志不为'A'
        {
            gpio_set(LIGHT_BLUE,LIGHT_OFF);  //设置灯“暗”
            mFlag='A';                        //改变状态标志
        }
        temperature = TempRegression(adc_read(AD_BOARD_TEMP));
        printf(" 环境温度：%d--\n",(int)temperature);

        mcu_temp_AD = adc_read(AD_MCU_TEMP);
        mcu_temp=TempTrans(mcu_temp_AD);
        printf(" MCU温度：%d--\n",(int)mcu_temp);
    }     //for(;;)结尾
    //（2）======主循环部分（结尾）========================================
}


/*
知识要素：
（1）main.c是一个模板，该文件所有代码均不涉及具体的硬件和环境，通过调用构件
实现对硬件的干预。
（2）本文件中标有【不变】的地方为系统保留，此类代码与具体项目无关，不宜删除。
（3）本文件中对宏GLOBLE_VAR进行了定义，所以在包含"includes.h"头文件时，会定
义全局变量，在其他文件中包含"includes.h"头文件时，
编译时会自动增加extern
*/




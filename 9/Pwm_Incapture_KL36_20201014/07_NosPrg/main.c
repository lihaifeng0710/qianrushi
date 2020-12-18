//====================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：SD-Arm（sumcu.suda.edu.cn）
//版本更新：2017.08, 2020.06
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
	level=50;
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    uint8_t  mFlag;           //主循环使用的临时变量
    uint8_t  mSec;	         //记当前秒的值
    uint8_t percent;
    percent=level;
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
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_ON);    //初始化蓝灯
    uart_init(UART_User, 115200);
    timer_init(TIMER_USER,20);   //设置TIMER_USER为20ms中断
    pwm_init(PWM_USER,375,65535,50,PWM_EDGE,PWM_PLUS);   //PWM输出初始化
    incapture_init(INCAP_USER,375,37500,CAP_DOUBLE);     //上升沿捕捉初始化

    //（1.6）使能模块中断
    timer_enable_int(TIMER_USER);
    cap_enable_int(INCAP_USER);    //使能输入捕捉中断
    uart_enable_re_int(UART_User);
    //（1.7）【不变】开总中断
    ENABLE_INTERRUPTS;

    printf("------------------------------------------------------\n");
    printf("金葫芦提示：PWM-INCAP实例 \n");
    printf("  ① 蓝灯闪烁\n");
   	printf("  ② 通过INCAP_USER输出4KHz的PWM信号，占空比为50%。 \n");
   	printf("  ③ 设置INCAP_USER为输入捕捉，采用双边沿捕捉， \n");
   	printf("  ④ 每次触发输入捕捉，都会向上位机输出当前捕捉到的通道值”。 \n");
    printf("------------------------------------------------------\n");

    //for(;;) {  }     //在此打桩，理解蓝色发光二极管为何亮起来了？
    
    //（1）======启动部分（结尾）==========================================
    
    //（2）======主循环部分（开头）=========================================
    for(;;){
	    while(percent!=level){
	    	pwm_update(PWM_USER,level);
	    	printf("%d",level);
	    	percent=level;
	    }
    }
    //（2）======主循环部分（结尾）========================================
}

//======以下为主函数调用的子函数存放处=====================================

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




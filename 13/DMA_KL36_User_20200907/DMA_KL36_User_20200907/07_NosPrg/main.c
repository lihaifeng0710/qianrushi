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
    //（1）======启动部分（开头）==========================================
    //（1.1）声明main函数使用的局部变量
    uint32_t mMainLoopCount;  //主循环使用的记录主循环次数变量
    uint8_t  mFlag;            //主循环使用的临时变量
    uint8_t WriteData[16]="Send_Message0";
    uint8_t ReadData[16];
    gDmaRecFlag = 0;
     
    uint8_t tempDmaBuf[] = {"\nStart DMA transmission\n"};
    for (int i=0; i<25; ++i)
    {
    	gDmaSendBuf[i] = tempDmaBuf[i];
    }
    
    //gDmaRecFlag=0;
    
    //（1.2）【不变】关总中断
    printf("成功5\n");
    DISABLE_INTERRUPTS;
    wdog_stop();

    //（1.3）给主函数使用的局部变量赋初值
    mMainLoopCount = 0;     //主循环使用的记录主循环次数变量
    mFlag='A';              //主循环使用的临时变量：蓝灯状态标志

    //（1.4）给全局变量赋初值

    //（1.5）用户外设模块初始化
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);    //初始化蓝灯
    //uart_init(UART_User, 115200);
    dma_init(DMA_CH0);
    uart_init(UART_User,115200);
    printf("成功6\n");
        //（1.7）使能模块中断
    uart_IdleIrq_enable(UART_User);//开串口空闲中断
    //（1.6）使能模块中断
    //uart_enable_re_int(UART_User);
    //（1.7）【不变】开总中断
    printf("成功7\n");
    ENABLE_INTERRUPTS;
    printf("成功9\n");
    printf("------------------------------------------------------\n");
    printf("金葫芦提示：DMA实例 \n");
    printf("  ① 蓝灯闪烁\n");
    printf("  ② 通过在主函数中发起DMA读取数据请求，完成直接通过硬件地址读取数据 \n");
    printf("     请退出本界面，转入“工具”→“串口工具”验证    \n");
    printf("------------------------------------------------------\n");

    //for(;;) {  }     //在此打桩，理解蓝色发光二极管为何亮起来了？
    printf("dma读取数据：");
    //dma_read(DMA_CH0 , &WriteData,13);
    //printf(ReadData);
    //dma_clear(DMA_CH0);
    printf("\ndma读取数据成功\n");

    //（1）======启动部分（结尾）==========================================

    //（2）======主循环部分（开头）=========================================
    for(;;)     //for(;;)（开头）
    {

        //（2.1）主循环次数+1，并判断是否小于特定常数
        mMainLoopCount++;                         //+1
        if (mMainLoopCount<=6556677)  continue;   //如果小于特定常数，继续循环
        //（2.2）主循环次数超过特定常数，灯状态进行切换（这样灯会闪烁）
        mMainLoopCount=0;      //清主循环次数
        
        /*切换灯状态
        if (mFlag=='A')   //若灯状态标志为'A'
        {
            gpio_set(LIGHT_BLUE,LIGHT_ON);   //设置灯“亮”
            printf("蓝灯：亮\n");             //通过调试串口输出灯的状态
            mFlag='L';                        //改变状态标志
        }
        else                   //否则,若灯状态标志不为'A'
        {
            gpio_set(LIGHT_BLUE,LIGHT_OFF);  //设置灯“暗”
            printf("蓝灯：暗\n");             //通过调试串口输出灯的状态
            mFlag='A';                        //改变状态标志
        }
        */
        
        //uart_sendN(UART_User,25,gDmaSendBuf);
        printf("成功8\n");
        if(gDmaRecFlag)
        {
        	// uart_sendN(UART_User,25,gDmaSendBuf);
        	//使用DMA发送内存中接收到的数据进行验证
        	for(uint32_t i = 0 ; i<6000*5;i++);
        	dma_send( DMA_CH0, (uint32_t)gDmaRecBuf, 10 );//通过DMA发送
        	printf("成功1\n");
        	gDmaRecFlag=0;//标志位清0
        }

    }     //for(;;)结尾
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




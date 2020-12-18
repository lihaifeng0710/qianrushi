//======================================================================
//文件名称：main.c（应用工程主函数）
//框架提供：苏大arm技术中心（sumcu.suda.edu.cn）
//版本更新：2017.08:1.0, 2019.1:A.10
//功能描述：见本工程的<01_Doc>文件夹下Readme.txt文件
//======================================================================
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
	uint_64 mMainLoopCount;  //主循环使用的记录主循环次数变量
    uint_64 mTime;           //主循环使用的临时时间变量
    uint_8  mFlag;           //主循环使用的临时变量
	uint_32 adrOffset =0;
	uint_32 RecAdr;

    //（1.2）【不变】BIOS中API接口表首地址、用户中断处理程序名初始化
         BIOS_API_Init();
         gTimeSec=1548950401;         //默认2019-02-01 00:00:01
         sysTimeSet(gTimeSec);        //设置系统时间初值
         mTime=sysTimeGet();          //获得当前系统时间（s）

        //特别注意，（1.2）程序段不能删除，否则系统不能运行

        //（1.3）【不变】关总中断
        DISABLE_INTERRUPTS;

        //（1.4）给主函数使用的局部变量赋初值
         mMainLoopCount = 0;     //主循环使用的记录主循环次数变量
         mFlag='A';              //主循环使用的临时变量

        //（1.5）给全局变量赋初值
         uint_8 tempDmaBuf[] = {"\nStart DMA transmission\n"};
         for (int i=0; i<25; ++i)
         {
         	gDmaSendBuf[i] = tempDmaBuf[i];
         }
         gDmaRecFlag=0;
        //（1.6）用户外设模块初始化
        gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_ON);    //初始化红灯
        dma_init(DMA_CH0);
        uart_init(UARTA,9600);

        //（1.7）使能模块中断
        uart_IdleIrq_enable(UARTA);//开串口空闲中断

        //（1.8）【不变】开总中断
        ENABLE_INTERRUPTS;

        //（1）======启动部分（结尾）==========================================

        //（2）======主循环部分（开头）========================================
        for(;;)  //for(;;)（开头）
        {
        	//主循环使用的记录主循环次数变量+1（需要时可使用）
        	mMainLoopCount++;
        	//获得当前系统时间（s）
            mTime=sysTimeGet();
            //判断是否与旧时间相同，若相同，即未到1秒，继续循环
            if (mTime==gTimeSec)  continue;
            //以下是1秒到的处理，红灯状态切换（这样红灯每秒闪一次）
            gTimeSec=mTime;                    //保存新时间,并转为字符串
            timeChange(gTimeSec,gTimeString);
           	gpio_reverse(LIGHT_RED);           //红灯状态切换,记录红灯状态
           	mFlag=(mFlag=='A'?'L':'A');
            //printf("s%",gTimeString);          //通过调试串口输出到PC机
            printf((mFlag=='A')?" LIGHT_RED:ON--\n":" LIGHT_RED:OFF==\n");

            if(gDmaRecFlag)
            {
                uart_sendN(UART_USER,25,gDmaSendBuf);
                //使用DMA发送内存中接收到的数据进行验证
            	Delay_ms(5);
                dma_send(DMA_CH0,(uint_32)gDmaRecBuf,10);//通过DMA发送
                gDmaRecFlag=0;//标志位清0
            }

        }  //for(;;)结尾
        //（2）======主循环部分（结尾）========================================
    }


    //======以下为主函数调用的子函数===========================================


    //=========================================================================
    /*
     知识要素：
     （1）main.c是一个模板，该文件所有代码均不涉及具体的硬件和环境，通过调用构件
          实现对硬件的干预。
     （2）本文件中标有【不变】的地方为系统保留，此类代码与具体项目无关，不宜删除。
     （3）本文件中对宏GLOBLE_VAR进行了定义，所以在包含"includes.h"头文件时，会定
          义全局变量，在其他文件中包含"includes.h"头文件时，
          编译时会自动增加extern
     */

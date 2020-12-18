//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================

#include "includes.h"   //包含总头文件


int main(void)
{
	//1. 声明主函数使用的变量
	uint_32  mRuncount;     //主循环计数器
	//2. 关总中断
	DISABLE_INTERRUPTS;

	//3. 初始化外设模块
	light_init(RUN_LIGHT_RED, LIGHT_OFF);  //红灯初始化
	light_init(RUN_LIGHT_BLUE, LIGHT_OFF);  //蓝灯初始化
	light_init(RUN_LIGHT_GREEN, LIGHT_ON);  //绿灯初始化
	uart_init(UART_0,MCGIRCLK, 9600);    //串口0时钟MCGIRCLK(4000Khz)
	uart_init (UART_1,BUSCLK, 9600);     //串口1、2使用总线时钟24000Khz
	uart_init (UART_2,BUSCLK, 9600);     //波特率使用9600
	uart_send_string(UART_0, "Hello Uart_0!\r\n"); //串口发送初始化提示
	uart_send_string(UART_1, "Hello Uart_1!\r\n");
	uart_send_string(UART_2, "Hello Uart_2!\r\n");
	//4. 给有关变量赋初值
	mRuncount=0;            //主循环计数器
	//5. 使能模块中断
	uart_enable_re_int(UART_0);   //使能串口0接收中断
	uart_enable_re_int(UART_1);   //使能串口1接收中断
	uart_enable_re_int(UART_2);   //使能串口2接收中断
	//6. 开总中断
	ENABLE_INTERRUPTS;
    
	//进入主循环
	//主循环开始==================================================================
	for(;;)
	{

		//运行指示灯（RUN_LIGHT）闪烁---------------------------------------------
		mRuncount++;					   //主循环次数计数器+1
		if (mRuncount >= RUN_COUNTER_MAX)  //主循环次数计数器大于设定的宏常数
		{
			mRuncount=0;				   //主循环次数计数器清零
			//if(uart_re1=='1')
			//light_change(RUN_LIGHT_BLUE);  //蓝色运行指示灯（RUN_LIGHT_BLUE）状态变化

			//else if(uart_re1=='2')
			//light_change(RUN_LIGHT_GREEN);  //蓝色运行指示灯（RUN_LIGHT_BLUE）状态变化
			//else
			//light_change(RUN_LIGHT_RED);  //蓝色运行指示灯（RUN_LIGHT_BLUE）状态变化

		}
		//以下加入用户程序--------------------------------------------------------
	}//主循环end_for
	//主循环结束==================================================================
}


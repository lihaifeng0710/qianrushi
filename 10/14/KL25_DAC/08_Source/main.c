//说明见工程文件夹下的Doc文件夹内Readme.txt文件
//============================================================================
#include "includes.h"    //包含总头文件

int main(void)
{
	//1. 声明主函数使用的变量
	uint_32  mRuncount;     //主循环计数器
	VReference = 0;
	//2. 关总中断
	DISABLE_INTERRUPTS;
	//3. 初始化外设模块
	light_init(RUN_LIGHT_BLUE,LIGHT_OFF);     //初始化蓝色RUN灯
    uart_init (UART_TEST,BUSCLK,9600);                  //串口1初始化, 总线时钟24000Khz,波特率9600
    uart_send_string(UART_TEST, "This is DAC Test!\r\n"); //打印测试信息
    dac_init(1);                                        //DAC初始化，选择参考电压VDDA=3.3V
	//4. 给有关变量赋初值
	mRuncount=0;            //主循环计数器
	//5. 使能模块中断
    uart_enable_re_int(UART_TEST); //使能串口1接收中断
	//6. 开总中断
	ENABLE_INTERRUPTS;

    //进入主循环
    //主循环开始==================================================================
	for(;;)
	{
		mRuncount++;
		if (mRuncount > RUN_COUNTER_MAX)
		{
			mRuncount = 0;
			//指示灯的亮、暗状态切换
		    //light_change(RUN_LIGHT_BLUE);  //蓝色运行指示灯（RUN_LIGHT_BLUE）状态变化

			//DAC数字量转换		
			dac_convert(VReference);
			//VReference -= 50;
			//if(VReference <= 0) VReference = 4000;
		} // end_if		
		//以下加入用户程序--------------------------------------------------------
	}//主循环end_for
	//主循环结束==================================================================
	return 0;
}

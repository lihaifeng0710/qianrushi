//===========================================================================
//文件名称：gpio.c
//功能概要：GPIO底层驱动构件源文件
//版权所有：苏州大学飞思卡尔嵌入式中心(sumcu.suda.edu.cn)
//更新记录：2014-7-21   V1.0
//===========================================================================
#include "gpio.h"   //包含本构件头文件

//各端口基地址放入常数数据组PORT_ARR[0]~PORT_ARR[4]中
static const PORT_MemMapPtr PORT_ARR[]={PORTA_BASE_PTR,PORTB_BASE_PTR,
		                       PORTC_BASE_PTR,PORTD_BASE_PTR,PORTE_BASE_PTR};
//GPIO口基地址放入常数数据组GPIO_ARR[0]~GPIO_ARR[4]中
static const GPIO_MemMapPtr GPIO_ARR[]={PTA_BASE_PTR,PTB_BASE_PTR,
		                        PTC_BASE_PTR,PTD_BASE_PTR,PTE_BASE_PTR};

//内部函数声明
static void gpio_port_pin_resolution(uint_16 port_pin,uint_8* port,uint_8* pin);

//------------------------------内部函数-------------------------------------

//===========================================================================
//函数名称：gpio_port_pin_resolution
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：PORTB|(5) 表示为B口5号脚）
//         port：端口号
//		   pin:引脚号（0~31，实际取值由芯片的物理引脚决定）
//功能概要：将传进参数port_pin进行解析，得出具体端口号与引脚号（如：PORTB|(5)
//         解析为PORTB与5，并将其分别赋值给port与pin）。
//===========================================================================
void gpio_port_pin_resolution(uint_16 port_pin,uint_8* port,uint_8* pin)
{
	*port = port_pin>>8;
	* pin = port_pin;
}

//===========================================================================
//函数名称：gpio_init
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：PORTB|(5) 表示为B口5号脚）
//         dir：引脚方向（0=输入，1=输出）
//         state：引脚初始状态（0=低电平，1=高电平）
//功能概要：初始化端口指定引脚作为GPIO引脚的功能，并定义为输入或输出，若是输出，
//         还指定初始状态是低电平或高电平
//===========================================================================
void gpio_init(uint_16 port_pin, uint_8 dir, uint_8 state)
{
	//局部变量声明
	PORT_MemMapPtr port_ptr;    //声明port_ptr为PORT结构体类型指针 
	GPIO_MemMapPtr gpio_ptr;    //声明port_ptr为GPIO结构体类型指针
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);
	
	
	//根据带入参数port，给局部变量port_ptr、gpio_ptr赋值（获得两个基地址）
	port_ptr = PORT_ARR[port];  //获得PORT模块相应口基地址
	gpio_ptr = GPIO_ARR[port];  //获得GPIO模块相应口基地址
	
	//根据带入参数pin,指定该引脚功能为GPIO功能（即令引脚控制寄存器的MUX=0b001）
    port_ptr->PCR[pin] = PORT_PCR_MUX(1);
    
    //根据带入参数dir，决定引脚为输出还是输入
    if (1 == dir)   //希望为输出
       {
         BSET(pin,gpio_ptr->PDDR);     //数据方向寄存器的pin位=1，定义为输出
         gpio_set(port_pin, state);   //调用gpio_set函数，设定引脚初始状态
       }
       else         //希望为输入
        	BCLR(pin,gpio_ptr->PDDR);  //数据方向寄存器的pin位=0，定义为输入
}

//===========================================================================
//函数名称：gpio_set
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：PORTB|(5) 表示为B口5号脚）
//         state：引脚初始状态（0=低电平，1=高电平）
//功能概要：设定引脚状态为低电平或高电平
//===========================================================================
void gpio_set(uint_16 port_pin, uint_8 state)
{
	GPIO_MemMapPtr gpio_ptr;    //声明port_ptr为GPIO结构体类型指针
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);
	
	//根据带入参数port，给局部变量gpio_ptr赋值（GPIO基地址）
	gpio_ptr = GPIO_ARR[port]; 
	
	//根据带入参数state，决定引脚为输出1还是0
	if (1==state) {BSET(pin,gpio_ptr->PDOR);} else {BCLR(pin,gpio_ptr->PDOR);}
}

//===========================================================================
//函数名称：gpio_get
//函数返回：指定引脚的状态（1或0）
//参数说明：port_pin：端口号|引脚号（如：PORTB|(5) 表示为B口5号脚）
//功能概要：获取指定引脚的状态（1或0）
//===========================================================================
uint_8 gpio_get(uint_16 port_pin)
{
	GPIO_MemMapPtr gpio_ptr;    //声明port_ptr为GPIO结构体类型指针（首地址）
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);
	
	//根据带入参数port，给局部变量port_ptr赋值（GPIO基地址）
	gpio_ptr = GPIO_ARR[port];  
	
	//返回引脚的状态
	return ((BGET(pin,gpio_ptr->PDIR))>=1 ? 1:0);
}

//===========================================================================
//函数名称：gpio_reverse
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：PORTB|(5) 表示为B口5号脚）
//功能概要：反转指定引脚输出状态。
//===========================================================================
void gpio_reverse(uint_16 port_pin)
{
	GPIO_MemMapPtr gpio_ptr;    //声明port_ptr为GPIO结构体类型指针（首地址）
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);
	
	//根据带入参数port，给局部变量port_ptr赋值（GPIO基地址）
	gpio_ptr = GPIO_ARR[port]; 
	
	//反转指定引脚输出状态
	BSET(pin,gpio_ptr->PTOR);
}

//===========================================================================
//函数名称：gpio_pull
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：PORTB|(5) 表示为B口5号脚）
//         pullselect：引脚拉高低电平（ 0=拉低电平，1=拉高电平）
//功能概要：使指定引脚上拉高电平或下拉低电平
//===========================================================================
void gpio_pull(uint_16 port_pin, uint_8 pullselect)
{
	PORT_MemMapPtr port_ptr;    //声明port_ptr为PORT结构体类型指针
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);

	port_ptr = PORT_ARR[port];  //获得PORT模块相应口基地址
    port_ptr->PCR[pin] = PORT_PCR_MUX(1);
	
    BSET(PORT_PCR_DSE_SHIFT,port_ptr->PCR[pin]);
	BSET(PORT_PCR_PE_SHIFT,port_ptr->PCR[pin]);  //将引脚上下拉使能
	
	//根据带入参数pullselect，决定引脚拉高还是拉低
	if (1==pullselect) {BSET(PORT_PCR_PS_SHIFT,port_ptr->PCR[pin]);} 
	else {BCLR(PORT_PCR_PS_SHIFT,port_ptr->PCR[pin]);}
}

//===========================================================================
//函数名称：gpio_enable_int
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：PORTB|(5) 表示为B口5号脚）
//       irqtype：引脚中断类型，宏定义：
//                  LowLevel        8    低电平触发
//                  HighLevel       12   高电平触发
//                  RisingEdge      9    上升沿触发
//                  FallingEdge     10   下降沿触发
//                  DoubleEdge      11   双边沿触发
//功能概要：开启引脚的指定类型中断,KW01中只对PTA、PTC、PTD口有效
//===========================================================================
void gpio_enable_int(uint_16 port_pin,uint_8 irqtype)
{
	PORT_MemMapPtr port_ptr;    //声明port_ptr为PORT结构体类型指针
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);

	port_ptr = PORT_ARR[port];  //获得PORT模块相应口基地址
    
	port_ptr->PCR[pin] |= PORT_PCR_ISF_MASK;  //清除引脚中断标志
    port_ptr->PCR[pin] |= PORT_PCR_IRQC(irqtype);//使能引脚中断
    
    switch(port)
    {
    case 0://PTA
    	enable_irq(30);   //开中断控制器IRQ中断
    	break;
    case 2://PTC
    case 3://PTD
    	enable_irq(31);   //开中断控制器IRQ中断
    	break;
    default:;
    }
}

//===========================================================================
//函数名称：gpio_disable_int
//函数返回：无
//参数说明：port_pin：端口号|引脚号（如：PORTB|(5) 表示为B口5号脚）
//功能概要：禁用引脚的指定类型中断,KW01中只对PTA、PTC、PTD口有效
//===========================================================================
void gpio_disable_int(uint_16 port_pin)
{
	PORT_MemMapPtr port_ptr;    //声明port_ptr为PORT结构体类型指针
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);

	port_ptr = PORT_ARR[port];  //获得PORT模块相应口基地址
    
    port_ptr->PCR[pin] &= ~PORT_PCR_IRQC_MASK;//禁用引脚中断
    
    switch(port)
    {
    case 0://PTA
    	disable_irq(30);   //关中断控制器IRQ中断
    	break;
    case 2://PTC
    case 3://PTD
    	disable_irq(31);   //关中断控制器IRQ中断
    	break;
    default:;
    }
}



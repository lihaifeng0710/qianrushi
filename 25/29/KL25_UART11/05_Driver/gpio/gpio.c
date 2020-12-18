//===========================================================================
//�ļ����ƣ�gpio.c
//���ܸ�Ҫ��GPIO�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2014-7-21   V1.0
//===========================================================================
#include "gpio.h"   //����������ͷ�ļ�

//���˿ڻ���ַ���볣��������PORT_ARR[0]~PORT_ARR[4]��
static const PORT_MemMapPtr PORT_ARR[]={PORTA_BASE_PTR,PORTB_BASE_PTR,
		                   PORTC_BASE_PTR,PORTD_BASE_PTR,PORTE_BASE_PTR};
//GPIO�ڻ���ַ���볣��������GPIO_ARR[0]~GPIO_ARR[4]��
static const GPIO_MemMapPtr GPIO_ARR[]={PTA_BASE_PTR,PTB_BASE_PTR,
		                   PTC_BASE_PTR,PTD_BASE_PTR,PTE_BASE_PTR};

//----------------------����Ϊ�ڲ�������Ŵ�--------------------------------
//===========================================================================
//�������ƣ�gpio_port_pin_resolution
//�������أ���
//����˵����port_pin���˿ں�|���źţ�����PORTB|(5) ��ʾΪB��5�Žţ�
//         port���˿ں�
//		   pin:���źţ�0~31��ʵ��ȡֵ��оƬ���������ž�����
//���ܸ�Ҫ������������port_pin���н������ó�����˿ں������źţ�����PORTB|(5)
//         ����ΪPORTB��5��������ֱ�ֵ��port��pin����
//===========================================================================
static void gpio_port_pin_resolution(uint_16 port_pin,uint_8* port,uint_8* pin)
{
	*port = port_pin>>8;
	* pin = port_pin;
}
//----------------------------�ڲ���������----------------------------------

//===========================================================================
//�������ƣ�gpio_init
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)������PORTB|(5) ��ʾΪB��5�Žţ�
//          dir�����ŷ���0=���룬1=���,�������ŷ���궨�壩
//          state���˿����ų�ʼ״̬��0=�͵�ƽ��1=�ߵ�ƽ��
//���ܸ�Ҫ����ʼ��ָ���˿�������ΪGPIO���Ź��ܣ�������Ϊ�������������������
//          ��ָ����ʼ״̬�ǵ͵�ƽ��ߵ�ƽ
//===========================================================================
void gpio_init(uint_16 port_pin, uint_8 dir, uint_8 state)
{
	//�ֲ���������
	PORT_MemMapPtr port_ptr;    //����port_ptrΪPORT�ṹ������ָ�� 
	GPIO_MemMapPtr gpio_ptr;    //����port_ptrΪGPIO�ṹ������ָ��
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);
	
	
	//���ݴ������port�����ֲ�����port_ptr��gpio_ptr��ֵ�������������ַ��
	port_ptr = PORT_ARR[port];  //���PORTģ����Ӧ�ڻ���ַ
	gpio_ptr = GPIO_ARR[port];  //���GPIOģ����Ӧ�ڻ���ַ
	
	//���ݴ������pin,ָ�������Ź���ΪGPIO���ܣ��������ſ��ƼĴ�����MUX=0b001��

    port_ptr->PCR[pin] &= ~PORT_PCR_MUX_MASK;
    port_ptr->PCR[pin] |= PORT_PCR_MUX(1);
    
    //���ݴ������dir����������Ϊ�����������
    if (1 == dir)   //ϣ��Ϊ���
       {
         BSET(pin,gpio_ptr->PDDR);     //���ݷ���Ĵ�����pinλ=1������Ϊ���
         gpio_set(port_pin, state);   //����gpio_set�������趨���ų�ʼ״̬
       }
       else         //ϣ��Ϊ����
        BCLR(pin,gpio_ptr->PDDR);  //���ݷ���Ĵ�����pinλ=0������Ϊ����
}

//===========================================================================
//�������ƣ�gpio_set
//�������أ���
//����˵����port_pin���˿ں�|���źţ�����PORTB|(5) ��ʾΪB��5�Žţ�
//         state�����ų�ʼ״̬��0=�͵�ƽ��1=�ߵ�ƽ��
//���ܸ�Ҫ���趨����״̬Ϊ�͵�ƽ��ߵ�ƽ
//===========================================================================
void gpio_set(uint_16 port_pin, uint_8 state)
{
	GPIO_MemMapPtr gpio_ptr;    //����port_ptrΪGPIO�ṹ������ָ��
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);
	
	//���ݴ������port�����ֲ�����gpio_ptr��ֵ��GPIO����ַ��
	gpio_ptr = GPIO_ARR[port]; 
	
	//���ݴ������state����������Ϊ���1����0
	if (1==state)
	    {BSET(pin,gpio_ptr->PDOR);}
	else
	    {BCLR(pin,gpio_ptr->PDOR);}
}

//===========================================================================
//�������ƣ�gpio_get
//�������أ�ָ�����ŵ�״̬��1��0��
//����˵����port_pin���˿ں�|���źţ�����PORTB|(5) ��ʾΪB��5�Žţ�
//���ܸ�Ҫ����ȡָ�����ŵ�״̬��1��0��
//===========================================================================
uint_8 gpio_get(uint_16 port_pin)
{
	GPIO_MemMapPtr gpio_ptr;    //����port_ptrΪGPIO�ṹ������ָ�루�׵�ַ��
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);
	
	//���ݴ������port�����ֲ�����port_ptr��ֵ��GPIO����ַ��
	gpio_ptr = GPIO_ARR[port];  
	
	//�������ŵ�״̬
	return ((BGET(pin,gpio_ptr->PDIR))>=1 ? 1:0);
}

//===========================================================================
//�������ƣ�gpio_reverse
//�������أ���
//����˵����port_pin���˿ں�|���źţ�����PORTB|(5) ��ʾΪB��5�Žţ�
//���ܸ�Ҫ����תָ���������״̬��
//===========================================================================
void gpio_reverse(uint_16 port_pin)
{
	GPIO_MemMapPtr gpio_ptr;    //����port_ptrΪGPIO�ṹ������ָ�루�׵�ַ��
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);
	
	//���ݴ������port�����ֲ�����port_ptr��ֵ��GPIO����ַ��
	gpio_ptr = GPIO_ARR[port]; 
	
	//��תָ���������״̬
	BSET(pin,gpio_ptr->PTOR);//PTOR�Ƿ�ת�Ĺؼ�
}

//===========================================================================
//�������ƣ�gpio_pull
//�������أ���
//����˵����port_pin���˿ں�|���źţ�����PORTB|(5) ��ʾΪB��5�Žţ�
//         pullselect���������ߵ͵�ƽ�� 0=���͵�ƽ��1=���ߵ�ƽ��
//���ܸ�Ҫ��ʹָ�����������ߵ�ƽ�������͵�ƽ
//===========================================================================
void gpio_pull(uint_16 port_pin, uint_8 pullselect)
{
	PORT_MemMapPtr port_ptr;    //����port_ptrΪPORT�ṹ������ָ��
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);

	port_ptr = PORT_ARR[port];  //���PORTģ����Ӧ�ڻ���ַ

    port_ptr->PCR[pin] &= ~PORT_PCR_MUX_MASK;
    port_ptr->PCR[pin] |= PORT_PCR_MUX(1);
	
    BSET(PORT_PCR_DSE_SHIFT,port_ptr->PCR[pin]);
	BSET(PORT_PCR_PE_SHIFT,port_ptr->PCR[pin]);  //������������ʹ��
	
	//���ݴ������pullselect�������������߻�������
	if (1==pullselect) {BSET(PORT_PCR_PS_SHIFT,port_ptr->PCR[pin]);} 
	else {BCLR(PORT_PCR_PS_SHIFT,port_ptr->PCR[pin]);}
}

//===========================================================================
//�������ƣ�gpio_enable_int
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)������PORTB|(5) ��ʾΪB��5�Žţ�
//          irqtype�������ж����ͣ��ɺ궨��������ٴ��о����£�
//                  LOW_LEVEL    8      //�͵�ƽ����
//                  HIGH_LEVEL   12     //�ߵ�ƽ����
//                  RISING_EDGE  9      //�����ش���
//                  FALLING_EDGE 10     //�½��ش���
//                  DOUBLE_EDGE  11     //˫���ش���
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ�����������������жϣ���
//          �����жϴ���������
//ע          �⣺ KL25оƬ��ֻ��PORTA��PORTD�ھ���GPIO���жϹ���
//           KW01оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//===========================================================================
void gpio_enable_int(uint_16 port_pin,uint_8 irqtype)
{
	PORT_MemMapPtr port_ptr;    //����port_ptrΪPORT�ṹ������ָ��
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);

	port_ptr = PORT_ARR[port];  //���PORTģ����Ӧ�ڻ���ַ
    
	port_ptr->PCR[pin] |= PORT_PCR_ISF_MASK;  //��������жϱ�־
    port_ptr->PCR[pin] |= PORT_PCR_IRQC(irqtype);//ʹ�������ж�
    
    switch(port)
    {
    case 0://PTA
    	enable_irq(30);   //���жϿ�����IRQ�ж�
    	break;
    case 3://PTD
    	enable_irq(31);   //���жϿ�����IRQ�ж�
    	break;
    default:;
    }
}

//===========================================================================
//�������ƣ�gpio_disable_int
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)������PORTB|(5) ��ʾΪB��5�Žţ�
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ���������ر������ж�
//ע          �⣺ KL25оƬ��ֻ��PORTA��PORTD�ھ���GPIO���жϹ���
//           KW01оƬ��ֻ��PORTA��PORTC��PORTD�ھ���GPIO���жϹ���
//===========================================================================
void gpio_disable_int(uint_16 port_pin)
{
	PORT_MemMapPtr port_ptr;    //����port_ptrΪPORT�ṹ������ָ��
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);

	port_ptr = PORT_ARR[port];  //���PORTģ����Ӧ�ڻ���ַ
    
    port_ptr->PCR[pin] &= ~PORT_PCR_IRQC_MASK;//���������ж�
    
    switch(port)
    {
    case 0://PTA
    	disable_irq(30);   //���жϿ�����IRQ�ж�
    	break;
    case 3://PTD
    	disable_irq(31);   //���жϿ�����IRQ�ж�
    	break;
    default:;
    }
}


//===========================================================================
//�������ƣ�gpio_drive_strength
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)������PORTB|(0) ��ʾΪB��0�Žţ�
//       control���������ŵ��������������ű�����Ϊ�������ʱ��DSE=1��������������DSE=0��������
//                ��������
//���ܸ�Ҫ������������������ָ�����������������ĳ�������һ����mA��λ������������������5mA,��������
//        ��18mA����        �����ű�����Ϊ�������ʱ,�����ŵ����������������ã�ֻ��PTB0,PTB1,PTD6,
//        PTD7ͬʱ���и�����������������������,��Щ���ſ�����ֱ������LED���MOSFET�������볡Ч
//        ����ܣ����磬�ú���ֻ����������4�����š�
//===========================================================================
void gpio_drive_strength(uint_16 port_pin, uint_8 control)
{
	//�ֲ���������
	PORT_MemMapPtr port_ptr;    //����port_ptrΪPORT�ṹ������ָ��
	uint_8 port;
	uint_8 pin;
	gpio_port_pin_resolution(port_pin , &port , &pin);

	//���ݴ������port�����ֲ�����port_ptr��ֵ
	port_ptr = PORT_ARR[port];

    //���ݴ������control����������Ϊ����ߵ���������������
	BCLR(PORT_PCR_DSE_SHIFT,port_ptr->PCR[pin]);
	if (1 == control)
	    BSET(PORT_PCR_DSE_SHIFT,port_ptr->PCR[pin]);
	else
		BCLR(PORT_PCR_DSE_SHIFT,port_ptr->PCR[pin]);
}

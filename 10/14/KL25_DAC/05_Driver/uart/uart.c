//============================================================================
//�ļ����ƣ�uart.c
//���ܸ�Ҫ��uart�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2012-11-12   V1.0
//============================================================================
#include "uart.h"

//����1��2�ŵ�ַӳ��
static const UART_MemMapPtr UART_ARR[] = {UART1_BASE_PTR, UART2_BASE_PTR};

//��MCGIRCLKʱ��
static void MCGIRCLK_OutEnable(void);

//============================================================================
//����MCGIRCLKʱ�ӣ����ʱ��Ƶ����31.25Khz ~ 4Mhz
void MCGIRCLK_OutEnable(void)
{

	MCG_C1 |= MCG_C1_IRCLKEN_MASK|MCG_C1_IREFSTEN_MASK;
	MCG_SC |= MCG_SC_FCRDIV(0x0);  //�ڲ�4M���ٲο�ʱ�ӷ�Ƶ���ӣ�
	                              //�ɽ�ʱ�ӷ�Ƶ��31.25Khz ~ 4Mhz
	MCG_C4 |= MCG_C4_FCTRIM(0xA);
	MCG_C2 |= MCG_C2_IRCS_MASK;
	while (!(MCG_S & MCG_S_IRCST_MASK));
}

//============================================================================
//�������ƣ�uart_init
//���ܸ�Ҫ����ʼ��uartģ��                                                
//����˵����uartNo:���ںţ�UART_0��UART_1��UART_2 
//          sel_clk:ѡ�񴮿�0ʱ��Դ:MCGIRCLK  (4000Khz)
//                                 MCGPLL    (48000Khz)
//								   BUSCLK     (24000khz)
//          baud:�����ʣ�300��600��1200��2400��4800��9600��19200��115200...
//�������أ���
//˵���� ������ΪUART_0ʱ��sel_clkֻ��ѡ��MCGIRCLK��MCGPLL����ѡ���ڲ�ʱ��MCGIRCLK,
//��������С��19200�� ������ΪUART_1����UART_2ʱ��sel_clkֻ��ѡ��BUSCLK
//============================================================================
 void  uart_init (uint_8 uartNo,uint_32 sel_clk,uint_32 baud_rate) 
 {	  
	//�ֲ���������
	register uint_16 sbr;
	uint_8 temp;  
	uint_32 clk_Khz;
	UARTLP_MemMapPtr uartch1=UART0_BASE_PTR;//����uartch1ΪUARTLP_MemMapPtr�ṹ������ָ�� 
    UART_MemMapPtr uartch2;     //����uartch2ΪUART_MemMapPtr�ṹ������ָ�� 
    uartch2 = UART_ARR[uartNo-1]; //���UART1��2ģ����Ӧ�ڻ���ַ
	
	//���ݴ������uartNo�����ֲ�����uartch1��ֵ
	
	if(uartNo==0)
	{
		switch(sel_clk)
		{
		case MCGIRCLK:
			//���ò�ѡ��UART0ʱ��ԴMCGIRCLK
			MCGIRCLK_OutEnable();      //�����ڲ�����ʱ��	
			SIM_SOPT2 |= SIM_SOPT2_UART0SRC(0x3);  //UART0ѡ��MCGIRCLK=4000Khzʱ��Դ
			break;
	   
		case MCGPLL:
			SIM_SOPT2 |= SIM_SOPT2_UART0SRC(1);   //UART0ѡ��MCGFLLCLK_khz=48000Khzʱ��Դ
			SIM_SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK;    
			break;
		   
		default:
			break;
		}
		
		//���Ÿ���Ϊ���ڹ��ܲ����ô���ģ��ʱ��  	   
		PORTA_PCR14 = PORT_PCR_MUX(0x3);      //ʹ��UART0_TXD
		PORTA_PCR15 = PORT_PCR_MUX(0x3);      //ʹ��UART0_RXD	
		SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;    //��������0ʱ��
		
		//��ʱ�رմ���0��������չ���  
		uartch1->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK); 
	
		//����ʱ��Դѡ��ʱ��Ƶ��
		if(MCGIRCLK == sel_clk)
			clk_Khz = MCGIR_CLK_KHZ;
		else if (MCGPLL == sel_clk)
			clk_Khz = MCGPLL_CLK_KHZ;
   
		//���ô��ڹ���ģʽ:8λ��У��ģʽ
		sbr = (uint_16)((clk_Khz*1000)/(baud_rate * 16));
		temp = UART_BDH_REG(uartch1) & ~(UART_BDH_SBR(0x1F));
		UART_BDH_REG(uartch1) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
		UART_BDL_REG(uartch1) = (uint_8)(sbr & UART_BDL_SBR_MASK);

		//��ʼ�����ƼĴ��������־λ
		UART0_C4 = 0x0F;
		UART0_C1 = 0x00;
		UART0_C3 = 0x00;
		UART0_MA1 = 0x00;
		UART0_MA2 = 0x00;
		UART0_S1 |= 0x1F;
		UART0_S2 |= 0xC0;    
	   	
		//�������ͽ���
		uartch1->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);    
	}
	else
	{
		 switch (uartNo)
		       {
		       case UART_1:
		           PORTE_PCR0 = PORT_PCR_MUX(0x3);    //ʹ��UART1_TXD
		           PORTE_PCR1 = PORT_PCR_MUX(0x3);    //ʹ��UART1_RXD
		           SIM_SCGC4 |= SIM_SCGC4_UART1_MASK; //��������1ʱ��
		           break;
		       case UART_2:
		           PORTE_PCR22 = PORT_PCR_MUX(0x4); //ʹ��UART2_TXD
		           PORTE_PCR23 = PORT_PCR_MUX(0x4); //ʹ��UART2_RXD
		           SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;//��������2ʱ��
		           break;
		       default:
		    	   break;  //���δ��󣬷���
		       }
		       
		 //��ʱ�رմ���1��2��������չ���  
		uartch2->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);
		   	  
		//���ò�����,KL25����1��2ʱ��Ƶ��ֻ��ʹ�� Bus clock = 24M ����ʱ��
		//���ô��ڹ���ģʽ,8λ��У��ģʽ
		uartch2->C1 = 0;          
		sbr = (uint_16)((BUS_CLK_KHZ*1000)/(baud_rate * 16));
		temp = UART_BDH_REG(uartch2) & ~(UART_BDH_SBR(0x1F));
		UART_BDH_REG(uartch2) = temp |  UART_BDH_SBR(((sbr & 0x1F00) >> 8));
		UART_BDL_REG(uartch2) = (uint_8)(sbr & UART_BDL_SBR_MASK);
		           
		//��ʼ�����ƼĴ��������־λ
		uartch2->C1 = 0x00;
		uartch2->C3 = 0x00;
		uartch2->S1 = 0x1F;
		uartch2->S2 = 0x00;   	               
		//�������ͽ���
		uartch2->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);                           	
	}
 }
 //============================================================================
//�������ƣ�uart_send1
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2 
//          ch:Ҫ���͵��ֽ�
//�������أ�����ִ��״̬��0=��������0=�쳣��
//���ܸ�Ҫ�����з���1���ֽ�
 //============================================================================
uint_8 uart_send1(uint_8 uartNo, uint_8 ch)
{
    uint_32 t;       
	UARTLP_MemMapPtr uartch1=UART0_BASE_PTR; //��ȡUART0����ַ
    UART_MemMapPtr uartch2 = UART_ARR[uartNo-1]; //��ȡUART1����2����ַ
    
    for (t = 0; t < 0xFBBB; t++)//��ѯָ������
    {
        
    	if(0==uartNo)     //�ж�ʹ�õ��ĸ�����
    	{
			if ( (uartch1->S1) & UART_S1_TDRE_MASK )//�жϷ��ͻ������Ƿ�Ϊ��
			{
				uartch1->D = ch;   //��ȡ���ݲ�����
				break;             //����ѭ��
			}
    	}
    	else
    	{
			if ( (uartch2->S1) & UART_S1_TDRE_MASK )//�жϷ��ͻ������Ƿ�Ϊ��
			{
				uartch2->D = ch;   //��ȡ���ݲ�����
				break;             //����ѭ��
			}
    	}
        
    }//end for
    if (t >= 0xFBBB)
        return 1; //���ͳ�ʱ������ʧ��
    else
        return 0; //�ɹ�����
        
}

//============================================================================
//�������ƣ�uart_sendN
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2 
//          buff: ���ͻ�����
//          len:���ͳ���
//�������أ� ����ִ��״̬��0=������1=�쳣
//���ܸ�Ҫ������ ����n���ֽ�   
//============================================================================
uint_8 uart_sendN (uint_8 uartNo ,uint_16 len ,uint_8* buff)
{
    uint_16 i;
    for (i = 0; i < len; i++)
    {
        if (uart_send1(uartNo, buff[i])) //����һ���ֽ����ݣ�ʧ��������ѭ��
		{
        	break;        
		}
    }
    if (i < len)  
        return 1;   //����len���ֽڳ���
    else 
        return 0;   //����len���ֽڳɹ�
}

//============================================================================
//�������ƣ�uart_send_string
//����˵����uartNo:UARTģ���:UART_0��UART_1��UART_2 
//          buff:Ҫ���͵��ַ������׵�ַ
//�������أ� ����ִ��״̬��0=��������0=�쳣��
//���ܸ�Ҫ����ָ��UART�˿ڷ���һ����'\0'�������ַ���
//============================================================================
uint_8 uart_send_string(uint_8 uartNo, void *buff)
{
    uint_16 i = 0;
    uint_8 *buff_ptr = (uint_8 *)buff;    //����ָ��ָ��Ҫ�����ַ����׵�ַ
    for(i = 0; buff_ptr[i] != '\0'; i++)  //�����ַ�������ַ�
    {
        if (uart_send1(uartNo,buff_ptr[i]))//����ָ���Ӧ���ַ�
            return 1;  //����ʧ��
    }
    return 0;         //���ͳɹ�
}

//============================================================================
//�������ƣ�uart_re1
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2 
//          fp:���ճɹ���־��ָ��:*fp=0���ɹ����գ�*fp=1������ʧ��
//�������أ����շ����ֽ�
//���ܸ�Ҫ�����н���1���ֽ�
//============================================================================
uint_8 uart_re1 (uint_8 uartNo,uint_8 *fp)
{
    uint_32 t;
    uint_8  dat;
	UARTLP_MemMapPtr uartch1=UART0_BASE_PTR;    //��ȡUART0����ַ
    UART_MemMapPtr uartch2 = UART_ARR[uartNo-1];//��ȡUART1����2����ַ

    for (t = 0; t < 0xFBBB; t++)//��ѯָ������
    {
    	if(0==uartNo)  //�ж�ʹ�õ��ĸ�����
    	{
            //�жϽ��ջ������Ƿ���
            if ((uartch1->S1) & UART_S1_RDRF_MASK )
            {
                dat = uartch1->D; //��ȡ���� 
                *fp= 0;  //���ܳɹ�
                break;
            }
    	}
    	else
    	{
            //�жϽ��ջ������Ƿ���
            if ((uartch2->S1) & UART_S1_RDRF_MASK )
            {
                dat = uartch2->D; //��ȡ���� 
                *fp= 0;  //���ܳɹ�
                break;
            }
    	}

    }//end for
    if(t >= 0xFBBB) 
    {
        dat = 0xFF; 
        *fp = 1;    //δ�յ�����
    }
    return dat;    //���ؽ��յ�������
    
}

//============================================================================
//�������ƣ�uart_reN
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2                                                   
//          buff: ���ջ�����
//          len:���ճ���
//�������أ�����ִ��״̬ 0=����;��0=�쳣
//���ܸ�Ҫ������ ����n���ֽ�
//============================================================================
uint_8 uart_reN (uint_8 uartNo ,uint_16 len ,uint_8* buff)
{
    uint_16 i;
    uint_8 flag = 0;
    
    //�ж��Ƿ��ܽ�������
    for (i = 0; i < len && 0 == flag; i++)
    {
        buff[i] = uart_re1(uartNo, &flag); //��������
    }
    if (i < len)
        return 1; //����ʧ��
    else
        return 0; //���ճɹ�
}


//====���崮��IRQ�Ŷ�Ӧ��====
static uint_8 table_irq_uart[3] = {12, 13, 14};
//============================================================================
//�������ƣ�uart_enable_re_int
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2 
//�������أ���
//���ܸ�Ҫ�������ڽ����ж�
//============================================================================
void uart_enable_re_int(uint_8 uartNo)
{
	UARTLP_MemMapPtr uartch1=UART0_BASE_PTR;
    UART_MemMapPtr uartch2 = UART_ARR[uartNo-1];
    if(0==uartNo)   
      uartch1->C2 |= UART_C2_RIE_MASK;        //����UART�����ж�
    else 
      uartch2->C2 |= UART_C2_RIE_MASK;        //����UART�����ж�
    enable_irq(table_irq_uart[uartNo]);   //���жϿ�����IRQ�ж�
}

//============================================================================
//�������ƣ�uart_disable_re_int
//����˵����uartNo: ���ں� :UART_0��UART_1��UART_2 
//�������أ���
//���ܸ�Ҫ���ش��ڽ����ж�
//============================================================================
void uart_disable_re_int(uint_8 uartNo)
{
	UARTLP_MemMapPtr uartch1=UART0_BASE_PTR; 
    UART_MemMapPtr uartch2 = UART_ARR[uartNo-1];
    if(0==uartNo) 
	  uartch1->C2 &= ~UART_C2_RIE_MASK;               //��ֹUART�����ж�
    else 
      uartch2->C2 &= ~UART_C2_RIE_MASK;               //��ֹUART�����ж�	
	disable_irq(table_irq_uart[uartNo]);          //��ֹ�жϿ�����IRQ�ж�
}



 
 
 
 
 
 
 
 
 

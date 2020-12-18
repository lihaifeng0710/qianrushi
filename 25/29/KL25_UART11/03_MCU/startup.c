
#include "common.h"
#include "sysinit.h"

extern int main(void);

//�����ڲ�����
static void vector_init(void);
static void m_zero_fill_bss(void);
static void m_data_seg_init(void);
static void sys_pin_enable_port(void);


//���Ź�WDOG(COP)�궨��
#define WDOG_DISABLE() {SIM_COPC = 0x00u;}  //���ÿ��Ź�
//COPʹ��LPOʱ�ӣ�COP��2^10��LPOʱ�����ں���ʱ
#define WDOG_ENABLE() {SIM_COPC |= SIM_COPC_COPT_MASK;} //ʹ�ܿ��Ź�


// ϵͳ�ϵ���������
 void startup(void)
{
	 WDOG_DISABLE();       //���ÿ��Ź�
        //WDOG_ENABLE();        ʹ�ܿ��Ź�  
	vector_init();          //�����ж���������RAM
	m_zero_fill_bss ();     //����δ��ʼ��BSS���ݶ�
	m_data_seg_init ();     //��ROM�еĳ�ʼ�����ݿ�����RAM��
	sys_init();             //��ʼ��ϵͳʱ��
	sys_pin_enable_port();  //ʹ�ܶ˿�ʱ��
	main();                 //����������
	while(1);               //����ѭ����������������ѭ��������ִ�в�������䣩          
}

//-------------------------------------------------------------------------------

//�����ж�������
void vector_init(void)
{
	extern char __VECTOR_RAM[];
	extern char __vector_table[];
	uint_32 n;
	
	if (__VECTOR_RAM != __vector_table)
	{
	    for (n = 0; n < 0x410; n++)
	        __VECTOR_RAM[n] = __vector_table[n];
	}
	//Point the VTOR to the new copy of the vector table 
      SCB_VTOR=(uint_32)__VECTOR_RAM;
}

// ��ʼ��BSS��
void m_zero_fill_bss(void)
{
	extern char __START_BSS[];
    extern char __END_BSS[];

    uint_8 *bss_start = (uint_8 *)__START_BSS;
    uint_8 *bss_end   = (uint_8 *)__END_BSS;
    uint_32 n = bss_end - bss_start;
    
    while (n--)
    	*bss_start++ = 0;
}

//����ROM������RAM
void m_data_seg_init(void)
{
	extern char __START_DATA[];
	extern char __END_DATA[];
	extern char __START_DATA_ROM[];
	
	uint_8 *data_start = (uint_8 *)__START_DATA;
	uint_8 *data_end   = (uint_8 *)__END_DATA;
	uint_8 *data_rom_start = (uint_8 *)__START_DATA_ROM;
	uint_32 n = data_end - data_start;
	
	while (n--)
	    *data_start++ = *data_rom_start++;
}

//ʹ�ܶ˿�ʱ��
void sys_pin_enable_port(void)
{
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK
			  | SIM_SCGC5_PORTB_MASK
			  | SIM_SCGC5_PORTC_MASK
			  | SIM_SCGC5_PORTD_MASK
			  | SIM_SCGC5_PORTE_MASK; 
}

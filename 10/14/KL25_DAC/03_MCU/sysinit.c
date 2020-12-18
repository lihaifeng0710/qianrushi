#include "sysinit.h"

//===========================================================================
//�������ƣ�sys_init
//�������أ���
//����˵������ 
//���ܸ�Ҫ��(1)KL25��EXTAL(40)��XTAL(41)��8Mhz�ⲿ���񣬲���PLL/FLL���ʱ��Ƶ
//             ��48MHz,�ں�ʱ��48MHz������ʱ��24MHz���ڲ��ο�ʱ��4MHz��
//          (2)������ЩƵ�ʣ�sys_init.h����Ӧ�ĺ곣��������Թ����ʱʹ��
//===========================================================================
void sys_init(void)  
{
    uint_32 i = 0;
    uint_8 temp_reg = 0;

 //1.���ȴ�FEIģʽ���ɵ�FBEģʽ
    
    //C2= 0x1C����Ϊ���ǵĺ��İ��ϲ������ⲿ����Ϊ8Mhz�����ڸ�Ƶ�ʷ�Χ��
    //C2[RANGE]����Ϊ0b01��C2[HGO]��Ϊ1�����þ��������и������������Ϊ
    //����ʹ�õ��ⲿ�ο�ʱ��Դ�Ǿ�������C2[EREFS]����Ϊ1��
    MCG_C2 = (MCG_C2_RANGE0(1) | MCG_C2_EREFS0_MASK);
    //C1 = 0x90 ��C1[CLKS]����Ϊ2��b10���Ա�ѡ����Ϊϵͳʱ��Դ���ⲿ�ο�ʱ�ӡ�
    //C1[FRDIV]����Ϊ3'b011����Ӧ256��Ƶ,��Ϊ8MHz/256=31.25kHz����FLLҪ���
    //31.25kHz��39.0625 kHzƵ�ʷ�Χ�ڡ�C1[IREFS]���Ϊ0��ѡ���ⲿ�ο�ʱ�Ӻ�
    //�ⲿ����
    MCG_C1 = (MCG_C1_CLKS(2) | MCG_C1_FRDIV(3));
    //��Ҫ�ȵ�S[OSCINIT]����λ�ⲿ�������ʹ��
    for (i = 0 ; i < 20000 ; i++)
    {
        //���S[OSCINIT]��ѭ������֮ǰ����λ������ѭ��
        if (MCG_S & MCG_S_OSCINIT0_MASK) break;
    }
    //�ȴ��ο�ʱ��״̬λ��0
    for (i = 0 ; i < 2000 ; i++)
    {
        //���IREFST��ѭ������֮ǰ����0������ѭ��
        if (!(MCG_S & MCG_S_IREFST_MASK)) break;
    }
    //�ȴ�ʱ��״̬λ����ʾʱ��ԴΪ�ⲿ�ο�ʱ��
    for (i = 0 ; i < 2000 ; i++)
    {
        //���CLKST��ʾ�ⲿʱ�ӱ�ѡ����ѭ������֮ǰ������ѭ��
        if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x2) break;
    }
 //2.���ڴ���FBE״̬��ʹ��ʱ�Ӽ���������FBEֱ��ת��ΪPBEģʽ
    MCG_C6 |= MCG_C6_CME0_MASK;
    //����PLLΪ2��Ƶ
    MCG_C5 |= MCG_C5_PRDIV0(1); 
    //����MCG_C6 ������PLL��Ƶ���Ӳ���ʱ��PLL��PLLSλ����λ��ʱ��PLL��MCGOUTʱ��Դ��Ȼ���ⲿ�ο�ʱ��          
    temp_reg = MCG_C6; //�洢��ǰC6��ֵ����ΪCME0λ֮ǰ����λ�ˣ�
    temp_reg &= ~MCG_C6_VDIV0_MASK; //��VDIV��0
    temp_reg |= MCG_C6_PLLS_MASK | MCG_C6_VDIV0(0); // ����дֵ��VDIV ����ʱ��PLL
    MCG_C6 = temp_reg; // ����MCG_C6��ֵ
    // �ȴ�PLLST״̬λ����
    for (i = 0 ; i < 2000 ; i++)
    {
        //���PLLST��ѭ������֮ǰ����λ������ѭ��
        if (MCG_S & MCG_S_PLLST_MASK) break;
    }
    //�ȴ�LOCKλ����
    for (i = 0 ; i < 4000 ; i++)
    {
        //���LOCK��ѭ������֮ǰ����λ������ѭ��
        if (MCG_S & MCG_S_LOCK0_MASK) break;
    }
  //3.���ڴ���PBEģʽ�����PBEģʽת����PEEģʽ
    // ���ú���ʱ�ӷ�Ƶ��2��Ƶ
    //��������ʱ�ӷ�Ƶ��2��Ƶ (����ʱ�ӵ�ʱ��Դ�Ǻ���ʱ��)
    SIM_CLKDIV1 = (SIM_CLKDIV1_OUTDIV1(1) | SIM_CLKDIV1_OUTDIV4(1) );
    //��CLKS����CLKS��·��������ѡ��PLL��ΪMCGCLKOUT
    MCG_C1 &= ~MCG_C1_CLKS_MASK;
    // �ȴ�ʱ��״̬λ����
    for (i = 0 ; i < 2000 ; i++)
    {
        //���CLKST��ѭ������֮ǰ����3������ѭ��
        if (((MCG_S & MCG_S_CLKST_MASK) >> MCG_S_CLKST_SHIFT) == 0x3) break;
    }
  //4.���ڴ���PEEģʽ
}






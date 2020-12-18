//˵���������ļ����µ�Doc�ļ�����Readme.txt�ļ�
//============================================================================
#include "includes.h"    //������ͷ�ļ�

int main(void)
{
	//1. ����������ʹ�õı���
	uint_32  mRuncount;     //��ѭ��������
	VReference = 0;
	//2. �����ж�
	DISABLE_INTERRUPTS;
	//3. ��ʼ������ģ��
	light_init(RUN_LIGHT_BLUE,LIGHT_OFF);     //��ʼ����ɫRUN��
    uart_init (UART_TEST,BUSCLK,9600);                  //����1��ʼ��, ����ʱ��24000Khz,������9600
    uart_send_string(UART_TEST, "This is DAC Test!\r\n"); //��ӡ������Ϣ
    dac_init(1);                                        //DAC��ʼ����ѡ��ο���ѹVDDA=3.3V
	//4. ���йر�������ֵ
	mRuncount=0;            //��ѭ��������
	//5. ʹ��ģ���ж�
    uart_enable_re_int(UART_TEST); //ʹ�ܴ���1�����ж�
	//6. �����ж�
	ENABLE_INTERRUPTS;

    //������ѭ��
    //��ѭ����ʼ==================================================================
	for(;;)
	{
		mRuncount++;
		if (mRuncount > RUN_COUNTER_MAX)
		{
			mRuncount = 0;
			//ָʾ�Ƶ�������״̬�л�
		    //light_change(RUN_LIGHT_BLUE);  //��ɫ����ָʾ�ƣ�RUN_LIGHT_BLUE��״̬�仯

			//DAC������ת��		
			dac_convert(VReference);
			//VReference -= 50;
			//if(VReference <= 0) VReference = 4000;
		} // end_if		
		//���¼����û�����--------------------------------------------------------
	}//��ѭ��end_for
	//��ѭ������==================================================================
	return 0;
}

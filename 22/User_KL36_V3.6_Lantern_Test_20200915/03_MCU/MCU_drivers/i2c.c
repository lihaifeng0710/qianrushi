//=====================================================================
//�ļ����ƣ�i2c.c
//���ܸ�Ҫ��i2c�ײ���������Դ�ļ�
//������λ�����ݴ�ѧǶ��ʽϵͳ���������о���(sumcu.suda.edu.cn)
//��    ����2019-05-09  V2.0
//����оƬ��KL25��KL26��KL36
//=====================================================================
#include  "i2c.h"

static const I2C_MemMapPtr I2C_BASE_TABLE[2] = I2C_BASE_PTRS;
static const IRQn_Type I2C_IRQ_TABLE[2] = {I2C0_IRQn,I2C1_IRQn};

 //**********************����ӿں���************************************
 //=====================================================================
 //�������ƣ�i2c_init
 //���ܸ�Ҫ����ʼ��IICXģ�顣Ĭ��Ϊ100K.
 //����˵����No:ģ���,���ò����ɲμ�gec.h�ļ�
 //         Mode��ģʽ  1������     0���ӻ�
 //         address����ģ���ʼ����ַ    ��Χ(1~255)
 //         BaudRate��Ϊ�����ʣ��䵥λΪKb/s����ȡֵΪ25,50,75,100K
 //�������أ���
 //=====================================================================
void i2c_init(uint8_t No,uint8_t Mode,uint8_t address,uint8_t BaudRate)
{
	ModeSelect = Mode;
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	if(No == 0)
	{
		BSET(SIM_SCGC4_I2C0_SHIFT,SIM_SCGC4); //��ʱ����
		PORTB_PCR2 = PORT_PCR_MUX(0x2);      //ʹ��IIC0_SCL
		PORTB_PCR3 = PORT_PCR_MUX(0x2);      //ʹ��IIC0_SDA
	}
	else
	{
		BSET(SIM_SCGC4_I2C1_SHIFT,SIM_SCGC4); //��ʱ����
		PORTC_PCR1 = PORT_PCR_MUX(0x2);      //ʹ��IIC1_SCL
		PORTC_PCR2 = PORT_PCR_MUX(0x2);      //ʹ��IIC1_SDA
	}
	i2c_ptr->C1 = 0X00;   //��ʼ��C1
	i2c_ptr->FLT |= I2C_FLT_STOPF_MASK;//��ֹͣ��־λ
	i2c_ptr->S |= I2C_S_ARBL_MASK | I2C_S_IICIF_MASK; //��ʼ��S
    if(1 == ModeSelect)   //����ģʽ
    {
    	switch(BaudRate)
    	{
			case 25:
				i2c_ptr->F = 0x9f;
				break;
			case 50:
				i2c_ptr->F = 0x5f;
				break;
			case 75:
				i2c_ptr->F = 0x25;
				break;
			case 100:
				i2c_ptr->F = 0x1f;
				break;
			default:
				i2c_ptr->F = 0x1f;
				break;
    	}
        BSET(I2C_C1_IICEN_SHIFT,i2c_ptr->C1);//��i2c0ģ��ʹ��
    }
    else            //�ӻ�ģʽ
    {
    	i2c_ptr->A1 = address << 1;
        BSET(I2C_C1_IICEN_SHIFT,i2c_ptr->C1);//ʹ��I2Cģ��
        BCLR(I2C_C1_TX_SHIFT,i2c_ptr->C1);//TX = 0,MCU����Ϊ����ģʽ
        BCLR(I2C_C1_MST_SHIFT,i2c_ptr->C1);//MSTλ��1���0������Ϊ�ӻ�ģʽ
    }
}

//=====================================================================
//�������ƣ�  i2c_read1
//���ܸ�Ҫ��  ��ȡ1���ֽ�����
//����˵����  No:ģ��ţ����ò����ɲμ�gec.h�ļ�
//          slaveAddress:��ȡ��Ŀ���ַ
//          command�� ��ȡ���ȡֵ��ΧΪ0~255��
//                   ���޶�ȡ������ò�����0xFFFF
//          Data:�����յ���һ���ֽ�����
//�������أ�  1����ʾ��ȡʧ�ܣ�0����ȡ�ɹ�
//����˵��: �ú���Ϊ���⺯�������Ը��������ȡ����Ӧ��1���ֽڣ������ȡ2��
//         �������ֽ������ݣ���ʹ��I2C_readN������������ʹ��ѭ�����ô˺���
//=====================================================================
uint8_t i2c_read1(uint8_t No,uint8_t slaveAddress,uint16_t command,uint8_t *Data)
{      
	uint8_t temp;
	i2c_start(No);               //���Ϳ�ʼ�ź�
	if(command!=0xFFFF)
	{
		temp = (slaveAddress << 1) & 0xfe;
		i2c_write(No,temp);          //����ַ�ͷ���λ���͸��ӻ�
		if(i2c_wait(No) == 1)        //�ȴ����
			return 1;                    //ʧ��
		if(i2c_get_ack(No) == 1)     //�ж��Ƿ���ACK
			return 1;                    //���Ƿ�Ӧ���ź��򷵻�ʧ��

		command = (uint8_t)command;
		i2c_write(No,command);       //������͸��ӻ�
		if(i2c_wait(No) == 1)        //�ȴ����
			return 1;                    //ʧ��
		i2c_restart(No);             //���¿�ʼ
	}

	temp = (slaveAddress << 1) | 0x01;
	i2c_write(No,temp);  //����ַ�ͷ���λ���͸��ӻ�
	if(i2c_wait(No) == 1)        //�ȴ����
		return 1;                    //ʧ��
	if(i2c_get_ack(No) == 1)     //�ж��Ƿ���ACK
		return 1;                    //���Ƿ�Ӧ���ź��򷵻�ʧ��
	i2c_changeDir(No,0);         //�ı䷽��
	i2c_sendNACK(No);            //����NACK
	i2c_read(No);                //�ն��������¸����ݴ���
	if(i2c_wait(No) == 1)        //�ȴ����
		return 1;                    //ʧ��
	i2c_stop(No);                //����ֹͣ�ź�
	*Data = i2c_read(No);  //��ȡ���ݣ�������ɣ������ں����������ʱ
	return 0;
}

//=====================================================================
//�������ƣ�i2c_readN.
//����˵���� ��ȡN���ֽڣ�������N��СΪ2��
//���������� i2cNO:i2cģ��� �����ò����ɲμ�gec.h�ļ�
//          slaveAddress:��ȡ��Ŀ���ַ
//          command�� ��ȡ���ȡֵ��ΧΪ0~255��
//                   ���޶�ȡ������ò�����0xFFFF
//          Data����ŵ������׵�ַ
//          DataNum��Ҫ��ȡ���ֽ��������ڵ���2��
//�������أ� 1����ʾ��ȡʧ�ܣ�0����ȡ�ɹ�
//=====================================================================
uint8_t i2c_readN(uint8_t No,uint8_t slaveAddress,uint16_t command,uint8_t *Data, uint8_t DataNum)
{
	uint8_t i,temp;
	i2c_start(No);               //���Ϳ�ʼ�ź�
	if(command!=0xFFFF)
	{
		temp = (slaveAddress << 1) & 0xfe;
		i2c_write(No,temp);          //����ַ�ͷ���λ���͸��ӻ�
		if(i2c_wait(No) == 1)        //�ȴ����
		{
			return 1;
		}
		if(i2c_get_ack(No) == 1)     //�ж��Ƿ���ACK
		{
			return 1;
		}                                //���Ƿ�Ӧ���ź��򷵻�ʧ��

		command = (uint8_t)command;
		i2c_write(No,command);       //������͸��ӻ�
		if(i2c_wait(No) == 1)        //�ȴ����
			return 1;                //ʧ��
	                               //ʧ��
		i2c_Dly_ms(100);
		i2c_restart(No);             //��restart֮ǰ��������������ʱ
	}
	temp = (slaveAddress << 1) | 0x01;
	i2c_write(No,temp);          //����ַ�ͷ���λ���͸��ӻ�
	if(i2c_wait(No) == 1)        //�ȴ����
	{
		return 1; //ʧ��
	}
	if(i2c_get_ack(No) == 1)     //�ж��Ƿ���ACK
	{
		return 1; //ʧ��
	}
	i2c_changeDir(No,0);         //�ı䷽��
	i2c_sendACK(No);             //����Ӧ��λACK
	i2c_read(No);                //�ն��������¸����ݴ���
	if(i2c_wait(No) == 1)        //�ȴ����
	{
		return 1; //ʧ��
	}
	for(i = 0; i < DataNum-2; i++)
	{
		Data[i] =  i2c_read(No);
		if(i2c_wait(No) == 1)    //�ȴ����
		{
			return 1;//ʧ��
		}
	}
	i2c_sendNACK(No);            //���ͷ�Ӧ��λACK
	Data[i++] = i2c_read(No);
	if(i2c_wait(No) == 1)        //�ȴ����
	{
		return 1;
	}
	i2c_stop(No);                //����ֹͣ�ź�
	Data[i] = i2c_read(No);      //��ȡ���ݣ�������ɣ������ں����������ʱ
	return 0;
}

//=====================================================================
//�������ƣ� i2c_write1
//���ܸ�Ҫ�� ����1���ֽ�����
//����˵���� No:ģ��ţ����ò����ɲμ�gec.h�ļ�
//          slaveAddress������Ŀ��ĵ�ַ
//          Data:�����͵ĵ�1���ֽ�����
//          command:��ַ�����
//�������أ�  0���ɹ�����һ���ֽڣ�1������һ���ֽ�ʧ��
//����˵��:  1����ʾ����ʧ�ܣ�0�����ͳɹ�
//=====================================================================
uint8_t i2c_write1(uint8_t No, uint8_t slaveAddress, uint8_t Data,uint16_t command)
{
	i2c_start(No);               //���Ϳ�ʼ�ź�
	slaveAddress = (slaveAddress << 1) & 0xfe;
	i2c_write(No,slaveAddress);  //����ַ�ͷ���λ���͸��ӻ�
	if(i2c_wait(No) == 1)        //�ȴ����
		return 1;                    //ʧ��
	if(i2c_get_ack(No) == 1)     //�ж��Ƿ���ACK
		return 1;                    //���Ƿ�Ӧ���ź��򷵻�ʧ��
	if(0xFFFF != command)
	{
		i2c_write(No,command);  //����ַ�ͷ���λ���͸��ӻ�
		if(i2c_wait(No) == 1)        //�ȴ����
			return 1;                    //ʧ��
		if(i2c_get_ack(No) == 1)     //�ж��Ƿ���ACK
			return 1;
	}
	i2c_write(No,Data);          //����ַ�ͷ���λ���͸��ӻ�
	if(i2c_wait(No) == 1)        //�ȴ����
		return 1;                    //ʧ��
	i2c_stop(No);                //����ֹͣ�ź�
}

//=====================================================================
//�������ƣ� I2C_writeN
//���ܸ�Ҫ�� ����N���ֽ�����
//����˵���� No:ģ��ţ����ò����ɲμ�gec.h�ļ�
//          slaveAddress������Ŀ��ĵ�ַ
//          *Data:������N�ֽ������׵�ַ
//          DataNum�����͵��ֽ���N
//�������أ�  0���ɹ�����һ���ֽڣ�1������һ���ֽ�ʧ��
//����˵��: 1����ʾ����ʧ�ܣ�0�����ͳɹ�
//=====================================================================
uint8_t i2c_writeN(uint8_t No, uint8_t slaveAddress, uint8_t *Data, uint8_t DataNum)
{
	uint8_t i;
	i2c_start(No);               //���Ϳ�ʼ�ź�
	slaveAddress = (slaveAddress << 1) & 0xfe;
	i2c_write(No,slaveAddress);  //����ַ�ͷ���λ���͸��ӻ�
	if(i2c_wait(No) == 1)        //�ȴ����
		return 1;                    //ʧ��
	if(i2c_get_ack(No) == 1)     //�ж��Ƿ���ACK
		return 1;                    //���Ƿ�Ӧ���ź��򷵻�ʧ��
	for(i = 0; i < DataNum; i++)
	{
		i2c_write(No,Data[i]);   //����ַ�ͷ���λ���͸��ӻ�
		if(i2c_wait(No) == 1)    //�ȴ����
			return 1;                //ʧ��
	}
	i2c_stop(No);                //����ֹͣ�ź�
	return 0;                        //�ɹ�
}

//==============================================================================
//�������ƣ�i2c_enable_re_int.
//����˵������i2c��IRQ�жϡ�
//����������No:i2cģ��ţ����ò����ɲμ�gec.h�ļ�
//�������أ��ޡ�
//==============================================================================
void i2c_enable_re_int(uint8_t No)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	i2c_ptr->S |= I2C_S_IICIF_MASK;
	i2c_ptr->C1 |= I2C_C1_IICIE_MASK;
}

//==============================================================================
//�������ƣ�i2c_disable_re_int
//����˵�����ر�i2c��IRQ�жϡ�
//����������No:i2cģ��ţ����ò����ɲμ�gec.h�ļ�
//�������أ��ޡ�
//==============================================================================
void i2c_disable_re_int(uint8_t No)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	i2c_ptr->C1 &= ~I2C_C1_IICIE_MASK;
	disable_irq (I2C_IRQ_TABLE[No]);
}

//=====================================================================
//�������ƣ�i2c_clear_re_int
//����˵�������i2c�Ľ����жϱ�־��
//����������No:i2cģ��� �����ò����ɲμ�gec.h�ļ�
//�������أ��ޡ�
//=====================================================================
void i2c_clear_re_int(uint8_t No)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	i2c_ptr->S|=0x02;
}

//=====================================================================
//�������ƣ�wait
//���ܸ�Ҫ���ȴ����
//����˵����No:ģ���,���ò����ɲμ�gec.h�ļ�
//�������أ�1����ʾ��ʱ��0����ʾ����
//=====================================================================
 uint8_t i2c_wait(uint8_t No)
{
	uint16_t time=0;
	uint16_t time_out = 0xfffe;
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	while(BGET(I2C_S_IICIF_SHIFT,i2c_ptr->S) == 0)
	{
		time++;
		if(time > time_out)
			return 1;
	}
	BSET(I2C_S_IICIF_SHIFT,i2c_ptr->S);
	return 0;
}

//=====================================================================
//�������ƣ�i2c_read
//���ܸ�Ҫ����������
//����˵����No:ģ���,���ò����ɲμ�gec.h�ļ�
//�������أ��Ĵ����е�����
//=====================================================================
 uint8_t i2c_read(uint8_t No)
{
	uint8_t result;
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	result = i2c_ptr->D;
	return result;
}

//=====================================================================
//�������ƣ� i2c_write
//���ܸ�Ҫ�� ��������
//����˵���� No:ģ���,���ò����ɲμ�gec.h�ļ�
//          data��Ҫд�������
//�������أ� ��
//=====================================================================
void i2c_write(uint8_t No,uint8_t data)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	i2c_ptr->D = data;
}

//=====================================================================
//�������ƣ� i2c_stop
//���ܸ�Ҫ�� ֹͣ�ź�
//����˵���� No:ģ���,���ò����ɲμ�gec.h�ļ�
//�������أ� ��
//=====================================================================
void i2c_stop(uint8_t No)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	BCLR(I2C_C1_MST_SHIFT,i2c_ptr->C1); //�������ĳɴӻ�����ֹͣ�ź�
	BCLR(I2C_C1_TX_SHIFT,i2c_ptr->C1);  //��λ����ģʽ
}

//=====================================================================
//�������ƣ� i2c_start
//���ܸ�Ҫ�� ��ʼ�ź�
//����˵���� No:ģ���,���ò����ɲμ�gec.h�ļ�
//�������أ� ��
//=====================================================================
 void i2c_start(uint8_t No)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	BSET(I2C_C1_TX_SHIFT,i2c_ptr->C1);  //��λ����ģʽ
	BSET(I2C_C1_MST_SHIFT,i2c_ptr->C1); //�������ĳɴӻ�����ֹͣ�ź�
}

//=====================================================================
//�������ƣ� i2c_restart
//���ܸ�Ҫ�� ���¿�ʼ�ź�
//����˵���� No:ģ���,���ò����ɲμ�gec.h�ļ�
//�������أ� ��
//=====================================================================
void i2c_restart(uint8_t No)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	BSET(I2C_C1_TX_SHIFT,i2c_ptr->C1);  //��λ����ģʽ
	BSET(I2C_C1_RSTA_SHIFT,i2c_ptr->C1); //�������ĳɴӻ�����ֹͣ�ź�
}

//=====================================================================
//�������ƣ� i2c_sendACK
//���ܸ�Ҫ�� ����ACK
//����˵���� No:ģ���,���ò����ɲμ�gec.h�ļ�
//�������أ���
//=====================================================================
 void i2c_sendACK(uint8_t No)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	BCLR(I2C_C1_TXAK_SHIFT,i2c_ptr->C1);
}

//=====================================================================
//�������ƣ� i2c_sendNACK
//���ܸ�Ҫ�� ����NACK
//����˵���� No:ģ���,���ò����ɲμ�gec.h�ļ�
//�������أ���
//=====================================================================
void i2c_sendNACK(uint8_t No)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	BSET(I2C_C1_TXAK_SHIFT,i2c_ptr->C1);
}

//=====================================================================
//�������ƣ� i2c_changeDir
//���ܸ�Ҫ�� �ı䷽��
//����˵���� No:ģ���,���ò����ɲμ�gec.h�ļ�
//         direction: ���� 0�ǽ��գ�1�Ƿ���
//�������أ� ��
//=====================================================================
void i2c_changeDir(uint8_t No,uint8_t direction)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	i2c_ptr->C1 &= ~I2C_C1_TX_MASK;
	i2c_ptr->C1 |= I2C_C1_TX(direction);
}

//=====================================================================
//�������ƣ� i2c_get_ack
//���ܸ�Ҫ�� ��ȡӦ����߷�Ӧ���ź�
//����˵���� No:ģ���,���ò����ɲμ�gec.h�ļ�
//�������أ�0��Ӧ���źţ�1����Ӧ���ź�
//=====================================================================
 uint8_t i2c_get_ack(uint8_t No)
{
	I2C_MemMapPtr i2c_ptr = I2C_BASE_TABLE[No];
	uint8_t ack;
	ack = BGET(I2C_S_RXAK_SHIFT,i2c_ptr->S);
    return ack;
}
void i2c_Dly_ms(uint32_t ms)
{
    for(uint32_t i= 0; i < (6000*ms); i++) __asm("nop");
}
//============================================================================
//�������ƣ�enable_irq
//�������أ���
//����˵����irq��irq��, ����ģ����жϺŶ�����MKL25Z.h��
//���ܸ�Ҫ��ʹ��irq�ж� 
//============================================================================
void enable_irq (IRQn_Type irq)
{
	//ȷ��irq��Ϊ��Ч��irq��
	if (irq > 32)
		return;
	EnableIRQ(irq);
}

//============================================================================
//�������ƣ�disable_irq
//�������أ���      
//����˵����irq��irq��, ����ģ����жϺŶ�����MKL25Z.h��
//���ܸ�Ҫ����ֹirq�ж� 
//============================================================================
void disable_irq (IRQn_Type irq)
{
	//ȷ��irq��Ϊ��Ч��irq��
	if (irq > 32)
		return;
	DisableIRQ(irq);
}
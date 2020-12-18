#include "emuart.h"

//֡ͷΪ0xa5,0x06��֡βΪ0xb6,0x07
static uint8_t emuartFrameHead[2] = {0xa5,0x06};  //֡ͷ
static uint8_t emuartFrameTail[2] = {0xb6,0x07};  //֡β
static uint8_t emuartTerminStr[13] ="StOpUeMySeLf";  //uecom�ս���֡�ַ���
static uint8_t UART_NO=2;      //emuartʹ�õĴ���

//======================�ڲ���������====================================
//�ں������崦����ϸ˵��
void sendFrame(uint16_t length,uint8_t *data);
uint16_t crc16(uint8_t *ptr,uint16_t len);

//======================�ڲ�������������==================================

//=====================================================================
//�������ƣ�emuart_init
//�������أ� ��
//����˵���� uartNo��emuartʹ�õĴ��ڣ� baud��emuart�Ĳ����ʡ�
//���ܸ�Ҫ����ʼ��emuart
//���¼�¼��20180602��wb��
//=====================================================================
void emuart_init(uint8_t uartNo,uint32_t baud)
{
	uart_init(uartNo,baud);
	uart_enable_re_int(uartNo);
	UART_NO = uartNo;
}

//=====================================================================
//�������ƣ�emuart_send1
//�������أ� ��
//����˵���� a�������͵�һ���ֽ�����
//���ܸ�Ҫ��ͨ��emuart����һ���ֽ�����
//���¼�¼��20180602��wb��
//=====================================================================
void emuart_send1(uint8_t a)
{
	sendFrame(1,&a);
}

//=====================================================================
//�������ƣ�emuart_sendN
//�������أ� ��
//����˵���� len������������ĳ��ȣ�buff�����������ݻ�����
//���ܸ�Ҫ��ͨ��emuart����һ���ֽ�����
//���¼�¼��20180602��wb��
//=====================================================================
void emuart_sendN(uint8_t len ,uint8_t* buff)
{
	sendFrame(len,buff);
}

//=====================================================================
//�������ƣ�emuart_send_string
//�������أ� ��
//����˵���� buff�������͵��ַ���
//���ܸ�Ҫ��ͨ��emuart����һ���ַ���
//���¼�¼��20180602��wb��
//=====================================================================
void emuart_send_string(uint8_t * buff)
{
	uint16_t len=0;
	while(buff[len])len++;
	sendFrame(len,buff);
}

//===========================================================================
//�������ƣ�emuart_recv
//���ܸ�Ҫ���齨����֡��������֡���ݼ��뵽����֡�С�������Ӧ���������ж��С�
//����˵����ch�������жϽ��յ���һ���ֽڵĴ������ݣ�data����Ž��յ������ݡ�
//�������أ�0��δ���յ����ݣ���0�����յ�һ֡������֡�ɹ����ҷ���ֵΪ���յ������ݳ���
//��ע��ʮ����������֡��ʽ
//        ֡ͷ       + ���ݳ���         + ��Ч����   +CRCУ���� +  ֡β
//        emuartFrameHead(2�ֽ�)  +  len(2�ֽ�)   + ��Ч����(N�ֽ� N=len[0]*256+len[1])
//        +CRCУ��(2�ֽ�)+  emuartFrameTail(2�ֽ�)
//
//===========================================================================
uint16_t emuart_recv(uint8_t ch, uint8_t *data)
{
	static uint16_t index = 0;
	static uint16_t length = 0;
	static uint8_t markPos=0;
	uint16_t ret_val;
	uint16_t i;
	uint8_t CRC1[2];
	uint16_t crc;


	//(0)���ַ��Ƚϣ��ж������ַ��Ƿ�Ϊ�ս���֡�ַ�190226hzx��2/2��------------
//	if(ch == emuartTerminStr[markPos])
//	{
//		markPos++;  //�ַ�λ��+1
//		//�ж��Ƿ�ȶԳɹ�����ɹ����ս���֡����
//		if(markPos==12)
//		{
//			markPos=0;
//			index = 0;
//			length = 0;
//			ret_val = 0;
//			goto uecom_recv_exit;
//		}
//	}
//	else
//	{
//		//�ȶ�ʧ�ܣ����½��бȶ�
//		if(ch == emuartTerminStr[0])
//			markPos=1;
//		else
//			markPos=0;
//	}
	//-----------------------------------------------------------

	//��1����δ���յ����ݻ���δ����֡ͷ�����˳�������0  ֡ͷ����Ϊ�����ֽ�
	if((index == 0 && ch != emuartFrameHead[0]) ||
			(index == 1 && ch != emuartFrameHead[1]))
	{
		index = 0;
		length = 0;
		ret_val = 0;     //�������ݴ���
		goto uecom_recv_exit;
	}
	//��2����ȷ���յ���֡ͷ������ִ�У������ݴ���data����
	data[index++] = ch;
	//��3������ȡ�����ĸ�����ʱ�������Ч���ݳ���
	if(index == 4)
	{
		length = ((uint16_t)data[2]<<8) + data[3];
	}

	//��4��������յ������ݴﵽһ֡���ȣ�֡����=��Ч���ݳ���+8��������CRCУ�飬���У��ͨ�����������ݵĴ���
	if(length != 0 && index >= length+8)
	{
		//��4.1������Ч���ݽ���CRCУ��
		crc = crc16(data+4,length);
		CRC1[0] =(uint8_t)( (crc>>8)&0xff);
		CRC1[1] = crc&0xff;
		//��4.2����δ��ȡ��֡β��CRCУ������������0
		if(data[index-2]!=emuartFrameTail[0] || data[index-1]!= emuartFrameTail[1]//δ����֡β
||	CRC1[0] != data[index-4] || CRC1[1] != data[index-3])//CRC�������
		{
			//������
			index = 0;
			length = 0;
			ret_val = 0;
			goto uecom_recv_exit;
		}
		//��4.3����ǰ4���ֽ��Ƴ�buf���飬��buf����ȫΪ��Ч���ݣ���������Ч����
		for(i=0;i<length;i++)
		{
			data[i] = data[i+4];
		}
		index = 0;
		ret_val = length; //������Ч���ݳ���
		data[length] = 0; //�����鳤��Ϊ0
		//��4.4���յ���������Ϊ��λ����Ѱemuart�豸���ַ������������Ӧ
		if(length == 21 &&
			!strcmp(data,"[Are you an emuart??]"))
		{
			emuart_send_string("[Yes,I am an emuart!!]");
			ret_val = 0;
		}
		length = 0; //����Ч���ݳ���Ϊ0
		goto uecom_recv_exit;
	}
	ret_val = 0;
uecom_recv_exit:
    return ret_val;
}

//======����Ϊ�ڲ�����====================================================
//=====================================================================
//�������ƣ�sendFrame
//�������أ� ��
//����˵���� length�����������ݵĳ��ȣ�data�����������ݻ�������
//���ܸ�Ҫ��ͨ��emuart����ָ�����ȵ��ֽ����顣
//���¼�¼��20180602��wb��
//=====================================================================
void sendFrame(uint16_t length,uint8_t *data)
{
	uint16_t crc,len;
	//����õ�CRCУ����
	crc = crc16(data,length);
	//����֡ͷ
	uart_send1(UART_NO,emuartFrameHead[0]);
	uart_send1(UART_NO,emuartFrameHead[1]);
	//����֡��
	uart_send1(UART_NO,length>>8);
	uart_send1(UART_NO,length);
	//����֡����
	uart_sendN(UART_NO,length,data);
    //����У����
	uart_send1(UART_NO,crc>>8);
	uart_send1(UART_NO,crc);
	//����֡β
	uart_send1(UART_NO,emuartFrameTail[0]);
	uart_send1(UART_NO,emuartFrameTail[1]);
}



//=====================================================================
//�������ƣ�crc16
//���ܸ�Ҫ�������ݽ���16λ��CRCУ�飬����У���Ľ��ֵ
//����˵����ptr:��ҪУ������ݻ�����
//      len:��Ҫ��������ݳ���
//�������أ�����õ���У��ֵ
//=====================================================================
uint16_t crc16(uint8_t *ptr,uint16_t len)
{
	uint16_t i,j,tmp,crc16;

	crc16 = 0xffff;
	for(i = 0;i < len;i++)
	{
		crc16 = ptr[i]^crc16;
		for(j = 0;j< 8;j++)
		{
			tmp = crc16 & 0x0001;
			crc16 = crc16>>1;
			if(tmp)
				crc16 = crc16^0xa001;
		}
	}
	return crc16;
}

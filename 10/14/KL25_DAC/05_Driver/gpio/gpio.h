//===========================================================================
//�ļ����ƣ�gpio.h
//���ܸ�Ҫ��GPIO�ײ���������ͷ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2014-8-11
//��ע��
//   (1)KL25�������Ͽɹ��û�ʹ�õ�GPIO����,��61��:
//      PTA:1-2��4-5��12~17
//      PTB:0-3��8~11��16~19
//      PTC:0~13��16~17
//      PTD:0~7
//      PTE:0-5��20~25��29~31
//   (2)����GPIO���ж�
//      PTA��PTD�����ž���GPIO���жϹ��ܣ��ֱ���46��47���ж�������
//   (3)�����������Ŷ����и��ù��ܣ��κ�ʱ��ֻ��ʹ������һ�ֹ���
//===========================================================================

#ifndef _GPIO_H       //��ֹ�ظ����壨gpio_H  ��ͷ)
#define _GPIO_H

#include "common.h"   //��������Ҫ��ͷ�ļ�

// �˿ںŵ�ַƫ�����궨��
#define PORTA    (0<<8)
#define PORTB    (1<<8)
#define PORTC    (2<<8)
#define PORTD    (3<<8)
#define PORTE    (4<<8)
//���ŷ���궨��
#define GPIO_IN      0
#define GPIO_OUTPUT  1
//�����ж����ͺ궨��
#define LowLevel        8    //�͵�ƽ����
#define HighLevel       12   //�ߵ�ƽ����
#define RisingEdge      9    //�����ش���
#define FallingEdge     10   //�½��ش���
#define DoubleEdge      11   //˫���ش���


//===========================================================================
//�������ƣ�gpio_init
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PORTB)|(5) ��ʾΪB��5�Žţ�
//          dir�����ŷ���0=���룬1=���,�������ŷ���궨�壩
//          state���˿����ų�ʼ״̬��0=�͵�ƽ��1=�ߵ�ƽ��
//���ܸ�Ҫ����ʼ��ָ���˿�������ΪGPIO���Ź��ܣ�������Ϊ�������������������
//          ��ָ����ʼ״̬�ǵ͵�ƽ��ߵ�ƽ
//===========================================================================
void gpio_init(uint_16 port_pin, uint_8 dir, uint_8 state);

//===========================================================================
//�������ƣ�gpio_set
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PORTB)|(5) ��ʾΪB��5�Žţ�
//          state��ϣ�����õĶ˿�����״̬��0=�͵�ƽ��1=�ߵ�ƽ��
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ���ʱ���������趨����״̬
//===========================================================================
void gpio_set(uint_16 port_pin, uint_8 state);

//===========================================================================
//�������ƣ�gpio_get
//�������أ�ָ���˿����ŵ�״̬��1��0��
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PORTB)|(5) ��ʾΪB��5�Žţ�
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ����������ȡָ������״̬
//===========================================================================
uint_8 gpio_get(uint_16 port_pin);

//===========================================================================
//�������ƣ�gpio_reverse
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PORTB)|(5) ��ʾΪB��5�Žţ�
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ���ʱ����������ת����״̬
//===========================================================================
void gpio_reverse(uint_16 port_pin);

//===========================================================================
//�������ƣ�gpio_pull
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PORTB)|(5) ��ʾΪB��5�Žţ�
//          pullselect������/������0=������1=������
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ��������������������/����
//===========================================================================
void gpio_pull(uint_16 port_pin, uint_8 pullselect);


//===========================================================================
//�������ƣ�gpio_enable_int
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PORTB)|(5) ��ʾΪB��5�Žţ�
//          irqtype�������ж����ͣ��ɺ궨��������ٴ��о����£�
//                  LowLevel        8    �͵�ƽ����
//                  HighLevel       12   �ߵ�ƽ����
//                  RisingEdge      9    �����ش���
//                  FallingEdge     10   �½��ش���
//                  DoubleEdge      11   ˫���ش���
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ�����������������жϣ���
//          �����жϴ���������
//ע    �⣺KW01оƬ��ֻ��PTA��PTC��PTD�ھ���GPIO���жϹ���
//===========================================================================
void gpio_enable_int(uint_16 port_pin,uint_8 irqtype);

//===========================================================================
//�������ƣ�gpio_disable_int
//�������أ���
//����˵����port_pin��(�˿ں�)|(���ź�)���磺(PORTB)|(5) ��ʾΪB��5�Žţ�
//���ܸ�Ҫ����ָ���˿����ű�����ΪGPIO������Ϊ����ʱ���������ر������ж�
//ע    �⣺KW01оƬ��ֻ��PTA��PTC��PTD�ھ���GPIO���жϹ���
//===========================================================================
void gpio_disable_int(uint_16 port_pin);


#endif     //��ֹ�ظ����壨gpio_H  ��β)


//===========================================================================
//������
//��1�����ǿ�����Դ���룬�ڱ������ṩ��Ӳ��ϵͳ����ͨ������Ϸ��׸���ᣬ����֮����
//     ��ӭָ����
//��2������ʹ�÷Ǳ�����Ӳ��ϵͳ���û�����ֲ����ʱ������ϸ�����Լ���Ӳ��ƥ�䡣
//
//���ݴ�ѧ��˼����Ƕ��ʽ���ģ����ݻ�����Ϣ�Ƽ����޹�˾��
//������ѯ��0512-65214835  http://sumcu.suda.edu.cn
//ҵ����ѯ��0512-87661670,18915522016  http://www.hxtek.com.cn
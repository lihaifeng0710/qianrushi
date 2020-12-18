#define GLOBLE_VAR
#include "includes.h"      
int main(void)
{
    
    uint8_t  mFlag;          
    uint8_t  mSec;	         
    DISABLE_INTERRUPTS;
    wdog_stop();
    mFlag='A';        
   	gTime[0] = 0;       //ʱ
   	gTime[1] = 0;	  	//��
   	gTime[2] = 0;	  	//��
   	mSec = gTime[2];	//��ס��ǰ���ֵ

    //��1.5���û�����ģ���ʼ��
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);   
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);  
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);  
    timer_init(TIMER_USER,20);   //����TIMER_USERΪ20ms�ж�
	uart_init(UART_User,115200);              
    
    //��1.6��ʹ��ģ���ж�
    uart_enable_re_int(UART_User);
    //��1.6��ʹ��ģ���ж�

    timer_enable_int(TIMER_USER);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;
    for(;;)    
    {

		 if(temp=='0')//00
        {
			__asm ("NOP");
			if (gTime[2] == mSec)   continue;
			mSec=gTime[2];
			if (mFlag=='A')   
			{
				gpio_set(LIGHT_GREEN,LIGHT_OFF);  
				gpio_set(LIGHT_RED,LIGHT_OFF); 
				gpio_set(LIGHT_BLUE,LIGHT_ON);   
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("���ƣ���\n");             
				mFlag='L';                        
			}
			else                   
			{   gpio_set(LIGHT_GREEN,LIGHT_OFF);  
				gpio_set(LIGHT_RED,LIGHT_OFF);  
				gpio_set(LIGHT_BLUE,LIGHT_OFF);  
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("���ƣ���\n");             
				mFlag='A';                       
			}
		}
			
		if(temp=='1')
        {
            __asm ("NOP");
			if (gTime[2] == mSec)   continue;
			mSec=gTime[2];
			if (mFlag=='A')   
			{	
				gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				gpio_set(LIGHT_RED,LIGHT_ON);   
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("��ƣ���\n");             
				mFlag='L';                        
			}
			else                   
			{   gpio_set(LIGHT_GREEN,LIGHT_OFF);
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				gpio_set(LIGHT_RED,LIGHT_OFF);  
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("��ƣ���\n");             
				mFlag='A';                       
			}
        }

		 if(temp=='2')
        {
            __asm ("NOP");
			if (gTime[2] == mSec)   continue;
			mSec=gTime[2];
			if (mFlag=='A')   
			{
				gpio_set(LIGHT_BLUE,LIGHT_OFF);
				gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_ON);   
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("���ƣ���\n");             
				mFlag='L';                        
			}
			else                   
			{   gpio_set(LIGHT_BLUE,LIGHT_OFF);
				gpio_set(LIGHT_RED,LIGHT_OFF);
				gpio_set(LIGHT_GREEN,LIGHT_OFF);  
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("���ƣ���\n");             
				mFlag='A';                       
			}
        }
		if(temp=='3')
        {
              __asm ("NOP");
			if (gTime[2] == mSec)   continue;
			mSec=gTime[2];
			if (mFlag=='A')   
			{
				gpio_set(LIGHT_GREEN,LIGHT_OFF); 
				gpio_set(LIGHT_RED,LIGHT_OFF); 
				gpio_set(LIGHT_BLUE,LIGHT_ON);   
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("���ƣ���\n");             
				mFlag='L';                        
			}
			else                   
			{   gpio_set(LIGHT_GREEN,LIGHT_OFF);    
				gpio_set(LIGHT_BLUE,LIGHT_OFF);  
				gpio_set(LIGHT_RED,LIGHT_ON);  
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("��ƣ���\n");             
				mFlag='A';                       
			}
        }  

    }     
    
}




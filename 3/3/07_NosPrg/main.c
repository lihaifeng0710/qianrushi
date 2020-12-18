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
    gpio_init(C0,GPIO_INPUT,LIGHT_OFF);  
    gpio_init(C1,GPIO_INPUT,LIGHT_OFF);  

    timer_init(TIMER_USER,20);   //����TIMER_USERΪ20ms�ж�
    //��1.6��ʹ��ģ���ж�

    timer_enable_int(TIMER_USER);
    //��1.7�������䡿�����ж�
    ENABLE_INTERRUPTS;
    for(;;)    
    {

		 if(gpio_get(C0)==0&&gpio_get(C1)==0)//00
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
			//gTime[2] == mSec||gTime[2]==( mSec+1)%60||gTime[2]==( mSec+2)%60
		if(gpio_get(C0)==1&&gpio_get(C1)==0)//01
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

		 if(gpio_get(C0)==0&&gpio_get(C1)==1)//10
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
		if(gpio_get(C0)==1&&gpio_get(C1)==1)//11
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




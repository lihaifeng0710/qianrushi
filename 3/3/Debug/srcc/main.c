#define GLOBLE_VAR
#include "includes.h"      
int main(void)
{
    
    uint8_t  mFlag;          
    uint8_t  mSec;	         
    DISABLE_INTERRUPTS;
    wdog_stop();
    mFlag='A';        
   	gTime[0] = 0;       //时
   	gTime[1] = 0;	  	//分
   	gTime[2] = 0;	  	//秒
   	mSec = gTime[2];	//记住当前秒的值

    //（1.5）用户外设模块初始化
    gpio_init(LIGHT_BLUE,GPIO_OUTPUT,LIGHT_OFF);   
    gpio_init(LIGHT_RED,GPIO_OUTPUT,LIGHT_OFF);  
    gpio_init(LIGHT_GREEN,GPIO_OUTPUT,LIGHT_OFF);  
    gpio_init(C0,GPIO_INPUT,LIGHT_OFF);  
    gpio_init(C1,GPIO_INPUT,LIGHT_OFF);  

    timer_init(TIMER_USER,20);   //设置TIMER_USER为20ms中断
    //（1.6）使能模块中断

    timer_enable_int(TIMER_USER);
    //（1.7）【不变】开总中断
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
				gpio_set(LIGHT_BLUE,LIGHT_ON);   
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("蓝灯：亮\n");             
				mFlag='L';                        
			}
			else                   
			{            
				gpio_set(LIGHT_BLUE,LIGHT_OFF);  
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("蓝灯：暗\n");             
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
				gpio_set(LIGHT_RED,LIGHT_ON);   
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("红灯：亮\n");             
				mFlag='L';                        
			}
			else                   
			{            
				gpio_set(LIGHT_BLUE,LIGHT_OFF);  
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("红灯：暗\n");             
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
				gpio_set(LIGHT_GREEN,LIGHT_ON);   
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("蓝灯：亮\n");             
				mFlag='L';                        
			}
			else                   
			{            
				gpio_set(LIGHT_GREEN,LIGHT_OFF);  
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("蓝灯：暗\n");             
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
				gpio_set(LIGHT_RED,LIGHT_OFF); 
				gpio_set(LIGHT_BLUE,LIGHT_ON);   
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("蓝灯：亮\n");             
				mFlag='L';                        
			}
			else                   
			{            
				gpio_set(LIGHT_BLUE,LIGHT_OFF);  
				gpio_set(LIGHT_RED,LIGHT_ON);  
				printf("%d:%d:%d",gTime[0],gTime[1],gTime[2]);
				printf("红灯：亮\n");             
				mFlag='A';                       
			}
        }  
    





    }     
    
}




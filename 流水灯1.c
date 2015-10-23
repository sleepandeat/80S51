#include<reg51.h>
#include<intrins.h>
#define LED P2
sbit K1=P1^1;
sbit K2=P1^2;   
unsigned int i;
void Delay(unsigned int n);

unsigned char KeyValue=0;
/*------------------------------------------------
                    定时器初始化子程序
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  //使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响		     
 TH0=(65536-500)/256;		  //重新赋值 12M晶振计算，指令周期1uS，
 TL0=(65536-500)%256;   
 EA=1;            //总中断打开
 ET0=1;           //定时器中断打开
 TR0=1;           //定时器开关打开
}
/*------------------------------------------------
                    主程序
------------------------------------------------*/
main()
{
 	LED=0XFE;
	Init_Timer0();
	while(1)
	{					 
		if(i==500)
		{			 
			if(KeyValue)
			{
				
					LED=_cror_(LED,1);									    
					i=0;
												   
			}
			else 
			{
				
				LED=_crol_(LED,1);
				
				i=0;
				 
			}
			
		}

			
	}
}		


/*------------------------------------------------
                 定时器中断子程序
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 using 1
{
 TH0=(65536-500)/256;		  //重新赋值 12M晶振计算，指令周期1uS，
 TL0=(65536-500)%256;         //半个周期500uS，即定时500次
 i++;
}



void Delay(unsigned int n)   //延时50us误差 0us
{
    unsigned char a,b;
		for(;n>0;n--)
		{
    	for(b=1;b>0;b--)
        for(a=22;a>0;a--);
		}
}
void key()
{			
	if(K1==0)
	{
		Delay(2000);	
		if(K1==0)
        {
			KeyValue=0;									    
			while(!K1);		
		}									   
	}	
	else if(K2==0)
	{
		Delay(2000);	
		if(K2==0)
           {
				KeyValue=1;	
				while(!K2);
				
			}
			
			
	}
}

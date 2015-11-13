/*-----------------------------------------------
名称：蜂鸣器模拟警报声
公司：南京爱思电子
编写：rantg
日期：2012.3
内容：蜂鸣器模拟警报声
------------------------------------------------*/
#include <reg52.h>

sbit SPK = P1^7;    //定义喇叭端口

void DelayUs2x(unsigned char t);//函数声明 
void DelayMs(unsigned char t);

/*------------------------------------------------
                    主函数
------------------------------------------------*/
main()
{
	unsigned int i;
	
	while(1)
	{
		for(i = 0;i < 500;i++)
		{
			DelayUs2x(200); 
			DelayUs2x(200); 
			SPK = !SPK;
		}
		for(i = 0;i < 500;i++)
		{
			DelayMs(1);  
			SPK = !SPK;
		}
	}
}

/*------------------------------------------------
 				uS延时函数
------------------------------------------------*/
void DelayUs2x(unsigned char t)
{   
	while(--t);
}

/*------------------------------------------------
				mS延时函数
------------------------------------------------*/
void DelayMs(unsigned char t)
{     
	while(t--)
	{
		//延时约1mS
		DelayUs2x(245);
		DelayUs2x(245);
	}
}

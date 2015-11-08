#include <reg51.h>
unsigned  int Temp;
unsigned  char Counter;
unsigned  char  code  LED_seg[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};    //段选代码
unsigned  char  code  LED_bit[6]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};    //位选代码
unsigned  char  Disp_Date[5];  //段码数字暂存

void Delay (unsigned int);
void Time();

//主函数
void main ()
{
    unsigned char i;
	Temp=0;
	Counter=0;
	Time();
	while (1)
	{
	    Disp_Date[0]=Temp%10;          	//个位
	    Disp_Date[1]=(Temp/10)%10;	    //十位
	    Disp_Date[2]=(Temp/100)%10; 	//百位
	    Disp_Date[3]=(Temp/1000)%10;	//千位
	    Disp_Date[4]=(Temp/10000)%10;	//万位
		for (i=0;i<5;i++)
		{
		    P0=LED_bit[i];    //位选定
		    P2=LED_seg[Disp_Date[i]];    //段码显示
			Delay (5);    //延时5ms
			P0=0xff;    //擦黑   ！！(共阴极)！！
		}
	}
}
  
//定时器程序
void Time()
{
    TMOD=0x01;    //定时器采用工作方式1
	TH0=(65536-54253)/256;
	TL0=(65536-54253)%256;    //设定定时器初值
	EA=1;    //打开总中断
	ET0=1;    //打开定时器0中断
	TR0=1;    //启动定时器0
}

//定时器中断响应程序
void Time_0()interrupt 1 using 1
{
    TH0=(65536-54253)/256;
	TL0=(65536-54253)%256;    //定时器设定初值
	Counter++;
	if(Counter==20)    //1S的时间
	{
	    Temp++;
		Counter=0;
	}
}


//延时程序
void Delay (unsigned int x)
{
    unsigned int y;
	for (x;x>0;x--)
	    for (y=110;y>0;y--);
}

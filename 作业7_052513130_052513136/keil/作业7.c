#include <reg51.h>
unsigned  int Temp;
unsigned  char Counter;
unsigned  char  code  LED_seg[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};    //��ѡ����
unsigned  char  code  LED_bit[6]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf};    //λѡ����
unsigned  char  Disp_Date[5];  //���������ݴ�

void Delay (unsigned int);
void Time();

//������
void main ()
{
    unsigned char i;
	Temp=0;
	Counter=0;
	Time();
	while (1)
	{
	    Disp_Date[0]=Temp%10;          	//��λ
	    Disp_Date[1]=(Temp/10)%10;	    //ʮλ
	    Disp_Date[2]=(Temp/100)%10; 	//��λ
	    Disp_Date[3]=(Temp/1000)%10;	//ǧλ
	    Disp_Date[4]=(Temp/10000)%10;	//��λ
		for (i=0;i<5;i++)
		{
		    P0=LED_bit[i];    //λѡ��
		    P2=LED_seg[Disp_Date[i]];    //������ʾ
			Delay (5);    //��ʱ5ms
			P0=0xff;    //����   ����(������)����
		}
	}
}
  
//��ʱ������
void Time()
{
    TMOD=0x01;    //��ʱ�����ù�����ʽ1
	TH0=(65536-54253)/256;
	TL0=(65536-54253)%256;    //�趨��ʱ����ֵ
	EA=1;    //�����ж�
	ET0=1;    //�򿪶�ʱ��0�ж�
	TR0=1;    //������ʱ��0
}

//��ʱ���ж���Ӧ����
void Time_0()interrupt 1 using 1
{
    TH0=(65536-54253)/256;
	TL0=(65536-54253)%256;    //��ʱ���趨��ֵ
	Counter++;
	if(Counter==20)    //1S��ʱ��
	{
	    Temp++;
		Counter=0;
	}
}


//��ʱ����
void Delay (unsigned int x)
{
    unsigned int y;
	for (x;x>0;x--)
	    for (y=110;y>0;y--);
}

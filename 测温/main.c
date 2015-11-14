/*-----------------------------------------------
���ƣ�DS18b20�¶ȼ��1602��ʾ
��˾���Ͼ���˼����
��д��rantg	
���ڣ�2012.3
���ݣ�DS18b20����¶���1602��ʾ
------------------------------------------------*/

#include<reg52.h> 
#include<stdio.h>
#include "18b20.h"
#include "1602.h"
#include "delay.h"

bit ReadTempFlag;//�����ʱ���־

void Init_Timer0(void);//��ʱ����ʼ��

/*------------------------------------------------
                    ������
------------------------------------------------*/
void main (void)
{                  
	unsigned int temp;
	float temperature;
	char displaytemp[16];//������ʾ������ʱ�洢����
	
	LCD_Init();           //��ʼ��Һ��
	DelayMs(20);          //��ʱ�������ȶ�
	LCD_Clear();          //����
	Init_Timer0();
	LCD_Write_String(0,0," www.nj-ices.com");
	LCD_Write_Char(14,1,'C'); 	//д���ַ�C

	while (1)         //��ѭ��
	{
		if(ReadTempFlag==1)
		{
			ReadTempFlag = 0;
			temp = ReadTemperature();
			
			temperature = (float)temp*0.0625;
			sprintf(displaytemp,"Temp  % 7.3f",temperature);//��ӡ�¶�ֵ
			LCD_Write_String(0,1,displaytemp);//��ʾ�ڶ���
		}	
	}
}

/*------------------------------------------------
                    ��ʱ����ʼ���ӳ���
------------------------------------------------*/
void Init_Timer0(void)
{
	TMOD |= 0x01;	  //ʹ��ģʽ1��16λ��ʱ����ʹ��"|"���ſ�����ʹ�ö����ʱ��ʱ����Ӱ��		     
	TH0 = (65536-2000)/256;		  
	TL0 = (65536-2000)%256;
	EA = 1;            //���жϴ�
	ET0 = 1;           //��ʱ���жϴ�
	TR0 = 1;           //��ʱ�����ش�
}
/*------------------------------------------------
                 ��ʱ���ж��ӳ���
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{
	static unsigned int num;
	TH0 = (65536-2000)/256;		  //���¸�ֵ 2ms
	TL0 = (65536-2000)%256;	
	num++;
	if(300 == num)        
	{
		num = 0;
		ReadTempFlag = 1; //����־λ��1
	}
}



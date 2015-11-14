#include "1602.h"
#include "delay.h"

sbit LCM_RS = P1^3;         /*�Ĵ���ѡ��*/
sbit LCM_E = P1^4;          /*��дʹ�ܿ���*/

/*------------------------------------------------
              д�������
------------------------------------------------*/
void LCD_Write_Com(unsigned char com) 
{  
	LCM_RS = 0;
	P0 = com;
	DelayMs(5);
	LCM_E = 1;
	DelayMs(5);
	LCM_E = 0;
}

/*------------------------------------------------
              д�����ݺ���
------------------------------------------------*/
void LCD_Write_Data(unsigned char Data) 
{ 
	LCM_RS = 1;
	P0 = Data;
	DelayMs(5);
	LCM_E = 1;
	DelayMs(5);
	LCM_E = 0;;
}

/*------------------------------------------------
                ��������
------------------------------------------------*/
void LCD_Clear(void) 
{ 
	LCD_Write_Com(0x01); 
	DelayMs(5);
}

/*------------------------------------------------
              д���ַ�����
------------------------------------------------*/
void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data) 
{     
	if (y == 0) 
	{     
		LCD_Write_Com(0x80 + x);     
	}    
	else 
	{     
		LCD_Write_Com(0xC0 + x);     
	}        
	LCD_Write_Data( Data);  
}

/*------------------------------------------------
              д���ַ�������
------------------------------------------------*/
void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s) 
{     
	if (0 == y) 
	{     
		LCD_Write_Com(0x80 + x);     //��ʾ��һ��
	}
	else 
	{      
		LCD_Write_Com(0xC0 + x);      //��ʾ�ڶ���
	}
	        
	while (*s) 
	{     
		LCD_Write_Data(*s);     
		s++;     
	}
}

/*------------------------------------------------
              ��ʼ������
------------------------------------------------*/
void LCD_Init(void) 
{
	LCM_E = 0;
	LCD_Write_Com(0x38);
	LCD_Write_Com(0x0c);
	LCD_Write_Com(0x06);
	LCD_Write_Com(0x01);
}

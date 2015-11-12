/*--------------------------------------------------------------------
���ƣ��������
��˾���Ͼ���˼����
��д��rantg
���ڣ�2012.3
����: �����������ɨ�貢���������ʾ��Ӧ�ļ�ֵ��ʹ�þ���
      ����ʱ����������P21���ö�ͨ����ñ�ӵ�������̶�
--------------------------------------------------------------------*/

#include <reg52.h>

typedef unsigned char uchar;
typedef unsigned int  uint;

unsigned char code table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
		                  	 0x77,0x7c,0x39,0x5e,0x79,0x71};//0-F
 
uchar KeyScan(void);
void DelayMs(uint i);

void main(void)
{
	uchar key;
	P0 = 0x00;			//1������� ����Ӧ�İ���������ʾ�����ϵ��ַ�
	P1 = 0xf7;
	while(1)
	{
		key=KeyScan();	//���ü���ɨ�裬
		switch(key)
		{		   
			case 0x7e:P0 = table[0];break;//0 ������Ӧ�ļ���ʾ���Ӧ����ֵ
			case 0x7d:P0 = table[1];break;//1
			case 0x7b:P0 = table[2];break;//2
			case 0x77:P0 = table[3];break;//3
			case 0xbe:P0 = table[4];break;//4
			case 0xbd:P0 = table[5];break;//5
			case 0xbb:P0 = table[6];break;//6
			case 0xb7:P0 = table[7];break;//7
			case 0xde:P0 = table[8];break;//8
			case 0xdd:P0 = table[9];break;//9
			case 0xdb:P0 = table[10];break;//a
			case 0xd7:P0 = table[11];break;//b
			case 0xee:P0 = table[12];break;//c
			case 0xed:P0 = table[13];break;//d
			case 0xeb:P0 = table[14];break;//e
			case 0xe7:P0 = table[15];break;//f
		}
	}
}

uchar KeyScan(void)//����ɨ�躯����ʹ�����з�תɨ�跨
{
	uchar cord_h,cord_l;	//����ֵ
	P3 = 0xf0;            //�������ȫΪ0
	cord_h = P3&0xf0;     //��������ֵ
	if(cord_h != 0xf0)    //�ȼ�����ް�������
	{
		DelayMs(100);        //ȥ��
		if(cord_h != 0xf0)
		{
			cord_h = P3&0xf0;  //��������ֵ
			P3 = cord_h|0x0f;  //�����ǰ����ֵ
			cord_l = P3&0x0f;  //��������ֵ
			return(cord_h+cord_l);//������������ֵ
		}
	}
	return(0xff);     //���ظ�ֵ
}


/*------------------------------------------------
				 ��ʱ����
------------------------------------------------*/
void DelayMs(unsigned int t)
{
	unsigned char i;
	for(;t > 0;t--)
		for(i = 110;i > 0;i--);
}
/*-----------------------------------------------
名称：数码管静态显示
公司：南京爱思电子
编写：rantg
日期：2012.3
内容：数码管静态显示0
	  在使用数码管显示时把P16 数码管/液晶显示复用
	  端用跳帽连起来，使用液晶显示时拔掉跳帽
------------------------------------------------*/

#include<reg52.h> 

/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main(void)
{
	P1 = 0xf7;
	P0 = 0x3f;
	while(1)
	{
	}
}


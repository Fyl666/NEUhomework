#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char
sbit led=P1^0; //LED灯
sbit beep=P2^3; //蜂鸣器

void delay()
{
	int i,j;
	for(i=0;i<=110;i++) //每1ms约执行110条指令
		{for(j=0;j<1000;j++);} //延迟1000ms，即1秒
}

void main()
{
	uchar i,temp;
	while(1)
	{
		temp = 0xfe; //对应11111110
		for(i=0;i<7;i++)
		{
			P1 = temp;
			beep=~beep; //蜂鸣器响<->不响
			delay();
			temp = _crol_(temp,1); //每次左移一位
		}
		
		for(i=0;i<7;i++)
		{
			P1 = temp;
			beep=~beep;
			delay();
			temp = _cror_(temp,1); //每次右移一位
		}
	}
}
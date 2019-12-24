/**********************51开发板实验************************
*  平台：Keil U4 + STC89C52RC
*  晶振：11.0592MHZ
******************************************************************/
/*-----------------------------------------------
  名称：遥控器红外解码数码管显示
  内容：按配套遥控器上1-9会在数码管上对应显示，流水灯依照亮灯
------------------------------------------------*/
#include <reg52.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义
#define DataPort P0   //定义数据端口 程序中遇到DataPort 则用P0 替换

sbit IR = P3 ^ 2; //红外接口标志
sbit LATCH1 = P2 ^ 6; //定义锁存使能端口 段锁存
sbit LATCH2 = P2 ^ 7; //                 位锁存
sbit LCD1602 = P2 ^ 5; //数码管
sbit led = P1 ^ 0; //LED灯
/*------------------------------------------------
                全局变量声明
------------------------------------------------*/

unsigned char code dofly_DuanMa[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f}; // 显示段码值0~9
unsigned char led_Order[10] = {0xff, 0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f, 0x00};//LED
unsigned char irtime; //红外用全局变量
unsigned int order1;//dofly_duanma_order

bit irpro_ok, irok;
unsigned char IRcord[4];//红外信号的4个字节
unsigned char irdata[33];//接收到的33位

/*------------------------------------------------
                  函数声明
------------------------------------------------*/

void Ir_work(void);//数码管和LED
void Ircordpro(void);//红外遥控解码
/*------------------------------------------------
                定时器0初始化
------------------------------------------------*/
void TIM0init(void) //定时器0初始化
{
    TMOD = 0x02; //定时器0工作方式2，TH0是重装值，TL0是初值
    TH0 = 0x00;  //重载值
    TL0 = 0x00;  //初始化值
    ET0 = 1;     //开中断
    TR0 = 1;
}
/*------------------------------------------------
                  外部中断0初始化
------------------------------------------------*/
void EX0init(void)
{
    IT0 = 1; //指定外部中断0下降沿触发，INT0 (P3.2)
    EX0 = 1; //使能外部中断
    EA = 1;  //开总中断
}

/*------------------------------------------------
                  定时器0中断处理
------------------------------------------------*/

void tim0_isr(void) interrupt 1 using 1
{
    irtime++; //用于计数2个下降沿之间的时间
}

/*------------------------------------------------
                  外部中断0中断处理
------------------------------------------------*/
void EX0_ISR(void) interrupt 0 //外部中断0服务函数
{
    static unsigned char i; //接收红外信号处理
    static bit startflag;   //是否开始处理标志位

    if (startflag)
    {
        if (irtime < 63 && irtime >= 33) //引导码 TC9012的头码，9ms+4.5ms
            i = 0;
        irdata[i] = irtime; //存储每个电平的持续时间，用于以后判断是0还是1
        irtime = 0;
        i++;
        if (i == 33)
        {
            irok = 1;
            i = 0;
        }
    }
    else
    {
        irtime = 0;
        startflag = 1;
    }
}

/*------------------------------------------------
                  键值处理
------------------------------------------------*/

void Ir_work(void) //红外键值散转程序
{
    switch (IRcord[2]) //判断第三个数码值
    {
    case 0x16:
        DataPort = dofly_DuanMa[0];
		order1 = 0;
        P1 = led_Order[0];
        break; //0
    case 0x0c:
        DataPort = dofly_DuanMa[1];
		order1 = 1;
        P1 = led_Order[1];
        break; //1 显示相应的按键值
    case 0x18:
        DataPort = dofly_DuanMa[2];
		order1 = 2;
        P1 = led_Order[2];
        break; //2
    case 0x5e:
        DataPort = dofly_DuanMa[3];
		order1 = 3;
        P1 = led_Order[3];
        break; //3
    case 0x08:
        DataPort = dofly_DuanMa[4];
		order1 = 4;
        P1 = led_Order[4];
        break; //4
    case 0x1c:
        DataPort = dofly_DuanMa[5];
		order1 = 5;
        P1 = led_Order[5];
        break; //5
    case 0x5a:
        DataPort = dofly_DuanMa[6];
		order1 = 6;
        P1 = led_Order[6];
        break; //6
    case 0x42:
        DataPort = dofly_DuanMa[7];
		order1 = 7;
        P1 = led_Order[7];
        break; //7
    case 0x52:
        DataPort = dofly_DuanMa[8];
		order1 = 8;
        P1 = led_Order[8];
        break; //8
    case 0x4a:
        DataPort = dofly_DuanMa[9];
		order1 = 9;
        P1 = led_Order[9];
        break; //9
	case 0x07:
		order1 = order1==0?9:order1-1;
		DataPort = dofly_DuanMa[order1];
		P1 = led_Order[order1];
		break;
	case 0x15:
		order1 = order1==9?0:order1+1;
		DataPort = dofly_DuanMa[order1];
		P1 = led_Order[order1];
		break;
    default:
        break;
    }

    irpro_ok = 0; //处理完成标志
}
/*------------------------------------------------
                红外码值处理
------------------------------------------------*/
void Ircordpro(void) //红外码值处理函数
{
    unsigned char i, j, k;
    unsigned char cord, value;

    k = 1;
    for (i = 0; i < 4; i++) //处理4个字节
    {
        for (j = 1; j <= 8; j++) //处理1个字节8位
        {
            cord = irdata[k];
            if (cord > 7) //大于某值为1，这个和晶振有绝对关系，这里使用12M计算，此值可以有一定误差
                value |= 0x80;
            if (j < 8)
            {
                value >>= 1;
            }
            k++;
        }
        IRcord[i] = value;
        value = 0;
    }
    irpro_ok = 1; //处理完毕标志位置1
}

/*------------------------------------------------
                    主函数
------------------------------------------------*/
void main(void)
{
    EX0init();  //初始化外部中断
    TIM0init(); //初始化定时器
    LCD1602 = 0;
    DataPort = 0x3e; //取位码 第一位数码管选通，即二进制0011 1110
    LATCH2 = 1;      //位锁存
    LATCH2 = 0;

    while (1) //主循环
    {
	LATCH1=0;
	LATCH2=0;

	P0=0x4f;	   //数字“3”的代码
	LATCH1=1;
	LATCH2=0;

	P0=0xfe;	   //选中第一个数码管
	LATCH1=1;
	LATCH2=0;
	/*
        if (irok) //如果接收好了进行红外处理
        {
            Ircordpro();
            irok = 0;
        }
		
        if (irpro_ok) //如果处理好后进行工作处理，如按对应的按键后显示对应的数字等
        {
            Ir_work();
        }
		*/
    }
}

#include<stc15f2k60s2.h>

#define uchar unsigned char
#define uint unsigned int

sbit HC138_A = P2^5;
sbit HC138_B = P2^6;
sbit HC138_C = P2^7;

sbit LED_1 = P0^0; 
sbit LED_2 = P0^1;
sbit LED_3 = P0^2;
sbit LED_4 = P0^3;

sbit R1 = P3^0;
sbit R2 = P3^1;
sbit R3 = P3^2;
sbit R4 = P3^3;

sbit C1 = P4^4;
sbit C2 = P4^2;
sbit C3 = P3^5;
sbit C4 = P3^4;

unsigned char duanma[20]=
	{0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,
	 0x80,0x90,0xc6,0x8c,0x88};		


uchar key_mutil = 0;
uint temp ;
uchar num1 = 0,num2 = 0;
uchar state = 1; 
uchar a = 25;
bit mode;

void Delay(uint xms)					 //延时函数
{
	uint i,j;
	for(i = xms;i > 0; i--)
		for(j = 845; j > 0; j--);
}
	
void SelectHC573(unsigned char channel)		//138译码器
{
	switch(channel)
	{
	case 4:
		P2 =  (P2 & 0x1f) | 0x80;
		break;
	case 5:
		P2 =  (P2 & 0x1f) | 0xa0;
		break;
	case 6:
		P2 =  (P2 & 0x1f) | 0xc0;
		break;
	case 7:
		P2 =  (P2 & 0x1f) | 0xe0;
		break;
	}
}
void init()								  //初始化
{
	 SelectHC573(5);	//
	 P0 = 0x00;
	 SelectHC573(4);    //关灯
	 P0 = 0xff;
}
void key_down()	  //矩阵键盘定义
{
	R1 = 0;
	R2 = R3 = R4 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		while(C1 == 0);
		key_mutil = 7; 
	}
	if(C2 == 0)
	{
		while(C2 == 0);
		key_mutil = 11; 
	}
	if(C3 == 0)
	{
		while(C3 == 0);
		key_mutil = 15; 
	}
	if(C4 == 0)
	{
		while(C4 == 0);
		key_mutil = 19; 
	}

	R2 = 0;
	R1 = R3 = R4 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		while(C1 == 0);
		key_mutil = 6; 
	}
	if(C2 == 0)
	{
		while(C2 == 0);
		key_mutil = 10; 
	}
	if(C3 == 0)
	{
		while(C3 == 0);
		key_mutil = 14; 
	}
	if(C4 == 0)
	{
		while(C4 == 0);
		key_mutil = 18; 
	}

	R3 = 0;
	R1 = R2 = R4 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		while(C1 == 0);
		key_mutil = 5; 
	}
	if(C2 == 0)
	{
		while(C2 == 0);
		key_mutil = 9; 
	}
	if(C3 == 0)
	{
		while(C3 == 0);
		key_mutil = 13; 
	}
	if(C4 == 0)
	{
		while(C4 == 0);
		key_mutil = 17; 
	}

	R4 = 0;
	R1 = R2 = R3 = 1;
	C1 = C2 = C3 = 1;
	if(C1 == 0)
	{
		while(C1 == 0);
		key_mutil = 4; 
	}
	if(C2 == 0)
	{
		while(C2 == 0);
		key_mutil = 8; 
	}
	if(C3 == 0)
	{
		while(C3 == 0);
		key_mutil = 12; 
	}
	if(C4 == 0)
	{
		while(C4 == 0);
		key_mutil = 16; 
	}							
}

void shumaguan(uchar pos, num)	  		  //不带小数点的数码管显示
{
	SelectHC573(6) ;
	P0 = 0x01 << (pos - 1);
	SelectHC573(7);
	P0= duanma[num]; 
	Delay(3);

}void main()
{
	init();

	while(1)
	{  	 
		key_down();
		shumaguan(1, num2);
		
		}}
#include "stc15f2k60s2.h"

unsigned char code duanma[16] = {0xc0,0xf9,
0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xc1,0x8c,0xc8};

unsigned int f_count = 0;
unsigned char count = 0;
unsigned int dat = 0;
void DelaySMG(unsigned int t)
{
	while(t--);

}
void SelectHC573(unsigned char channel,unsigned char dat)
{
	P0 = dat;
	switch(channel)
	{
		case 4:P2 = (P2 & 0x1f) | 0x80;break;
		case 5:P2 = (P2 & 0x1f) | 0xa0;break;
		case 6:P2 = (P2 & 0x1f) | 0xc0;break;
		case 7:P2 = (P2 & 0x1f) | 0xe0;break;
		case 0:P2 = (P2 & 0x1f) | 0x00;break;
	}
	P2 = (P2 & 0x1f) | 0x00;
}
void DisplaySMG(unsigned char pos,unsigned char dat)
{
	SelectHC573(6,0x01 << pos);
	SelectHC573(7,dat);
	DelaySMG(500);
	SelectHC573(6,0x01 << pos);
	SelectHC573(7,0xff);
}

void Display()
{
	DisplaySMG(7,duanma[dat%10]);
	if(dat >= 10)
	{
		DisplaySMG(6,duanma[dat/10%10]);	
	}
	if(dat >= 100)
	{
		DisplaySMG(5,duanma[dat/100%10]);
	}
	if(dat >= 1000)
	{
		DisplaySMG(4,duanma[dat/1000%10]);
	}
	if(dat >= 10000)
	{
		DisplaySMG(3,duanma[dat/10000%10]);
	}							   
	if(dat >= 100000)
	{
		DisplaySMG(2,duanma[dat/100000%10]);
	}

}

void Init_Timer()
{
	TMOD = 0x16;
	TH0 = 0xff;
	TL0 = 0xff;

	TH1 = (0 - 50000)/256;
	TL1 = (0 - 50000)%256;

	ET0 = 1;
	ET1 = 1; 
	
	EA = 1;
	
	TR0 = 1;
	TR1 = 1;

}

void Service_Timer0()   interrupt 1
{
	TH0 = 0xff;
	TL0 = 0xff;
	f_count++;



}
void Service_Timer1()   interrupt 3
{
	TH1 = (0 - 50000)/256;
	TL1 = (0 - 50000)%256;
	count ++;
	if(count == 20)
	{
		dat = f_count;
		f_count = 0;
		count = 0;
			
	}

}
void Init()
{
	SelectHC573(0,0x00);
	SelectHC573(5,0x00);
	SelectHC573(4,0xff);	
}
void main()
{
	Init();
	Init_Timer();
	while(1)
	{
		Display();
		
	}
}

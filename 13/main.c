#include "onewire.h"
#include "ds1302.h"

unsigned char code duanma[20] = {0xc0,0xf9,
0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xc1};
unsigned char WRITE[7] = {0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};
unsigned char READ[7] = {0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};
unsigned char TIME[7] = {0x28,0x59,0x23};
unsigned char state = 1;
unsigned char mode = 0;
unsigned int T = 23;
unsigned int SMG_ds18b20 = 0;
unsigned int L1_time = 0;
unsigned char L_state = 0xff;
unsigned int count_5 = 0;

float temp_ds18b20 = 0;

sbit C1 = P3^2;						
sbit C2 = P3^3;

sbit R1 = P3^4;
sbit R2 = P3^5;


void Delay(unsigned int t)
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
	Delay(500);
	SelectHC573(6,0x01 << pos);
	SelectHC573(7,0xff);		
}

void Display()
{
	switch(state)
	{
		case 1:
		DisplaySMG(0,duanma[11]);
		DisplaySMG(1,duanma[1]);
		DisplaySMG(5,duanma[SMG_ds18b20/100]) ;
		DisplaySMG(6,duanma[(SMG_ds18b20/10)%10] & 0x7f) ;
		DisplaySMG(7,duanma[SMG_ds18b20%10]) ;

		break;
		case 2:
		DisplaySMG(0,duanma[11]);
		DisplaySMG(1,duanma[2]);
		DisplaySMG(3,duanma[TIME[2]/16]);
		DisplaySMG(4,duanma[TIME[2]%16]);
		DisplaySMG(5,duanma[10]);
		DisplaySMG(6,duanma[TIME[1]/16]);
		DisplaySMG(7,duanma[TIME[1]%16]);
		break;
		case 3:
		DisplaySMG(0,duanma[11]);
		DisplaySMG(1,duanma[3]);

		DisplaySMG(6,duanma[T/10]);
		DisplaySMG(7,duanma[T%10]);
		break;
		case 4:
		DisplaySMG(0,duanma[11]);
		DisplaySMG(1,duanma[2]);
		DisplaySMG(3,duanma[TIME[1]/16]);
		DisplaySMG(4,duanma[TIME[1]%16]);
		DisplaySMG(5,duanma[10]);
		DisplaySMG(6,duanma[TIME[0]/16]);
		DisplaySMG(7,duanma[TIME[0]%16]);
		break;
	}
}

void Display_ds18b20()
{
	unsigned int temp;
	unsigned char low,high;
	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0x44);
	Display();

	init_ds18b20();
	Write_DS18B20(0xcc);
	Write_DS18B20(0xbe);
	low = Read_DS18B20();
	high = Read_DS18B20();
	init_ds18b20();

	temp = high;
	temp = (temp << 8) | low;
	if((temp & 0xf800)  == 0x0000 )
	{
		temp_ds18b20 = temp *0.0625;
		SMG_ds18b20 = temp_ds18b20*10;
		Display();	
	}
}

void Write_config()
{
	unsigned char i;
	Write_Ds1302_Byte(0x8e,0x00);
	for(i = 0; i < 7; i ++)
	{
		Write_Ds1302_Byte(WRITE[i],TIME[i]);			
	}
	Write_Ds1302_Byte(0x8e,0x80);

}
void Read_ds1302()
{
	unsigned char i;
	for(i = 0; i < 7; i++)
	{
		TIME[i] = Read_Ds1302_Byte(READ[i]);	
	}
	if(TIME[1] == 0 && TIME[0] == 0)
	{
		L_state &= ~0x01; 
		SelectHC573(4,L_state);
		if(mode == 1)
		{
		 	SelectHC573(5,0x10);
		}
		L1_time = 1;	
	}	
}

void Time0_Init()
{
	TMOD = 0x01;
	TH0 = (0 - 50000)/256;
	TL0 = (0 - 50000)%256;
	ET0 = 1;
	EA = 1;
	TR0 = 1;
}											
void Service_Timer0()  interrupt 1
{	
	TH0 = (0 - 50000)/256;
	TL0 = (0 - 50000)%256;
	Read_ds1302();
	if(L1_time == 1)
	{

		count_5 ++;
		if(count_5 == 100)
		{
			L_state |= 0x01;
			SelectHC573(4,L_state);			
			SelectHC573(5,0x00);
			L1_time = 0;
			count_5 = 0;
				
		}
	}
}
void key_down()
{
	C2 = 0; C1 = R1 = R2 = 1;
	if(R2 == 0)
	{  //S12
		Delay(200);
		if(R2 == 0)
		{
			while(R2 == 0);
			state ++;
			if(state == 4)
			{
				state = 1;
			}
		}
	} 
	C1 = 0;C2 = R1 = R2 = 1;
	if(R2 == 0)
	{  //S13
		Delay(200);
		{
			if(R2 == 0)
			{
				if(mode == 0)
				{
					while(R2 == 0);
					mode = 1;
				}	
				else
				{
					while(R2 == 0);
					mode = 0;
				}
			}
		}
	}
	C2 = 0;	C1 = R1 = R2 = 1;
	if(R1 == 0)
	{ //S16
		Delay(200);
		if(R1 == 0)
		{
			if(state == 3)
			{
				while(R1 == 0);
				if(T == 99)
				{
					T = 99;
				}
				else 
				{
					T = T + 1;
				}
			}

		}
	}
	C1 = 0;C2 = R1 = R2 = 1;
	if(R1 == 0)
	{//S17
		Delay(200);
		if(R1 == 0)
		{
			if(state == 3)
			{
				while(R1 == 0);
				if(T ==10)
				{
					T = 10;
				}
				else
				{
					T = T - 1;
				}
			}
			if(state == 2)
			{
				while(R1 == 0)
				{
					state = 4 ;
					Display();
				}
				state = 2;

			}
		}
	}
		
}

void Init()
{
	SelectHC573(0,0x00);
	SelectHC573(5,0x00);
	SelectHC573(4,0xff);
	Write_config();
	Time0_Init();

}
void main()
{
	Init();
	while(1)
	{
		Display_ds18b20();
		key_down();
		if(mode == 0)
		{
			L_state &= ~0x02;
			SelectHC573(4,L_state);
			if(SMG_ds18b20 > T*10)
			{
				SelectHC573(5,0x10);		
			}
			else 
			{
				SelectHC573(5,0x00);		
			}

		}
		else 
		{
			L_state |= 0x02;
			SelectHC573(4,L_state);

		}
	}

}

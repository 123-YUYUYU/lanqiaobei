#include "DS1302.H"

unsigned char code duanma[20] = {0xc0,0xf9,0xa4,
0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
unsigned char WRITE[7] = {0x80,0x82,0x84,0x86,0x88,0x8a,0x8c} ;
unsigned char READ[7] = {0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};
unsigned char TIME[7] = {0x24,0x59,0x23,0x18,0x04,0x06,0x20} ;

void Delay(unsigned char t)
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
	SelectHC573(6, 0x01 << pos);        
  	SelectHC573(7, 0xff);        

}
void Display()
{
	DisplaySMG(0,duanma[TIME[2]/16]);

	DisplaySMG(1,duanma[TIME[2]%16]);

	DisplaySMG(2,duanma[10]);

	DisplaySMG(3,duanma[TIME[1]/16]);

	DisplaySMG(4,duanma[TIME[1]%16]);

	DisplaySMG(5,duanma[10]);

	DisplaySMG(6,duanma[TIME[0]/16]);

	DisplaySMG(7,duanma[TIME[0]%16]);

}

void DS1302_config()
{
	unsigned char i;
	Write_Ds1302_Byte(0x8E,0x00);
	for(i = 0; i < 7; i++ )
	{
		Write_Ds1302_Byte(WRITE[i],TIME[i]);	
	}
	Write_Ds1302_Byte(0x8E,0x80);

}

void Read_DS1302()
{
	unsigned char i;
   	for(i = 0; i < 7; i++ )
	{
	TIME[i] = Read_Ds1302_Byte(READ[i]);		
	}
	

}							   
void Init()
{
	SelectHC573(0,0x00);
	SelectHC573(5,0x00);
	SelectHC573(4,0xff);
	SelectHC573(6,0xff);
	SelectHC573(7,0xff);

  	
}
void main()
{	
	Init();
	DS1302_config();
	while(1)
	{
		Read_DS1302();
		Display();	

	}


}
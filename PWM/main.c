#include <stc15f2k60s2.h>

sbit L1 = P0^0;
sbit S7 = P3^0;
void SelectHC573()
{
	P2 = (P2 & 0x1f) | 0x80;

}
//***********¶¨Ê±Æ÷********************************
unsigned char count	=0;
unsigned char pwm_duty = 0;
//void InitTimer0()
//{
//	TMOD = 0x01;
//	TH0 = (25535- 100) / 256;
//	TL0 = (25535- 100) % 256; 
//
//	ET0 = 1;
//	EA = 1;
//
//}

//void  ServiceTimer0() interrupt 1
//{
//	TH0 = (25535- 100) / 256;
//	TL0 = (25535- 100) % 256;
//
//	count++;
//	if(count == pwm_duty)
//	{
//		L1 = 1;
//	}
//	else if(count == 100)
//	{	
//	 	L1 = 0;
//		count = 0;
//	}
//
//}
//*************************************************



//void Delay(unsigned int t)
//{
//	while(t--);
//}

//unsigned char stat = 0;
//void ScanKey()
//{
//	if(S7 = 0)
//	{
//	Delay(100);
//	if(S7 = 0)
//	{
//		switch(stat)
//		{
//			case 0:
//				L1 = 0;
//				TR0 = 1;
//				pwm_duty = 10;
//				stat = 1;
//			break;
//			case 1:
//				pwm_duty = 50;
//				stat = 2;
//			break;
//			case 2:
//				pwm_duty = 90;
//				stat = 3;
//			break;
//			case 3:
//				L1 = 1;
//				TR0 = 0;
//				stat = 0;
//			break;
//
//
//
//		}
//		while(S7 ==0);
//			
//	}}
//}



void main()
{
	SelectHC573();
	P2 = 0xff;

//	InitTimer0();
	while(1)
	{
		//SelectHC573();
		//L1 = 0;

	//	ScanKey();
	
	}
}
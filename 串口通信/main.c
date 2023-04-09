#include <stc15f2k60s2.h>



unsigned char urdat;

void SendByte(unsigned char dat)
{
	SBUF = dat;
	while(TI == 0);
	TI =  0;
}


void InitUart()
{
	TMOD = 0x20;
	TH1 =  0xfd;
	TL1 = 0xfd;
	TR1 = 1;

	SCON = 0x50;		   //异步8位UART并且允许接收： SCON = 0x50; 
	ES = 1;				//串行中断允许控制位
	EA = 1;													  
	AUXR = 0x00;		



}



void ServiceUart() interrupt 4
{
	if(RI == 1)
	{
		RI = 0;
	 	urdat = SBUF;
		SendByte(urdat + 1);
		  
	}


}


void main()
{

	InitUart();
	SendByte(0x5A);
	SendByte(0x5A);
	while(1);


	
		
	
}

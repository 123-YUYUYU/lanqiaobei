#include <STC15F2K60S2.H>

unsigned char t_h = 0;
unsigned char t_m = 0;
unsigned char t_s = 0;
unsigned char t_005s = 0;

unsigned char command = 0;

unsigned char code SMG_duanma[18]={0xc0,0xf9,
		0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
	 	0x88,0x80,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};

void Delay(unsigned int t)
{
	while(t--) ;
}

void DelaySMG(unsigned int t)
{
	while(t--) ;
}
void Init_74HC573(unsigned char channel)
{
	switch(channel)
	{
		case 4:
			P2 = (P2 & 0x1f) | 0x80;	  //LED
		break;
		case 5:
			P2 = (P2 & 0x1f) | 0xA0;      //�������ͼ̵���
		break;
		case 6:
			P2 = (P2 & 0x1f) | 0xC0;	 //�����λѡ
		break;
		case 7:
			P2 = (P2 & 0x1f) | 0xE0;	 //���ܶ���
		break;
		case 0:
			P2 = (P2 & 0x1f) | 0x00;	 //�ر����������� 
		break;
	
	}

}

void DisplaySMG(unsigned char value, unsigned char pos)
{
	Init_74HC573(4);
	P0 = 0xff;
	Init_74HC573(6);
	P0 = 0x01 << pos;
	Init_74HC573(7);
	P0 = value;
}
void Display_time()
{
	DisplaySMG(SMG_duanma[t_s%10],7);  
	DelaySMG(500);
	DisplaySMG(SMG_duanma[t_s/10],6);
	DelaySMG(500);

	DisplaySMG(SMG_duanma[16],5);
	DelaySMG(500);

	DisplaySMG(SMG_duanma[t_m%10],4);
	DelaySMG(500);
	DisplaySMG(SMG_duanma[t_m/10],3);
	DelaySMG(500);

	DisplaySMG(SMG_duanma[16],2);
	DelaySMG(500);

	DisplaySMG(SMG_duanma[t_h%10],1);	
	DelaySMG(500);
	DisplaySMG(SMG_duanma[t_h/10],0);    
	

}
void InitTimer0()
{
	TMOD = 0x21;
	TH0 = (65535 - 50000) / 256; 
	TL0	= (65535 - 50000) % 256;
	ET0 = 1;         //ʹ�ܶ�ʱ��0
	EA = 1;			 //ʹ�����ж�
	TR0 = 1;		 //	������ʱ��T0
}

void ServiceTimer0() interrupt 1
{
	TH0 = (65535 - 50000) / 256; 
	TL0	= (65535 - 50000) % 256;
	t_005s ++;
	if(t_005s == 20)
	{
		t_005s = 0;
		t_s ++;
		if(t_s == 60)
		{
			t_s = 0;
			t_m ++;
			if(t_m == 60)
			{
				t_m = 0;
				t_h ++;
			}			
		}	
	}	
}

void ServiceUart() interrupt 4
{
	if(RI == 1)
	{
		command = SBUF;		   //�ѽ��յ������ݱ��浽command����
		RI = 0;				   //��������ɱ�־RI��0
	
	}

}

void SendByte(unsigned char dat)
{
	SBUF = dat;
	while(TI == 0);
	TI = 0;
}

void InitUart()
{
	TMOD = 0x21;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;  		 //������ʱ��1

	SCON = 0x50;	//8λUARTģʽ������ӷ�
	AUXR =0x00;     //�����Ĵ���

	ES = 1;			//ʹ�ܴ����ж�
	EA = 1;			//ʹ�����ж�

}

void ServiceTimer() interrupt 4
{

	

}
void Init()
{
	Init_74HC573(5);
	P0 = 0x00;
	Init_74HC573(4);
	P0 = 0xff  ;
	Init_74HC573(0);

	


}
void main()
{
	Init()
	while(1)
	{
	
	}

}

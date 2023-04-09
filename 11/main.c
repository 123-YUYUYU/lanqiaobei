#include "iic.h"

unsigned char key_mutil = 0;
unsigned char state = 1;
unsigned char adc_value = 0; 
unsigned int smg_volt = 0;
unsigned int smg_Vp = 300;
float adc_volt = 0;
unsigned int count = 0;
unsigned int error = 0;
unsigned int dat_24c02 = 0;

unsigned char code duanma[16] = {0xc0,0xf9,
0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xc1,0x8c,0xc8};
//10000011


sbit R1 = P3^2;
sbit R2 = P3^3;

sbit C1 = P3^5;
sbit C2 = P3^4;

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
	switch(state)
	{
		case 1:
		DisplaySMG(0,duanma[10]);
		DisplaySMG(5,duanma[smg_volt/100] & 0x7f);
		DisplaySMG(6,duanma[(smg_volt/10)%10]);
		DisplaySMG(7,duanma[smg_volt%10]); 
		break;
		
		case 2:
		DisplaySMG(0,duanma[11]);
		DisplaySMG(5,duanma[smg_Vp/100] & 0x7f);
		DisplaySMG(6,duanma[(smg_Vp/10)%10]);
		DisplaySMG(7,duanma[smg_Vp%10]);
		break;
		
		case 3:
		DisplaySMG(0,duanma[12]);
		DisplaySMG(6,duanma[count/10]);
		DisplaySMG(7,duanma[count%10]);


		break;	
	}

}
void Init_Timer0()
{
	TH0 = (0 - 50000) / 256;
	TL0 = (0 - 50000) % 256;
	TMOD = 0x01;	//
	ET0 = 1;		//使能定时器0中断
	EA = 1;			//打开总中断
	TR0 = 1;		//启动定时器0


}

void Write_24C02(unsigned char addr,unsigned char dat )
{
	IIC_Start();
	IIC_WaitAck();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();
}


unsigned char Read_24C02(unsigned char addr)
{
	unsigned char tmp;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(addr);
	IIC_WaitAck();

	IIC_Start();
	IIC_WaitAck();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	tmp = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	return tmp;
}

unsigned char Read_PCF8591_AIN3()
{
	unsigned char tmp;
	IIC_Start();
	IIC_SendByte(0x90);	  //PCF8591的写设备地址
	IIC_WaitAck();

	IIC_SendByte(0x03);	 //选择AIN3通道，可调电阻
	IIC_WaitAck();
	IIC_Stop();

	Display();

	IIC_Start();
	IIC_SendByte(0x91);	//PCF8591的读设备地址
	IIC_WaitAck();

	tmp = IIC_RecByte();
	IIC_SendAck(1);
	IIC_Stop();
	return tmp;

} 
void App_Volt()
{
	unsigned char i;
	for(i = 0; i < 3; i++)
	{
		adc_value += Read_PCF8591_AIN3();	
	}
	adc_value = adc_value / 3;
	adc_volt = adc_value * (5.0 / 255);
	smg_volt = adc_volt * 100;
//	if(smg_volt < smg_Vp )
}

void key_down()
{  // sbit R1 = P3^2; sbit R2 = P3^3; sbit C1 = P3^5;sbit C2 = P3^4;
	C1 = 0; C2 = R1 = R2 = 1;
	if(R1 == 0)
	{//S13
	}	DelaySMG(200);
	if(R1 == 0)
	{
		if(state == 3)
		{
			error = 0;
			while(R1 == 0);
			count = 0;
		}
		else 
		{
			error ++;
		}
	}	
	if(R2 == 0)
	{  //S12
		DelaySMG(200);	
		if(R2 == 0)
		{	while(R2 == 0);
			state ++;
			
			if(state == 4)
			{
				error = 0;
				state = 1;
			}
			else if(state == 3)
			{
				dat_24c02 = smg_Vp /10;
				Write_24C02(0x00,dat_24c02);
			}
		}
	}
	C1 = R1 = R2 = 1; C2 = 0;
	if(R1 == 0)
	{	 //S17
		DelaySMG(200);	
		if(R1 == 0)
		{
			if(state == 2)
			{
				error = 0;
				while(R1 == 0);
				smg_Vp = smg_Vp - 50 ;
				if(smg_Vp == 0)
				{
					smg_Vp = 500;
				}
			}
			else 
			{
				error++;
			}
		}
	}
		if(R2 == 0)
		{	 //S16
			DelaySMG(200);	
			if(R2 == 0)
			{
				if(state == 2)
				{
					error = 0;
					while(R2 == 0);
					smg_Vp = smg_Vp + 50 ;
					if(smg_Vp == 500)
					{
						smg_Vp = 0;
					}
				}
				else 
				{
					error ++;
				}
			}
	}
	
}
void Init()
{
   SelectHC573(0,0x00);
   SelectHC573(5,0x00);
   SelectHC573(4,0xff);

   dat_24c02 = Read_24C02(0x00);
   if(dat_24c02 >50 || dat_24c02 %5 != 0)
   {
   	dat_24c02 = 0;
   }
   smg_Vp = dat_24c02 * 10;

}

void main()
{
	Init();
	while(1)
	{
		key_down();
		App_Volt();
		Display();
		DelaySMG(100);	
	}
}
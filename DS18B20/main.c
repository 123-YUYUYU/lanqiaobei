#include "reg52.h"
#include "onewire.h"
 
unsigned char code SMG_NoDot[18]={0xc0,0xf9,
    0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
    0x88,0x80,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};
unsigned char code SMG_Dot[10]={0x40,0x79,
    0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
float temp_ds18b20 = 0;          //ʵ���¶�ֵ
unsigned int smg_ds18b20 = 0;    //�������ʾ�¶�ֵ
void delay(unsigned int t)
{
 	while(t--);
}
 
void Init_74HC138(unsigned char channel)
{
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
 
void  SMG_DisplayBit(unsigned char pos,unsigned char dat)
{
 	P0 = (0x01 << pos);
	Init_74HC138(6);
	P0 = dat;
	Init_74HC138(7);
}
 
void SMG_All(unsigned char dat)
{
 	P0 = 0xff;
	Init_74HC138(6);
	P0 = dat;
	Init_74HC138(7);
}
 
void Display()
{
	 if(smg_ds18b20>99)
     {
         SMG_DisplayBit(5,SMG_NoDot[smg_ds18b20 / 100]);        
         delay(500);
         SMG_DisplayBit(5,0xff);    //����
     }
 
	 SMG_DisplayBit(6,SMG_Dot[(smg_ds18b20 / 10) % 10]);
	 delay(200);
	 SMG_DisplayBit(6,0xff);
	 delay(200);
	 SMG_DisplayBit(7,SMG_NoDot[smg_ds18b20  % 10]);
	 delay(200);
	 SMG_DisplayBit(7,0xff);
	 delay(200);
	 SMG_All(0xff);
	 delay(200);
}	
	
 
//==============DS18B20�¶ȶ�������ʾ==============
void Read_Dsiplay_DS18B20()
{
//  unsigned char LSB,MSB;      
//  unsigned int temp = 0;      
//  
//  init_ds18b20();              //��ʼ��DS18B20
//  Write_DS18B20(0xcc);        //����ROM����
//  Write_DS18B20(0x44);        //�����¶�ת��
//  Display();
//  init_ds18b20();              //��ʼ��DS18B20
//  Write_DS18B20(0xcc);        //����ROM����
//  Write_DS18B20(0xbe);        //�����ڲ��洢��
//  LSB = Read_DS18B20();        //��0�ֽڣ��¶ȵ�8λ
//  MSB = Read_DS18B20();        //��1�ֽڣ��¶ȸ�8λ
//  init_ds18b20();              //��ʼ����ֹͣ��ȡ
//  
//  temp = MSB;                  //�ϳ�16λ�¶�ԭʼ����
//  temp = (temp << 8) | LSB;
//  if((temp & 0xf800) == 0x0000)    //�������¶�
//  {
//    temp_ds18b20 = temp * 0.0625;  //����ʵ���¶�ֵ
//  }
//  smg_ds18b20 = temp_ds18b20 * 10;
//  Display();


	unsigned int temp;
	unsigned char low,high;
	init_ds18b20();
	Write_DS18B20(0xcc);;
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
	if((temp & 0xf800)  == 0x0000  )
	{
		temp_ds18b20 = temp *0.0625;
		smg_ds18b20 = temp_ds18b20*10;
		Display();	
		
	} 
}
 
void Init_System()
{
 	P0 = 0xff;
	Init_74HC138(4);
	P0 = 0x00;
	Init_74HC138(5);
	SMG_All(0xff);
}
 
void main()
{
  Init_System();  
  while(1)
  {
    Read_Dsiplay_DS18B20();
  }
}























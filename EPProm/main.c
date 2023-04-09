//#include "stc15f2k60s2.h"
//#include "iic.h"
//
//unsigned char code duanma[18]={0xc0,0xf9,
//    0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf};
//unsigned char dat1 = 0,dat2 = 0,dat3 = 0;
//
//
//void Delay(unsigned char t)
//{
//	while(t--);
//}
//
//void SelectHC573(unsigned char channel,unsigned char dat)
//{
//	P0 = dat;
//	switch(channel)
//	{
//		case 4:P2 = (P2 & 0x1f) | 0x80;break;
//		case 5:P2 = (P2 & 0x1f) | 0xa0;break;
//		case 6:P2 = (P2 & 0x1f) | 0xc0;break;
//		case 7:P2 = (P2 & 0x1f) | 0xe0;break;
//		case 0:P2 = (P2 & 0x1f) | 0x00;break;	
//	}
//	P2 = (P2 & 0x1f) | 0x00;
//}
//
//void DisplaySMG(unsigned char pos,unsigned char dat)
//{
//	SelectHC573(6,0x01 << pos);
//	SelectHC573(7,dat);
//	Delay(500);
//	SelectHC573(6,0x01 << pos);
//	SelectHC573(7,0xff);
//
//}
//
//void DisplaySMG_All(unsigned char value)
//{
//  SelectHC573(6, 0xff);    //ʹ�����������
//  SelectHC573(7, value);  //�������ʾ����  
//}
//void Display()
//{
//	DisplaySMG(0,duanma[dat1 / 10]);
//
//	DisplaySMG(1,duanma[dat1 % 10]);
//							 
//	DisplaySMG(2,duanma[10]);
//
//	DisplaySMG(3,duanma[dat2 / 10]);
//
//	DisplaySMG(4,duanma[dat2 % 10]);
//
//	DisplaySMG(5,duanma[10]);
//
//	DisplaySMG(6,duanma[dat3 / 10]);
//
//	DisplaySMG(7,duanma[dat3 % 10]);
//
//}
//
//void Write_24C02(unsigned char addr,unsigned char dat)
//{
//	IIC_Start();          //��ʼ�ź�
//  	IIC_SendByte(0xa0);    //EEPROM��д�豸��ַ
//  	IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
//  	IIC_SendByte(addr);    //�ڴ浥Ԫ��ַ
//  	IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
//  	IIC_SendByte(dat);    //�ڴ�д������
//  	IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
//  	IIC_Stop();            //ֹͣ�ź�
//  	
//}
//
//unsigned char Read_24C02(unsigned char addr)
//{
//	  unsigned char tmp;
//	  //���ȣ�����һ��αд����
//	  IIC_Start();          //��ʼ�ź�
//	  IIC_SendByte(0xa0);    //EEPROM��д�豸��ַ
//	  IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
//	  IIC_SendByte(addr);    //�ڴ浥Ԫ��ַ
//	  IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
//	  //Ȼ�󣬿�ʼ�ֽڶ�����
//	  IIC_Start();          //��ʼ�ź�
//	  IIC_SendByte(0xa1);    //EEPROM�Ķ��豸��ַ
//	  IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
//	  tmp = IIC_RecByte();  //��ȡ�ڴ��е�����
//	  IIC_SendAck(1);        //������Ӧ���ź�
//	  IIC_Stop();            //ֹͣ�ź�
//	  return tmp;
//
//}
//void Read_Write_24C02()
//{
////  if(Read_24C02(0x21) != 4)
////  {
////  	Write_24C02(0x21,4);
////	Delay(6000); 
////	Write_24C02(0x01,0);
////	Delay(6000); 
////	Write_24C02(0x03,0);
////	Delay(6000); 
////	Write_24C02(0x05,0);
////	Delay(6000);
////  }
//  dat1 = Read_24C02(0x01);  //��24C02��ȡdat1
//  dat2 = Read_24C02(0x03);  //��24C02��ȡdat2
//  dat3 = Read_24C02(0x05);  //��24C02��ȡdat3
//  
//  dat1 = dat1 + 1;          //��1����������+1
//  dat2 = dat2 + 2;          //��2����������+2
//  dat3 = dat3 + 3;          //��3����������+3
//  if(dat1 > 10)
//    dat1 = 0;
//  if(dat2 > 20)
//    dat2 = 0;
//  if(dat3 > 30)
//    dat3 = 0;
//  
//  Write_24C02(0x01, dat1);
//  Delay(6000);            //�ȴ��ֽ�д�����
//  Write_24C02(0x03, dat2);
//  Delay(6000);            //�ȴ�ʱ�䲻����Ӱ��dat3д��
//  Write_24C02(0x05, dat3);
//  Delay(6000);
//}
//						   
//void Init()
//{
//	SelectHC573(0,0x00);
//	SelectHC573(5,0x00);
//	SelectHC573(4,0xff);
//	DisplaySMG_All(0xff);
//  	
//}
//void main()
//{	
//	Init();
//	Read_Write_24C02();
//	while(1)
//	{
//		Display();	
//	}
//
//}

/*==================���ű���Ƭ����ѵ==================
������03����24C02�Ļ�����д����
**ƽ  ̨��CT107D��Ƭ���ۺ�ʵѵƽ̨
**ģ  ʽ��IOģʽ
**�ײ������ļ���2022�꾺����Դ���ݰ��ṩ���ļ�
**��  �ƣ�ŷ��Դ��С�۷���ʦ��ohy3686@qq.com��
**ʱ  �䣺2022-04-01
**���������www.xmf393.com
====================================================*/
#include "stc15f2k60s2.h"
#include "iic.h"

//���嶯̬��ʾ�е�������ܵ���ʱ��
#define TSMG  500
//-------��������ܵĶ���������С���㣩--------
//0 1 2 3 4 5 6 7 8 9 A b C D E F - .
unsigned char code SMG_NoDot[18]={0xc0,0xf9,
    0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
    0x88,0x83,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};
//-----------------------------------------------
//����3����������
unsigned char dat1 = 0, dat2 = 0, dat3 = 0;
//==============����ܶ�̬��ʾר����ʱ����=============
void DelaySMG(unsigned int t)
{
  while(t--);
}
//==================����ѡͨ��������===================
void Set_HC573(unsigned char channel, unsigned char dat)
{
  P0 = dat;                      //����������
  switch(channel)                //ѡͨ������
  {
    case 4:
      P2 = (P2 & 0x1f) | 0x80;  //Y4���0��LED����
    break;
    case 5:
      P2 = (P2 & 0x1f) | 0xa0;  //Y5���0���������ͼ̵�������
    break;
    case 6:
      P2 = (P2 & 0x1f) | 0xc0;  //Y6���0�������λѡ
    break;
    case 7:
      P2 = (P2 & 0x1f) | 0xe0;  //Y7���0������ܶ���
    break;
    case 0:
      P2 = (P2 & 0x1f) | 0x00;  //������������ѡ��
    break;
  }
  P2 = (P2 & 0x1f) | 0x00;      //������ɣ��ر�ȫ��������
}
//=================��������ܶ�̬��ʾ=================
void DisplaySMG_Bit(unsigned char pos, unsigned char value)
{
  Set_HC573(6, 0x01 << pos);    //����ܵĶ�λ
  Set_HC573(7, value);          //�������ʾ����
  DelaySMG(TSMG);                //����ܵ���ʱ��
  Set_HC573(6, 0x01 << pos);        
  Set_HC573(7, 0xff);            //����
}
//=================ȫ������ܾ�̬��ʾ=================
void DisplaySMG_All(unsigned char value)
{
  Set_HC573(6, 0xff);    //ʹ�����������
  Set_HC573(7, value);  //�������ʾ����  
}
//===================��ȡֵ��ʾ����===================
void DisplaySMG_24C02()
{
  //����������0λ
  DisplaySMG_Bit(7,SMG_NoDot[dat3  % 10]);
  //����������1λ
  DisplaySMG_Bit(6,SMG_NoDot[dat3 / 10]);    
  //����������2λ
  DisplaySMG_Bit(5,SMG_NoDot[16]);        
  
  //����������3λ
  DisplaySMG_Bit(4,SMG_NoDot[dat2  % 10]);
  //����������4λ
  DisplaySMG_Bit(3,SMG_NoDot[dat2 / 10]);    
  //����������5λ
  DisplaySMG_Bit(2,SMG_NoDot[16]);        
  
  //����������6λ
  DisplaySMG_Bit(1,SMG_NoDot[dat1 % 10]);        
  //����������7λ
  DisplaySMG_Bit(0,SMG_NoDot[dat1 / 10]);        
}
//================24C02���ֽ�д��=================
void Write_24C02(unsigned char addr, unsigned char dat)
{
  IIC_Start();          //��ʼ�ź�
  IIC_SendByte(0xa0);    //EEPROM��д�豸��ַ
  IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
  IIC_SendByte(addr);    //�ڴ浥Ԫ��ַ
  IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
  IIC_SendByte(dat);    //�ڴ�д������
  IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
  IIC_Stop();            //ֹͣ�ź�
}
//================24C02���ֽڶ�ȡ=================
unsigned char Read_24C02(unsigned char addr)
{
  unsigned char tmp;
  //���ȣ�����һ��αд����
  IIC_Start();          //��ʼ�ź�
  IIC_SendByte(0xa0);    //EEPROM��д�豸��ַ
  IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
  IIC_SendByte(addr);    //�ڴ浥Ԫ��ַ
  IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
  //Ȼ�󣬿�ʼ�ֽڶ�����
  IIC_Start();          //��ʼ�ź�
  IIC_SendByte(0xa1);    //EEPROM�Ķ��豸��ַ
  IIC_WaitAck();        //�ȴ��ӻ�Ӧ��
  tmp = IIC_RecByte();  //��ȡ�ڴ��е�����
  IIC_SendAck(1);        //������Ӧ���ź�		
  IIC_Stop();            //ֹͣ�ź�
  return tmp;
}
//==============24C02���ݶ�ȡ��д��===============
void Read_Write_24C02()
{
  dat1 = Read_24C02(0x01);  //��24C02��ȡdat1
  dat2 = Read_24C02(0x03);  //��24C02��ȡdat2
  dat3 = Read_24C02(0x05);  //��24C02��ȡdat3
  
  dat1 = dat1 + 1;          //��1����������+1
  dat2 = dat2 + 2;          //��2����������+2
  dat3 = dat3 + 3;          //��3����������+3
  if(dat1 > 10)
    dat1 = 0;
  if(dat2 > 20)
    dat2 = 0;
  if(dat3 > 30)			  
    dat3 = 0;
  
  Write_24C02(0x01, dat1);
  DelaySMG(6000);            //�ȴ��ֽ�д�����
  Write_24C02(0x03, dat2);
  DelaySMG(6000);            //�ȴ�ʱ�䲻����Ӱ��dat3д��
  Write_24C02(0x05, dat3);
  DelaySMG(6000);
}
//===================ϵͳ��ʼ��===================
void Init_sys()
{
  Set_HC573(0, 0x00);        //�ر�����������
  Set_HC573(5, 0x00);        //�رշ������ͼ̵���
  Set_HC573(4, 0xff);        //�ر�ȫ��LED��
  DisplaySMG_All(0xff);      //�ر�ȫ�������
}
//=======================������=======================
void main()
{
  Init_sys();                //ϵͳ��ʼ��
  Read_Write_24C02();        //��д24C02��������Ԫ������
  while(1)
  {
    DisplaySMG_24C02();      //ѭ����̬ˢ�������
  }
}


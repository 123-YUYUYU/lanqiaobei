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
//  SelectHC573(6, 0xff);    //使能所有数码管
//  SelectHC573(7, value);  //数码管显示内容  
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
//	IIC_Start();          //起始信号
//  	IIC_SendByte(0xa0);    //EEPROM的写设备地址
//  	IIC_WaitAck();        //等待从机应答
//  	IIC_SendByte(addr);    //内存单元地址
//  	IIC_WaitAck();        //等待从机应答
//  	IIC_SendByte(dat);    //内存写入数据
//  	IIC_WaitAck();        //等待从机应答
//  	IIC_Stop();            //停止信号
//  	
//}
//
//unsigned char Read_24C02(unsigned char addr)
//{
//	  unsigned char tmp;
//	  //首先，进行一个伪写操作
//	  IIC_Start();          //起始信号
//	  IIC_SendByte(0xa0);    //EEPROM的写设备地址
//	  IIC_WaitAck();        //等待从机应答
//	  IIC_SendByte(addr);    //内存单元地址
//	  IIC_WaitAck();        //等待从机应答
//	  //然后，开始字节读操作
//	  IIC_Start();          //起始信号
//	  IIC_SendByte(0xa1);    //EEPROM的读设备地址
//	  IIC_WaitAck();        //等待从机应答
//	  tmp = IIC_RecByte();  //读取内存中的数据
//	  IIC_SendAck(1);        //产生非应答信号
//	  IIC_Stop();            //停止信号
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
//  dat1 = Read_24C02(0x01);  //从24C02读取dat1
//  dat2 = Read_24C02(0x03);  //从24C02读取dat2
//  dat3 = Read_24C02(0x05);  //从24C02读取dat3
//  
//  dat1 = dat1 + 1;          //第1个计数变量+1
//  dat2 = dat2 + 2;          //第2个计数变量+2
//  dat3 = dat3 + 3;          //第3个计数变量+3
//  if(dat1 > 10)
//    dat1 = 0;
//  if(dat2 > 20)
//    dat2 = 0;
//  if(dat3 > 30)
//    dat3 = 0;
//  
//  Write_24C02(0x01, dat1);
//  Delay(6000);            //等待字节写入完成
//  Write_24C02(0x03, dat2);
//  Delay(6000);            //等待时间不够会影响dat3写入
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

/*==================蓝桥杯单片机特训==================
【进阶03】：24C02的基本读写操作
**平  台：CT107D单片机综合实训平台
**模  式：IO模式
**底层驱动文件：2022年竞赛资源数据包提供的文件
**设  计：欧浩源（小蜜蜂老师，ohy3686@qq.com）
**时  间：2022-04-01
**更多详见：www.xmf393.com
====================================================*/
#include "stc15f2k60s2.h"
#include "iic.h"

//定义动态显示中单个数码管点亮时长
#define TSMG  500
//-------共阳数码管的段码编码表（无小数点）--------
//0 1 2 3 4 5 6 7 8 9 A b C D E F - .
unsigned char code SMG_NoDot[18]={0xc0,0xf9,
    0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,
    0x88,0x83,0xc6,0xc0,0x86,0x8e,0xbf,0x7f};
//-----------------------------------------------
//定义3个计数变量
unsigned char dat1 = 0, dat2 = 0, dat3 = 0;
//==============数码管动态显示专用延时函数=============
void DelaySMG(unsigned int t)
{
  while(t--);
}
//==================设置选通的锁存器===================
void Set_HC573(unsigned char channel, unsigned char dat)
{
  P0 = dat;                      //待设置数据
  switch(channel)                //选通锁存器
  {
    case 4:
      P2 = (P2 & 0x1f) | 0x80;  //Y4输出0，LED控制
    break;
    case 5:
      P2 = (P2 & 0x1f) | 0xa0;  //Y5输出0，蜂鸣器和继电器控制
    break;
    case 6:
      P2 = (P2 & 0x1f) | 0xc0;  //Y6输出0，数码管位选
    break;
    case 7:
      P2 = (P2 & 0x1f) | 0xe0;  //Y7输出0，数码管段码
    break;
    case 0:
      P2 = (P2 & 0x1f) | 0x00;  //所有锁存器不选择
    break;
  }
  P2 = (P2 & 0x1f) | 0x00;      //设置完成，关闭全部锁存器
}
//=================单个数码管动态显示=================
void DisplaySMG_Bit(unsigned char pos, unsigned char value)
{
  Set_HC573(6, 0x01 << pos);    //数码管的段位
  Set_HC573(7, value);          //数码管显示内容
  DelaySMG(TSMG);                //数码管点亮时长
  Set_HC573(6, 0x01 << pos);        
  Set_HC573(7, 0xff);            //消隐
}
//=================全部数码管静态显示=================
void DisplaySMG_All(unsigned char value)
{
  Set_HC573(6, 0xff);    //使能所有数码管
  Set_HC573(7, value);  //数码管显示内容  
}
//===================读取值显示函数===================
void DisplaySMG_24C02()
{
  //数码管右起第0位
  DisplaySMG_Bit(7,SMG_NoDot[dat3  % 10]);
  //数码管右起第1位
  DisplaySMG_Bit(6,SMG_NoDot[dat3 / 10]);    
  //数码管右起第2位
  DisplaySMG_Bit(5,SMG_NoDot[16]);        
  
  //数码管右起第3位
  DisplaySMG_Bit(4,SMG_NoDot[dat2  % 10]);
  //数码管右起第4位
  DisplaySMG_Bit(3,SMG_NoDot[dat2 / 10]);    
  //数码管右起第5位
  DisplaySMG_Bit(2,SMG_NoDot[16]);        
  
  //数码管右起第6位
  DisplaySMG_Bit(1,SMG_NoDot[dat1 % 10]);        
  //数码管右起第7位
  DisplaySMG_Bit(0,SMG_NoDot[dat1 / 10]);        
}
//================24C02单字节写入=================
void Write_24C02(unsigned char addr, unsigned char dat)
{
  IIC_Start();          //起始信号
  IIC_SendByte(0xa0);    //EEPROM的写设备地址
  IIC_WaitAck();        //等待从机应答
  IIC_SendByte(addr);    //内存单元地址
  IIC_WaitAck();        //等待从机应答
  IIC_SendByte(dat);    //内存写入数据
  IIC_WaitAck();        //等待从机应答
  IIC_Stop();            //停止信号
}
//================24C02单字节读取=================
unsigned char Read_24C02(unsigned char addr)
{
  unsigned char tmp;
  //首先，进行一个伪写操作
  IIC_Start();          //起始信号
  IIC_SendByte(0xa0);    //EEPROM的写设备地址
  IIC_WaitAck();        //等待从机应答
  IIC_SendByte(addr);    //内存单元地址
  IIC_WaitAck();        //等待从机应答
  //然后，开始字节读操作
  IIC_Start();          //起始信号
  IIC_SendByte(0xa1);    //EEPROM的读设备地址
  IIC_WaitAck();        //等待从机应答
  tmp = IIC_RecByte();  //读取内存中的数据
  IIC_SendAck(1);        //产生非应答信号		
  IIC_Stop();            //停止信号
  return tmp;
}
//==============24C02数据读取与写入===============
void Read_Write_24C02()
{
  dat1 = Read_24C02(0x01);  //从24C02读取dat1
  dat2 = Read_24C02(0x03);  //从24C02读取dat2
  dat3 = Read_24C02(0x05);  //从24C02读取dat3
  
  dat1 = dat1 + 1;          //第1个计数变量+1
  dat2 = dat2 + 2;          //第2个计数变量+2
  dat3 = dat3 + 3;          //第3个计数变量+3
  if(dat1 > 10)
    dat1 = 0;
  if(dat2 > 20)
    dat2 = 0;
  if(dat3 > 30)			  
    dat3 = 0;
  
  Write_24C02(0x01, dat1);
  DelaySMG(6000);            //等待字节写入完成
  Write_24C02(0x03, dat2);
  DelaySMG(6000);            //等待时间不够会影响dat3写入
  Write_24C02(0x05, dat3);
  DelaySMG(6000);
}
//===================系统初始化===================
void Init_sys()
{
  Set_HC573(0, 0x00);        //关闭所有锁存器
  Set_HC573(5, 0x00);        //关闭蜂鸣器和继电器
  Set_HC573(4, 0xff);        //关闭全部LED灯
  DisplaySMG_All(0xff);      //关闭全部数码管
}
//=======================主函数=======================
void main()
{
  Init_sys();                //系统初始化
  Read_Write_24C02();        //读写24C02的三个单元的数据
  while(1)
  {
    DisplaySMG_24C02();      //循环动态刷新数码管
  }
}


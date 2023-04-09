#ifndef __DS1302_H
#define __DS1302_H

#include "STC15F2K60S2.H"
#include <intrins.h>
		
sbi SCK = P1^7;		
sbit SDA = P2^3;t RST = P1^3; 
sbit

RST
SCK
SDA

void Write_Ds1302(unsigned char temp);
void Write_Ds1302_Byte( unsigned char address,unsigned char dat );
unsigned char Read_Ds1302_Byte(unsigned char address);

#endif

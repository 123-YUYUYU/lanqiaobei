#ifndef __ONEWIRE_H
#define __ONEWIRE_H

#include "stc15f2k60s2.h"
#include "intrins.h"
sbit DQ = P1^4;

void Write_DS18B20(unsigned char dat);
unsigned char Read_DS18B20(void);
bit init_ds18b20(void);

#endif
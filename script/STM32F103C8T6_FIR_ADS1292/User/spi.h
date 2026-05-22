//-----------------------------------------------------------------
//   - V1.0: (2014-02-07)spi驱动头文件
// - V1.0.1:(2014-02-16)头文件中不包含其他头文件
//-----------------------------------------------------------------
#ifndef __SPI_H
#define __SPI_H
#include <stm32f10x.h>
			  	    													  
void SPI2_Init(void);			 //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet); //设置SPI速度   
u8 SPI2_ReadWriteByte(u8 TxData);

		 
#endif

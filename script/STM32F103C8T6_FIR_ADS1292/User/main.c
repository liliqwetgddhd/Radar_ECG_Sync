// 版    本: V1.0
//           ADS1292心电实验
//           2019/1/12
// 说    明: 接口说明
// 					 (1) 本程序可以通过上位机ADS1292调试工具显示心电模拟器的心电波和呼吸波;
//					 但是只能测试显示人体的心电波形						 
//					 (2) 接口说明
//						ADS1292模块            核心板
// 						  PW(PWDN)		->  		 	PB10
// 					    ST(START)  	->   			PB11
// 						  CS  	 			->   			PB12
// 						  DR(DRDY)		->   			PA8
// 						  SCL(SCLK)		->   			PB13
// 						  OUT(DOUT)		->   			PB14
// 						  IN(DIN)			->   			PB15
//              5V 					->   			5V
//						  GND					->	 			GND
//							sync_out    ->				PB9
//
//					 USB转串口模块           核心板
//							RXD					->				PA9
//							TXD					->				PA10
//							GND					->				GND
//
//					   三导联线					 		人体（导联线需要用电极片）
//						 红线（RL）		-> 				右脚
//						 黄线（LA）		-> 				左脚
//						 绿线（RA）		-> 				右手
//
//					   三导联线						 心电模拟器(测试心电波形)
//						 红线（RL）		-> 				 RL
//						 黄线（LA）		-> 				 LA
//						 绿线（RA）		-> 				 RA
//					   三导联线						 心电模拟器(测试呼吸波形, 首先请保证心电模拟器具有呼吸波功能)
//						 红线（RL）		-> 				 RL
//						 黄线（LA）		-> 				 LL
//						 绿线（RA）		-> 				 RA
//
//					 (3) ADS1292调试工具显示和液晶显示不能同时进行, 本程序使用的是ADS1292串口上位机显示程序
//
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "stm32f10x.h"
#include "Delay.h"
#include "LED.h"
#include "usart.h"	
#include "ADS1292.h"	
#include "spi.h"
#include "EXTInterrupt.h"
#include "PeripheralInit.h"
#include "arm_math.h"

//-----------------------------------------------------------------
// 主程序
//-----------------------------------------------------------------
u32 ch1_data;		// 通道1的数据
u32 ch2_data;		// 通道2的数据
u8 flog;				// 触发中断标志位
u16 point_cnt;	// 两个峰值之间的采集点数，用于计算心率

u32 samples_sum = 1000;					//采样总数
u32 point_flog_sum = 0;
u32 point_flog = 0;


#define Samples_Number  1    											// 采样点数
#define Block_Size      1     										// 调用一次arm_fir_f32处理的采样点个数
#define NumTaps        	129     									// 滤波器系数个数

uint32_t blockSize = Block_Size;									// 调用一次arm_fir_f32处理的采样点个数
uint32_t numBlocks = Samples_Number/Block_Size;   // 需要调用arm_fir_f32的次数

float32_t Input_data1; 														// 输入缓冲区
float32_t Output_data1;         									// 输出缓冲区
float32_t firState1[Block_Size + NumTaps - 1]; 		// 状态缓存，大小numTaps + blockSize - 1
float32_t Input_data2; 														// 输入缓冲区
float32_t Output_data2;         									// 输出缓冲区
float32_t firState2[Block_Size + NumTaps - 1]; 		// 状态缓存，大小numTaps + blockSize - 1


int main(void)
{

	
	flog=0;
	sync_out_L;
	
  PeripheralInit(); // 外设初始化
	
	CS_L;
	Delay_1us(10);
  SPI2_ReadWriteByte(RDATAC);		// 发送启动连续读取数据命令
  Delay_1us(10);
	CS_H;						
  START_H; 				// 启动转换
	CS_L;
	sync_flog_L;
  while (1)
  {	
		
		if(flog==1)
		{

			// 通道1呼吸波数据			
			Input_data1=(u32)(ch1_data^0x800000);
			// 实现FIR滤波
			
			// 通道2心电波形数据			
			Input_data2=(u32)(ch2_data^0x800000);
			// 实现FIR滤波
			
			// 数据：呼吸波、心电信号、心率
			if(point_flog_sum < (samples_sum + 1) && point_flog == 1)
			{
				printf("%8d\n",((u32)Input_data2));
			}
			point_flog = 1;
			flog=0;

		}
  }
}

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------

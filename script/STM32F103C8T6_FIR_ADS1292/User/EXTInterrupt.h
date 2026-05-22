

#ifndef _EXTInterrupt_H
#define _EXTInterrupt_H

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
void GPIO_EXTInterrupt_Configuration(void);
void EXTInterrupt_Mode_Configuration(void);
void NVIC_Configuration(void);
extern void EXTInterrupt_Init(void);

#endif

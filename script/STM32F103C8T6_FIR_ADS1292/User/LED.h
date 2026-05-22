//-----------------------------------------------------------------

#ifndef _LED_H
#define _LED_H

//-----------------------------------------------------------------
// 位操作
//-----------------------------------------------------------------
#define LED1_ON      GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define LED1_OFF     GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define LED1_State   GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13)
#define LED1_Toggle  GPIO_WriteBit(GPIOC, GPIO_Pin_13, (BitAction)(1 - LED1_State))

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
extern void GPIO_LED_Configuration(void);

#endif

//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------

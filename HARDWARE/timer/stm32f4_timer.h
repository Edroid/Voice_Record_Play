#ifndef __STM32F4_TIMER_H
#define __STM32F4_TIMER_H

#include "stm32f4xx.h"

#define WRITECOMPLED 1;

//uint32_t writeAdder = 0x0800C004;  //从扇区3开始写入
//uint32_t readAdder = 0x0800C004;  //从扇区3开始读出
//uint32_t readflash;

void TIM3_config(void);
void TIM2_config(void);

#endif


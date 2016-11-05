#ifndef __STM32F4_KEY_H
#define __STM32F4_KEY_H

#include "stm32f4xx.h"


typedef struct key_gpio_s
{
	int num; 	              /*led编号*/
	GPIO_TypeDef	*group;   /*LED使用的是哪一组GPIO*/
	u16	pin;                /*LED使用的GPIO组中哪一个pin*/
} key_gpio_t;


enum
{
	KEY1 = 0,
	KEY2 = 1,
	KEY3 = 2,
	MAX_KEY,
}; 


 void key_config(void);
u8 key_pressed(int witch);

#endif



/*********************************************************************************
   *      Copyright:  (C) 2016 SCUEC
   *                  All rights reserved.
   *
   *       Filename:  stm32_key.c
   *    Description: 
   *
   *        Version:  1.0.0(5/11/16)
   *         Author:  LI WJNG <liwjng@gmail.com>
   *      ChangeLog:  1, Release initial version on "5/11/16 09:59:18"
   *
   ********************************************************************************/
	 
#include "stm32f4_key.h"

static key_gpio_t   key_gpio[MAX_KEY] =
{
		{KEY1, GPIOF, GPIO_Pin_3}, 
    {KEY2, GPIOF, GPIO_Pin_4},
		{KEY3, GPIOF, GPIO_Pin_5},
		
};

void key_config(void)

{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	 
}

u8 key_pressed(int witch)
{
	int keyvalue = 0;
	keyvalue = GPIO_ReadInputDataBit(key_gpio[witch].group,key_gpio[witch].pin);
	return !keyvalue;
}


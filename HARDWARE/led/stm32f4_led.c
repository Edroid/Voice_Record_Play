/*********************************************************************************
   *      Copyright:  (C) 2016 SCUEC
   *                  All rights reserved.
   *
   *       Filename:  stm32_led.c
   *    Description: 
   *
   *        Version:  1.0.0(5/11/16)
   *         Author:  LI WJNG <liwjng@gmail.com>
   *      ChangeLog:  1, Release initial version on "5/11/16 09:45:18"
   *
   ********************************************************************************/
	 
//注意：stm32使用任何外设都必须要使能外设的时钟，GPIO也是一样
#include "stm32f4_led.h"
#include "sys.h"

static led_gpio_t   leds_gpio[MAX_LED] =
{
		{LED2, GPIOF, GPIO_Pin_7}, 
    {LED3, GPIOF, GPIO_Pin_8},
		{LED4, GPIOF, GPIO_Pin_9},
		{LED5, GPIOF, GPIO_Pin_10},
};


void Init_LED_GPIO(void)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_OUT;             //
	GPIO_Initstructure.GPIO_OType = GPIO_OType_PP;            //推完输出
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;     //
	GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;             //上拉输入
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_100MHz;        //
	
	GPIO_Init(GPIOF,&GPIO_Initstructure);
	GPIO_SetBits(GPIOF,GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10); 
}


void turn_led(int witch,int cmd)
{
	if(witch<0 || witch>MAX_LED)
		return ;
	if(OFF == cmd)
		GPIO_SetBits(leds_gpio[witch].group,leds_gpio[witch].pin);
	if(ON == cmd)
		GPIO_ResetBits(leds_gpio[witch].group,leds_gpio[witch].pin);
}

void twinkle_led(int witch)
{
	if(witch<0||witch>MAX_LED)
		return ;
	else
		LED_5 = !LED_5;
}

/*********************************************************************************
   *      Copyright:  (C) 2016 SCUEC
   *                  All rights reserved.
   *
   *       Filename:  main.c
   *    Description: 
   *
   *        Version:  1.0.0(5/11/16)
   *         Author:  LI WJNG <liwjng@gmail.com>
   *      ChangeLog:  1, Release initial version on "5/11/16 10:52:13"
   *
   ********************************************************************************/
	 
#include "stm32f4xx.h"
#include "stm32f4_flash.h"
#include "stm32f4_timer.h"
#include "stm32f4_adc.h"
#include "stm32f4_dac.h"
#include "stm32f4_key.h"
#include "stm32f4_led.h"

extern uint32_t g_writeAdder;
extern uint32_t g_readAdder;
volatile u16 g_flag = 0;
void Record(void);
void  Play(void);

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
  key_config();       //按键初始化
  Init_LED_GPIO();    //LED初始化
  TIM2_config();      //TIM2定时器配置
	TIM3_config();      //TIM3定时器配置，
	ADC_config();       //ADC配置
	DMA_config();       //DMA配置
	DAC_config();       //DAC配置
	
	while(1)
  {		
		if(key_pressed(KEY1) && !g_flag)
		{
			Record();
		}
		
		if(g_flag && key_pressed(KEY2))
		{
			Play();//开始执行Play函数
			if(g_readAdder == 0x0800C004)
			{
			 TIM_Cmd(TIM2,DISABLE);
			}
		}
  }

}
 


/***************采集并且存储**************/		
void Record(void)
{
	turn_led(LED2,ON);//LED相关参数配置，点亮LED3
	TIM_Cmd(TIM3,ENABLE); 
}


/*****读取flash中的值并通过DAC输出*/
void Play(void)
{
	TIM_Cmd(TIM2,ENABLE); //使能定时器2
	turn_led(LED4,ON);
}





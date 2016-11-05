/*********************************************************************************
   *      Copyright:  (C) 2016 SCUEC
   *                  All rights reserved.
   *
   *       Filename:  stm32_timer.c
   *    Description: 
   *
   *        Version:  1.0.0(5/11/16)
   *         Author:  LI WJNG <liwjng@gmail.com>
   *      ChangeLog:  1, Release initial version on "5/11/16 09:59:18"
   *
   ********************************************************************************/


#include "stm32f4_timer.h"
#include "stm32f4_flash.h"
#include "usart.h"
#include "stm32f4_led.h"

#define ARR	100-1
#define PRESCARE	42-1
uint32_t g_writeAdder = 0x0800C004;  //从扇区3开始写入
uint32_t g_readAdder = 0x0800C004;   //从扇区3开始读出
uint32_t readflash;
extern uint32_t g_ADC_Value;
extern u16 g_flag;
void 
	TIM3_config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //84MHz 
	
  TIM_TimeBaseInitStructure.TIM_Period = ARR; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler =PRESCARE ;  
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); 
	
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


void TIM2_config(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  ///使能TIM2时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = ARR; 	
	TIM_TimeBaseInitStructure.TIM_Prescaler=PRESCARE;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);//初始化TIM2
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE); //允许定时器2更新中断
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //定时器2中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


/*********定时2器控制以一定的时间读取flash中的值转化成模拟信号输出*/
void  TIM2_IRQHandler(void)//播放
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
	{
		if(g_readAdder <=0x080FFFFF)//如果flash中的数据还没读完
		{
				
			  readflash=STMFLASH_Read(g_readAdder); //读取flash中的数据
			
			  DAC_SetChannel2Data(DAC_Align_12b_R,readflash);  //并将读取的数据通过DAC输出
			  g_readAdder+=4;//地址增加4，方便下一次读取数据		
		}
		else
		{
			g_readAdder = 0x0800C004; //设置读取地址为Flash首地址，方便重复读取
			TIM_Cmd(TIM2,DISABLE);     //关闭定时器2
			turn_led(LED4,OFF);        //熄灭LED4，表示读取结束
		}

		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); 
	}
}


/*******定时器3控制以一定的速度往flash中写入数字量*/
void   TIM3_IRQHandler(void)  //采集
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //如果TIM3设置的数值溢出
	{
		

    if(g_writeAdder<=0x080FFFFF)//如果flash还没写满
		{
			
		  STMFLASH_Write(g_writeAdder,g_ADC_Value); //向flash里面写入ADC采样得到的数g_ADC_Value
			g_writeAdder += 4;//地址加4 ，便于下一次存入
		}
		else
			{	
        TIM_Cmd(TIM3,DISABLE);				
				ADC_Cmd(ADC1, DISABLE);
				ADC_DMACmd(ADC1, DISABLE); 
				turn_led(LED2,OFF);//如果flash内存已经写满，则熄灭LED3
				g_flag = 1;
			}
			
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

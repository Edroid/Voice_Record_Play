/*********************************************************************************
   *      Copyright:  (C) 2016 SCUEC
   *                  All rights reserved.
   *
   *       Filename:  stm32_dac.c
   *    Description: 
   *
   *        Version:  1.0.0(5/11/16)
   *         Author:  LI WJNG <liwjng@gmail.com>
   *      ChangeLog:  1, Release initial version on "5/11/16 09:59:18"
   *
   ********************************************************************************/
	 
#include "stm32f4_dac.h"

void  DAC_config(void)
{
	GPIO_InitTypeDef      GPIO_InitStructure;
	DAC_InitTypeDef       DAC_InitType;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能 PA 时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//使能 DAC 时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //PA5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 GPIO
	
	DAC_InitType.DAC_Trigger = DAC_Trigger_None; //不使用触发功能 TEN1=0
	DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置			
	DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable ;//输出缓存关闭
	DAC_Init(DAC_Channel_2,&DAC_InitType); //初始化 DAC 通道 2
	DAC_Cmd(DAC_Channel_2, ENABLE); //使能 DAC 通道 1
		
}



/*********************************************************************************
   *      Copyright:  (C) 2016 SCUEC
   *                  All rights reserved.
   *
   *       Filename:  stm32_adc.c
   *    Description: 
   *
   *        Version:  1.0.0(5/11/16)
   *         Author:  LI WJNG <liwjng@gmail.com>
   *      ChangeLog:  1, Release initial version on "5/11/16 09:59:18"
   *
   ********************************************************************************/
	
	
#include "stm32f4_adc.h"

#define  ADC1_DR_ADDRESS         ((uint32_t)0x4001204C) //ADC1 DR¼Ä´æÆ÷»ùµØÖ·

uint32_t g_ADC_Value;

void ADC_config(void)
{

  ADC_InitTypeDef       ADC_InitStructure;
 
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
 
  GPIO_InitTypeDef      GPIO_InitStructure;
  
  RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;  
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	

  RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);
	
  RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);  	
 
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;
  
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_2;
  
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  
  ADC_CommonInit(&ADC_CommonInitStructure);
 
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; 
  
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;
  
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
												
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  
  ADC_Init(ADC1, &ADC_InitStructure);

 ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_15Cycles);
 

  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);

  ADC_DMACmd(ADC1, ENABLE);  

  ADC_Cmd(ADC1, ENABLE);
  
  ADC_SoftwareStartConv(ADC1);

}




void DMA_config(void)
{
  DMA_InitTypeDef      DMA_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&g_ADC_Value;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);         

}


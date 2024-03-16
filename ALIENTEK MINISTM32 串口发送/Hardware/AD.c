#include "stm32f10x.h"                  // Device header


uint16_t AD_Value[4];


void AD_Init(void)
{
	//开启adc gpio时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADCCLK = 72MHZ/6 = 12MHZ
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//gpio配置成模拟输入
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
	
	//配置adc转换器
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//连续扫描
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//扫描模式
	ADC_Init(ADC1, &ADC_InitStructure);
	

	DMA_InitTypeDef DMA_InitStructure;	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//外设站点起始地址
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//数据宽度(半字)
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//不自增
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;//存储器站点起始地址
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;//数据宽度
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//自增	

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向 //外设站点作数据源端
	DMA_InitStructure.DMA_BufferSize = 4;//传输计数器
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA循环模式
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//硬件触发	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	//开启DMA触发信号
	ADC_DMACmd(ADC1, ENABLE);  
	
	//开启adc
	ADC_Cmd(ADC1, ENABLE);
	
	//adc校准
	ADC_ResetCalibration(ADC1);//复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);//返回复位校准的状态 开始校准：1 SET 校准完成：0 RESET
	ADC_StartCalibration(ADC1);//开始校准
	while (ADC_GetCalibrationStatus(ADC1) == SET);//返回开始校准的状态
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换
}





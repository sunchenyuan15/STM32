#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	//开启adc gpio时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADCCLK = 72MHZ/6 = 12MHZ
	
	//gpio配置成模拟输入
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//配置多路开关 规则组列表
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	//配置adc转换器
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//单次转换
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//软件触发
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//开启adc
	ADC_Cmd(ADC1, ENABLE);
	
	//adc校准
	ADC_ResetCalibration(ADC1);//复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);//返回复位校准的状态 开始校准：1 SET 校准完成：0 RESET
	ADC_StartCalibration(ADC1);//开始校准
	while (ADC_GetCalibrationStatus(ADC1) == SET);//返回开始校准的状态
}

uint16_t AD_GetValue(void)//无符号16位整型
{
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//软件触发转换
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//规则组转换完成标志位 转换完成：1 SET 开始转换：0 RESET
	return ADC_GetConversionValue(ADC1);	
}

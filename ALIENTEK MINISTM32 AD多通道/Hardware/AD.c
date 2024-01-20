#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	//����adc gpioʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADCCLK = 72MHZ/6 = 12MHZ
	
	//gpio���ó�ģ������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	
	//����adcת����
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//����ת��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//����adc
	ADC_Cmd(ADC1, ENABLE);
	
	//adcУ׼
	ADC_ResetCalibration(ADC1);//��λУ׼
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);//���ظ�λУ׼��״̬ ��ʼУ׼��1 SET У׼��ɣ�0 RESET
	ADC_StartCalibration(ADC1);//��ʼУ׼
	while (ADC_GetCalibrationStatus(ADC1) == SET);//���ؿ�ʼУ׼��״̬
}

uint16_t AD_GetValue(uint8_t ADC_Channel)//unsigned char
{
	//���ö�·���� �������б�
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//�������ת��
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//������ת����ɱ�־λ ת����ɣ�1 SET ��ʼת����0 RESET
	return ADC_GetConversionValue(ADC1);	
}



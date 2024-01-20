#include "stm32f10x.h"                  // Device header


uint16_t AD_Value[4];


void AD_Init(void)
{
	//����adc gpioʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADCCLK = 72MHZ/6 = 12MHZ
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	//gpio���ó�ģ������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
	
	//����adcת����
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//����ɨ��
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�������
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_NbrOfChannel = 4;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//ɨ��ģʽ
	ADC_Init(ADC1, &ADC_InitStructure);
	

	DMA_InitTypeDef DMA_InitStructure;	
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//����վ����ʼ��ַ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���ݿ��(����)
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//������
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)AD_Value;//�洢��վ����ʼ��ַ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_HalfWord;//���ݿ��
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//����	

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//���䷽�� //����վ��������Դ��
	DMA_InitStructure.DMA_BufferSize = 4;//���������
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMAѭ��ģʽ
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//Ӳ������	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, ENABLE);
	
	//����DMA�����ź�
	ADC_DMACmd(ADC1, ENABLE);  
	
	//����adc
	ADC_Cmd(ADC1, ENABLE);
	
	//adcУ׼
	ADC_ResetCalibration(ADC1);//��λУ׼
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);//���ظ�λУ׼��״̬ ��ʼУ׼��1 SET У׼��ɣ�0 RESET
	ADC_StartCalibration(ADC1);//��ʼУ׼
	while (ADC_GetCalibrationStatus(ADC1) == SET);//���ؿ�ʼУ׼��״̬
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//�������ת��
}





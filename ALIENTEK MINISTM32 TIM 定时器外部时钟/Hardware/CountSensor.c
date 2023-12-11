#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	////
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXIT_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//����GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//����AFIOʱ��
	////EXTI NVICʱ��ʼ�տ���
		
	
	//����GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//����AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);
	
	//����EXTI
	EXIT_InitStructure.EXTI_Line = EXTI_Line15;
	EXIT_InitStructure.EXTI_LineCmd = ENABLE;
	EXIT_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXIT_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	EXTI_Init(&EXIT_InitStructure);
	
	//����NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 1;
	NVIC_Init(&NVIC_InitStructure);	
	
}
//�ⲿ�ж��ź� GPIO->AFIO->EXTI->NVIC->CPU

uint16_t CountSensor_Get(void)//���ر���ֵ
{
	return CountSensor_Count;
	
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line15) == SET)//�жϱ�־λ�ж� ȷ���Ƕ�����ж�Դ�������жϺ���
	{
		CountSensor_Count ++;
		
		EXTI_ClearITPendingBit(EXTI_Line15);//�жϱ�־λ���
	}
	
}

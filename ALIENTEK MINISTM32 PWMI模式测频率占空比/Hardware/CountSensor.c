#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;

void CountSensor_Init(void)
{
	////
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXIT_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//开启GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//开启AFIO时钟
	////EXTI NVIC时钟始终开启
		
	
	//配置GPIO
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource15);
	
	//配置EXTI
	EXIT_InitStructure.EXTI_Line = EXTI_Line15;
	EXIT_InitStructure.EXTI_LineCmd = ENABLE;
	EXIT_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXIT_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	EXTI_Init(&EXIT_InitStructure);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority  = 1;
	NVIC_Init(&NVIC_InitStructure);	
	
}
//外部中断信号 GPIO->AFIO->EXTI->NVIC->CPU

uint16_t CountSensor_Get(void)//返回变量值
{
	return CountSensor_Count;
	
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line15) == SET)//中断标志位判断 确保是定义的中断源触发的中断函数
	{
		CountSensor_Count ++;
		
		EXTI_ClearITPendingBit(EXTI_Line15);//中断标志位清除
	}
	
}

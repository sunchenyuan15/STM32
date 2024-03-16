#include "stm32f10x.h"                  // Device header



/*TIM2-CH2 PA1*/
void PWM_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InternalClockConfig(TIM2);//配置时基单元时钟
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //采样时钟分频 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式:向上计数
	
	//时基单元寄存器数值
	TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1; //ARR自动重装器
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; //PSC预分配器
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; //REP重复次数计数器   
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	
	
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0; //CCR
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);//通道2
	
	TIM_CtrlPWMOutputs(TIM2,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //CH1预装载使能	 
	
	TIM_ARRPreloadConfig(TIM2, ENABLE); //使能TIMx在ARR上的预装载寄存器
	
	
	
	TIM_Cmd(TIM2, ENABLE); //启动定时器
}


void PWM_SetCompare2(uint16_t Compare)
{
	TIM_SetCompare2(TIM2, Compare);
	
}


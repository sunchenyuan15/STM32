#include "stm32f10x.h"                  // Device header

//extern uint16_t num; //跨文件变量
 
void Timer_Init(void) //定时中断初始化
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; //定义结构体变量
	NVIC_InitTypeDef NVIC_InitTypeStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_InternalClockConfig(TIM2);//配置时基单元时钟
	
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //采样时钟分频 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //计数器模式:向上计数
	
	//时基单元寄存器数值
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1; //ARR自动重装器
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1; //PSC预分配器
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; //REP重复次数计数器   
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //使能更新中断
	
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	NVIC_InitTypeStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitTypeStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级
	NVIC_InitTypeStructure.NVIC_IRQChannelSubPriority = 1; //相应优先级
	
	NVIC_Init(&NVIC_InitTypeStructure);
	
	TIM_Cmd(TIM2, ENABLE); //启动定时器
	

}

//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) //更新中断
//	{

//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除标志位
//			
//	}
//	
//}

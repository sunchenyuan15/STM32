#include "stm32f10x.h"                  // Device header

//extern uint16_t num; //���ļ�����
 
void Timer_Init(void) //��ʱ�жϳ�ʼ��
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; //����ṹ�����
	NVIC_InitTypeDef NVIC_InitTypeStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//	TIM_InternalClockConfig(TIM2);//����ʱ����Ԫʱ�ӣ��ڲ�ʱ�ӣ�
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //��������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);//ETR�ⲿʱ��ģʽ2 A0
	
	
	
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷ�Ƶ 
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //������ģʽ:���ϼ���
	
	//ʱ����Ԫ�Ĵ�����ֵ
	TIM_TimeBaseInitStructure.TIM_Period = 10 - 1; //ARR�Զ���װ��
	TIM_TimeBaseInitStructure.TIM_Prescaler = 1 - 1; //PSCԤ������
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0; //REP�ظ�����������   
	
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //ʹ�ܸ����ж�
	
	//NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	
	NVIC_InitTypeStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitTypeStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitTypeStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�
	NVIC_InitTypeStructure.NVIC_IRQChannelSubPriority = 1; //��Ӧ���ȼ�
	
	NVIC_Init(&NVIC_InitTypeStructure);
	
	TIM_Cmd(TIM2, ENABLE); //������ʱ��
	

}

uint16_t Timer_GetCounter(void)
{
	return TIM_GetCounter(TIM2);
	
}

//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET) //�����ж�
//	{

//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //�����־λ
//			
//	}
//	
//}

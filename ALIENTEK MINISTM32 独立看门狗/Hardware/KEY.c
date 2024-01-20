#include "stm32f10x.h"                  // Device header
#include "delay.h"

//按键 
//A15 KEY1 
//C5 KEY0
void Key_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);//开启时钟

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}

uint8_t Key_GetNum(void) //uint8_t(unsigned char)
{
	uint8_t KeyNum = 0;
	
	if (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) ==0)
	{
		delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_5) ==0);
		{
			
		}
		KeyNum = 1;
			
	}
	
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) ==0)
	{
		delay_ms(10);
		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15) ==0);
		{
			
		}
		KeyNum = 2;
			
	}
	return 	KeyNum;
	
}

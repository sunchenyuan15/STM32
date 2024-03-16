#include "stm32f10x.h"                  // Device header

void LightSensor_Init(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);//开启时钟

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);

}

uint8_t LightSensor_Get(void)
{
	return GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
	
}

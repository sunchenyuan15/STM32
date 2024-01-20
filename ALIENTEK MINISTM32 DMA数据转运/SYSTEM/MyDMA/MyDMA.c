#include "stm32f10x.h"                  // Device header

uint16_t DMA_Size;

void MyDMA_Init(uint32_t AddrA, uint32_t AddrB, uint16_t Size)
{
	DMA_Size = Size;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;	
	DMA_InitStructure.DMA_PeripheralBaseAddr = AddrA;//外设站点起始地址
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//数据宽度
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;//是否自增
	DMA_InitStructure.DMA_MemoryBaseAddr = AddrB;//存储器站点起始地址
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;//数据宽度
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//是否自增	

	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向 //外设站点作数据源端
	DMA_InitStructure.DMA_BufferSize = Size;//传输计数器
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//不自动重装
	DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;//软件触发	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//中等优先级
	
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_Cmd(DMA1_Channel1, DISABLE);
	
}

void MyDMA_Transfer(void)
{
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, DMA_Size);
	DMA_Cmd(DMA1_Channel1, ENABLE);
	while (DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET); //转运完成标志位
	DMA_ClearFlag(DMA1_FLAG_TC1);//清除标志位	
}



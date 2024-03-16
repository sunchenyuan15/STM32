#include "stm32f10x.h"                  // Device header
#include "MyFlash.h"

#define Store_Start_Address 0x0800FC00
#define Store_Count 512

//1024 Byte
uint16_t Store_Data[Store_Count];

//初始化闪存 最后一页
void Store_Init(void)
{
	if(MyFLASH_ReadHalfWord(0x0800FC00) != 0xA5A5 )//第一次使用
	{
		MyFlash_ErasePage(0x0800FC00);//擦除最后一页
		MyFlash_ProgramHalfWord(0x0800FC00, 0xA5A5);//最后一页第一个半字
		for(uint16_t i = 1; i<Store_Count; i++)
		{
			MyFlash_ProgramHalfWord(0x0800FC00 + i*2, 0x0000);//一个半字2个字节，占两个地址
		}
	}
	
	for(uint16_t i = 0; i<Store_Count; i++)
	{
		Store_Data[i] = MyFLASH_ReadHalfWord(0x0800FC00 + i*2);//闪存数据恢复至SRAM数组
	}
}  

void Store_Save(void)
{
	MyFlash_ErasePage(0x0800FC00);//擦除最后一页
	for(uint16_t i = 0; i<Store_Count; i++)
	{
		MyFlash_ProgramHalfWord(0x0800FC00 + i*2, Store_Data[i]);//SRAM数据备份至闪存最后一页
	}
}


void Store_Clear(void)
{
	for(uint16_t i = 1; i<Store_Count; i++)
	{
		Store_Data[i] = 0x0000;
			
	}
	Store_Save();
}






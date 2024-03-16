#include "stm32f10x.h"                  // Device header

//读取
uint32_t MyFLASH_ReadWord(uint32_t Address)
{
	return *((__IO uint32_t *)(Address));	//使用指针访问指定地址下的数据并返回
}


uint16_t MyFLASH_ReadHalfWord(uint32_t Address)
{
	return *((__IO uint16_t *)(Address));	//使用指针访问指定地址下的数据并返回
}


uint8_t MyFLASH_ReadByte(uint32_t Address)
{
	return *((__IO uint8_t *)(Address));	//使用指针访问指定地址下的数据并返回
}

//全擦除
void MyFlash_EraseAllPages(void)
{
	FLASH_Unlock();
	FLASH_EraseAllPages();
	FLASH_Lock();
	
}

//页擦除
void MyFlash_ErasePage(uint32_t PageAddress)
{
	FLASH_Unlock();
	FLASH_ErasePage(PageAddress);
	FLASH_Lock();
	
}

//编程
void MyFlash_ProgramWord(uint32_t Address, uint32_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramWord(Address, Data);
	FLASH_Lock();
}

void MyFlash_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
	FLASH_Unlock();
	FLASH_ProgramHalfWord(Address, Data);
	FLASH_Lock();
}



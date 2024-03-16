#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Inc.h"

void W25Q64_Init(void)
{
	MySPI_Init();
}

//指针实现多返回值
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_JEDEC_ID);
	*MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);//厂商ID
	*DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);//设备ID高8位
	*DID <<= 8;
	*DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);//设备ID低8位
	MySPI_Stop();
}

//写使能
void W25Q64_WriteEnable(void)
{
	MySPI_Start();
	MySPI_SwapByte(W25Q64_WRITE_ENABLE);
	MySPI_Stop();
}

//等待busy的功能
void W25Q64_WaitBusy(void)
{
	uint32_t Timeout=100000;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
	while((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)
	{
		Timeout--;
		if(Timeout == 0)
		{
			break;
		}
			
	}
	MySPI_Stop();
}

//页编程写数据 //使用指针传递数组 Address 3个字节
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
	W25Q64_WriteEnable();
	uint16_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
	
	MySPI_SwapByte(Address >> 16);//最高字节
	MySPI_SwapByte(Address >> 8);//中间字节
	MySPI_SwapByte(Address);//最低字节 
	for(i=0; i<Count; i++)
	{
		MySPI_SwapByte(DataArray[i]);
	}
	MySPI_Stop();
	
	W25Q64_WaitBusy();
	  
} 

//扇区擦除
void W25Q64_SectorErase(uint32_t Address)
{
	W25Q64_WriteEnable();
	MySPI_Start();
	MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
	
	MySPI_SwapByte(Address >> 16);//最高字节
	MySPI_SwapByte(Address >> 8);//中间字节
	MySPI_SwapByte(Address);//最低字节
	
	MySPI_Stop();
	
	W25Q64_WaitBusy();
	
}

//读数据
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
	uint32_t i;
	MySPI_Start();
	MySPI_SwapByte(W25Q64_READ_DATA);
	
	MySPI_SwapByte(Address >> 16);//最高字节
	MySPI_SwapByte(Address >> 8);//中间字节
	MySPI_SwapByte(Address);//最低字节 
	
	
	for(i=0; i<Count; i++)
	{
		DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
	}
	MySPI_Stop();
	
}



#ifndef __W25Q64_H
#define __W25Q64_H

void W25Q64_Init(void);

//指针实现多返回值
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);


//页编程写数据 //使用指针传递数组 Address 3个字节
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count);

//扇区擦除
void W25Q64_SectorErase(uint32_t Address);

//读数据
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count);
#endif



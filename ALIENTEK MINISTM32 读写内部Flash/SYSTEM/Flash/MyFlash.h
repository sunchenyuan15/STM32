#ifndef __MyFlash_H
#define __MyFlash_H

uint32_t MyFLASH_ReadWord(uint32_t Address);


uint16_t MyFLASH_ReadHalfWord(uint32_t Address);


uint8_t MyFLASH_ReadByte(uint32_t Address);


//È«²Á³ý
void MyFlash_EraseAllPages(void);

//Ò³²Á³ý
void MyFlash_ErasePage(uint32_t PageAddress);

void MyFlash_ProgramWord(uint32_t Address, uint32_t Data);

void MyFlash_ProgramHalfWord(uint32_t Address, uint16_t Data);
#endif


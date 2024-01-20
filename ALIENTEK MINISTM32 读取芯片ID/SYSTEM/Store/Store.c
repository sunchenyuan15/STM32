#include "stm32f10x.h"                  // Device header
#include "MyFlash.h"

#define Store_Start_Address 0x0800FC00
#define Store_Count 512

//1024 Byte
uint16_t Store_Data[Store_Count];

//��ʼ������ ���һҳ
void Store_Init(void)
{
	if(MyFLASH_ReadHalfWord(0x0800FC00) != 0xA5A5 )//��һ��ʹ��
	{
		MyFlash_ErasePage(0x0800FC00);//�������һҳ
		MyFlash_ProgramHalfWord(0x0800FC00, 0xA5A5);//���һҳ��һ������
		for(uint16_t i = 1; i<Store_Count; i++)
		{
			MyFlash_ProgramHalfWord(0x0800FC00 + i*2, 0x0000);//һ������2���ֽڣ�ռ������ַ
		}
	}
	
	for(uint16_t i = 0; i<Store_Count; i++)
	{
		Store_Data[i] = MyFLASH_ReadHalfWord(0x0800FC00 + i*2);//�������ݻָ���SRAM����
	}
}  

void Store_Save(void)
{
	MyFlash_ErasePage(0x0800FC00);//�������һҳ
	for(uint16_t i = 0; i<Store_Count; i++)
	{
		MyFlash_ProgramHalfWord(0x0800FC00 + i*2, Store_Data[i]);//SRAM���ݱ������������һҳ
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






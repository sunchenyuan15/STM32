#include "stm32f10x.h"                  // Device header
#include "delay.h"

void MyIIC_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, (BitAction)BitValue);//BitAction SET RESET
	delay_us(10);
	
}

void MyIIC_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, (BitAction)BitValue);
	delay_us(10);
}

uint8_t MyIIC_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	delay_us(10);
	return BitValue;
}


void MyIIC_Init(void)
{
	//SCL PB10 SDA PB11
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;//开漏输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//SCL SDA置高电平
	GPIO_SetBits(GPIOB, GPIO_Pin_10|GPIO_Pin_11);
}

void MyIIC_Start(void)
{
	//起始条件
	MyIIC_W_SDA(1);
	MyIIC_W_SCL(1);

	
	MyIIC_W_SDA(0);
	MyIIC_W_SCL(0);
	
}

void MyIIC_Stop(void)
{
	//终止条件
	MyIIC_W_SDA(0);
	MyIIC_W_SCL(1);
	MyIIC_W_SDA(1);
	
}

void MyIIC_SendByte(uint8_t Byte)//发送一个字节
{
	
	uint8_t i;
	for (i=0; i<8; i++)
	{
		MyIIC_W_SDA(Byte & (0x80 >> i));//取最高位 高位先行
		MyIIC_W_SCL(1);
		MyIIC_W_SCL(0);//驱动时钟一个脉冲
		
	}
}


uint8_t MyI2C_ReceiveByte(void)//接受一个字节
{
	uint8_t i, Byte = 0x00;
	MyIIC_W_SDA(1);
	for (i=0; i<8; i++)
	{
		MyIIC_W_SCL(1);
		if (MyIIC_R_SDA() == 1)
		{
			Byte |= (0x80 >> i);
		}
		MyIIC_W_SCL(0);
		
	}
	return Byte;

}

void MyIIC_SendAck(uint8_t AckBit)//发送应答
{
	MyIIC_W_SDA(AckBit);
	MyIIC_W_SCL(1);
	MyIIC_W_SCL(0);//驱动时钟一个脉冲

}


uint8_t MyI2C_ReceiveAck(void)////接受应答
{
	uint8_t AckBit;
	MyIIC_W_SDA(1);
	MyIIC_W_SCL(1);
	AckBit = MyIIC_R_SDA();
	MyIIC_W_SCL(0);
	return AckBit;
}




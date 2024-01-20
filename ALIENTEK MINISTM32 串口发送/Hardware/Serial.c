#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>//用于访问函数参数列表中的可变参数

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//目前只设定 发送模式
	
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//TX复用推挽输出 RX输入模式 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	//初始化USART
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;//校验位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长
	
	USART_Init(USART1, &USART_InitStructure);
}


//发送一个字节
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);//写入TDR
	while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );//发送数据寄存器空标志位, 为SET结束等待	
}

//发送一个数组
//使用指针传递数组（长度参数）
void Serial_SendArray(uint8_t *Array, uint16_t length)
{
	uint16_t i;
	
	for(i=0; i<length; i++)
	{
		Serial_SendByte(Array[i]);	
	}
}

//发送字符串
//通过指针传递字符串
void Serial_SendString(char *String)
{
	uint8_t i;  
	
	for (i=0; String[i]!='\0'; i++)
	{
		Serial_SendByte(String[i]);
	}
//	while (String[i] != '\0')
//	{
//		Serial_SendByte(String[i]);
//		i++;		
//	}
}

//求x的y次方数值函数
uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
	uint32_t result = 1;
	while(y--)
	{
		result *= x;		
	}
	return result;
	
}


//发送字符形式数字
void Serial_Sendnumber(uint32_t number, uint8_t length)
{
	uint8_t i;
	for (i=0; i<length; i++){
		Serial_SendByte(number/Serial_Pow(10, length-i-1)%10 + '0');//将数字拆分成每一位，将每一位转换为 ASCII 字符
		
	}	
	
}
 
//printf函数移植方法
//fputc重定向到串口（非控制台）
//int fputc(int ch, FILE *f)
//{
//	Serial_SendByte(ch);
//	return ch;	
//}


//封装sprintf函数
void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
	
}



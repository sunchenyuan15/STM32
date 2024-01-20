#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>//���ڷ��ʺ��������б��еĿɱ����

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//Ŀǰֻ�趨 ����ģʽ
	
	//��ʼ��GPIO
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//TX����������� RX����ģʽ 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	//��ʼ��USART
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;//У��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�
	
	USART_Init(USART1, &USART_InitStructure);
}


//����һ���ֽ�
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);//д��TDR
	while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );//�������ݼĴ����ձ�־λ, ΪSET�����ȴ�	
}

//����һ������
//ʹ��ָ�봫�����飨���Ȳ�����
void Serial_SendArray(uint8_t *Array, uint16_t length)
{
	uint16_t i;
	
	for(i=0; i<length; i++)
	{
		Serial_SendByte(Array[i]);	
	}
}

//�����ַ���
//ͨ��ָ�봫���ַ���
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

//��x��y�η���ֵ����
uint32_t Serial_Pow(uint32_t x, uint32_t y)
{
	uint32_t result = 1;
	while(y--)
	{
		result *= x;		
	}
	return result;
	
}


//�����ַ���ʽ����
void Serial_Sendnumber(uint32_t number, uint8_t length)
{
	uint8_t i;
	for (i=0; i<length; i++){
		Serial_SendByte(number/Serial_Pow(10, length-i-1)%10 + '0');//�����ֲ�ֳ�ÿһλ����ÿһλת��Ϊ ASCII �ַ�
		
	}	
	
}
 
//printf������ֲ����
//fputc�ض��򵽴��ڣ��ǿ���̨��
//int fputc(int ch, FILE *f)
//{
//	Serial_SendByte(ch);
//	return ch;	
//}


//��װsprintf����
void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
	
}



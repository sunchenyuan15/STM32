#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>//���ڷ��ʺ��������б��еĿɱ����


int8_t Serial_RxPacket[100];//�����غ�����
uint8_t Serial_Rxflag;

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
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;//TX����������� RX����ģʽ 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	
	//��ʼ��USART
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;//У��λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//ֹͣλ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�
	
	USART_Init(USART1, &USART_InitStructure);
	
	//���ڽ��� �жϷ���
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//����RXNE��־λ��NVIC�����
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd  = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
}


//����һ���ֽ�
void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1, Byte);//д��TDR
	while( USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );//�������ݼĴ����ձ�־λ, ΪSET�����ȴ�	
}

//ʹ��ָ�봫�����飨���Ȳ�����
void Serial_SendArray(uint8_t *Array, uint16_t length)
{
	uint16_t i;
	
	for(i=0; i<length; i++)
	{
		Serial_SendByte(Array[i]);	
	}
}

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
		Serial_SendByte(number/Serial_Pow(10, length-i-1)%10 + '0');//�����ֲ�ֳ�ÿһλ��ÿһλת��Ϊ ASCII �ַ�		
	}	
}
 
//printf������ֲ����
//fputc�ض��򵽴��ڣ��ǿ���̨��
int Serial_fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;	
}


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

//uint8_t Serial_GetRxflag(void)//�Ƿ���ܵ����ݰ������յ�֮�����������־λ
//{
//	if(Serial_Rxflag == 1)
//	{
//		Serial_Rxflag=0;
//		return 1;
//	}
//	return 0;
//}



void Serial_USART1_IRQHandler(void)//�ж�
{
	static uint8_t RxState = 0;//״̬��־λ
	static uint8_t pRxPacket = 0;
	
	
	if(USART_GetFlagStatus(USART1, USART_IT_RXNE) == SET)
	{
		int8_t RxData = USART_ReceiveData(USART1);
		
		if(RxState == 0)//״̬0
		{
			if(RxData == '@' && Serial_Rxflag==0)//��������ٽ�����һ�����ݰ�
			{
				RxState=1;
				pRxPacket=0;
			}	
		}
		
		else if(RxState == 1)//״̬1
		{
			if(RxData=='\r')
			{
				RxState=2;
			}
			else 
			{
				Serial_RxPacket[pRxPacket]=RxData;
				pRxPacket++;
			}
		}
		
		else if(RxState == 2)//״̬2
		{
			if(RxData == '\n')
				{
					RxState=0;
					Serial_RxPacket[pRxPacket]='\0';
					Serial_Rxflag=1;//���յ�һ�����ݰ�				
				}		
		}
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);//����жϱ�־λ	
	}
}


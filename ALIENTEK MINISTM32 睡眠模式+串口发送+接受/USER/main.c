#include "stm32f10x.h"
#include "LED.h"
#include "KEY.h"
#include "delay.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "lcd.h"
#include "usart.h"
//#include "CountSensor.h"
#include "Encoder.h"
#include "Timer.h"
#include "AD.h"
#include "Serial.h"

uint8_t Rxdata;

int main(void)
{
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	 //���ڳ�ʼ��Ϊ9600
	LCD_Init();
	POINT_COLOR=RED;
	
	LCD_ShowString(30,40,200,24,24,"RxData:");

	Serial_Init();
	
//	Serial_SendByte(0x41);
//	Serial_SendByte('A');
//	
//	uint8_t SendArray[]={0x42, 0x43, 0x44, 0x45};

//	Serial_SendArray(SendArray, 4);
//	
//	Serial_SendString("abcdef");
//	
//	Serial_Sendnumber(12345, 5);
//	
//	printf("Num=%d\r\n", 666);
	
	//sprintfָ����ӡλ�� ���漰�ض���
//	char String[100];
//	sprintf(String, "Num=%d\r\n", 666);//����ʽ��������д���ַ�����
//	Serial_SendString(String);
	
	//
//	Serial_Printf("Num=%d\r\n", 666);
	
	
	while(1)
	{
//		//���ڽ��� ��ѯ����
//		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
//		{
//			Rxdata = USART_ReceiveData(USART1);
//			LCD_ShowxNum(30,70,Rxdata ,4,24,0); //��ʾ��ֵ
//		}
		
		
		LCD_ShowString(30,100,200,24,24,"Running");
		delay_ms(500);
		LCD_ShowString(30,100,200,24,24,"       ");
		delay_ms(500);	
		
		//���ڽ��� �жϷ���
		if (Serial_GetRxflag() == 1)
		{
			Rxdata = Serial_GetRxdata();
			Serial_SendByte(Rxdata);
			LCD_ShowxNum(30,70,Rxdata ,4,24,0); //��ʾ��ֵ
		}
		
		
		//����˯��ģʽ һ��ʡ��		
		__WFI();//�жϻ���
	}
}
 




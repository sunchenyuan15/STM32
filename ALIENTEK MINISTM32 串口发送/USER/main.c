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


int main(void)
{
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	 //���ڳ�ʼ��Ϊ9600
	LCD_Init();
	POINT_COLOR=RED;
	

	Serial_Init();
	
//	Serial_SendByte(0x41);
//	Serial_SendByte('A');//����һ���ֽ�
//	
//	uint8_t SendArray[]={0x42, 0x43, 0x44, 0x45};

//	Serial_SendArray(SendArray, 4);//����һ������
//	
//	Serial_SendString("abcdef");//�����ַ���
//	
//	Serial_Sendnumber(12345, 5);//�����ַ���ʽ����
//	
//	printf("Num=%d\r\n", 666);
	
	
	//sprintfָ����ӡλ�� ���漰�ض���
//	char String[100];
//	sprintf(String, "Num=%d\r\n", 666);//����ʽ��������д���ַ�����
//	Serial_SendString(String);

    //��װsprintf
	Serial_Printf("Num=%d\r\n", 666);
	Serial_Printf("���");
	
	
	while(1)
	{
		
	}
}
 





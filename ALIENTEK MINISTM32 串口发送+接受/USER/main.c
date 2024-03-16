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
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	POINT_COLOR=RED;
	

	Serial_Init();
	
	LCD_ShowString(30,40,200,24,24,"Rxdata:");
	
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
	
	//sprintf指定打印位置 不涉及重定向
//	char String[100];
//	sprintf(String, "Num=%d\r\n", 666);//将格式化的数据写入字符串中
//	Serial_SendString(String);
	
	//
//	Serial_Printf("Num=%d\r\n", 666);
	
	
	while(1)
	{
		//串口接受 查询方法
//		if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
//		{
//			Rxdata = USART_ReceiveData(USART1);
//			LCD_ShowxNum(30,70,Rxdata,10,24,0); //显示数值
//		}
		
		//串口接受 中断方法
		if (Serial_GetRxflag() == 1)
		{
			Rxdata = Serial_GetRxdata();
			Serial_SendByte(Rxdata);
			LCD_ShowxNum(30,70,Rxdata ,4,24,0); //显示数值
		}
	}
}
 





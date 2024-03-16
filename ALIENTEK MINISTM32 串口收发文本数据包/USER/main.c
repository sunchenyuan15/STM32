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
#include "KEY.h"

#include <string.h>
uint8_t KeyNum;
uint8_t Rxdata;

int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	POINT_COLOR=RED;
	
	LED_Init();

	Serial_Init();
	
	LCD_ShowString(30,40,200,24,24,"TxPacket");
	LCD_ShowString(30,100,200,24,24,"RxPacket");

	while(1)
	{
		
		if(Serial_Rxflag==1)
			{
				LCD_ShowString(30,70,200,24,24,"              ");
				LCD_ShowString(30,70,200,24,24,Serial_RxPacket);
			}
			
		if(strcmp(Serial_RxPacket, "LED_ON") == 0)
		{
			LED_ON();
			Serial_SendString("LED_ON_OK\r\n");
			LCD_ShowString(30,130,200,24,24,"              ");
			LCD_ShowString(30,130,200,24,24,"LED_ON_OK");
		}
		
		else if(strcmp(Serial_RxPacket, "LED_OFF") == 0)
		{
			LED_OFF();
			Serial_SendString("LED_ON_OFF\r\n");
			LCD_ShowString(30,130,200,24,24,"              ");
			LCD_ShowString(30,130,200,24,24,"LED_ON_OFF");
		}
		
		else
		{
			Serial_SendString("ERROR\r\n");
			LCD_ShowString(30,130,200,24,24,"              ");
			LCD_ShowString(30,130,200,24,24,"ERROR");
			
		}
		
		Serial_Rxflag==0;
	}
}
 





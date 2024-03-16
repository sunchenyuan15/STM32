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
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	POINT_COLOR=RED;
	

	Serial_Init();
	
//	Serial_SendByte(0x41);
//	Serial_SendByte('A');//发送一个字节
//	
//	uint8_t SendArray[]={0x42, 0x43, 0x44, 0x45};

//	Serial_SendArray(SendArray, 4);//发送一个数组
//	
//	Serial_SendString("abcdef");//发送字符串
//	
//	Serial_Sendnumber(12345, 5);//发送字符形式数字
//	
//	printf("Num=%d\r\n", 666);
	
	
	//sprintf指定打印位置 不涉及重定向
//	char String[100];
//	sprintf(String, "Num=%d\r\n", 666);//将格式化的数据写入字符串中
//	Serial_SendString(String);

    //封装sprintf
	Serial_Printf("Num=%d\r\n", 666);
	Serial_Printf("你好");
	
	
	while(1)
	{
		
	}
}
 





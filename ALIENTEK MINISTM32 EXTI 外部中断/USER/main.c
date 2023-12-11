#include "stm32f10x.h"
#include "LED.h"
#include "KEY.h"
#include "delay.h"
#include "Buzzer.h"
#include "LightSensor.h"
#include "lcd.h"
#include "usart.h"
#include "CountSensor.h"
#include "Encoder.h"


uint16_t num; //(unsigned short)

int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
//	Encoder_Init();
	
	CountSensor_Init();
	POINT_COLOR=RED;
	LCD_ShowString(30,40,200,24,24,"Mini STM32");
	LCD_ShowString(30,70,200,24,24,"Count:");

//	LCD_ShowString(30,70,200,24,24,"Num:");

	while(1)
	{
		LCD_ShowxNum(100,70,CountSensor_Get(),5,24,0); //显示数字
//		num += Encoder_Get();
//		LCD_ShowxNum(100,70,num,5,24,0); //显示数字
		
	}
}


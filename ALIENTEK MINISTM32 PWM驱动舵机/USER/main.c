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
#include "Timer.h"
#include "Servo.h"
uint8_t Keynum;

uint16_t num=0; //(unsigned short)+
float angle;


int main(void)
{
	
	delay_init();	    	 //延时函数初始化	
	uart_init(9600);	 	 //串口初始化为9600	
    LCD_Init();
	
	Servo_Init();
	Key_Init();
	LCD_ShowString(30,40,200,24,24,"Mini STM32");
	LCD_ShowString(30,70,200,24,24,"angle");


	while(1)
	{
		LCD_ShowxNum(90,70,angle,5,24,0); //显示数字
		Keynum = Key_GetNum();
		if (Keynum == 1)
		{
			angle += 30;
			if (angle > 180)
			{
				angle = 0;
			}
		}
		Servo_SetAngle(angle);
			
	}
}


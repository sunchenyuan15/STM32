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

#include "MPU6050.h"
#include "W25Q64.h"
#include <string.h>
#include "MyRTC.h"



int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	POINT_COLOR=RED;
	
	LCD_ShowString(30,40,200,24,24,"SYSCLK");
	LCD_ShowxNum(30,70,SystemCoreClock,8,24,0);



//	LCD_ShowString(30,40,200,24,24,"W");
//	LCD_ShowxNum(30,70,ArrayWrite[0],4,24,0);
//	LCD_ShowxNum(90,70,ArrayWrite[1],5,24,0);
//	
//	LCD_ShowString(30,100,200,24,24,"R");
//	LCD_ShowxNum(30,130,ArrayRead[0],4,24,0);
//	LCD_ShowxNum(90,130,ArrayRead[1],5,24,0);


	while(1)
	{
		LCD_ShowString(30,100,200,24,24,"running");
		delay_ms(500);
		LCD_ShowString(30,100,200,24,24,"       ");
		delay_ms(500);	
	}
}



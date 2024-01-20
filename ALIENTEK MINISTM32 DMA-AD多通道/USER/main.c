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


int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	
	AD_Init();
	
	POINT_COLOR=RED;
	LCD_ShowString(30,40,200,24,24,"AD0");
	LCD_ShowString(30,70,200,24,24,"AD1");
	LCD_ShowString(30,100,200,24,24,"AD2");
	LCD_ShowString(30,130,200,24,24,"AD3");


	while(1)
	{
		

			
		LCD_ShowxNum(100,40,AD_Value[0],4,24,0); //显示adc数值
		LCD_ShowxNum(100,70,AD_Value[1],4,24,0); //显示adc数值
		LCD_ShowxNum(100,100,AD_Value[2],4,24,0); //显示adc数值
		LCD_ShowxNum(100,130,AD_Value[3],4,24,0); //显示adc数值
		
		delay_ms(100);
	}
}





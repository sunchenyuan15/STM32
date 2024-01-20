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

float Voltage;

int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	
	AD_Init();
	
	POINT_COLOR=RED;
	LCD_ShowString(30,40,200,24,24,"Mini STM32");
	LCD_ShowString(30,70,200,24,24,"Value:");
	LCD_ShowString(30,100,200,24,16,"Voltage:");


	while(1)
	{
		
		LCD_ShowxNum(100,70,AD_GetValue(),5,24,0); //显示adc数值
		
		Voltage = (float)AD_GetValue() / 4095 * 3.3;
		
		LCD_ShowxNum(100,100,Voltage*100,5,24,0); //显示电压
		
	}
}





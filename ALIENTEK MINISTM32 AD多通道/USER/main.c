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

uint16_t AD0, AD1, AD2, AD3;

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
		AD0=AD_GetValue(ADC_Channel_0);
		AD1=AD_GetValue(ADC_Channel_1);
		AD2=AD_GetValue(ADC_Channel_2);
		AD3=AD_GetValue(ADC_Channel_3);
		
		LCD_ShowxNum(100,40,AD0,4,24,0); //显示adc数值
		LCD_ShowxNum(100,70,AD1,4,24,0); //显示adc数值
		LCD_ShowxNum(100,100,AD2,4,24,0); //显示adc数值
		LCD_ShowxNum(100,130,AD3,4,24,0); //显示adc数值
		
		delay_ms(100);
	}
}





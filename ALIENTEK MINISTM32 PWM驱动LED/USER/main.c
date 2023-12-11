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
#include "PWM.h"
uint16_t num; //(unsigned short)

int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
//	LCD_Init();
	PWM_Init();



	while(1)
	{
		for (num=0; num<100; num++)
		{
			PWM_SetCompare1(num);
			delay_ms(10);		
			
		}
		
		for (num=0; num<100; num++)
		{
			PWM_SetCompare1(100 - num);
			delay_ms(10);		
			
		}
				
	}
}


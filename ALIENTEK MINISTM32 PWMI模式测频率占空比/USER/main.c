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
#include "IC.h"
uint16_t num; //(unsigned short)

int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	PWM_Init();
	
	IC_Init();
    
	PWM_SetPrescaler(720 - 1); //Freq = 72M / (PSC+1) / (ARR+1)
	PWM_SetCompare1(50);       //Duty = CCR / (ARR+1)


	LCD_ShowString(30, 40, 200, 24, 24, "Mini STM32");
	LCD_ShowString(30, 70, 200, 24, 24, "Freq:00000Hz");
	LCD_ShowString(30, 100, 200, 24, 24, "Duty: 00%");
	
	while(1)
	{
		LCD_ShowxNum(90, 70, IC_GetFreq(), 5, 24, 0);
		LCD_ShowxNum(90, 100, IC_GetDuty(), 3, 24, 0);

				
	}
}


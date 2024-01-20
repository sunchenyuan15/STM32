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
		
	Key_Init();
	
	
	LCD_ShowString(30,40,200,24,24,"WWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST) == SET)
	{
		LCD_ShowString(30,70,200,24,24,"WWDGRST");
		delay_ms(500);
		LCD_ShowString(30,70,200,24,24,"       ");
		delay_ms(500);
		
		RCC_ClearFlag();//清除标志位
	}
	else
	{
		LCD_ShowString(30,100,200,24,24,"RST");
		delay_ms(500);
		LCD_ShowString(30,100,200,24,24,"   ");
		delay_ms(500);
	}
	
	
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);
	
	//写入预分频和窗口值
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(0x40 | 21);//窗口时间30ms
	
	//写入控制寄存器
	IWDG_ReloadCounter();
	
	//使能窗口看门狗
	WWDG_Enable(0x40 | 54);//T6位设为1 
	//超时时间50ms

	while(1)
	{
		
//		LCD_ShowString(30,40,200,24,24,"CNT");
//		LCD_ShowxNum(30,70,RTC_GetCounter(),10,24,0);

		Key_GetNum();
		
	
//		LCD_ShowString(30,130,200,24,24,"FEED");
//		delay_ms(20);
//		LCD_ShowString(30,130,200,24,24,"    ");
		delay_ms(30);
		
		//喂狗
		WWDG_SetCounter(0x40 | 54);
		
	}
}


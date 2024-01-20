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
#include "MyFlash.h"
#include "Store.h"



uint8_t keynum;
uint8_t num=0;

int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	POINT_COLOR=RED;
	
	Key_Init();
	
	Store_Init();
		
	
	LCD_ShowString(30,40,200,24,24,"flag");
	LCD_ShowString(30,100,200,24,24,"data");

	while(1)
	{
		
		keynum = Key_GetNum();
		
		if(keynum == 1)
		{
			num++;
			
			Store_Data[1] ++;
			Store_Data[2] ++;
			Store_Data[3] ++;
			Store_Data[4] ++;
			
			Store_Save();
		}	
		if(keynum == 2)
		{
			Store_Clear();
		}
	
		LCD_ShowxNum(30,70,Store_Data[0],5,24,0);
		LCD_ShowxNum(30,130,Store_Data[1],5,24,0);
		LCD_ShowxNum(30,160,Store_Data[2],5,24,0);
		LCD_ShowxNum(30,190,Store_Data[3],5,24,0);
		LCD_ShowxNum(30,220,Store_Data[4],5,24,0);
			
	}
}

//		LCD_ShowString(30,40,200,24,24,"CNT");
//		LCD_ShowxNum(30,70,keynum,1,24,0);

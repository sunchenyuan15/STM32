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
	
	
	LCD_ShowString(30,40,200,24,24,"Size");
	LCD_ShowxNum(30,70,*((__IO uint16_t *)(0x1FFFF7E0)),4,24,0);
	
	LCD_ShowString(30,100,200,24,24,"U_ID");
	LCD_ShowxNum(30,130,*((__IO uint16_t *)(0x1FFFF7E8)),4,24,0);
	LCD_ShowxNum(30,160,*((__IO uint16_t *)(0x1FFFF7E8 + 0x02)),4,24,0);
	LCD_ShowxNum(30,190,*((__IO uint32_t *)(0x1FFFF7E8 + 0x04)),8,24,0);
	LCD_ShowxNum(30,220,*((__IO uint32_t *)(0x1FFFF7E8 + 0x08)),8,24,0);
	
	
	while(1)
	{
		
	}
}

//		LCD_ShowString(30,40,200,24,24,"CNT");
//		LCD_ShowxNum(30,70,keynum,1,24,0);

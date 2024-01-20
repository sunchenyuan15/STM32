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

uint8_t MID;
uint16_t DID;

uint8_t ArrayWrite[] = {0, 1, 2, 3};
uint8_t ArrayRead[4];


int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	POINT_COLOR=RED;
	
	W25Q64_Init();
	W25Q64_ReadID(&MID, &DID);

	LCD_ShowString(30,40,200,24,24,"MID");
	LCD_ShowxNum(30,70,MID,4,24,0);
	
	LCD_ShowString(30,100,200,24,24,"DID");
	LCD_ShowxNum(30,130,DID,4,24,0);
	
	
	LCD_ShowString(30,160,200,24,24,"W");
	
	LCD_ShowString(30,220,200,24,24,"R");
	
	
	W25Q64_SectorErase(0x000000);
	
	W25Q64_PageProgram(0x000000, ArrayWrite, 4);
	W25Q64_ReadData(0x0000, ArrayRead, 4);
	
	LCD_ShowxNum(30,190,ArrayWrite[0],2,24,0);
	LCD_ShowxNum(60,190,ArrayWrite[1],2,24,0);
	LCD_ShowxNum(90,190,ArrayWrite[2],2,24,0);
	LCD_ShowxNum(120,190,ArrayWrite[3],2,24,0);
	
	LCD_ShowxNum(30,250,ArrayRead[0],2,24,0);
	LCD_ShowxNum(60,250,ArrayRead[1],2,24,0);
	LCD_ShowxNum(90,250,ArrayRead[2],2,24,0);
	LCD_ShowxNum(120,250,ArrayRead[3],2,24,0);


	while(1)
	{
		

	}

}



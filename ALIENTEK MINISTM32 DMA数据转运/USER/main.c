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
#include "MyDMA.h"

uint8_t DataA[] = {0x01, 0x02, 0x03, 0x04};
uint8_t DataB[] = {0, 0, 0, 0};


int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	POINT_COLOR=RED;

	
	MyDMA_Init((uint32_t)DataA, (uint32_t)DataB, 4);
	
	while(1)
	{
		
		DataA[0]++;
		DataA[1]++;
		DataA[2]++;
		DataA[3]++;
		
		
		LCD_ShowxNum(30,40,DataA[0],1,24,0); 
		LCD_ShowxNum(30,70,DataA[1],1,24,0); 
		LCD_ShowxNum(30,100,DataA[2],1,24,0); 
		LCD_ShowxNum(30,130,DataA[3],1,24,0); 
	
		LCD_ShowxNum(80,40,DataB[0],1,24,0); 	
		LCD_ShowxNum(80,70,DataB[1],1,24,0); 
		LCD_ShowxNum(80,100,DataB[2],1,24,0); 
		LCD_ShowxNum(80,130,DataB[3],1,24,0); 
		
		delay_ms(1000);
		    
		MyDMA_Transfer();
		
		LCD_ShowxNum(30,40,DataA[0],1,24,0); 
		LCD_ShowxNum(30,70,DataA[1],1,24,0); 
		LCD_ShowxNum(30,100,DataA[2],1,24,0); 
		LCD_ShowxNum(30,130,DataA[3],1,24,0); 
	
		LCD_ShowxNum(80,40,DataB[0],1,24,0); 	
		LCD_ShowxNum(80,70,DataB[1],1,24,0); 
		LCD_ShowxNum(80,100,DataB[2],1,24,0); 
		LCD_ShowxNum(80,130,DataB[3],1,24,0); 
		
		delay_ms(1000);
	}
	
}





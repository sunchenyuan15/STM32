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

uint8_t KeyNum;
uint8_t Rxdata;

int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	POINT_COLOR=RED;
	
	Key_Init();

	Serial_Init();
	
	LCD_ShowString(30,40,200,24,24,"TxPacket");
	LCD_ShowString(30,120,200,24,24,"RxPacket");


	Serial_TxPacket[0]=0x01;
	Serial_TxPacket[1]=0x02;
	Serial_TxPacket[2]=0x03;
	Serial_TxPacket[3]=0x04;
	

	while(1)
	{
		KeyNum=Key_GetNum();
		
		if(KeyNum==1)
			{
				Serial_TxPacket[0]++;
				Serial_TxPacket[1]++;
				Serial_TxPacket[2]++;
				Serial_TxPacket[3]++;
				
				Serial_SendPacket();
				
				LCD_ShowxNum(30,80,Serial_TxPacket[0],2,24,0);//发送数据包				 
				LCD_ShowxNum(60,80,Serial_TxPacket[1],2,24,0); 
				LCD_ShowxNum(90,80,Serial_TxPacket[2],2,24,0); 
				LCD_ShowxNum(120,80,Serial_TxPacket[3],2,24,0);
			}

		if(Serial_GetRxflag() == 1)
			{

				LCD_ShowxNum(30,160,Serial_RxPacket[0],2,24,0);//接受数据包
				LCD_ShowxNum(60,160,Serial_RxPacket[1],2,24,0); 
				LCD_ShowxNum(90,160,Serial_RxPacket[2],2,24,0); 
				LCD_ShowxNum(120,160,Serial_RxPacket[3],2,24,0); 
				
			}		
	}
}
 





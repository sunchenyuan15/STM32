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
#include <string.h>

int16_t AX, AY, AZ, GX, GY, GZ;

int main(void)
{
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	 //���ڳ�ʼ��Ϊ9600
	LCD_Init();
	POINT_COLOR=RED;
	
	
	MPU6050_Init();
	
//	MPU6050_WriteReg(0x6B, 0x00);//��Դ����Ĵ���д1�����˯��ģʽ
	
//	uint8_t ID = MPU6050_ReadReg(0x75);
	

//	LCD_ShowString(30,40,200,24,24,"Ack");

//	LCD_ShowxNum(65,40,ID,2,24,0);


	while(1)
	{
		MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
		
		LCD_ShowxNum(30,40,AX,4,24,0);
		LCD_ShowxNum(30,70,AY,4,24,0);
		LCD_ShowxNum(30,100,AZ,4,24,0);
		
		LCD_ShowxNum(30,130,GX,4,24,0);
		LCD_ShowxNum(30,160,GY,4,24,0);
		LCD_ShowxNum(30,190,GZ,4,24,0);
		
		
	}

}



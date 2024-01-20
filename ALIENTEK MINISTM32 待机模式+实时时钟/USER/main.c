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
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	 //���ڳ�ʼ��Ϊ9600
	LCD_Init();
	POINT_COLOR=RED;
	
	MyRTC_Init();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	LCD_ShowString(30,40,200,24,24,"CNT");
	LCD_ShowString(30,100,200,24,24,"ALR");
	LCD_ShowString(30,160,200,24,24,"ALRF");
	
	
	//WKUP���������ػ��Ѵ���ģʽ
	PWR_WakeUpPinCmd(ENABLE);
	
	
	uint32_t alarm = RTC_GetCounter() + 10;
	
	//RTC�����¼����Ѵ���ģʽ
	RTC_SetAlarm(alarm);//��ǰ���� + 10
	
	LCD_ShowxNum(30,130,alarm,10,24,0);
	

	while(1)
	{
		
		MyRTC_ReadTime();
		
		
		LCD_ShowxNum(30,70,RTC_GetCounter(),10,24,0);
		
		LCD_ShowxNum(30,190,RTC_GetFlagStatus(RTC_FLAG_ALR),1,24,0);
		
		LCD_ShowString(30,220,200,24,24,"running");
		delay_ms(500);
		LCD_ShowString(30,220,200,24,24,"       ");
		delay_ms(500);
		
		//�������ģʽ
		PWR_EnterSTANDBYMode();
		
		//֮��Ĵ����޷�ִ��
	
	}
}


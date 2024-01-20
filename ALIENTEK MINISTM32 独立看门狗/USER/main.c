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
		
	Key_Init();
	
	
	LCD_ShowString(30,40,200,24,24,"IWDG TEST");
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET)
	{
		LCD_ShowString(30,70,200,24,24,"IWDGRST");
		delay_ms(500);
		LCD_ShowString(30,70,200,24,24,"       ");
		delay_ms(500);
		
		RCC_ClearFlag();//�����־λ
	}
	else
	{
		LCD_ShowString(30,100,200,24,24,"RST");
		delay_ms(500);
		LCD_ShowString(30,100,200,24,24,"   ");
		delay_ms(500);
	}
	
	
	//����LSIʱ��
	//�Զ�����
	
	//���д����
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//дʹ��
	
	//д��Ԥ��Ƶ����װֵ
	IWDG_SetPrescaler(IWDG_Prescaler_16);
	IWDG_SetReload(2499); //1000ms
	
	//ι��
	IWDG_ReloadCounter();
	
	//�����������Ź�
	IWDG_Enable();

	while(1)
	{
		
//		LCD_ShowString(30,40,200,24,24,"CNT");
//		LCD_ShowxNum(30,70,RTC_GetCounter(),10,24,0);

		Key_GetNum();
		
		//ι��
		IWDG_ReloadCounter();
			
		LCD_ShowString(30,130,200,24,24,"FEED");
		delay_ms(200);
		LCD_ShowString(30,130,200,24,24,"    ");
		delay_ms(600);
		
	}
}


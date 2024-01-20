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


uint16_t num; //(unsigned short)

int main(void)
{
	
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	 //���ڳ�ʼ��Ϊ9600
	LCD_Init();
	POINT_COLOR=RED;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	
//	Encoder_Init();
	
	CountSensor_Init();
	
	LCD_ShowString(30,40,200,24,24,"Mini STM32");
	LCD_ShowString(30,70,200,24,24,"Count:");

//	LCD_ShowString(30,70,200,24,24,"Num:");

	while(1)
	{
		LCD_ShowxNum(100,70,CountSensor_Get(),5,24,0); //��ʾ����
//		num += Encoder_Get();
//		LCD_ShowxNum(100,70,num,5,24,0); //��ʾ����
		
		LCD_ShowString(30,110,200,24,24,"running");
		delay_ms(500);
		LCD_ShowString(30,110,200,24,24,"       ");
		delay_ms(500);
		
		//����ֹͣģʽ
		PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
		SystemInit();
		
	}
}


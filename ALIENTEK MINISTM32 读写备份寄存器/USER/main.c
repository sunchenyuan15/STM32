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



uint16_t ArrayWrite[] = {0x1234, 0x5678};
uint16_t ArrayRead[2];

uint16_t DR;
int main(void)
{
	
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	 //串口初始化为9600
	LCD_Init();
	POINT_COLOR=RED;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);//RCC(Reset and Clock Control 复位和时钟控制),peripheral-外设
	
	PWR_BackupAccessCmd(ENABLE);
	
	BKP_WriteBackupRegister(BKP_DR1, ArrayWrite[0]);//写入寄存器
	BKP_WriteBackupRegister(BKP_DR2, ArrayWrite[1]);//读取寄存器
	
	ArrayRead[0] = BKP_ReadBackupRegister(BKP_DR1);
	ArrayRead[1] = BKP_ReadBackupRegister(BKP_DR2);
	

	LCD_ShowString(30,40,200,24,24,"W");
	LCD_ShowxNum(30,70,ArrayWrite[0],4,24,0);
	LCD_ShowxNum(90,70,ArrayWrite[1],5,24,0);
	
	LCD_ShowString(30,100,200,24,24,"R");
	LCD_ShowxNum(30,130,ArrayRead[0],4,24,0);
	LCD_ShowxNum(90,130,ArrayRead[1],5,24,0);


	while(1)
	{
		

	}

}




#include "stm32f10x.h"
#include "LED.h"
#include "KEY.h"
#include "delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

uint8_t KeyNum;

int main(void)
{
	delay_init();
	Buzzer_Init();
	LightSensor_Init();
	while(1)
	{
		if (LightSensor_Get() == 1)
		{
			Buzzer_ON();
			
		}
		else
		{
			Buzzer_OFF();

		}
	}

}

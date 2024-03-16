#include "stm32f10x.h"                  // Device header
#include <time.h>


uint16_t MyRTC_Time[] = {2023, 1, 1, 23, 59, 55};

void MyRTC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	
	//使能BKP RTC访问
	PWR_BackupAccessCmd(ENABLE);
	
	//BKP是否存在
	if(BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		//开启LSE时钟
		RCC_LSEConfig(RCC_LSE_ON);

		//等待LSE时钟启动完成
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);

		//选择 LSE 作为RTCCLK时钟源
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

		//使能
		RCC_RTCCLKCmd(ENABLE);

		//等待同步
		RTC_WaitForSynchro();

		//等待上一次写入操作完成
		RTC_WaitForLastTask();

		//32768Hz -> 1Hz
		RTC_SetPrescaler(32768 - 1);

		//等待上一次写入操作完成
		RTC_WaitForLastTask();

		//初始化时间
		RTC_SetCounter(1672588795);//Beijing 2023-1-1 23:59:55

		//等待上一次写入操作完成
		RTC_WaitForLastTask();
		
		//写BKP寄存器
		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
	else
	{
		//等待同步
		RTC_WaitForSynchro();

		//等待上一次写入操作完成
		RTC_WaitForLastTask();
	}	

}

//设置时间
void MyRTC_SetTime(void)
{
	time_t time_cnt;
	struct tm time_date;
	time_date.tm_year = MyRTC_Time[0] - 1900;
	time_date.tm_mon = MyRTC_Time[1] - 1;
	time_date.tm_mday = MyRTC_Time[2];
	time_date.tm_hour  = MyRTC_Time[3];
	time_date.tm_min = MyRTC_Time[4];
	time_date.tm_sec = MyRTC_Time[5];
	
	//日期时间数据类型 -> 秒计数器数据类型
	time_cnt = mktime(&time_date);
	
	//写入CNT
	RTC_SetCounter(time_cnt - 8*60*60);
	
	//等待上一次写入操作完成
	RTC_WaitForLastTask();
	
}

//读取时间
void MyRTC_ReadTime(void)
{
	// unsigned int(uint32_t) time_t; 
	time_t time_cnt;
	struct tm time_date;
	
	time_cnt = RTC_GetCounter() + 8*60*60;//转为 东八区 北京时间
	
	time_date = *localtime(&time_cnt);
	
	MyRTC_Time[0] = time_date.tm_year + 1900;
	MyRTC_Time[1] = time_date.tm_mon + 1;
	MyRTC_Time[2] = time_date.tm_mday;
	MyRTC_Time[3] = time_date.tm_hour;
	MyRTC_Time[4] = time_date.tm_min;
	MyRTC_Time[5] = time_date.tm_sec;
}



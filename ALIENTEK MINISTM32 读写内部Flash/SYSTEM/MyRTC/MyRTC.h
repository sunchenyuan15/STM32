#ifndef __MyRTC_H
#define __MyRTC_H


extern uint16_t MyRTC_Time[];

void MyRTC_Init(void);

//设置时间
void MyRTC_SetTime(void);

//读取时间
void MyRTC_ReadTime(void);


#endif


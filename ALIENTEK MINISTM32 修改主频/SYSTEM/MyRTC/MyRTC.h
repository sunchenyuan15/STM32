#ifndef __MyRTC_H
#define __MyRTC_H


extern uint16_t MyRTC_Time[];

void MyRTC_Init(void);

//����ʱ��
void MyRTC_SetTime(void);

//��ȡʱ��
void MyRTC_ReadTime(void);


#endif


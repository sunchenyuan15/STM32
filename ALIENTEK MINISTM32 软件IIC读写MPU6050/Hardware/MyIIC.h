#ifndef __MyIIC_H
#define __MyIIC_H


void MyIIC_Init(void);

void MyIIC_Start(void);

void MyIIC_Stop(void);

void MyIIC_SendByte(uint8_t Byte);//����һ���ֽ�

uint8_t MyI2C_ReceiveByte(void);//����һ���ֽ�

void MyIIC_SendAck(uint8_t AckBit);//����Ӧ��

uint8_t MyI2C_ReceiveAck(void);////����Ӧ��

#endif

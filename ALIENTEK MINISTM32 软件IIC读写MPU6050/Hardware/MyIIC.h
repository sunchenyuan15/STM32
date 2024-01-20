#ifndef __MyIIC_H
#define __MyIIC_H


void MyIIC_Init(void);

void MyIIC_Start(void);

void MyIIC_Stop(void);

void MyIIC_SendByte(uint8_t Byte);//发送一个字节

uint8_t MyI2C_ReceiveByte(void);//接受一个字节

void MyIIC_SendAck(uint8_t AckBit);//发送应答

uint8_t MyI2C_ReceiveAck(void);////接受应答

#endif

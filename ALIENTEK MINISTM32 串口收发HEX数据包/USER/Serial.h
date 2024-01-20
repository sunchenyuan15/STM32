#ifndef __Serial_H
#define __Serial_H

extern uint8_t Serial_TxPacket[];//�����غ�����
extern uint8_t Serial_RxPacket[];//�����غ�����

void Serial_Init(void);

void Serial_SendByte(uint8_t Byte);

void Serial_SendArray(uint8_t *Array, uint16_t length);

void Serial_SendString(char *String);

void Serial_Sendnumber(uint32_t number, uint8_t length);

void Serial_Printf(char *format, ...);

uint8_t Serial_GetRxflag(void);//�Ƿ���ܵ����ݰ�

void Serial_SendPacket(void);
#endif


#ifndef __Serial_H
#define __Serial_H

extern uint8_t Serial_TxPacket[];//发送载荷数据
extern uint8_t Serial_RxPacket[];//接受载荷数据

void Serial_Init(void);

void Serial_SendByte(uint8_t Byte);

void Serial_SendArray(uint8_t *Array, uint16_t length);

void Serial_SendString(char *String);

void Serial_Sendnumber(uint32_t number, uint8_t length);

void Serial_Printf(char *format, ...);

uint8_t Serial_GetRxflag(void);//是否接受到数据包

void Serial_SendPacket(void);
#endif


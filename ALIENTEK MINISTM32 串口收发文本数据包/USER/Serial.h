#ifndef __Serial_H
#define __Serial_H


extern int8_t Serial_RxPacket[];//接受载荷数据
extern uint8_t Serial_Rxflag;

void Serial_Init(void);

void Serial_SendByte(uint8_t Byte);

void Serial_SendArray(uint8_t *Array, uint16_t length);

void Serial_SendString(char *String);

void Serial_Sendnumber(uint32_t number, uint8_t length);

void Serial_Printf(char *format, ...);

//uint8_t Serial_GetRxflag(void);//是否接受到数据包

#endif


#ifndef __MySPI_H
#define __MySPI_H


void MySPI_Init(void);

void MySPI_Start(void);

void MySPI_Stop(void);

//����һ���ֽ� ģʽ0
uint8_t MySPI_SwapByte(uint8_t ByteSend);

//��λ����
uint8_t MySPI_SwapByte_2(uint8_t ByteSend);



#endif


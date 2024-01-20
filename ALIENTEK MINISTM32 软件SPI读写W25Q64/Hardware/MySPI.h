#ifndef __MySPI_H
#define __MySPI_H


void MySPI_Init(void);

void MySPI_Start(void);

void MySPI_Stop(void);

//交换一个字节 模式0
uint8_t MySPI_SwapByte(uint8_t ByteSend);

//移位操作
uint8_t MySPI_SwapByte_2(uint8_t ByteSend);



#endif


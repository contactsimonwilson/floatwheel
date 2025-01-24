#ifndef __USART_H
#define __USART_H

#include "hk32f030m.h"

void USART1_Init(uint32_t Baud);
void USART1_Send_Byte(uint8_t byte);
void USART1_Send_Bytes(uint8_t *pbyte,uint8_t len);

#endif



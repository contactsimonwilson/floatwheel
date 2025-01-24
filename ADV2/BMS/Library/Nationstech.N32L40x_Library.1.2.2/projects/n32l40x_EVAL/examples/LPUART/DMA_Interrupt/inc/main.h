/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x.h"

// #define _LPUART_USART3_
#define _LPUART_UART5_

#ifdef _LPUART_USART3_
#define LPUART_GPIO           GPIOA
#define LPUART_GPIO_CLK       RCC_APB2_PERIPH_GPIOA
#define LPUART_RxPin          GPIO_PIN_3
#define LPUART_TxPin          GPIO_PIN_4
#define LPUART_Rx_GPIO_AF     GPIO_AF6_LPUART
#define LPUART_Tx_GPIO_AF     GPIO_AF6_LPUART
#define LPUART_DAT_Base       (LPUART_BASE + 0x10)
#define LPUART_Tx_DMA_Channel DMA_CH1
#define LPUART_Tx_DMA_FLAG    DMA_FLAG_TC1
#define LPUART_Rx_DMA_Channel DMA_CH2
#define LPUART_Rx_DMA_FLAG    DMA_FLAG_TC2
#define LPUART_IRQn           LPUART_IRQn

#define USARTz                USART3
#define USARTz_GPIO           GPIOC
#define USARTz_CLK            RCC_APB1_PERIPH_USART3
#define USARTz_GPIO_CLK       RCC_APB2_PERIPH_GPIOC
#define USARTz_RxPin          GPIO_PIN_11
#define USARTz_TxPin          GPIO_PIN_10
#define USARTz_Rx_GPIO_AF     GPIO_AF5_USART3
#define USARTz_Tx_GPIO_AF     GPIO_AF5_USART3
#define USARTz_APBxClkCmd     RCC_EnableAPB1PeriphClk
#define USARTz_DAT_Base       (USART3_BASE + 0x04)
#define USARTz_Tx_DMA_Channel DMA_CH4
#define USARTz_Tx_DMA_FLAG    DMA_FLAG_TC4
#define USARTz_Rx_DMA_Channel DMA_CH5
#define USARTz_Rx_DMA_FLAG    DMA_FLAG_TC5
#define USARTz_Tx_DMA_REMAP   DMA_REMAP_USART3_TX
#define USARTz_Rx_DMA_REMAP   DMA_REMAP_USART3_RX
#endif

#ifdef _LPUART_UART5_
#define LPUART_GPIO           GPIOB
#define LPUART_GPIO_CLK       RCC_APB2_PERIPH_GPIOB
#define LPUART_RxPin          GPIO_PIN_7
#define LPUART_TxPin          GPIO_PIN_6
#define LPUART_Rx_GPIO_AF     GPIO_AF6_LPUART
#define LPUART_Tx_GPIO_AF     GPIO_AF6_LPUART
#define LPUART_DAT_Base       (LPUART_BASE + 0x10)
#define LPUART_Tx_DMA_Channel DMA_CH5
#define LPUART_Tx_DMA_FLAG    DMA_FLAG_TC5
#define LPUART_Rx_DMA_Channel DMA_CH6
#define LPUART_Rx_DMA_FLAG    DMA_FLAG_TC6
#define LPUART_IRQn           LPUART_IRQn

#define USARTz                UART5
#define USARTz_GPIO           GPIOB
#define USARTz_CLK            RCC_APB2_PERIPH_UART5
#define USARTz_GPIO_CLK       RCC_APB2_PERIPH_GPIOB
#define USARTz_RxPin          GPIO_PIN_5
#define USARTz_TxPin          GPIO_PIN_4
#define USARTz_Rx_GPIO_AF     GPIO_AF7_UART5
#define USARTz_Tx_GPIO_AF     GPIO_AF6_UART5
#define USARTz_APBxClkCmd     RCC_EnableAPB2PeriphClk
#define USARTz_DAT_Base       (UART5_BASE + 0x04)
#define USARTz_Tx_DMA_Channel DMA_CH7
#define USARTz_Tx_DMA_FLAG    DMA_FLAG_TC7
#define USARTz_Rx_DMA_Channel DMA_CH8
#define USARTz_Rx_DMA_FLAG    DMA_FLAG_TC8
#define USARTz_Tx_DMA_REMAP   DMA_REMAP_UART5_TX
#define USARTz_Rx_DMA_REMAP   DMA_REMAP_UART5_RX
#endif

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

void RCC_Configuration(uint32_t LPUART_CLK_SRC);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void DMA_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
void Delay(__IO uint32_t nCount);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

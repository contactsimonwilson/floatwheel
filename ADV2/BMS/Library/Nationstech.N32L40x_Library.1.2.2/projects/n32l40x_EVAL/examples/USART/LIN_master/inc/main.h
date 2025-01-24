/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x.h"
#include "log.h"
#include "delay.h"
#include "lin_master.h"

#define _USART2_

#ifdef _USART2_


#define USARTz              USART2
#define USARTz_GPIO         GPIOB
#define USARTz_CLK          RCC_APB1_PERIPH_USART2
#define USARTz_GPIO_CLK     RCC_APB2_PERIPH_GPIOB
#define USARTz_RxPin        GPIO_PIN_5
#define USARTz_TxPin        GPIO_PIN_4
#define USARTz_APBxClkCmd   RCC_EnableAPB1PeriphClk
#define USARTz_IRQn         USART2_IRQn
#define USARTz_IRQHandler   USART2_IRQHandler
#define USARTz_RxPin_REMAP  GPIO_AF6_USART2
#define USARTz_TxPin_REMAP  GPIO_AF4_USART2

#endif
void delay_xms(uint32_t nms);
void Buffercopy(uint8_t *dest, uint8_t *src, uint16_t BufferLength);
void *Memset(void *s, s8 c,  u32 count);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

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
 * @file log.c
 * @author Nations Solution Team
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "log.h"

#if LOG_ENABLE

#include "n32l40x.h"
#include "n32l40x_gpio.h"
#include "n32l40x_usart.h"
#include "n32l40x_rcc.h"

#define LOG_USARTx      USART1
#define LOG_PERIPH      RCC_APB2_PERIPH_USART1
#define LOG_GPIO        GPIOA
#define LOG_PERIPH_GPIO RCC_APB2_PERIPH_GPIOA
#define LOG_TX_PIN      GPIO_PIN_9
#define LOG_RX_PIN      GPIO_PIN_10

void log_init(void)
{
    GPIO_InitType GPIO_InitStructure;
    USART_InitType USART_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | LOG_PERIPH_GPIO, ENABLE);

    RCC_EnableAPB2PeriphClk(LOG_PERIPH, ENABLE);


    GPIO_InitStructure.Pin        = LOG_TX_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Slew_Rate = GPIO_Slew_Rate_High;
		GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART1;
    GPIO_InitPeripheral(LOG_GPIO, &GPIO_InitStructure);

    //GPIO_InitStructure.Pin       = LOG_RX_PIN;
    //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    //GPIO_InitPeripheral(LOG_GPIO, &GPIO_InitStructure);

    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_TX;

    // init uart
    USART_Init(LOG_USARTx, &USART_InitStructure);

    // enable uart
    USART_Enable(LOG_USARTx, ENABLE);
}

static int is_lr_sent = 0;

int fputc(int ch, FILE* f)
{
    if (ch == '\r')
    {
        is_lr_sent = 1;
    }
    else if (ch == '\n')
    {
        if (!is_lr_sent)
        {
            USART_SendData(LOG_USARTx, (uint8_t)'\r');
            /* Loop until the end of transmission */
            while (USART_GetFlagStatus(LOG_USARTx, USART_FLAG_TXC) == RESET)
            {
            }
        }
        is_lr_sent = 0;
    }
    else
    {
        is_lr_sent = 0;
    }
    USART_SendData(LOG_USARTx, (uint8_t)ch);
    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(LOG_USARTx, USART_FLAG_TXC) == RESET)
    {
    }
    return ch;
}

#ifdef USE_FULL_ASSERT

__WEAK void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    log_error("assertion failed: `%s` at %s:%d", expr, file, line);
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT

#endif // LOG_ENABLE

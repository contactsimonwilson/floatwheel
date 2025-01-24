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
 * @file main.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include <stdio.h>
#include "main.h"

/** @addtogroup N32L43X_StdPeriph_Examples
 * @{
 */
void RCC_Configuration(void);
void GPIO_Configuration(void);


/**
 * @brief memery set a value
 * @param s source
 * @param c value
 * @param count number
 * @reture pointer of the memoey
 */
void *Memset(void *s, s8 c, u32 count)
{
    s8 *xs = (s8 *) s;
    while(count--)
    {
        *xs++ = c;
    }
    return s;
}

/**
 * @brief Compare two buffers
 * @param pBuffer1,pBuffer2:buffers to be compared.
 * @param BufferLength buffer's length
 * @reture PASSED:pBuffer1 identical to pBuffer2
 *         FAILED:pBuffer1 differs from pBuffer2
 */
void Buffercopy(uint8_t *dest, uint8_t *src, uint16_t BufferLength)
{
    while(BufferLength--)
    {
        *dest = *src;
        dest++;
        src++;
    }
}

/**
 * @brief  Main program
 */
int main(void)
{
    USART_InitType USART_InitStructure;
    log_init();
    delay_init();
    printf("\r\nTest LIN in master mode\r\n");
    /* System Clocks Configuration */
    RCC_Configuration();
    /* Configure the GPIO ports */
    GPIO_Configuration();
    /* USARTy and USARTz configuration ------------------------------------------------------*/
    USART_InitStructure.BaudRate            = 9600;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
    /* Configure USARTy and USARTz */
    USART_Init(USARTz, &USART_InitStructure);
    /* Enable the USARTz LIN mode*/
    USART_ConfigLINBreakDetectLength(USARTz, USART_LINBDL_10B);
    USART_EnableLIN(USARTz, ENABLE);
    /* Enable USARTz Receive and Transmit interrupts */
    // USART_ConfigInt(USARTz, USART_INT_RXDNE, ENABLE);
    // USART_ConfigInt(USARTz, USART_INT_TXDE, ENABLE);
    // USART_ConfigInt(USARTz, USART_INT_LINBD, ENABLE);
    /* Enable the USARTx */
    USART_Enable(USARTz, ENABLE);

    while(1){
        TestLinMaster();
        delay_xms(2000);
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(USARTz_GPIO_CLK | RCC_APB2_PERIPH_AFIO, ENABLE);
    /* Enable USARTz Clock */
    USARTz_APBxClkCmd(USARTz_CLK, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    
    GPIO_InitStruct(&GPIO_InitStructure);
    
    /* Configure USARTx Rx as input floating */
    GPIO_InitStructure.Pin              = USARTz_RxPin;
    GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Current     = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate   = USARTz_RxPin_REMAP;
    GPIO_InitPeripheral(USARTz_GPIO, &GPIO_InitStructure);
    
    /* Configure USARTx Tx as alternate function push-pull */
    GPIO_InitStructure.Pin              = USARTz_TxPin;
    GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate   = USARTz_TxPin_REMAP;
    GPIO_InitPeripheral(USARTz_GPIO, &GPIO_InitStructure);
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param file pointer to the source file name
 * @param line assert_param error line source number
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}

#endif

/**
 * @}
 */

/**
 * @}
 */

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
 * @file main.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include <stdio.h>
#include "main.h"

/** @addtogroup N32L40x_StdPeriph_Examples
 * @{
 */

/** @addtogroup LPUART_Polling
 * @{
 */

#define TxBufferSize1 (countof(TxBuffer1))
#define TxBufferSize2 (countof(TxBuffer2))

#define countof(a) (sizeof(a) / sizeof(*(a)))

LPUART_InitType LPUART_InitStructure;
USART_InitType USART_InitStructure;
uint8_t TxBuffer1[] = "Buffer Send from LPUART to USARTz using Flags";
uint8_t RxBuffer1[TxBufferSize1];
uint8_t TxBuffer2[] = "Buffer Send from USARTz to LPUART using Flags";
uint8_t RxBuffer2[TxBufferSize2];
__IO uint8_t TxCounter = 0, RxCounter = 0;
volatile TestStatus TransferStatus = FAILED;

/**
 * @brief  Main program
 */
int main(void)
{
    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* System Clocks Configuration */
    RCC_Configuration(RCC_LPUARTCLK_SRC_LSE);

    /* LPUART and USARTz configuration ------------------------------------------------------*/
    
    USART_DeInit(USARTz);
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate            = 9600;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
    /* Configure USARTz */
    USART_Init(USARTz, &USART_InitStructure);
    /* Enable the USARTz */
    USART_Enable(USARTz, ENABLE);

    /* Wait for some delay */
    Delay(0x2FFFF);

    LPUART_DeInit();
    LPUART_StructInit(&LPUART_InitStructure);
    LPUART_InitStructure.BaudRate            = 9600;
    LPUART_InitStructure.Parity              = LPUART_PE_NO;
    LPUART_InitStructure.RtsThreshold        = LPUART_RTSTH_FIFOFU;
    LPUART_InitStructure.HardwareFlowControl = LPUART_HFCTRL_NONE;
    LPUART_InitStructure.Mode                = LPUART_MODE_RX | LPUART_MODE_TX;    
    /* Configure LPUART */
    LPUART_Init(&LPUART_InitStructure);

    while (TxCounter < TxBufferSize1)
    {
        /* Send one byte from LPUART to USARTz */
        LPUART_SendData(TxBuffer1[TxCounter++]);

        /* Loop until USARTy DAT register is empty */
        while (LPUART_GetFlagStatus(LPUART_FLAG_TXC) == RESET)
        {
        }
        LPUART_ClrFlag(LPUART_FLAG_TXC); 

        /* Loop until the USARTz Receive Data Register is not empty */
        while (USART_GetFlagStatus(USARTz, USART_FLAG_RXDNE) == RESET)
        {
        }        
        /* Store the received byte in RxBuffer */
        RxBuffer1[RxCounter++] = USART_ReceiveData(USARTz);
    } 

    /* Check the received data with the send ones */
    /* TransferStatus = PASSED, if the data transmitted from LPUART and
       received by USARTz are the same */
    /* TransferStatus = FAILED, if the data transmitted from LPUART and
       received by USARTz are different */
    TransferStatus = Buffercmp(TxBuffer1, RxBuffer1, TxBufferSize1);

    TxCounter = 0;
    RxCounter = 0;
    TransferStatus = FAILED;
    while (TxCounter < TxBufferSize1)
    {
        /* Send one byte from USARTz to LPUART */
        USART_SendData(USARTz, TxBuffer2[TxCounter++]);
        /* Loop until USARTz DAT register is empty */
        while (USART_GetFlagStatus(USARTz, USART_FLAG_TXDE) == RESET)
        {
        }

        /* Loop until the LPUART Receive Data Register is not empty */
        while (LPUART_GetFlagStatus(LPUART_FLAG_FIFO_NE) == RESET)
        {
        }
        /* Store the received byte in RxBuffer */
        RxBuffer2[RxCounter++] = LPUART_ReceiveData();
    }

    /* Check the received data with the send ones */
    /* TransferStatus = PASSED, if the data transmitted from USARTz and
       received by LPUART are the same */
    /* TransferStatus = FAILED, if the data transmitted from USARTz and
       received by LPUART are different */
    TransferStatus = Buffercmp(TxBuffer2, RxBuffer2, TxBufferSize2);

    while (1)
    {
    }
}

/**
 * @brief  Configures LPUART and USARTz clocks.
 * @param  LPUART_CLK_SRC: specifies the LPUART clock source.
 */
void RCC_Configuration(uint32_t LPUART_CLK_SRC)
{
    switch(LPUART_CLK_SRC)
    {
        case RCC_LPUARTCLK_SRC_LSE:
        {            
            RCC_EnableAPB1PeriphClk (RCC_APB1_PERIPH_PWR, ENABLE); 
            PWR->CTRL1 |= PWR_CTRL1_DRBP;
            /* Configures the External Low Speed oscillator (LSE) */
            RCC_ConfigLse(RCC_LSE_ENABLE,0x1FF);
            while (RCC_GetFlagStatus(RCC_LDCTRL_FLAG_LSERD) == RESET)
            {
            }
            /* Specifies the LPUART clock source, LSE selected as LPUART clock */
            RCC_ConfigLPUARTClk(RCC_LPUARTCLK_SRC_LSE);
        }
        break;
        case RCC_LPUARTCLK_SRC_HSI:
        {
            /* Configures the High Speed Internal RC clock (HSI) */
            RCC_ConfigHsi(RCC_HSI_ENABLE);
            while (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF) == RESET)
            {
            }
            /* Specifies the LPUART clock source, HSI selected as LPUART clock */
            RCC_ConfigLPUARTClk(RCC_LPUARTCLK_SRC_HSI);
        }
        break;
        case RCC_LPUARTCLK_SRC_SYSCLK:
        {
            /* Specifies the LPUART clock source, SYSCLK selected as LPUART clock */
            RCC_ConfigLPUARTClk(RCC_LPUARTCLK_SRC_SYSCLK);
        }
        break;
        default:
        {
            /* Specifies the LPUART clock source, APB1 selected as LPUART clock */
            RCC_ConfigLPUARTClk(RCC_LPUARTCLK_SRC_APB1);
        }
        break;
    } 

    /* Enable LPUART and USARTz Clock */
    RCC_EnableRETPeriphClk(RCC_RET_PERIPH_LPUART, ENABLE);
    USARTz_APBxClkCmd(USARTz_CLK, ENABLE);
}


/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(LPUART_GPIO_CLK | USARTz_GPIO_CLK, ENABLE);
	
    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure LPUART Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = LPUART_TxPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = LPUART_Tx_GPIO_AF;
    GPIO_InitPeripheral(LPUART_GPIO, &GPIO_InitStructure);

    /* Configure USARTz Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = USARTz_TxPin;
    GPIO_InitStructure.GPIO_Alternate = USARTz_Tx_GPIO_AF;
    GPIO_InitPeripheral(USARTz_GPIO, &GPIO_InitStructure);    

    /* Configure LPUART Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = LPUART_RxPin;  
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;  
    GPIO_InitStructure.GPIO_Alternate = LPUART_Rx_GPIO_AF;
    GPIO_InitPeripheral(LPUART_GPIO, &GPIO_InitStructure);

    /* Configure USARTz Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = USARTz_RxPin;
    GPIO_InitStructure.GPIO_Alternate = USARTz_Rx_GPIO_AF;
    GPIO_InitPeripheral(USARTz_GPIO, &GPIO_InitStructure); 
}    

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer1 identical to pBuffer2
 *         FAILED: pBuffer1 differs from pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

/**
 * @brief  Inserts a delay time.
 * @param nCount specifies the delay time length.
 */
void Delay(__IO uint32_t nCount)
{
    /* Decrement nCount value */
    for (; nCount != 0; nCount--)
        ;
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

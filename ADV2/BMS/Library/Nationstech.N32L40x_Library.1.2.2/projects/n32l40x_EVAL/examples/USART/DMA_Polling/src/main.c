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

/** @addtogroup N32L40X_StdPeriph_Examples
 * @{
 */

/** @addtogroup USART_DMA_Polling
 * @{
 */

#define TxBufferSize1 (countof(TxBuffer1) - 1)
#define TxBufferSize2 (countof(TxBuffer2) - 1)

#define countof(a) (sizeof(a) / sizeof(*(a)))

USART_InitType USART_InitStructure;
uint8_t TxBuffer1[] = "USART DMA Polling: USARTy -> USARTz using DMA";
uint8_t TxBuffer2[] = "USART DMA Polling: USARTz -> USARTy using DMA";
uint8_t RxBuffer1[TxBufferSize2];
uint8_t RxBuffer2[TxBufferSize1];
volatile TestStatus TransferStatus1 = FAILED;
volatile TestStatus TransferStatus2 = FAILED;

/**
 * @brief  Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* Configure the DMA */
    DMA_Configuration();

    /* USARTy and USARTz configuration ------------------------------------------------------*/
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    /* Configure USARTy and USARTz */
    USART_Init(USARTy, &USART_InitStructure);
    USART_Init(USARTz, &USART_InitStructure);

    /* Enable USARTy DMA Rx and TX request */
    USART_EnableDMA(USARTy, USART_DMAREQ_RX | USART_DMAREQ_TX, ENABLE);
    /* Enable USARTz DMA Rx and TX request */
    USART_EnableDMA(USARTz, USART_DMAREQ_RX | USART_DMAREQ_TX, ENABLE);

    /* Enable USARTy TX DMA Channel */
    DMA_EnableChannel(USARTy_Tx_DMA_Channel, ENABLE);
    /* Enable USARTy RX DMA Channel */
    DMA_EnableChannel(USARTy_Rx_DMA_Channel, ENABLE);

    /* Enable USARTz TX DMA Channel */
    DMA_EnableChannel(USARTz_Tx_DMA_Channel, ENABLE);
    /* Enable USARTz RX DMA Channel */
    DMA_EnableChannel(USARTz_Rx_DMA_Channel, ENABLE);

    /* Enable the USARTy and USARTz */
    USART_Enable(USARTy, ENABLE);
    USART_Enable(USARTz, ENABLE);

    /* Wait until USARTy TX DMA Channel Transfer Complete */
    while (DMA_GetFlagStatus(USARTy_Tx_DMA_FLAG, DMA) == RESET)
    {
    }
    /* Wait until USARTy RX DMA Channel Transfer Complete */
    while (DMA_GetFlagStatus(USARTy_Rx_DMA_FLAG, DMA) == RESET)
    {
    }

    /* Wait until USARTz TX DMA Channel Transfer Complete */
    while (DMA_GetFlagStatus(USARTz_Tx_DMA_FLAG, DMA) == RESET)
    {
    }
    /* Wait until USARTz RX DMA Channel Transfer Complete */
    while (DMA_GetFlagStatus(USARTz_Rx_DMA_FLAG, DMA) == RESET)
    {
    }

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);
    /* TransferStatus1 = PASSED, if the data transmitted from USARTz and
       received by USARTy are the same */
    /* TransferStatus1 = FAILED, if the data transmitted from USARTz and
       received by USARTy are different */
    TransferStatus2 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);
    /* TransferStatus2 = PASSED, if the data transmitted from USARTy and
       received by USARTz are the same */
    /* TransferStatus2 = FAILED, if the data transmitted from USARTy and
       received by USARTz are different */

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);
    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(USARTy_GPIO_CLK | USARTz_GPIO_CLK, ENABLE);
    /* Enable USARTy and USARTz Clock */
    USARTy_APBxClkCmd(USARTy_CLK, ENABLE);
    USARTz_APBxClkCmd(USARTz_CLK, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure USARTy Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = USARTy_TxPin;    
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = USARTy_Tx_GPIO_AF;
    GPIO_InitPeripheral(USARTy_GPIO, &GPIO_InitStructure);

    /* Configure USARTz Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = USARTz_TxPin;
    GPIO_InitStructure.GPIO_Alternate = USARTz_Tx_GPIO_AF;
    GPIO_InitPeripheral(USARTz_GPIO, &GPIO_InitStructure);

    /* Configure USARTy Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = USARTy_RxPin;
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = USARTy_Rx_GPIO_AF;
    GPIO_InitPeripheral(USARTy_GPIO, &GPIO_InitStructure);    

    /* Configure USARTz Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = USARTz_RxPin;
    GPIO_InitStructure.GPIO_Alternate = USARTz_Rx_GPIO_AF;
    GPIO_InitPeripheral(USARTz_GPIO, &GPIO_InitStructure);      
}

/**
 * @brief  Configures the DMA.
 */
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* USARTy TX DMA1 Channel (triggered by USARTy Tx event) Config */
    DMA_DeInit(USARTy_Tx_DMA_Channel);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = USARTy_DAT_Base;
    DMA_InitStructure.MemAddr        = (uint32_t)TxBuffer1;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = TxBufferSize1;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_VERY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(USARTy_Tx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(USARTy_Tx_DMA_REMAP, DMA, USARTy_Tx_DMA_Channel, ENABLE);

    /* USARTy RX DMA1 Channel (triggered by USARTy Rx event) Config */
    DMA_DeInit(USARTy_Rx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = USARTy_DAT_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)RxBuffer1;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize    = TxBufferSize2;
    DMA_Init(USARTy_Rx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(USARTy_Rx_DMA_REMAP, DMA, USARTy_Rx_DMA_Channel, ENABLE);

    /* USARTz TX DMA1 Channel (triggered by USARTz Tx event) Config */
    DMA_DeInit(USARTz_Tx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = USARTz_DAT_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)TxBuffer2;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize    = TxBufferSize2;
    DMA_Init(USARTz_Tx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(USARTz_Tx_DMA_REMAP, DMA, USARTz_Tx_DMA_Channel, ENABLE);

    /* USARTz RX DMA1 Channel (triggered by USARTz Rx event) Config */
    DMA_DeInit(USARTz_Rx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = USARTz_DAT_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)RxBuffer2;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize    = TxBufferSize1;
    DMA_Init(USARTz_Rx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(USARTz_Rx_DMA_REMAP, DMA, USARTz_Rx_DMA_Channel, ENABLE);
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

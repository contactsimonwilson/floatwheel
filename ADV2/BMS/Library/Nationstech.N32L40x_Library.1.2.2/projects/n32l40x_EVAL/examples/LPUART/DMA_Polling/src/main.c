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

/** @addtogroup LPUART_DMA_Polling
 * @{
 */

#define TxBufferSize1 (countof(TxBuffer1))
#define TxBufferSize2 (countof(TxBuffer2))

#define countof(a) (sizeof(a) / sizeof(*(a)))

LPUART_InitType LPUART_InitStructure;
USART_InitType USART_InitStructure;
uint8_t TxBuffer1[] = "LPUART DMA Polling: LPUART -> USARTz using DMA";
uint8_t TxBuffer2[] = "LPUART DMA Polling: USARTz -> LPUART using DMA";
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
    RCC_Configuration(RCC_LPUARTCLK_SRC_LSE);

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* Configure the DMA */
    DMA_Configuration();    	

    /* LPUART and USARTz configuration ------------------------------------------------------*/
    
    USART_DeInit(USARTz);
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate = 9600;
    USART_InitStructure.WordLength = USART_WL_8B;
    USART_InitStructure.StopBits = USART_STPB_1;
    USART_InitStructure.Parity = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode = USART_MODE_RX | USART_MODE_TX;
    /* Configure USARTz */
    USART_Init(USARTz, &USART_InitStructure);
    /* Enable the USARTz */
    USART_Enable(USARTz, ENABLE);

    // Delay(0x2FFFF); 

    LPUART_DeInit();
    LPUART_StructInit(&LPUART_InitStructure);
    LPUART_InitStructure.BaudRate            = 9600;
    LPUART_InitStructure.Parity              = LPUART_PE_NO;
    LPUART_InitStructure.RtsThreshold        = LPUART_RTSTH_FIFOFU;
    LPUART_InitStructure.HardwareFlowControl = LPUART_HFCTRL_NONE;
    LPUART_InitStructure.Mode                = LPUART_MODE_RX | LPUART_MODE_TX;    
    /* Configure LPUART*/
    LPUART_Init(&LPUART_InitStructure);

    /* Enable LPUART DMA Rx and TX request */
    LPUART_EnableDMA(LPUART_DMAREQ_RX | LPUART_DMAREQ_TX, ENABLE);
    /* Enable USARTz DMA Rx and TX request */
    USART_EnableDMA(USARTz, USART_DMAREQ_RX | USART_DMAREQ_TX, ENABLE);

    /* Enable LPUART TX DMA Channel */
    DMA_EnableChannel(LPUART_Tx_DMA_Channel, ENABLE);
    /* Enable LPUART RX DMA Channel */
    DMA_EnableChannel(LPUART_Rx_DMA_Channel, ENABLE);

    /* Enable USARTz TX DMA Channel */
    DMA_EnableChannel(USARTz_Tx_DMA_Channel, ENABLE);
    /* Enable USARTz RX DMA Channel */
    DMA_EnableChannel(USARTz_Rx_DMA_Channel, ENABLE);

    /* Wait until LPUART TX DMA Channel Transfer Complete */
    while (DMA_GetFlagStatus(LPUART_Tx_DMA_FLAG, DMA) == RESET)
    {
    }    
    /* Wait until USARTz RX DMA Channel Receive Complete */
    while (DMA_GetFlagStatus(USARTz_Rx_DMA_FLAG, DMA) == RESET)
    {
    }

    /* Wait until USARTz TX DMA Channel Transfer Complete */
    while (DMA_GetFlagStatus(USARTz_Tx_DMA_FLAG, DMA) == RESET)
    {
    }
    /* Wait until LPUART RX DMA Channel Receive Complete */
    while (DMA_GetFlagStatus(LPUART_Rx_DMA_FLAG, DMA) == RESET)
    {
    }

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(TxBuffer2, RxBuffer1, TxBufferSize2);
    /* TransferStatus1 = PASSED, if the data transmitted from USARTz and
       received by LPUART are the same */
    /* TransferStatus1 = FAILED, if the data transmitted from USARTz and
       received by LPUART are different */
    TransferStatus2 = Buffercmp(TxBuffer1, RxBuffer2, TxBufferSize1);
    /* TransferStatus2 = PASSED, if the data transmitted from LPUART and
       received by USARTz are the same */
    /* TransferStatus2 = FAILED, if the data transmitted from LPUART and
       received by USARTz are different */

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
    GPIO_InitStructure.GPIO_Alternate =  USARTz_Tx_GPIO_AF;
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
 * @brief  Configures the DMA.
 */
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);

    /* LPUART TX DMA Channel (triggered by LPUART Tx event) Config */
    DMA_DeInit(LPUART_Tx_DMA_Channel);
    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.PeriphAddr     = LPUART_DAT_Base;
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
    DMA_Init(LPUART_Tx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_LPUART_TX, DMA, LPUART_Tx_DMA_Channel, ENABLE);

    /* LPUART RX DMA Channel (triggered by LPUART Rx event) Config */
    DMA_DeInit(LPUART_Rx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = LPUART_DAT_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)RxBuffer1;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize    = TxBufferSize2;
    DMA_Init(LPUART_Rx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_LPUART_RX, DMA, LPUART_Rx_DMA_Channel, ENABLE);

    /* USARTx TX DMA Channel (triggered by USARTx Tx event) Config */
    DMA_DeInit(USARTz_Tx_DMA_Channel);
    DMA_InitStructure.PeriphAddr = USARTz_DAT_Base;
    DMA_InitStructure.MemAddr    = (uint32_t)TxBuffer2;
    DMA_InitStructure.Direction  = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize    = TxBufferSize2;
    DMA_Init(USARTz_Tx_DMA_Channel, &DMA_InitStructure);
    DMA_RequestRemap(USARTz_Tx_DMA_REMAP, DMA, USARTz_Tx_DMA_Channel, ENABLE);

    /* USARTx RX DMA Channel (triggered by USARTx Rx event) Config */
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

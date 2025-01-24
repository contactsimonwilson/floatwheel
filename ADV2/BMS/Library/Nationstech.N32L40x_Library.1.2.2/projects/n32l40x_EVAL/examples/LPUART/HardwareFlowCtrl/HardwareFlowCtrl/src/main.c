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

/** @addtogroup LPUART_Interrupt
 * @{
 */

#define TxBufferSize1 (countof(TxBuffer1))
#define TxBufferSize2 (countof(TxBuffer2))
#define RxBufferSize1 TxBufferSize2
#define RxBufferSize2 TxBufferSize1

#define countof(a) (sizeof(a) / sizeof(*(a)))

LPUART_InitType LPUART_InitStructure;
USART_InitType USART_InitStructure;
uint8_t TxBuffer1[] = "LPUART Interrupt Example: LPUART -> USARTz using Interrupt";
uint8_t TxBuffer2[] = "LPUART Interrupt Example: USARTz -> LPUART using Interrupt";
uint8_t RxBuffer1[RxBufferSize1];
uint8_t RxBuffer2[RxBufferSize2];
__IO uint8_t TxCounter1         = 0x00;
__IO uint8_t TxCounter2         = 0x00;
__IO uint8_t RxCounter1         = 0x00;
__IO uint8_t RxCounter2         = 0x00;
uint8_t NbrOfDataToTransfer1    = TxBufferSize1;
uint8_t NbrOfDataToTransfer2    = TxBufferSize2;
uint8_t NbrOfDataToRead1        = RxBufferSize1;
uint8_t NbrOfDataToRead2        = RxBufferSize2;
__IO TestStatus TransferStatus1 = FAILED;
__IO TestStatus TransferStatus2 = FAILED;

/**
 * @brief  Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration(RCC_LPUARTCLK_SRC_LSE);

    /* NVIC configuration */
    NVIC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* LPUART and USARTz configuration ------------------------------------------------------*/
    
    USART_DeInit(USARTz);	
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate            = 9600;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_RTS | USART_HFCTRL_CTS;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
    /* Configure USARTz */
    USART_Init(USARTz, &USART_InitStructure); 
    /* Enable the USARTz */
    USART_Enable(USARTz, ENABLE);

    LPUART_DeInit();    
    LPUART_StructInit(&LPUART_InitStructure);
    LPUART_InitStructure.BaudRate            = 9600;
    LPUART_InitStructure.Parity              = LPUART_PE_NO;
    LPUART_InitStructure.RtsThreshold        = LPUART_RTSTH_FIFOFU;
    LPUART_InitStructure.HardwareFlowControl = LPUART_HFCTRL_RTS | LPUART_HFCTRL_CTS;
    LPUART_InitStructure.Mode                = LPUART_MODE_RX | LPUART_MODE_TX;
    /* Configure LPUART */
    LPUART_Init(&LPUART_InitStructure);

    /* Enable LPUART Receive and Transmit interrupts */
    LPUART_ConfigInt(LPUART_INT_FIFO_NE, ENABLE);
    LPUART_ConfigInt(LPUART_INT_TXC, ENABLE);

    /* Enable USARTz Receive and Transmit interrupts */
    USART_ConfigInt(USARTz, USART_INT_RXDNE, ENABLE);
    USART_ConfigInt(USARTz, USART_INT_TXDE, ENABLE);

    LPUART_SendData(TxBuffer1[TxCounter1]);
    /* Wait until end of transmission from LPUART to USARTz */
    while (RxCounter2 < RxBufferSize2)
    {
    }

    /* Wait until end of transmission from USARTz to LPUART */
    while (RxCounter1 < RxBufferSize1)
    {       
    }    

    /* Check the received data with the send ones */
    // TransferStatus1 = Buffercmp(TxBuffer1, RxBuffer1, RxBufferSize1);
    TransferStatus1 = Buffercmp(TxBuffer2, RxBuffer1, RxBufferSize1);
    /* TransferStatus1 = PASSED, if the data transmitted from USARTz and
       received by LPUART are the same */
    /* TransferStatus1 = FAILED, if the data transmitted from USARTz and
       received by LPUART are different */
    TransferStatus2 = Buffercmp(TxBuffer1, RxBuffer2, RxBufferSize2);
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

    /* Configure LPUART Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = LPUART_TxPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = LPUART_Tx_GPIO_AF;
    GPIO_InitPeripheral(LPUART_GPIO, &GPIO_InitStructure);

    /* Configure LPUART CTS as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = LPUART_CTSPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = LPUART_CTS_GPIO_AF;
    GPIO_InitPeripheral(LPUART_GPIO, &GPIO_InitStructure);

    /* Configure USARTz CTS as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin             = USARTz_CTSPin;
    GPIO_InitStructure.GPIO_Mode       = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Alternate = USARTz_CTS_GPIO_AF;
    GPIO_InitPeripheral(USARTz_GPIO, &GPIO_InitStructure);

    /* Configure LPUART RTS as alternate function push-pull */
    GPIO_InitStructure.Pin            = LPUART_RTSPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = LPUART_RTS_GPIO_AF;
    GPIO_InitPeripheral(LPUART_GPIO, &GPIO_InitStructure);

    /* Configure USARTy RTS as alternate function push-pull */
    GPIO_InitStructure.Pin            = USARTz_RTSPin;
    GPIO_InitPeripheral(USARTz_GPIO, &GPIO_InitStructure);

   	
}

/**
 * @brief  Configures the nested vectored interrupt controller.
 */
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the LPUART Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel            = LPUART_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd         = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USARTz Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel            = USARTz_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd         = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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

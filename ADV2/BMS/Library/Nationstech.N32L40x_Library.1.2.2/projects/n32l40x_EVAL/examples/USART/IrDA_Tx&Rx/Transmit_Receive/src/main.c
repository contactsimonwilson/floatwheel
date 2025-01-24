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
#include "bsp_Tim_38K.h"

/** @addtogroup N32L40X_StdPeriph_Examples
 * @{
 */

/** @addtogroup USART_IrDA_Tx
 * @{
 */

#define TxBufferSize1 (countof(TxBuffer1))

#define countof(a) (sizeof(a) / sizeof(*(a)))

USART_InitType USART_InitStructure;
uint8_t TxBuffer1[]                = "USART IrDA Example: Board1_USARTy -> Board2_USARTz using TXE and RXNE Flags";
uint8_t RxBuffer1[TxBufferSize1];
__IO uint8_t NbrOfDataToRead1 = TxBufferSize1;
__IO uint8_t TxCounter             = 0;
__IO uint8_t RxCounter             = 0;
volatile TestStatus TransferStatus = FAILED;

/**
 * @brief  Configures the nested vectored interrupt controller.
 */
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USARTz Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel            = USARTz_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd         = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
 * @brief  Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();
    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* NVIC configuration */
    NVIC_Configuration();

    /* GPIO PD9 Output 38KHz Clock */
    ADVANCE_TIM_Init();

    /* USARTy and USARTz configuration ------------------------------------------------------*/
    USART_StructInit(&USART_InitStructure);
    USART_InitStructure.BaudRate            = 1200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    /* Configure USARTy */
    USART_Init(USARTy, &USART_InitStructure);
    USART_Init(USARTz, &USART_InitStructure);
    /* Enable USARTz Receive interrupts */
    USART_ConfigInt(USARTz, USART_INT_RXDNE, ENABLE);
	
    /* Set the USARTy prescaler */
    USART_SetPrescaler(USARTy, 0x1);
    USART_SetPrescaler(USARTz, 0x1);
    /* Configure the USARTy IrDA mode */
    USART_ConfigIrDAMode(USARTy, USART_IRDAMODE_NORMAL);
    USART_ConfigIrDAMode(USARTz, USART_IRDAMODE_NORMAL);

    /* Enable the USARTy IrDA mode */
    USART_EnableIrDA(USARTy, ENABLE);
    USART_EnableIrDA(USARTz, ENABLE);

    /* Enable the USARTy */
    USART_Enable(USARTy, ENABLE);
    USART_Enable(USARTz, ENABLE);
    while (TxCounter < TxBufferSize1)
    {
        /* Send one byte from Board1_USARTy to Board2_USARTz */
        USART_SendData(USARTy, TxBuffer1[TxCounter++]);
        /* Loop until Board1_USARTy DAT register is empty */
        while (USART_GetFlagStatus(USARTy, USART_FLAG_TXDE) == RESET)
        {
        }
    }
    while (RxCounter < TxBufferSize1)
    {
    }
    /* Check the received data with the send ones */
    /* TransferStatus = PASSED, if the data transmitted from USARTy and
       received by USARTz are the same */
    /* TransferStatus = FAILED, if the data transmitted from USARTy and
       received by USARTz are different */
    TransferStatus = Buffercmp(TxBuffer1, RxBuffer1, TxBufferSize1);
    while (1)
    {
    }
}

/**
 * @brief  Configures USART clock.
 */
void RCC_Configuration(void)
{    
    RCC_EnableAPB2PeriphClk(USARTy_GPIO_CLK | USARTz_GPIO_CLK, ENABLE);
	/* Enable USARTy Clock */
    USARTy_APBxClkCmd(USARTy_CLK, ENABLE);
    /* Enable USARTz Clock */
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

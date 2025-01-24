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
 * @file n32l40x_it.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l40x_it.h"
#include "main.h"

/** @addtogroup N32L40X_StdPeriph_Template
 * @{
 */

extern uint8_t TxBuffer1[];
extern uint8_t TxBuffer2[];
extern uint8_t RxBuffer1[];
extern uint8_t RxBuffer2[];
extern __IO uint8_t TxCounter1;
extern __IO uint8_t TxCounter2;
extern __IO uint8_t RxCounter1;
extern __IO uint8_t RxCounter2;
extern uint8_t NbrOfDataToTransfer1;
extern uint8_t NbrOfDataToTransfer2;
extern uint8_t NbrOfDataToRead1;
extern uint8_t NbrOfDataToRead2;

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles SVCall exception.
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 N32L40X Peripherals Interrupt Handlers                     */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_n32l40x.s).                                                 */
/******************************************************************************/

/**
 * @brief  This function handles USARTy global interrupt request.
 */
void USARTy_IRQHandler(void)
{
    if (USART_GetIntStatus(USARTy, USART_INT_RXDNE) != RESET)
    {
        /* Read one byte from the receive data register */
        RxBuffer1[RxCounter1++] = USART_ReceiveData(USARTy);

        if (RxCounter1 == NbrOfDataToRead1)
        {
            /* Disable the USARTy Receive interrupt */
            USART_ConfigInt(USARTy, USART_INT_RXDNE, DISABLE);
        }
    }

    if (USART_GetIntStatus(USARTy, USART_INT_TXDE) != RESET)
    {
        /* Write one byte to the transmit data register */
        USART_SendData(USARTy, TxBuffer1[TxCounter1++]);

        if (TxCounter1 == NbrOfDataToTransfer1)
        {
            /* Disable the USARTy Transmit interrupt */
            USART_ConfigInt(USARTy, USART_INT_TXDE, DISABLE);
        }
    }
    if(USART_GetIntStatus(USARTy, USART_INT_OREF) != RESET)
    {
        /*Read the STS register first,and the read the DAT 
        register to clear the overflow interrupt*/
        (void)USARTy->STS;
        (void)USARTy->DAT;
    }
}

/**
 * @brief  This function handles USARTz global interrupt request.
 */
void USARTz_IRQHandler(void)
{
    if (USART_GetIntStatus(USARTz, USART_INT_RXDNE) != RESET)
    {
        /* Read one byte from the receive data register */
        RxBuffer2[RxCounter2++] = USART_ReceiveData(USARTz);

        if (RxCounter2 == NbrOfDataToRead1)
        {
            /* Disable the USARTz Receive interrupt */
            USART_ConfigInt(USARTz, USART_INT_RXDNE, DISABLE);
        }
    }

    if (USART_GetIntStatus(USARTz, USART_INT_TXDE) != RESET)
    {
        /* Write one byte to the transmit data register */
        USART_SendData(USARTz, TxBuffer2[TxCounter2++]);

        if (TxCounter2 == NbrOfDataToTransfer2)
        {
            /* Disable the USARTz Transmit interrupt */
            USART_ConfigInt(USARTz, USART_INT_TXDE, DISABLE);
        }
    }
    if(USART_GetIntStatus(USARTz, USART_INT_OREF) != RESET)
    {
        /*Read the STS register first,and the read the DAT 
        register to clear the overflow interrupt*/
        (void)USARTz->STS;
        (void)USARTz->DAT;
    }
}

/**
 * @}
 */

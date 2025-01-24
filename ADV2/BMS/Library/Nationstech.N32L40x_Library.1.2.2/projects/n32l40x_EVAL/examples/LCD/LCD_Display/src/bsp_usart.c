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
 * @file bsp_usart.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "bsp_usart.h"

/**
 * @brief  Configure nested vector interrupt controller NVIC.
 */
static void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Select nested vector interrupt controller group */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Configure USART as interrupt source */
    NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART_IRQ;
    /*Set the priority*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /*Set the sub priority */
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /*Enable interrupt */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    /* Initialize configuration NVIC */
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  Configure parameters of usart port.
 */
void Debug_USART_Config(void)
{
    GPIO_InitType GPIO_InitStructure;
    USART_InitType USART_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    // Turn on the clock of usart port GPIO
    DEBUG_USART_GPIO_APBxClkCmd(DEBUG_USART_GPIO_CLK, ENABLE);

    // Turn on the clock of usart peripheral
    DEBUG_USART_APBxClkCmd(DEBUG_USART_CLK, ENABLE);

    // Configure GPIO of USART TX as push pull multiplexing mode
    GPIO_InitStructure.Pin              = DEBUG_USART_TX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate   = DEBUG_USART_TX_GPIO_RMP;
    GPIO_InitPeripheral(DEBUG_USART_TX_GPIO_PORT, &GPIO_InitStructure);

    // Configure GPIO of USART RX as floating input mode
    GPIO_InitStructure.Pin              = DEBUG_USART_RX_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode        = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate   = DEBUG_USART_RX_GPIO_RMP;
    GPIO_InitPeripheral(DEBUG_USART_RX_GPIO_PORT, &GPIO_InitStructure);

    // Configure parameters of usart port
    // Configure baud rate
    USART_InitStructure.BaudRate = DEBUG_USART_BAUDRATE;
    // Configure the length of frame data
    USART_InitStructure.WordLength = USART_WL_8B;
    // Configure stop bits
    USART_InitStructure.StopBits = USART_STPB_1;
    // Configure check bit
    USART_InitStructure.Parity = USART_PE_NO;
    // Configure hardware flow control
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    // Configure working mode, send and receive together
    USART_InitStructure.Mode = USART_MODE_RX | USART_MODE_TX;
    // Complete initialization configuration of usart port
    USART_Init(DEBUG_USARTx, &USART_InitStructure);

    // Configuration interrupt priority of the usart port
    NVIC_Configuration();

    // Enable usart port receive interrupt
    //  USART_ConfigInt(DEBUG_USARTx, USART_INT_RXDNE, ENABLE);

    // Enable usart
    USART_Enable(DEBUG_USARTx, ENABLE);
}

/*****************  Send one byte data **********************/
void Usart_SendByte(USART_Module* pUSARTx, uint8_t ch)
{
   /* Clear transmission complete flag */
    USART_ClrFlag(pUSARTx, USART_FLAG_TXC);
    
    /* Send one byte data to usart */
    USART_SendData(pUSARTx, ch);

    /* Waiting to send data register is empty */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXDE) == RESET);
}

/****************** Send an array of 8 bit************************/
void Usart_SendArray(USART_Module* pUSARTx, uint8_t* array, uint16_t num)
{
    uint8_t i;

    for (i = 0; i < num; i++)
    {
        /* Send one byte data to usart */
        Usart_SendByte(pUSARTx, array[i]);
    }
    /* Wait to send finished */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXC) == RESET);
}

/*****************  Send string **********************/
void Usart_SendString(USART_Module* pUSARTx, char* str)
{
    unsigned int k = 0;
    do
    {
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    } while (*(str + k) != '\0');

    /* Wait to send finished */
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXC) == RESET);
}

/*****************  Send a 16 bits number **********************/
void Usart_SendHalfWord(USART_Module* pUSARTx, uint16_t ch)
{
    uint8_t temp_h, temp_l;

    /* Take out the high byte */
    temp_h = (ch & 0XFF00) >> 8;
    /* Take out the loe byte */
    temp_l = ch & 0XFF;

    /* Send the high byte */
    USART_SendData(pUSARTx, temp_h);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXDE) == RESET);

    /* Send the low byte */
    USART_SendData(pUSARTx, temp_l);
    while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXDE) == RESET);
}

// Redirect C library printf function to USART port.After rewriting, printf function can be used.
static int is_lr_sent = 0;
int fputc(int ch, FILE* f)
{
    uint8_t tchar = (uint8_t)ch;
    
    if (tchar == '\r')
    {
        is_lr_sent = 1;
    }
    else if (tchar == '\n')
    {
        if (!is_lr_sent)
        {
            tchar = '\r';
        }

        is_lr_sent = 0;
    }
    else
    {
        is_lr_sent = 0;
    }

    Usart_SendByte(DEBUG_USARTx, tchar);

    return (ch);
}


// Redirect C library scanf function to USART port.After rewriting, functions such as scanf, getchar can be used.
int fgetc(FILE* f)
{
    /* Waiting for usart port input data */
    while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXDNE) == RESET);

    return (int)USART_ReceiveData(DEBUG_USARTx);
}


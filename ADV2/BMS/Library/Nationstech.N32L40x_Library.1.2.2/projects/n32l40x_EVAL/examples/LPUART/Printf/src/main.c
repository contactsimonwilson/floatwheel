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

/** @addtogroup LPUART_Printf
 * @{
 */

LPUART_InitType LPUART_InitStructure;

/**
 * @brief  Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration(RCC_LPUARTCLK_SRC_APB1);

    /* Configure the GPIO ports */
    GPIO_Configuration();

    LPUART_DeInit();
    /* LPUART configuration ------------------------------------------------------*/
    LPUART_StructInit(&LPUART_InitStructure);
    LPUART_InitStructure.BaudRate            = 9600;
    LPUART_InitStructure.Parity              = LPUART_PE_NO;
    LPUART_InitStructure.RtsThreshold        = LPUART_RTSTH_FIFOFU;
    LPUART_InitStructure.HardwareFlowControl = LPUART_HFCTRL_NONE;
    LPUART_InitStructure.Mode                = LPUART_MODE_RX | LPUART_MODE_TX;
    /* Configure LPUART */
    LPUART_Init(&LPUART_InitStructure);

    /* Output a message on Hyperterminal using printf function */
    printf("\n\rLPUART Printf Example: retarget the C library printf function to the LPUART\n\r");

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 * @param  LPUART_CLK_SRC: specifies the LPUART clock source.
 */
void RCC_Configuration(uint32_t LPUART_CLK_SRC)
{
    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(LPUART_GPIO_CLK, ENABLE);

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
    
    /* Enable LPUART Clock */    
    RCC_EnableRETPeriphClk(RCC_RET_PERIPH_LPUART, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure LPUART Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = LPUART_TxPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = LPUART_Tx_GPIO_AF;
    GPIO_InitPeripheral(LPUART_GPIO, &GPIO_InitStructure);

    /* Configure LPAURT Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = LPUART_RxPin;
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;    
    GPIO_InitStructure.GPIO_Alternate = LPUART_Rx_GPIO_AF;
    GPIO_InitPeripheral(LPUART_GPIO, &GPIO_InitStructure);
}

/* retarget the C library printf function to the LPUART */
int fputc(int ch, FILE* f)
{
    LPUART_SendData((uint8_t)ch);
    while (LPUART_GetFlagStatus(LPUART_FLAG_TXC) == RESET)
        ;
    LPUART_ClrFlag(LPUART_FLAG_TXC);      

    return (ch);
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

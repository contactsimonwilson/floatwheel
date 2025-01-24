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

/** @addtogroup N32L40x_StdPeriph_Template
 * @{
 */

 uint16_t IC3ReadValue1 = 0, IC3ReadValue2 = 0;
__IO uint16_t CaptureNumber   = 0;
__IO uint32_t Capture         = 0;
__IO uint32_t TIM3Freq        = 0;
__IO uint32_t TIM3EnterIrqCnt = 0;

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
/*                 N32L40x Peripherals Interrupt Handlers                     */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_n32l40x.s).                                                 */
/******************************************************************************/
/**
 * @brief  This function handles TIM3 global interrupt request.
 */

//uint32_t freq_cnt = (SystemCoreClock / 2);   //计数器时钟频率
void TIM3_IRQHandler(void)
{
    if (TIM_GetIntStatus(TIM3, TIM_INT_CC2) == SET)
    {
        /* Clear TIM3 Capture compare interrupt pending bit */
        TIM_ClrIntPendingBit(TIM3, TIM_INT_CC2);
        if (CaptureNumber == 0)
        {
            /* Get the Input Capture value */
            IC3ReadValue1 = TIM_GetCap2(TIM3);
            CaptureNumber = 1;
            TIM3EnterIrqCnt = 0;
            Capture = 0;
            TIM3Freq = 0;
        }
        else if (CaptureNumber == 1)
        {
            /* Get the Input Capture value */
            IC3ReadValue2 = TIM_GetCap2(TIM3);

            /* Capture computation */
            if (IC3ReadValue2 > IC3ReadValue1)
            {
                Capture = (IC3ReadValue2 - IC3ReadValue1)+ (TIM3EnterIrqCnt * 0xFFFF);
            }
            else
            {
                Capture = ((TIM3EnterIrqCnt * 0xFFFF - IC3ReadValue1) + IC3ReadValue2);
            }
            /* Frequency computation */
            TIM3Freq      = (uint32_t)(SystemCoreClock / 2) / Capture;
            CaptureNumber = 0;
        }
    }
    if(TIM_GetIntStatus(TIM3, TIM_INT_UPDATE) == SET)
    {
        TIM_ClrIntPendingBit(TIM3, TIM_INT_UPDATE);
        if(CaptureNumber == 1)
        {
            TIM3EnterIrqCnt++;
        }
        else
        {
            TIM3EnterIrqCnt = 0;
        }
    }
}

/**
 * @}
 */

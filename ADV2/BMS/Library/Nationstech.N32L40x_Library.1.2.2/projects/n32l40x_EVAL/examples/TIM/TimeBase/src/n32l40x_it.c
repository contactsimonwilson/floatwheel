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

uint16_t capture = 0;
extern __IO uint16_t CCR1_Val;
extern __IO uint16_t CCR2_Val;
extern __IO uint16_t CCR3_Val;
extern __IO uint16_t CCR4_Val;

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
 * @brief  This function handles TIM2 global interrupt request.
 */
void TIM2_IRQHandler(void)
{
    if (TIM_GetIntStatus(TIM2, TIM_INT_CC1) != RESET)
    {
        TIM_ClrIntPendingBit(TIM2, TIM_INT_CC1);

        /* Pin PC.06 toggling with frequency = 73.24 Hz */
        GPIO_WriteBit(GPIOC, GPIO_PIN_6, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_PIN_6)));
        capture = TIM_GetCap1(TIM2);
        TIM_SetCmp1(TIM2, capture + CCR1_Val);
    }
    else if (TIM_GetIntStatus(TIM2, TIM_INT_CC2) != RESET)
    {
        TIM_ClrIntPendingBit(TIM2, TIM_INT_CC2);

        /* Pin PC.07 toggling with frequency = 109.8 Hz */
        GPIO_WriteBit(GPIOC, GPIO_PIN_7, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_PIN_7)));
        capture = TIM_GetCap2(TIM2);
        TIM_SetCmp2(TIM2, capture + CCR2_Val);
    }
    else if (TIM_GetIntStatus(TIM2, TIM_INT_CC3) != RESET)
    {
        TIM_ClrIntPendingBit(TIM2, TIM_INT_CC3);

        /* Pin PC.08 toggling with frequency = 219.7 Hz */
        GPIO_WriteBit(GPIOC, GPIO_PIN_8, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_PIN_8)));
        capture = TIM_GetCap3(TIM2);
        TIM_SetCmp3(TIM2, capture + CCR3_Val);
    }
    else
    {
        TIM_ClrIntPendingBit(TIM2, TIM_INT_CC4);

        /* Pin PC.09 toggling with frequency = 439.4 Hz */
        GPIO_WriteBit(GPIOC, GPIO_PIN_9, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOC, GPIO_PIN_9)));
        capture = TIM_GetCap4(TIM2);
        TIM_SetCmp4(TIM2, capture + CCR4_Val);
    }
}

/**
 * @}
 */

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
 * @author Nations Solution Team
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l40x_it.h"
#include "n32l40x.h"

/** @addtogroup N32L40X_StdPeriph_Template
 * @{
 */

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 */
void NMI_Handler(void)
{
    /* This interrupt is generated when HSE clock fails */

    if (RCC_GetIntStatus(RCC_INT_CLKSSIF) != RESET)
    {
        /* At this stage: HSE, PLL are disabled (but no change on PLL config) and HSI
            is selected as system clock source */

        /* Enable HSE */
        RCC_ConfigHse(RCC_HSE_ENABLE);

        /* Enable HSE Ready interrupt */
        RCC_ConfigInt(RCC_INT_HSERDIF, ENABLE);

#ifndef SYSCLK_HSE
        /* Enable PLL Ready interrupt */
        RCC_ConfigInt(RCC_INT_PLLRDIF, ENABLE);
#endif /* SYSCLK_HSE */

        /* Clear Clock Security System interrupt pending bit */
        RCC_ClrIntPendingBit(RCC_CLR_CLKSSIF);

        /* Once HSE clock recover, the HSERDY interrupt is generated and in the RCC INTSTS
           routine the system clock will be reconfigured to its previous state (before
           HSE clock failure) */
    }
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

/**
 * @brief  This function handles RCC interrupt request.
 */
void RCC_IRQHandler(void)
{
    if (RCC_GetIntStatus(RCC_INT_HSERDIF) != RESET)
    {
        /* Clear HSERDY interrupt pending bit */
        RCC_ClrIntPendingBit(RCC_CLR_HSERDIF);

        /* Check if the HSE clock is still available */
        if (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF) != RESET)
        {
#ifdef SYSCLK_HSE
            /* Select HSE as system clock source */
            RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSE);
#else
            /* Enable PLL: once the PLL is ready the PLLRDY interrupt is generated */
            RCC_EnablePll(ENABLE);
#endif /* SYSCLK_HSE */
        }
    }

    if (RCC_GetIntStatus(RCC_INT_PLLRDIF) != RESET)
    {
        /* Clear PLLRDY interrupt pending bit */
        RCC_ClrIntPendingBit(RCC_CLR_PLLRDIF);

        /* Check if the PLL is still locked */
        if (RCC_GetFlagStatus(RCC_CTRL_FLAG_PLLRDF) != RESET)
        {
            /* Select PLL as system clock source */
            RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);
        }
    }
}

/******************************************************************************/
/*                 N32L40X Peripherals Interrupt Handlers                     */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_n32l40x.s).                                                 */
/******************************************************************************/

/**
 * @brief  This function handles PPP interrupt request.
 */
/*void PPP_IRQHandler(void)
{
}*/

/**
 * @}
 */

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

__IO uint32_t step = 1;

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
    /* Generate TIM1 COM event by software */
    TIM_GenerateEvent(TIM1, TIM_EVT_SRC_COM);
}

/******************************************************************************/
/*            N32L40X Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
 * @brief  This function handles TIM1 Trigger and commutation interrupts
 *   requests.
 */
void TIM1_TRG_COM_IRQHandler(void)
{
    /* Clear TIM1 COM pending bit */
    TIM_ClrIntPendingBit(TIM1, TIM_INT_COM);

    if (step == 1)
    {
        /* Next step: Step 2 Configuration ---------------------------- */
        /*  Channel3 configuration */
        TIM_EnableCapCmpCh(TIM1, TIM_CH_3, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_3, TIM_CAP_CMP_N_DISABLE);

        /*  Channel1 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_1, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_1, TIM_CAP_CMP_ENABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_1, TIM_CAP_CMP_N_DISABLE);

        /*  Channel2 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_2, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_2, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_2, TIM_CAP_CMP_N_ENABLE);
        step++;
    }
    else if (step == 2)
    {
        /* Next step: Step 3 Configuration ---------------------------- */
        /*  Channel2 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_2, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_2, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_2, TIM_CAP_CMP_N_ENABLE);

        /*  Channel3 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_3, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_3, TIM_CAP_CMP_ENABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_3, TIM_CAP_CMP_N_DISABLE);

        /*  Channel1 configuration */
        TIM_EnableCapCmpCh(TIM1, TIM_CH_1, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_1, TIM_CAP_CMP_N_DISABLE);
        step++;
    }
    else if (step == 3)
    {
        /* Next step: Step 4 Configuration ---------------------------- */
        /*  Channel3 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_3, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_3, TIM_CAP_CMP_ENABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_3, TIM_CAP_CMP_N_DISABLE);

        /*  Channel2 configuration */
        TIM_EnableCapCmpCh(TIM1, TIM_CH_2, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_2, TIM_CAP_CMP_N_DISABLE);

        /*  Channel1 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_1, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_1, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_1, TIM_CAP_CMP_N_ENABLE);
        step++;
    }
    else if (step == 4)
    {
        /* Next step: Step 5 Configuration ---------------------------- */
        /*  Channel3 configuration */
        TIM_EnableCapCmpCh(TIM1, TIM_CH_3, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_3, TIM_CAP_CMP_N_DISABLE);

        /*  Channel1 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_1, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_1, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_1, TIM_CAP_CMP_N_ENABLE);

        /*  Channel2 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_2, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_2, TIM_CAP_CMP_ENABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_2, TIM_CAP_CMP_N_DISABLE);
        step++;
    }
    else if (step == 5)
    {
        /* Next step: Step 6 Configuration ---------------------------- */
        /*  Channel3 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_3, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_3, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_3, TIM_CAP_CMP_N_ENABLE);

        /*  Channel1 configuration */
        TIM_EnableCapCmpCh(TIM1, TIM_CH_1, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_1, TIM_CAP_CMP_N_DISABLE);

        /*  Channel2 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_2, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_2, TIM_CAP_CMP_ENABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_2, TIM_CAP_CMP_N_DISABLE);
        step++;
    }
    else
    {
        /* Next step: Step 1 Configuration ---------------------------- */
        /*  Channel1 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_1, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_1, TIM_CAP_CMP_ENABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_2, TIM_CAP_CMP_N_DISABLE);

        /*  Channel3 configuration */
        TIM_SelectOcMode(TIM1, TIM_CH_3, TIM_OCMODE_PWM1);
        TIM_EnableCapCmpCh(TIM1, TIM_CH_3, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_3, TIM_CAP_CMP_N_ENABLE);

        /*  Channel2 configuration */
        TIM_EnableCapCmpCh(TIM1, TIM_CH_2, TIM_CAP_CMP_DISABLE);
        TIM_EnableCapCmpChN(TIM1, TIM_CH_2, TIM_CAP_CMP_N_DISABLE);
        step = 1;
    }
}

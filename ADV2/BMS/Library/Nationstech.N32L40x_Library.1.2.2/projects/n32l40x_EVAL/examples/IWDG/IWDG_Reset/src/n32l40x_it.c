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
//#include "n32l40x_eval.h"

/** @addtogroup n32l40x_StdPeriph_Template
 * @{
 */

extern __IO uint32_t TimingDelay;
 uint16_t IC1ReadValue1 = 0, IC1ReadValue2 = 0;
 uint16_t CaptureNumber = 0;
 uint32_t Capture       = 0;
extern uint32_t LsiFreq;

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
 * @brief  This function handles Debug Monitor exception.
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles SVCall exception.
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles PendSV_Handler exception.
 */
void PendSV_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 */
void SysTick_Handler(void)
{
    TimingDelay--;
}

/******************************************************************************/
/*            n32l40x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
 * @brief  This function handles TIM9 global interrupt request.
 */
void TIM9_IRQHandler(void)
{
    if (TIM_GetIntStatus(TIM9, TIM_INT_CC3) != RESET)
    {
        if (CaptureNumber == 0)
        {
            /* Get the Input Capture value */
            IC1ReadValue1 = TIM_GetCap3(TIM9);
        }
        else if (CaptureNumber == 2)
        {
            RCC_ClocksType clks;
            /* Get the Input Capture value */
            IC1ReadValue2 = TIM_GetCap3(TIM9);

            /* Capture computation */
            if (IC1ReadValue2 > IC1ReadValue1)
            {
                Capture = (IC1ReadValue2 - IC1ReadValue1);
            }
            else
            {
                Capture = ((0xFFFF - IC1ReadValue1) + IC1ReadValue2);
            }
            RCC_GetClocksFreqValue(&clks);
            /* Frequency computation */
            LsiFreq = (uint32_t)clks.Pclk1Freq / Capture;
            LsiFreq *= 32;

        }

        CaptureNumber++;

        /* Clear TIM9 Capture compare interrupt pending bit */
        TIM_ClrIntPendingBit(TIM9, TIM_INT_CC3);
    }
}

/******************************************************************************/
/*                 n32l40x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_n32l40x.s).                                            */
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
/**
 * @}
 */

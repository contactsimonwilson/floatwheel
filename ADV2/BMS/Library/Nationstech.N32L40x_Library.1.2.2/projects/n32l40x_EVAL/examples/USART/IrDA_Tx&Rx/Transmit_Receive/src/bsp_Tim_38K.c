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
 * @file bsp_Tim_38K.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

#include "bsp_Tim_38K.h"

void ADVANCE_TIM_GPIO_Config(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(PORTx_CLK, ENABLE);
    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure PD9 as Out_PP */
    GPIO_InitStructure.Pin            = PORTx_PIN;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(PORTx, &GPIO_InitStructure);
}

static void ADVANCE_TIM_NVIC_Config(void)
{
    NVIC_InitType NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    NVIC_InitStructure.NVIC_IRQChannel                   = ADVANCE_TIM_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void ADVANCE_TIM_Mode_Config(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;

    ADVANCE_TIM_APBxClock_FUN(ADVANCE_TIM_CLK, ENABLE);
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = ADVANCE_TIM_Period;
    TIM_TimeBaseStructure.Prescaler = ADVANCE_TIM_Prescaler;
    TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.RepetCnt  = 0;
    TIM_InitTimeBase(ADVANCE_TIM, &TIM_TimeBaseStructure);

    TIM_ClearFlag(ADVANCE_TIM, TIM_FLAG_UPDATE);
    TIM_ConfigInt(ADVANCE_TIM, TIM_INT_UPDATE, ENABLE);

    TIM_Enable(ADVANCE_TIM, ENABLE);
}

void ADVANCE_TIM_Init(void)
{
    ADVANCE_TIM_GPIO_Config();
    ADVANCE_TIM_NVIC_Config();
    ADVANCE_TIM_Mode_Config();
}

void ADVANCE_TIM_IRQHandler(void)
{
    if (TIM_GetIntStatus(ADVANCE_TIM, TIM_INT_UPDATE) != RESET)
    {
        TIM_ClrIntPendingBit(ADVANCE_TIM, TIM_FLAG_UPDATE);
        digitalToggle(PORTx, PORTx_PIN);
    }
}

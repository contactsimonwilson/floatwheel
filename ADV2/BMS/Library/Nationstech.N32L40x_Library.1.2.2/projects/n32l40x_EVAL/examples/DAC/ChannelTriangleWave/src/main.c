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
#include "n32l40x.h"

/** @addtogroup DAC_TwoChannels_TriangleWave
 * @{
 */

void GPIO_Configuration(void);
void TIM5_Init(void);
void DmaChannelsConfig(void);

/**
 * @brief   Main program.
 */
int main(void)
{
    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_Configuration();
    TIM5_Init();
    DmaChannelsConfig();
    /* TIM2 enable counter */
    TIM_Enable(TIM5, ENABLE);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */

/**
 * @brief  TIM5 Init.
 */
void TIM5_Init(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    /* TIM5 Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
    /* TIM5 Configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 0xF;
    TIM_TimeBaseStructure.Prescaler = 0xF;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM5, &TIM_TimeBaseStructure);

    /* TIM5 TRGO selection */
    TIM_SelectOutputTrig(TIM5, TIM_TRGO_SRC_UPDATE);
}
/**
 * @brief  DAC channel1 Configuration.
 */
void DmaChannelsConfig(void)
{
    DAC_InitType DAC_InitStructure;

    /* DAC Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC, ENABLE);
    /* DAC channel1 Configuration */
    DAC_InitStructure.Trigger          = DAC_TRG_T5_TRGO;
    DAC_InitStructure.WaveGen          = DAC_WAVEGEN_TRIANGLE;
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_TRIAMP_2047;
    DAC_InitStructure.BufferOutput     = DAC_BUFFOUTPUT_DISABLE;
    DAC_Init(&DAC_InitStructure);

    /* DAC channel2 Configuration */
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_TRIAMP_1023;


    /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
             automatically connected to the DAC converter. */
    DAC_Enable(ENABLE);
    /* Set DAC  channel DR12DCH register */
    DAC_SetChData(DAC_ALIGN_R_12BIT,0x100);
}
/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOA Periph clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_InitStructure.Pin       = GPIO_PIN_4 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Pull = GPIO_No_Pull;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

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

/** @addtogroup DAC_OneChanneloutputNoiseWave
 * @{
 */

void GPIO_Configuration(void);
void DAC_ChannelConfig(void);

/**
 * @brief   Main program.
 */
int main(void)
{
    /* Once the DAC channel is enabled, the corresponding GPIO pin is automatically
       connected to the DAC converter. In order to avoid parasitic consumption,
       the GPIO pin should be configured in analog */
    GPIO_Configuration();
    DAC_ChannelConfig();
    DAC_SoftTrgEnable(ENABLE);
    while (1)
    {
        /* Start DAC Channel1 conversion by software */
        DAC_SoftTrgEnable(ENABLE);
    }
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
    GPIO_InitStructure.Pin       = GPIO_PIN_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Pull = GPIO_No_Pull;
    //GPIO_InitStructure.GPIO_Pull = GPIO_Mode_AF_OD; 
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void DAC_ChannelConfig(void)
{
    DAC_InitType DAC_InitStructure;

    /* DAC Periph clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_DAC, ENABLE);
    /* DAC channel1 Configuration */
    DAC_InitStructure.Trigger          = DAC_TRG_SOFTWARE;
    DAC_InitStructure.WaveGen          = DAC_WAVEGEN_NOISE;
    DAC_InitStructure.LfsrUnMaskTriAmp = DAC_UNMASK_LFSRBIT0;
    DAC_InitStructure.BufferOutput     = DAC_BUFFOUTPUT_ENABLE;
    DAC_Init(&DAC_InitStructure);

    /* Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
       automatically connected to the DAC converter. */
      
    DAC_Enable(ENABLE);

    /* Set DAC Channel1 DHR12L register */
    DAC_SetChData(DAC_ALIGN_R_12BIT, 4094);
}

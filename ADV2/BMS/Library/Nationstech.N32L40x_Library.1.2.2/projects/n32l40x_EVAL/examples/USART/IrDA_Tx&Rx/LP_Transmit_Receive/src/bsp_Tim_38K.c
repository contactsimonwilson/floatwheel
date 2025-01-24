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
void LPTIM_OutputIoInit(void);

void ADVANCE_TIM_Init(void)
{
    RCC_ConfigLPTIMClk(ADVANCE_TIM_CLK);
    RCC_EnableRETPeriphClk(RCC_RET_PERIPH_LPTIM,ENABLE);
	
    /* Init output IO */
    LPTIM_SetPrescaler(LPTIM,ADVANCE_TIM_Prescaler);
    LPTIM_OutputIoInit();
    /* Init lptim module */ 
    LPTIM->INTEN = 0x7F;

    LPTIM_SetWaveform(LPTIM,LPTIM_OUTPUT_WAVEFORM_PWM); 
    /* output wave */ 
    LPTIM_SetPolarity(LPTIM,LPTIM_OUTPUT_POLARITY_REGULAR);  
    /* config the prescaler */          
    LPTIM_EnableIT_CMPOK(LPTIM);

    LPTIM_Enable(LPTIM);
    /* config ARR ande compare register */ 
    LPTIM_SetAutoReload(LPTIM,ADVANCE_TIM_Period);      
    LPTIM_SetCompare(LPTIM,ADVANCE_TIM_Pulse);
    LPTIM_StartCounter(LPTIM,LPTIM_OPERATING_MODE_CONTINUOUS);  	
}
/**
 * @brief  output IO Initaliza.
 * @param NONE.
 *   This parameter can be one of following parameters:
 *     @arg NONE
 */
void LPTIM_OutputIoInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable the GPIO Clock */
    RCC_EnableAPB2PeriphClk(PORTx_CLK, ENABLE);

    /* Configure the GPIO pin */
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = PORTx_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_LPTIM;
    GPIO_InitPeripheral(PORTx, &GPIO_InitStructure);
}

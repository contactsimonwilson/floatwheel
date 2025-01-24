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
#include "main.h"

/** @addtogroup TIM_PWM_Output
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
uint16_t CCR1_Val       = 333;
uint16_t CCR2_Val       = 249;
uint16_t CCR3_Val       = 166;
uint16_t CCR4_Val       = 83;
uint16_t PrescalerValue = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);

/**
 * @brief  Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* Compute the prescaler value */
    PrescalerValue = (uint16_t)(SystemCoreClock / 12000000) - 1;
    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Period    = 665;
    TIM_TimeBaseStructure.Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    TIM_InitOcStruct(&TIM_OCInitStructure);    
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR1_Val;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM3, &TIM_OCInitStructure);

    TIM_ConfigOc1Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR2_Val;

    TIM_InitOc2(TIM3, &TIM_OCInitStructure);

    TIM_ConfigOc2Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

    /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR3_Val;

    TIM_InitOc3(TIM3, &TIM_OCInitStructure);

    TIM_ConfigOc3Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

    /* PWM1 Mode configuration: Channel4 */
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = CCR4_Val;

    TIM_InitOc4(TIM3, &TIM_OCInitStructure);

    TIM_ConfigOc4Preload(TIM3, TIM_OC_PRE_LOAD_ENABLE);

    TIM_ConfigArPreload(TIM3, ENABLE);

    /* TIM3 enable counter */
    TIM_Enable(TIM3, ENABLE);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* TIM3 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);

    /* GPIOA and GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(
        RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
}

/**
 * @brief  Configure the TIM3 Ouput Channels.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOA Configuration:TIM3 Channel1, 2, 3 and 4 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
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

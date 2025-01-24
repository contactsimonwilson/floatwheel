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

/** @addtogroup ADC_TIMTrigger_AutoInjection
 * @{
 */

ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;
TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
__IO uint16_t ADC_RegularConvertedValueTab[32], ADC_InjectedConvertedValueTab[32];

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);

/**
 * @brief   Main program
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* NVIC configuration ------------------------------------------------------*/
    NVIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* TIM1 configuration ------------------------------------------------------*/
    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 0x8FF; // 0xFF;
    TIM_TimeBaseStructure.Prescaler = 0x4;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);
    /* TIM1 channel1 configuration in PWM mode */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 0x7F;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_LOW;
    TIM_InitOc1(TIM1, &TIM_OCInitStructure);
    TIM_InitOc2(TIM1, &TIM_OCInitStructure);
    TIM_InitOc4(TIM1, &TIM_OCInitStructure);

    /* DMA Channel1 Configuration ----------------------------------------------*/
    DMA_DeInit(DMA_CH1);
    DMA_InitStructure.PeriphAddr     = (uint32_t)&ADC->DAT;
    DMA_InitStructure.MemAddr        = (uint32_t)ADC_RegularConvertedValueTab;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = 32;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA_CH1, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_ADC1, DMA, DMA_CH1, ENABLE);
    /* Enable DMA channel1 */
    DMA_EnableChannel(DMA_CH1, ENABLE);
    ADC_DeInit(ADC);
    /* ADC configuration ------------------------------------------------------*/
    ADC_InitStructure.MultiChEn      = DISABLE;
    ADC_InitStructure.ContinueConvEn = DISABLE;
    ADC_InitStructure.ExtTrigSelect  = ADC_EXT_TRIGCONV_T1_CC2;
    ADC_InitStructure.DatAlign       = ADC_DAT_ALIGN_R;
    ADC_InitStructure.ChsNumber      = 1;
    ADC_Init(ADC, &ADC_InitStructure);

    /* Set injected sequencer length */
    ADC_ConfigInjectedSequencerLength(ADC, 1);
    /* ADC injected channel Configuration */
    ADC_ConfigInjectedChannel(ADC, ADC_CH_14_PC3, 1, ADC_SAMP_TIME_71CYCLES5);
    /* ADC injected external trigger configuration */
    ADC_ConfigExternalTrigInjectedConv(ADC, ADC_EXT_TRIG_INJ_CONV_NONE);
    /* Enable automatic injected conversion start after regular one */
    ADC_EnableAutoInjectedConv(ADC, ENABLE);
    /* Enable JEOC interrupt */
    ADC_ConfigInt(ADC, ADC_INT_JENDC, ENABLE);

    /* ADC regular channel configuration */
    ADC_ConfigRegularChannel(ADC, ADC_CH_13_PC2, 1, ADC_SAMP_TIME_13CYCLES5);
    /* Enable ADC DMA */
    ADC_EnableDMA(ADC, ENABLE);
    /* Enable ADC external trigger */
    ADC_EnableExternalTrigConv(ADC, ENABLE);

    /* Enable ADC */
    ADC_Enable(ADC, ENABLE);
    /* Check ADC Ready */
    while(ADC_GetFlagStatusNew(ADC,ADC_FLAG_RDY) == RESET)
        ;
    /* Start ADC calibration */
    ADC_StartCalibration(ADC);
    /* Check the end of ADC calibration */
    while (ADC_GetCalibrationStatus(ADC))
        ;

    /* TIM1 counter enable */
    TIM_Enable(TIM1, ENABLE);
    /* TIM1 main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);

#if 0
    /* Test on channel1 transfer complete flag */
    while(!DMA_GetFlagStatus(DMA_FLAG_TC1,DMA));
    /* Clear channel1 transfer complete flag */
    DMA_ClearFlag(DMA_FLAG_TC1,DMA);
    /* TIM1 counter disable */
    TIM_Enable(TIM1, DISABLE);
#endif

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable peripheral clocks ------------------------------------------------*/
    /* Enable TIM1 clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
    /* Enable DMA clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);

    /* Enable GPIOC clocks */
    RCC_EnableAPB2PeriphClk(
        RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC, ENABLE);
    /* Enable ADC clocks */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_ADC ,ENABLE);

    /* RCC_ADCHCLK_DIV16*/
    ADC_ConfigClk(ADC_CTRL3_CKMOD_AHB, RCC_ADCHCLK_DIV16);
    RCC_ConfigAdc1mClk(RCC_ADC1MCLK_SRC_HSE, RCC_ADC1MCLK_DIV8);  //selsect HSE as RCC ADC1M CLK Source
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure TIM1_CH1 (PA8),CH4(PA11) as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8 | GPIO_PIN_11;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Configure PC.06 as output push-pull */
    GPIO_InitStructure.Pin       = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);

    /* Configure PC.02 and PC.03 as analog input */
    GPIO_InitStructure.Pin       = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  Configures NVIC and Vector Table base location.
 */
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Configure and enable ADC interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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

    /* Infinite loop */
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

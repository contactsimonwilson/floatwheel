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

/** @addtogroup TIM_Input_Capture
 * @{
 */

TIM_ICInitType TIM_ICInitStructure;
uint16_t gOnePulsEn = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void GenTwoRisingEdge(void);

/**
 * @brief  Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* NVIC configuration */
    NVIC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* TIM3 configuration: Input Capture mode ---------------------
     The external signal is connected to TIM3 CH2 pin (PA.07) ,Rising edge
     The external signal is connected to TIM3 CH1 pin (PA.07) ,Falling edge
     The TIM3 CCDAT1+CCDAT2 is used to compute the frequency value

    gOnePulsEn = 1,will do GenTwoRisingEdge
    then
    see Capture that is dist time
    ------------------------------------------------------------ */
    TIM_InitIcStruct(&TIM_ICInitStructure);
    TIM_ICInitStructure.Channel     = TIM_CH_2;
    TIM_ICInitStructure.IcPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.IcSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.IcPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStructure.IcFilter    = 0x0;

    TIM_ICInit(TIM3, &TIM_ICInitStructure);
    
    TIM_ICInitStructure.Channel     = TIM_CH_1;
    TIM_ICInitStructure.IcPolarity  = TIM_IC_POLARITY_FALLING;
    TIM_ICInitStructure.IcSelection = TIM_IC_SELECTION_INDIRECTTI;
    TIM_ICInitStructure.IcPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStructure.IcFilter    = 0x0;

    TIM_ICInit(TIM3, &TIM_ICInitStructure);

    /* TIM enable counter */
    TIM_Enable(TIM3, ENABLE);

    /* Enable the CC2 Interrupt Request */
    TIM_ConfigInt(TIM3, TIM_INT_CC1 | TIM_INT_CC2, ENABLE);

    while (1)
    {
        GenTwoRisingEdge();
    }
}

// generation two rising edge
void GenTwoRisingEdge(void)
{
    if (gOnePulsEn)
    {
        gOnePulsEn = 0;
        GPIO_SetBits(GPIOA, GPIO_PIN_3);
        {
            uint32_t i = 0;
            while (i++ < 50)
                ;
        }
        GPIO_ResetBits(GPIOA, GPIO_PIN_3);
        {
            uint32_t i = 0;
            while (i++ < 50)
                ;
        }

        GPIO_SetBits(GPIOA, GPIO_PIN_3);
        {
            uint32_t i = 0;
            while (i++ < 50)
                ;
        }
        GPIO_ResetBits(GPIOA, GPIO_PIN_3);
        {
            uint32_t i = 0;
            while (i++ < 50)
                ;
        }
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
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOB, ENABLE);
}

/**
 * @brief  Configure the GPIOD Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* TIM3 channel 2 pin (PA.07) configuration */
    GPIO_InitStructure.Pin        = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;///GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    // PA3
    GPIO_InitStructure.Pin       = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  Configure the nested vectored interrupt controller.
 */
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Enable the TIM3 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
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

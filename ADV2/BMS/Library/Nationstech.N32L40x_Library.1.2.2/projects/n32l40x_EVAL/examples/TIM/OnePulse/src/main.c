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

/** @addtogroup TIM_OnePulse
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
TIM_ICInitType TIM_ICInitStructure;
OCInitType TIM_OCInitStructure;
uint16_t PrescalerValue = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void SendOneTrig(void);
uint16_t gSendTrigEn = 0;

/**
 * @brief  Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* Compute the prescaler value */
    PrescalerValue = (uint16_t)(SystemCoreClock / 24000000) - 1;
    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Period    = 65535;
    TIM_TimeBaseStructure.Prescaler = PrescalerValue;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

    /* TIM4 PWM2 Mode configuration: Channel1 */
    TIM_InitOcStruct(&TIM_OCInitStructure);    
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 16383;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM4, &TIM_OCInitStructure);

    /* TIM4 configuration in Input Capture Mode */

    TIM_InitIcStruct(&TIM_ICInitStructure);

    TIM_ICInitStructure.Channel     = TIM_CH_2;
    TIM_ICInitStructure.IcPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.IcSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.IcPrescaler = TIM_IC_PSC_DIV1;
    TIM_ICInitStructure.IcFilter    = 0;

    TIM_ICInit(TIM4, &TIM_ICInitStructure);

    /* One Pulse Mode selection */
    TIM_SelectOnePulseMode(TIM4, TIM_OPMODE_SINGLE);

    /* Input Trigger selection */
    TIM_SelectInputTrig(TIM4, TIM_TRIG_SEL_TI2FP2);

    /* Slave Mode selection: Trigger Mode */
    TIM_SelectSlaveMode(TIM4, TIM_SLAVE_MODE_TRIG);

    while (1)
    {
        SendOneTrig();
    }
}

/**
 * @brief  Send one trig byself.
 */
void SendOneTrig(void)
{
    if (gSendTrigEn)
    {
        gSendTrigEn = 0;
        GPIO_SetBits(GPIOA, GPIO_PIN_3);
        {
            volatile uint32_t i=0;
            while (i++ < 50)
                ;
        }
        GPIO_ResetBits(GPIOA, GPIO_PIN_3);
    }
}
/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* TIM4 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);

    /* GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOA, ENABLE);
}

/**
 * @brief  Configure the GPIOD Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    
    /* TIM4_CH1 pin (PB.06) configuration as out*/
    GPIO_InitStructure.Pin        = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM4;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;

    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    /* TIM4_CH2 pin (PB.07) configuration as trig*/
    GPIO_InitStructure.Pin       = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input; 
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    /* TIM4_CH2 pin (PA.03) configuration as send trig*/
    GPIO_InitStructure.Pin       = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
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

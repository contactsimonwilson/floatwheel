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

/** @addtogroup TIM_Cascade_Synchro
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;

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

    /* Timers synchronisation in cascade mode ----------------------------
     1/TIM2 is configured as Master Timer:
     - PWM Mode is used
     - The TIM2 Update event is used as Trigger Output

     2/TIM3 is slave for TIM2 and Master for TIM4,
     - PWM Mode is used
     - The ITR1(TIM2) is used as input trigger
     - Gated mode is used, so start and stop of slave counter
      are controlled by the Master trigger output signal(TIM2 update event).
      - The TIM3 Update event is used as Trigger Output.

      3/TIM4 is slave for TIM3,
     - PWM Mode is used
     - The ITR2(TIM3) is used as input trigger
     - Gated mode is used, so start and stop of slave counter
      are controlled by the Master trigger output signal(TIM3 update event).

     * For Low-density, Medium-density, High-density and Connectivity line devices:
       The TIMxCLK is fixed to 64 MHz, the TIM2 counter clock is 64 MHz.

       The Master Timer TIM2 is running at TIM2 frequency :
       TIM2 frequency = (TIM2 counter clock)/ (TIM2 period + 1) = 250 KHz
       and the duty cycle = TIM2_CCR1/(TIM2_ARR + 1) = 25%.

       The TIM3 is running:
       - At (TIM2 frequency)/ (TIM3 period + 1) = 62.5 KHz and a duty cycle
         equal to TIM3_CCR1/(TIM3_ARR + 1) = 25%

        The TIM4 is running:
      - At (TIM3 frequency)/ (TIM4 period + 1) = 15.625 KHz and a duty cycle
        equal to TIM4_CCR1/(TIM4_ARR + 1) = 25%

    -------------------------------------------------------------------- */

    /* Time base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Period    = 255;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.Period = 3;
    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

    TIM_TimeBaseStructure.Period = 3;
    TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

    /* Master Configuration in PWM1 Mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);    
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 64;
    TIM_OCInitStructure.OcPolarity  = TIM_OC_POLARITY_HIGH;

    TIM_InitOc1(TIM2, &TIM_OCInitStructure);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM2, TIM_MASTER_SLAVE_MODE_ENABLE);

    /* Master Mode selection */
    TIM_SelectOutputTrig(TIM2, TIM_TRGO_SRC_UPDATE);

    /* Slaves Configuration: PWM1 Mode */
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 1;

    TIM_InitOc1(TIM3, &TIM_OCInitStructure);

    TIM_InitOc1(TIM4, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM3 */
    TIM_SelectSlaveMode(TIM3, TIM_SLAVE_MODE_GATED);
    TIM_SelectInputTrig(TIM3, TIM_TRIG_SEL_IN_TR1);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM3, TIM_MASTER_SLAVE_MODE_ENABLE);

    /* Master Mode selection: TIM3 */
    TIM_SelectOutputTrig(TIM3, TIM_TRGO_SRC_UPDATE);

    /* Slave Mode selection: TIM4 */
    TIM_SelectSlaveMode(TIM4, TIM_SLAVE_MODE_GATED);
    TIM_SelectInputTrig(TIM4, TIM_TRIG_SEL_IN_TR2);

    /* TIM enable counter */
    TIM_Enable(TIM3, ENABLE); 
    TIM_Enable(TIM4, ENABLE);
    TIM_Enable(TIM2, ENABLE);
    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* TIM2, TIM3 and TIM4 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2 | RCC_APB1_PERIPH_TIM3 | RCC_APB1_PERIPH_TIM4, ENABLE);

    /* GPIOA, GPIOB, GPIOC and AFIO clocks enable */
    RCC_EnableAPB2PeriphClk(
        RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_AFIO, ENABLE);
}

/**
 * @brief  Configure the GPIOD Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOA Configuration: PA0(TIM2 CH1) as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM2;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* GPIOA Configuration: PA6(TIM3 CH1) as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_6;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: PB6(TIM4 CH1) as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_6;
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

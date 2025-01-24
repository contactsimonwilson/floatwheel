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

/** @addtogroup TIM_TIM1_Synchro
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
TIM_BDTRInitType TIM_BDTRInitStructure;

void RCC_Configuration(void);
void GPIO_Configuration(void);

/**
 * @brief   Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* TIM1 and Timers(TIM3 and TIM4) synchronisation in parallel mode -----------
     1/TIM1 is configured as Master Timer:
     - PWM Mode is used
     - The TIM1 Update event is used as Trigger Output

     2/TIM3 and TIM4 are slaves for TIM1,
     - PWM Mode is used
     - The ITR0(TIM1) is used as input trigger for both slaves
     - Gated mode is used, so starts and stops of slaves counters
       are controlled by the Master trigger output signal(update event).

    The TIMxCLK is fixed to 64 MHz, Prescaler = 0 so the TIM1 counter clock is 64 MHz.

    The Master Timer TIM1 is running at:
    TIM1 frequency = TIM1 counter clock / (TIM1_Period + 1) = 250 KHz
    and the duty cycle is equal to: TIM1_CCR1/(TIM1_ARR + 1) = 50%

    The TIM3 is running at:
    (TIM1 frequency)/ ((TIM3 period +1)* (Repetition_Counter+1)) = 16.667 KHz and
    a duty cycle equal to TIM3_CCR1/(TIM3_ARR + 1) = 33.3%

    The TIM4 is running at:
    (TIM1 frequency)/ ((TIM4 period +1)* (Repetition_Counter+1)) = 25 KHz and
    a duty cycle equal to TIM4_CCR1/(TIM4_ARR + 1) = 50%

    --------------------------------------------------------------------------- */

    /* TIM3 Peripheral Configuration ----------------------------------------*/
    /* TIM3 Slave Configuration: PWM1 Mode */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Period    = 2;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM3, &TIM_TimeBaseStructure);

    TIM_InitOcStruct(&TIM_OCInitStructure);
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 1;

    TIM_InitOc1(TIM3, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM3 */
    TIM_SelectSlaveMode(TIM3, TIM_SLAVE_MODE_GATED);
    TIM_SelectInputTrig(TIM3, TIM_TRIG_SEL_IN_TR0);

    /* TIM4 Peripheral Configuration ----------------------------------------*/
    /* TIM4 Slave Configuration: PWM1 Mode */
    TIM_TimeBaseStructure.Period    = 1;
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;

    TIM_InitTimeBase(TIM4, &TIM_TimeBaseStructure);

    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 1;

    TIM_InitOc1(TIM4, &TIM_OCInitStructure);

    /* Slave Mode selection: TIM4 */
    TIM_SelectSlaveMode(TIM4, TIM_SLAVE_MODE_GATED);
    TIM_SelectInputTrig(TIM4, TIM_TRIG_SEL_IN_TR0);

    /* TIM1 Peripheral Configuration ----------------------------------------*/
    /* Time Base configuration */
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period    = 255;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.RepetCnt  = 4;

    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    /* Channel 1 Configuration in PWM mode */
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = 127;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OcNPolarity  = TIM_OCN_POLARITY_LOW;
    TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;

    TIM_InitOc1(TIM1, &TIM_OCInitStructure);

    /* Automatic Output enable, Break, dead time and lock configuration*/
    TIM_InitBkdtStruct(&TIM_BDTRInitStructure);
    TIM_BDTRInitStructure.OssrState       = TIM_OSSR_STATE_ENABLE;
    TIM_BDTRInitStructure.OssiState       = TIM_OSSI_STATE_ENABLE;
    TIM_BDTRInitStructure.LockLevel       = TIM_LOCK_LEVEL_1;
    TIM_BDTRInitStructure.DeadTime        = 5;
    TIM_BDTRInitStructure.Break           = TIM_BREAK_IN_DISABLE;
    TIM_BDTRInitStructure.BreakPolarity   = TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStructure.AutomaticOutput = TIM_AUTO_OUTPUT_DISABLE;

    TIM_ConfigBkdt(TIM1, &TIM_BDTRInitStructure);

    /* Master Mode selection */
    TIM_SelectOutputTrig(TIM1, TIM_TRGO_SRC_UPDATE);

    /* Select the Master Slave Mode */
    TIM_SelectMasterSlaveMode(TIM1, TIM_MASTER_SLAVE_MODE_ENABLE);

    /* TIM1 counter enable */
    TIM_Enable(TIM1, ENABLE);

    /* TIM enable counter */
    TIM_Enable(TIM3, ENABLE);
    TIM_Enable(TIM4, ENABLE);

    /* Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* TIM1, GPIOA and GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOC
                                | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO,
                            ENABLE);

    /* TIM3 and TIM4 clock enable */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3 | RCC_APB1_PERIPH_TIM4, ENABLE);
}

/**
 * @brief  Configures TIM1, TIM3 and TIM4 Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    
	  GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOA Configuration: TIM1 Channel1 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
	  GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: TIM3 Channel1 as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_6;
	  GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM3;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: TIM4 Channel1 as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_6;
	  GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM4;
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

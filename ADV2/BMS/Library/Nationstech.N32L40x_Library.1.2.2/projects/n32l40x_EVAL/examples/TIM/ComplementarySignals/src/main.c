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

/** @addtogroup TIM_ComplementarySignals
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
TIM_BDTRInitType TIM_BDTRInitStructure;
uint16_t TimerPeriod   = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0;

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

    /* -----------------------------------------------------------------------
    TIM1 Configuration to:

    1/ Generate 3 complementary PWM signals with 3 different duty cycles:
    TIM1CLK is fixed to SystemCoreClock, the TIM1 Prescaler is equal to 0 so the
    TIM1 counter clock used is SystemCoreClock.
    * SystemCoreClock is set to 64 MHz

    The objective is to generate PWM signal at 17.57 KHz:
    - TIM1_Period = (SystemCoreClock / 17570) - 1

    The Three Duty cycles are computed as the following description:

    The channel 1 duty cycle is set to 50% so channel 1N is set to 50%.
    The channel 2 duty cycle is set to 25% so channel 2N is set to 75%.
    The channel 3 duty cycle is set to 12.5% so channel 3N is set to 87.5%.
    The Timer pulse is calculated as follows:
      - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100

    2/ Insert a dead time equal to 11/SystemCoreClock ns
    3/ Configure the break feature, active at High level, and using the automatic
     output enable feature
    4/ Use the Locking parameters level1.
    ----------------------------------------------------------------------- */

    /* Compute the value to be set in AR register to generate signal frequency at 17.57 Khz */
    TimerPeriod = (SystemCoreClock / 17570) - 1;
    /* Compute CCDAT1 value to generate a duty cycle at 50% for channel 1 */
    Channel1Pulse = (uint16_t)(((uint32_t)5 * (TimerPeriod - 1)) / 10);
    /* Compute CCDAT2 value to generate a duty cycle at 25%  for channel 2 */
    Channel2Pulse = (uint16_t)(((uint32_t)25 * (TimerPeriod - 1)) / 100);
    /* Compute CCDAT3 value to generate a duty cycle at 12.5%  for channel 3 */
    Channel3Pulse = (uint16_t)(((uint32_t)125 * (TimerPeriod - 1)) / 1000);

    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period    = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.RepetCnt  = 0;

    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    /* Channel 1, 2 and 3 Configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);    
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = Channel1Pulse;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OcNPolarity  = TIM_OCN_POLARITY_LOW;
    TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;

    TIM_InitOc1(TIM1, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel2Pulse;
    TIM_InitOc2(TIM1, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel3Pulse;
    TIM_InitOc3(TIM1, &TIM_OCInitStructure);

    /* Automatic Output enable, Break, dead time and lock configuration*/
    TIM_InitBkdtStruct(&TIM_BDTRInitStructure);
    TIM_BDTRInitStructure.OssrState       = TIM_OSSR_STATE_ENABLE;
    TIM_BDTRInitStructure.OssiState       = TIM_OSSI_STATE_ENABLE;
    TIM_BDTRInitStructure.LockLevel       = TIM_LOCK_LEVEL_1;
    TIM_BDTRInitStructure.DeadTime        = 11;
    TIM_BDTRInitStructure.Break           = TIM_BREAK_IN_ENABLE;
    TIM_BDTRInitStructure.BreakPolarity   = TIM_BREAK_POLARITY_HIGH;
    TIM_BDTRInitStructure.AutomaticOutput = TIM_AUTO_OUTPUT_ENABLE;
    TIM_BDTRInitStructure.IomBreakEn      = true;

    TIM_ConfigBkdt(TIM1, &TIM_BDTRInitStructure);

    /* TIM1 counter enable */
    TIM_Enable(TIM1, ENABLE);

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
    /* TIM1, GPIOA, GPIOB, GPIOE and AFIO clocks enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB
                                | RCC_APB2_PERIPH_AFIO,
                            ENABLE);
}

/**
 * @brief  Configure the TIM1 Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOA Configuration: Channel 1, 2 and 3 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    /* GPIOB Configuration: BKIN pin */
    GPIO_InitStructure.Pin       = GPIO_PIN_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Down;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF5_TIM1;  //GPIO_NO_AF; //
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

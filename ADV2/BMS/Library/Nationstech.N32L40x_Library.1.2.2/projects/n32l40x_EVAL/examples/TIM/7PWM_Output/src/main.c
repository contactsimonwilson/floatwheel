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

/** @addtogroup TIM_7PWM_Output
 * @{
 */

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
uint16_t TimerPeriod   = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void WritePuls(void);
#define CC4_GPIO 0

/**
 * @brief   intial timx program
 */
void TIM_Initial(TIM_Module* TIMx)
{
    /* TIMx Configuration ---------------------------------------------------
    Generate 7 PWM signals with 4 different duty cycles:
    TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
    SystemCoreClock is set to 64MHz

    The objective is to generate 7 PWM signal at 17.57 KHz:
     - TIMx_Period = (SystemCoreClock / 17570) - 1
    The channel 1 and channel 1N duty cycle is set to 50%
    The channel 2 and channel 2N duty cycle is set to 37.5%
    The channel 3 and channel 3N duty cycle is set to 25%
    The channel 4 duty cycle is set to 12.5%
    The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
    ----------------------------------------------------------------------- */
    /* Compute the value to be set in AR regiter to generate signal frequency at 17.57 Khz */
    TimerPeriod = (SystemCoreClock / 17570 ) - 1;
    /* Compute CCDAT1 value to generate a duty cycle at 50% for channel 1 and 1N */
    Channel1Pulse = (uint16_t)(((uint32_t)5 * (TimerPeriod - 1)) / 10);  //24.5
    /* Compute CCDAT2 value to generate a duty cycle at 37.5%  for channel 2 and 2N */
    Channel2Pulse = (uint16_t)(((uint32_t)375 * (TimerPeriod - 1)) / 1000); //18
    /* Compute CCDAT3 value to generate a duty cycle at 25%  for channel 3 and 3N */
    Channel3Pulse = (uint16_t)(((uint32_t)25 * (TimerPeriod - 1)) / 100); //12
    /* Compute CCDAT4 value to generate a duty cycle at 12.5%  for channel 4 */
    Channel4Pulse = (uint16_t)(((uint32_t)125 * (TimerPeriod - 1)) / 1000); //6

    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period    = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.RepetCnt  = 0;

    TIM_InitTimeBase(TIMx, &TIM_TimeBaseStructure);

    /* Channel 1, 2,3 and 4 Configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);    
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = Channel1Pulse;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_HIGH;
    TIM_OCInitStructure.OcNPolarity  = TIM_OCN_POLARITY_HIGH;
    TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;
    TIM_InitOc1(TIMx, &TIM_OCInitStructure);

    TIM_OCInitStructure.Pulse = Channel3Pulse;
    TIM_InitOc3(TIMx, &TIM_OCInitStructure);
    TIM_OCInitStructure.Pulse = Channel4Pulse;
    TIM_InitOc4(TIMx, &TIM_OCInitStructure);

    // TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_DISABLE;
    TIM_OCInitStructure.Pulse = Channel2Pulse;
    TIM_InitOc2(TIMx, &TIM_OCInitStructure);

    /* TIM1 counter enable */
    TIM_Enable(TIMx, ENABLE);

    /* TIM1 Main Output Enable */
    TIM_EnableCtrlPwmOutputs(TIMx, ENABLE);
}
/**
 * @brief   Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    TIM_Initial(TIM1);//IntialTimx(TIM1);
    TIM_Initial(TIM8);//IntialTimx(TIM8);
    while (1)
    {
#if CC4_GPIO
        WritePuls();
#endif
    }
}

void WritePuls(void)
{
    GPIO_SetBits(GPIOA, GPIO_PIN_11);
    {
        int i = 0;
        while (i++ < 100)
            ;
    }
    GPIO_ResetBits(GPIOA, GPIO_PIN_11);
    {
        int i = 0;
        while (i++ < 100)
            ;
    }
}
/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* TIM1,TIM8, GPIOA, GPIOB, GPIOC GPIOD and AFIO clocks enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC | RCC_APB2_PERIPH_TIM1
                                | RCC_APB2_PERIPH_TIM8 | RCC_APB2_PERIPH_GPIOD | RCC_APB2_PERIPH_AFIO,
                            ENABLE);
    //When debug ,TIM1 and TIM8 stop
    DBG_ConfigPeriph(DBG_TIM1_STOP | DBG_TIM8_STOP , ENABLE);
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
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: Channel 1N, 2N and 3N as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_11;
#if CC4_GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
#endif
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    // TIM8 CHx:PC6,PC7,PC8,PC9     CHxN:PA7,PB0,PB1
    GPIO_InitStructure.Pin = GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF6_TIM8;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.Pin = GPIO_PIN_7;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.Pin = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF7_TIM8;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_TIM8;
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

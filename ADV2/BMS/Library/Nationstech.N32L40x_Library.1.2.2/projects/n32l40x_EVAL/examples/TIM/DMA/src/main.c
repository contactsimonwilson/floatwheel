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

/** @addtogroup TIM_DMA
 * @{
 */

#define TIM1_CCR3_Address 0x40012C3C

TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
uint16_t SRC_Buffer[3] = {0, 0, 0};
uint16_t TimerPeriod   = 0;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void DMA_Configuration(void);

/**
 * @brief  Main program
 */
int main(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* DMA Configuration */
    DMA_Configuration();

    /* TIM1 DMA Transfer example -------------------------------------------------
    TIM1CLK = SystemCoreClock, Prescaler = 0, TIM1 counter clock = SystemCoreClock
    SystemCoreClock is set to 64 MHz.

    The objective is to configure TIM1 channel 3 to generate complementary PWM
    signal with a frequency equal to 17.57 KHz:
     - TIM1_Period = (SystemCoreClock / 17570) - 1
    and a variable duty cycle that is changed by the DMA after a specific number of
    Update DMA request.

    The number of this repetitive requests is defined by the TIM1 Repetition counter,
    each 3 Update Requests, the TIM1 Channel 3 Duty Cycle changes to the next new
    value defined by the SRC_Buffer .
    -----------------------------------------------------------------------------*/
    /* Compute the value to be set in AR register to generate signal frequency at 17.57 Khz */
    TimerPeriod = (SystemCoreClock / 17570) - 1;
    /* Compute CCDAT1 value to generate a duty cycle at 50% */
    SRC_Buffer[0] = (uint16_t)(((uint32_t)5 * (TimerPeriod - 1)) / 10);
    /* Compute CCDAT1 value to generate a duty cycle at 37.5% */
    SRC_Buffer[1] = (uint16_t)(((uint32_t)375 * (TimerPeriod - 1)) / 1000);
    /* Compute CCDAT1 value to generate a duty cycle at 25% */
    SRC_Buffer[2] = (uint16_t)(((uint32_t)25 * (TimerPeriod - 1)) / 100);

    /* TIM1 Peripheral Configuration --------------------------------------------*/
    /* Time Base configuration */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Prescaler = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_TimeBaseStructure.Period    = TimerPeriod;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.RepetCnt  = 5;

    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    /* Channel 3 Configuration in PWM mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);    
    TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_ENABLE;
    TIM_OCInitStructure.Pulse        = SRC_Buffer[0];
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OcNPolarity  = TIM_OCN_POLARITY_LOW;
    TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;

    TIM_InitOc3(TIM1, &TIM_OCInitStructure);

    /* TIM1 Update DMA Request enable */
    TIM_EnableDma(TIM1, TIM_DMA_UPDATE, ENABLE);

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
    /* TIM1, GPIOA and GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB, ENABLE);
    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);
}

/**
 * @brief  Configure the TIM1 Pins.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOA Configuration: Channel 3 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* GPIOB Configuration: Channel 3N as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_15;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  Configures the DMA.
 */
void DMA_Configuration(void)
{
    DMA_InitType DMA_InitStructure;

    /* DMA Channel5 Config */
    DMA_DeInit(DMA_CH5);

    DMA_InitStructure.PeriphAddr     = (uint32_t)&TIM1->CCDAT3;  //TIM1_CCR3_Address;
    DMA_InitStructure.MemAddr        = (uint32_t)SRC_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = 3;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.CircularMode   = DMA_MODE_CIRCULAR;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    
    DMA_Init(DMA_CH5, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_TIM1_UP,DMA,DMA_CH5,ENABLE); 
    /* DMA Channel5 enable */
    DMA_EnableChannel(DMA_CH5, ENABLE);
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

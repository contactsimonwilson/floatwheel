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

/** @addtogroup TIM_DMABurst
 * @{
 */

#define TIM1_DMAR_ADDRESS ((uint32_t)0x40012C4C) /* TIMx_DADDR address */

GPIO_InitType GPIO_InitStructure;
DMA_InitType DMA_InitStructure;
TIM_TimeBaseInitType TIM_TimeBaseStructure;
OCInitType TIM_OCInitStructure;
uint16_t SRC_Buffer[6] = {0x0FFF, 0x0000, 0x0555};
uint16_t DmaAgain      = 0;

/**
 * @brief  Main program
 */
int main(void)
{
    /* TIM1 and GPIOA clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1 | RCC_APB2_PERIPH_GPIOA, ENABLE);

    /* DMA clock enable */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* GPIOA Configuration: Channel 1 as alternate function push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* TIM1 DeInit */
    TIM_DeInit(TIM1);

    /* DMA Channel5 Config */
    DMA_DeInit(DMA_CH5);

    DMA_InitStructure.PeriphAddr     = (uint32_t)&TIM1->DADDR;   //TIM1_DMAR_ADDRESS;
    DMA_InitStructure.MemAddr        = (uint32_t)SRC_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_DST;
    DMA_InitStructure.BufSize        = 3;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_DISABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_HALFWORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_DISABLE;
    DMA_Init(DMA_CH5, &DMA_InitStructure);
    DMA_RequestRemap(DMA_REMAP_TIM1_UP,DMA,DMA_CH5,ENABLE);

    /* Time base configuration */
    /* -----------------------------------------------------------------------
    TIM1 Configuration: generate 1 PWM signal using the DMA burst mode:
    The TIM1CLK frequency is set to SystemCoreClock (Hz), to get TIM1 counter
    clock at 24 MHz the Prescaler is computed as following:
     - Prescaler = (TIM1CLK / TIM1 counter clock) - 1
    SystemCoreClock is set to 64 MHz

    The TIM1 period is 5.8 KHz: TIM1 Frequency = TIM1 counter clock/(AR + 1)
                                               = 24 MHz / 4096 = 5.8KHz KHz
    TIM1 Channel1 duty cycle = (TIM1_CCR1/ TIM1_ARR)* 100 = 33.33%
    ----------------------------------------------------------------------- */
    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);    
    TIM_TimeBaseStructure.Period    = 0xFFFF;
    TIM_TimeBaseStructure.Prescaler = (uint16_t)(SystemCoreClock / 24000000) - 1;
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);

    /* TIM Configuration in PWM Mode */
    TIM_InitOcStruct(&TIM_OCInitStructure);    
    TIM_OCInitStructure.OcMode      = TIM_OCMODE_PWM1;
    TIM_OCInitStructure.OutputState = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.Pulse       = 0xFFF;
    TIM_InitOc1(TIM1, &TIM_OCInitStructure);

    /* TIM1 DADDR Base register and DMA Burst Length Config */
    TIM_ConfigDma(TIM1, TIM_DMABASE_AR, TIM_DMABURST_LENGTH_3TRANSFERS);

    /* TIM1 DMA Update enable */
    TIM_EnableDma(TIM1, TIM_DMA_UPDATE, ENABLE);

    /* TIM1 enable */
    TIM_Enable(TIM1, ENABLE);

    /* TIM1 PWM Outputs Enable */
    TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);

    /* DMA Channel5 enable */
    DMA_EnableChannel(DMA_CH5, ENABLE);

    /* Wait until DMA Channel5 end of Transfer */
    while (!DMA_GetFlagStatus(DMA_FLAG_TC5, DMA))
    {
    }

    DMA_ClearFlag(DMA_FLAG_GL5 | DMA_FLAG_TC5 | DMA_FLAG_HT5 | DMA_FLAG_TE5, DMA);
    /* Infinite loop */
    while (1)
    {
        if (DmaAgain)
        {
            DmaAgain = 0;

            DMA_DeInit(DMA_CH5);
            DMA_Init(DMA_CH5, &DMA_InitStructure);

            TIM_ConfigDma(TIM1, TIM_DMABASE_AR, TIM_DMABURST_LENGTH_3TRANSFERS);
            TIM_EnableDma(TIM1, TIM_DMA_UPDATE, ENABLE);

            /* DMA Channel5 enable */
            DMA_EnableChannel(DMA_CH5, ENABLE);

            /* Wait until DMA Channel5 end of Transfer */
            while (!DMA_GetFlagStatus(DMA_FLAG_TC5, DMA))
            {
            }

            DMA_ClearFlag(DMA_FLAG_GL5 | DMA_FLAG_TC5 | DMA_FLAG_HT5 | DMA_FLAG_TE5, DMA);
        }
    }
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

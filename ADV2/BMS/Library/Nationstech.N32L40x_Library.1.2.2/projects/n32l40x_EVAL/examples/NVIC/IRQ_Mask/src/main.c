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
#include <stdio.h>

/**
 *  NVIC IRQ Mask
 */





uint8_t Key_Status = DISABLE;

void TIM_Config(void);
void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin);


/**
 * @brief  Main program.
 */
int main(void)
{
    /* log Init */
    log_init();
    log_info("NVIC IRQ Mask \r\n");

    KeyInputExtiInit(KEY_INPUT_PORT, KEY_INPUT_PIN);
    /* TIM configuration -------------------------------------------------------*/
    TIM_Config();

    while (1)
    {
        while (Key_Status == DISABLE)
        {
        }
        log_info("Disable irq \r\n");
        /* This instruction raises the execution priority to 0. This prevents all
           exceptions with configurable priority from activating, other than through
           the HardFault fault escalation mechanism. */
        __disable_irq();

        while (GPIO_ReadInputDataBit(KEY_INPUT_PORT, KEY_INPUT_PIN) != SET)
        {
        }
        log_info("enable irq \r\n");
        /* This instruction will allow all exceptions with configurable priority to
           be activated. */
        __enable_irq();
        while (Key_Status == ENABLE)
        {
        }
    }
}

/**
 * @brief  Configures the used Timers.
 */
void TIM_Config(void)
{
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    OCInitType TIM_OCInitStructure;
    NVIC_InitType NVIC_InitStructure;

    /* Enable TIM2 clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);

    /* TIM2 configuration */
    TIM_TimeBaseStructure.Period    = 0x4AF;
    TIM_TimeBaseStructure.Prescaler = ((SystemCoreClock / 1200) - 1);
    TIM_TimeBaseStructure.ClkDiv    = 0x0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
    TIM_InitTimeBase(TIM2, &TIM_TimeBaseStructure);
    TIM_InitOcStruct(&TIM_OCInitStructure);

    /* Output Compare Timing Mode configuration: Channel1 */
    TIM_OCInitStructure.OcMode = TIM_OCMODE_TIMING;
    TIM_OCInitStructure.Pulse  = 0x0;
    TIM_InitOc1(TIM2, &TIM_OCInitStructure);

    /* Immediate load of TIM2 Precaler values */
    TIM_ConfigPrescaler(TIM2, ((SystemCoreClock / 1200) - 1), TIM_PSC_RELOAD_MODE_IMMEDIATE);

    /* Clear TIM2 update pending flags */
    TIM_ClearFlag(TIM2, TIM_FLAG_UPDATE);

    /* Configure two bits for preemption priority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the TIM2 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable TIM2 Update interrupts */
    TIM_ConfigInt(TIM2, TIM_INT_UPDATE, ENABLE);

    /* TIM2 enable counters */
    TIM_Enable(TIM2, ENABLE);
}

/**
 * @brief  Configures key port.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    GPIO_InitStruct(&GPIO_InitStructure);
    
    /* Enable the GPIO Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);

    /*Configure the GPIO pin as input floating*/
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);

    /*Configure key EXTI Line to key input Pin*/
    GPIO_ConfigEXTILine(KEY_INPUT_PORT_SOURCE, KEY_INPUT_PIN_SOURCE);

    /*Configure key EXTI line*/
    EXTI_InitStructure.EXTI_Line    = KEY_INPUT_EXTI_LINE;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /*Set key input interrupt priority*/
    NVIC_InitStructure.NVIC_IRQChannel                   = KEY_INPUT_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
/**
 * @}
 */

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
*          line: assert_param error line source number
 * @return None
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {}
}

/**
 * @}
 */
#endif

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
 * @file bsp_led.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

#include "bsp_led.h"

/**
 * @brief  Initailise the IO of LED
 */
void LED_GPIO_Config(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure LED1_GPIO_PIN as Out_PP */
    GPIO_InitStructure.Pin        = LED1_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(LED1_GPIO_PORT, &GPIO_InitStructure);

    /* Configure LED2_GPIO_PIN as Out_PP */
    GPIO_InitStructure.Pin = LED2_GPIO_PIN;
    GPIO_InitPeripheral(LED2_GPIO_PORT, &GPIO_InitStructure);

    /* Configure LED3_GPIO_PIN as Out_PP */
    GPIO_InitStructure.Pin = LED3_GPIO_PIN;
    GPIO_InitPeripheral(LED3_GPIO_PORT, &GPIO_InitStructure);

    /* close the all LED */
    GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
    GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
    GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
}

// void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
// {
//     LED1_RED_ON;
// }

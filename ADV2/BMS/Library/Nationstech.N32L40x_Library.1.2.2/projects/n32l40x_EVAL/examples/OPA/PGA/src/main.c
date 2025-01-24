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

/** @addtogroup OPAMP_PGA
 * @{
 */

ADC_InitType ADC_InitStructure;
DMA_InitType DMA_InitStructure;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void OPAMP_Configuration(void);
void NVIC_Configuration(void);

/**
 * @brief   Main program,Test PGA is work ok? Opa out Pin can view by scope
 */
int main(void)
{
    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* OPAMP configuration ------------------------------------------------------*/
    OPAMP_Configuration();
    while (1)
    {
        ;
    }
}

/**
 * @brief  Configures the Opa.
 */
void OPAMP_Configuration(void)
{
    OPAMP_InitType OPAMP_Initial;
    OPAMP_StructInit(&OPAMP_Initial);
    OPAMP_Initial.Gain = OPAMP_CS_PGA_GAIN_2;
    /*configure opamp1*/
    OPAMP_Init(OPAMP1, &OPAMP_Initial);
    OPAMP_SetVpSel(OPAMP1, OPAMP1_CS_VPSEL_PA1);
    OPAMP_Enable(OPAMP1, ENABLE);
    /*configure opamp2*/
    OPAMP_Init(OPAMP2, &OPAMP_Initial);
    OPAMP_SetVpSel(OPAMP2, OPAMP2_CS_VPSEL_PA7);
    OPAMP_Enable(OPAMP2, ENABLE);
    // OPAMP output pin enable pix pin when OPAMPx En.not to remap or select output pin
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* Enable COMPE clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP | RCC_APB1_PERIPH_OPAMP | RCC_APB1_PERIPH_COMP_FILT, ENABLE);
    /* Enable GPIOA, GPIOB, GPIOC and GPIOD clocks */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_GPIOC
                                | RCC_APB2_PERIPH_GPIOD , ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure OPAMP1_VP, OPAMP2_Vp, 
                 PA1       PA7          as analog inputs */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.Pin       = GPIO_PIN_1 | GPIO_PIN_7;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    // OPAMP output pin enable pix pin when OPAMPx En.not to remap or select output pin
    /* configure OP1_out,  OP2_out, 
                   PA2        PA6       as analog output */
    GPIO_InitStructure.Pin = GPIO_PIN_2 | GPIO_PIN_6;
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

    /* Infinite loop */
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

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
#include <stdint.h>

/**
 * @brief  Inserts a delay time.
 * @param count specifies the delay time length.
 */
void Delay(uint32_t count)
{
    for (; count > 0; count--)
        ;
}
/**
 * @brief  Configures as JTAG function.
 */
void JTAGPortEnableInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO | RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB, ENABLE);
    
    /* Configure PA.13 (JTMS/SWDIO) and PA.15 (JTDI) as alternate output push-pull and pull up*/
    GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SW_JTAG;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Configure PB.04 (JTRST) as alternate output push-pull and pull up */
    GPIO_InitStructure.Pin = GPIO_PIN_4;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    /* Configure  PA.14 (JTCK/SWCLK) as alternate output push-pull and pull down*/
    GPIO_InitStructure.Pin        = GPIO_PIN_14;
    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Down;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Configure PB.03 (JTDO) as alternate output push-pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_3;
    GPIO_InitStructure.GPIO_Pull = GPIO_No_Pull;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

}
/**
 * @brief  Configures JTAG as GPIO.
 */
void JTAGPortDisableInit(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB, ENABLE);
    
    /* Configure PA.13 (JTMS/SWDIO) and PA.15 (JTDI) as gpio */
    GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Pull = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Configure PB.04 (JTRST) as gpio */
    GPIO_InitStructure.Pin = GPIO_PIN_4;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

    /* Configure  PA.14 (JTCK/SWCLK) as gpio */
    GPIO_InitStructure.Pin        = GPIO_PIN_14;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Configure PB.03 (JTDO) as gpio */
    GPIO_InitStructure.Pin        = GPIO_PIN_3;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

}
/**
 * @brief  Configures key GPIO.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void KeyInputInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOD)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        }
    }

    /* Configure the GPIO pin as input floating*/
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin        = Pin;
        GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    }
}
/**
 * @brief  Configures LED GPIO.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOD)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        }
    }

    /* Configure the GPIO pin */
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin        = Pin;
        GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
        GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    }
}
/**
 * @brief  Turns selected Led on as output low level.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}
/**
 * @brief  Turns selected Led Off as output high level.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

/**
 * @brief Assert failed function by user.
 * @param file The name of the call that failed.
 * @param line The source line number of the call that failed.
 */
#ifdef USE_FULL_ASSERT
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    while (1)
    {
    }
}
#endif // USE_FULL_ASSERT

/**
 * @brief  Main program.
 */
int main(void)
{
    /*SystemInit() function has been called by startup file startup_n32l40x.s*/

    /* Initialize Led1~Led2 as output pushpull mode*/
    LedInit(LED1_PORT, LED1_PIN);
    LedInit(LED2_PORT, LED2_PIN);

    KeyInputInit(KEY_INPUT_PORT, KEY_INPUT_PIN);

    while (1)
    {
        if (GPIO_ReadInputDataBit(KEY_INPUT_PORT, KEY_INPUT_PIN) == Bit_RESET)
        {
            /*Turn on Led1*/
            LedOn(LED1_PORT, LED1_PIN);
            /*Turn off Led2*/
            LedOff(LED2_PORT, LED2_PIN);

            /* Disable the JTAG Debug Port SWJ-DP */
            JTAGPortDisableInit();

            while (1)
            {
                /*Toggle JTMS/SWDAT pin*/
                GPIO_WriteBit(GPIOA, GPIO_PIN_13, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_PIN_13)));
                /* Insert delay */
                Delay(0x8FFFF);

                /*Toggle JTCK/SWCLK pin*/
                GPIO_WriteBit(GPIOA, GPIO_PIN_14, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_PIN_14)));
                /* Insert delay */
                Delay(0x8FFFF);

                /* Toggle JTDI pin */
                GPIO_WriteBit(GPIOA, GPIO_PIN_15, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOA, GPIO_PIN_15)));
                /* Insert delay */
                Delay(0x8FFFF);

                /* Toggle JTDO pin */
                GPIO_WriteBit(GPIOB, GPIO_PIN_3, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_PIN_3)));
                /* Insert delay */
                Delay(0x8FFFF);

                /* Toggle JTRST pin */
                GPIO_WriteBit(GPIOB, GPIO_PIN_4, (Bit_OperateType)(1 - GPIO_ReadOutputDataBit(GPIOB, GPIO_PIN_4)));
                /* Insert delay */
                Delay(0x8FFFF);

                if (GPIO_ReadInputDataBit(KEY_INPUT_PORT, KEY_INPUT_PIN) == Bit_SET)
                {
                    break;
                }
            }
        }
        else
        {
            /* Enablethe JTAG Debug Port SWJ-DP */
            JTAGPortEnableInit();

            /*Turn on Led2*/
            LedOn(LED2_PORT, LED2_PIN);
            /*Turn off Led1*/
            LedOff(LED1_PORT, LED1_PIN);

            while (1)
            {
                if (GPIO_ReadInputDataBit(KEY_INPUT_PORT, KEY_INPUT_PIN) == Bit_RESET)
                {
                    break;
                }
            }
        }
    }
}
/**
 * @}
 */

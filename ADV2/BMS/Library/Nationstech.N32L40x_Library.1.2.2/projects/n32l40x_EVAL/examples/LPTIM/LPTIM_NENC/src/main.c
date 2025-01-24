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
#include "n32l40x_lptim.h"
#include "n32l40x_rcc.h"
/** @addtogroup 
 * @{
 */


void LedBlink(GPIO_Module* GPIOx, uint16_t Pin);
void LEDInit(uint16_t Pin);
void LedOn(uint16_t Pin);
void LedOff(uint16_t Pin);
void Ledlink(uint16_t Pin);
void delay(vu32 nCount);


void EncInputIoConfig(void);
void Lptim_NENCInit(void);
void NoEncWaveOutput(uint16_t count);
uint16_t encCNT = 0;
/**
 * @brief  Main program.
 */
int main(void)
{

    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32l40x_xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32l40x.c file
       */
    /* Init LED GPIO */
    LEDInit(LED1);
    LEDInit(LED2);
    /* Enable the LSI source */
    RCC_EnableLsi(ENABLE);
    RCC_EnableRETPeriphClk(RCC_RET_PERIPH_LPTIM,ENABLE);

    /* LPTIM input1 IO Init and encoder*/
    LPTIM_SetPrescaler(LPTIM,LPTIM_PRESCALER_DIV1);
    EncInputIoConfig();
    Lptim_NENCInit();

    /* LPTIM start count*/
    LPTIM_StartCounter(LPTIM,LPTIM_OPERATING_MODE_CONTINUOUS); 
    /* Great 20 square waves ,and encCNT should be equal to 20*/
    NoEncWaveOutput(20);
    encCNT = LPTIM->CNT;

    while (1)
    {

    }
}
/**
 * @brief  NoEncode input IO Initaliza.
 * @param NONE.
 *   This parameter can be one of following parameters:
 *     @arg NONE
 */
void EncInputIoConfig(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Enable the GPIO Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

    /* Configure the GPIO pin */
    GPIO_InitStructure.Pin        = GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Alternate =  (GPIO_AF2_LPTIM);	
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    /* Configure the GPIO pin */
    GPIO_InitStructure.Pin        = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Alternate =  (GPIO_AF5_LPTIM);
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}
/**
 * @brief  NoEncode module Initaliza.
 * @param NONE.
 *   This parameter can be one of following parameters:
 *     @arg NONE
 */
void Lptim_NENCInit(void)
{
    //config LPTIM     
    LPTIM->INTEN = 0x7F;
    LPTIM_SetClockSource(LPTIM,LPTIM_CLK_SOURCE_INTERNAL);
    LPTIM->CFG &=~(LPTIM_CFG_NENC|LPTIM_CFG_ENC);
    LPTIM_EnableNoEncoderMode(LPTIM);
       
    //ENC MODE1 
    LPTIM_SetEncoderMode(LPTIM,LPTIM_ENCODER_MODE_FALLING);

    LPTIM_Enable(LPTIM);
    //LPTIM_SetAutoReload(LPTIM,60000);  
    LPTIM_SetAutoReload(LPTIM,15000);
    LPTIM_SetCompare(LPTIM,10000);    



}
/**
 * @brief  Toggles the selected Led.
 * @param Led Specifies the Led to be toggled.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 */
void Ledlink(uint16_t Pin)
{
    GPIOB->POD ^= Pin;
}
/**
 * @brief  Turns selected Led on.
 * @param Led Specifies the Led to be set on.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 */
void LedOn(uint16_t Pin)
{
    GPIOB->PBC = Pin;
}
/**
 * @brief  Turns selected Led Off.
 * @param Led Specifies the Led to be set off.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 */
void LedOff(uint16_t Pin)
{
    GPIOB->PBSC = Pin;
}
/**
 * @brief  Configures LED GPIO.
 * @param Led Specifies the Led to be configured.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 */

void LEDInit(uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Enable the GPIO_LED Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;

    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

void delay(vu32 nCount)
{
    vu32 index = 0;
    for (index = (34000 * nCount); index != 0; index--)
    {
    }
}



/**
 * @brief  Great NoEncode square  waves.
* @param count: the number of waves.
 *   This parameter can be PB0 and PB1.
 */
void NoEncWaveOutput(uint16_t count)
{
    while(count--)
    {
        GPIO_SetBits(GPIOB, GPIO_PIN_0);
        delay(2);
        GPIO_ResetBits(GPIOB, GPIO_PIN_0);
        delay(2);
        GPIO_SetBits(GPIOB, GPIO_PIN_1);
        delay(2);
        GPIO_ResetBits(GPIOB, GPIO_PIN_1);
        delay(2);
    }

}

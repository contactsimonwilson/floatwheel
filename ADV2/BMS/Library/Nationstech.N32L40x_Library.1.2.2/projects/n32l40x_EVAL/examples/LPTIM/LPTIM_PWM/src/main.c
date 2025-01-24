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

/** @addtogroup LPTIM_PWM
 * @{
 */


void LedBlink(GPIO_Module* GPIOx, uint16_t Pin);
void LEDInit(uint16_t Pin);
void LedOn(uint16_t Pin);
void LedOff(uint16_t Pin);
void Ledlink(uint16_t Pin);
void delay(vu32 nCount);

void LPTIM_OutputIoInit(void);
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
//**********************************************************
    /* Init LED GPIO */
    LEDInit(LED1);
    /* Enable the LSI source */
    RCC_EnableLsi(ENABLE);	
    RCC_ConfigLPTIMClk(RCC_LPTIMCLK_SRC_LSI);
    RCC_EnableRETPeriphClk(RCC_RET_PERIPH_LPTIM,ENABLE);
    
    /* Init output IO */
    LPTIM_SetPrescaler(LPTIM,LPTIM_PRESCALER_DIV4);
    LPTIM_OutputIoInit();
    /* Init lptim module */ 
    LPTIM->INTEN = 0x7F;

    LPTIM_SetWaveform(LPTIM,LPTIM_OUTPUT_WAVEFORM_PWM); 
    /* output wave */ 
    LPTIM_SetPolarity(LPTIM,LPTIM_OUTPUT_POLARITY_REGULAR);  
    /* config the prescaler */          
    LPTIM_EnableIT_CMPOK(LPTIM);

    LPTIM_Enable(LPTIM);
    /* config ARR ande compare register */ 
    LPTIM_SetAutoReload(LPTIM,600);        
    LPTIM_SetCompare(LPTIM,300);
    //while(!(LPTIM->INTSTS & LPTIM_INTSTS_CMPUPD));
    LPTIM_StartCounter(LPTIM,LPTIM_OPERATING_MODE_CONTINUOUS);  
    while (1)
    {
    }
}
/**
 * @brief  output IO Initaliza.
 * @param NONE.
 *   This parameter can be one of following parameters:
 *     @arg NONE
 */
void LPTIM_OutputIoInit(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Enable the GPIO Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

    /* Configure the GPIO pin */
    GPIO_InitStructure.Pin        = GPIO_PIN_1;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_LPTIM;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
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


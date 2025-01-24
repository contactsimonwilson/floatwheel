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
/** @addtogroup PWR_PVD
 * @{
 */


void LedBlink(GPIO_Module* GPIOx, uint16_t Pin);
void LEDInit(uint16_t Pin);
void LedOn(uint16_t Pin);
void LedOff(uint16_t Pin);
void Ledlink(uint16_t Pin);
void delay(vu32 nCount);
void LPTIMNVIC_Config(FunctionalState Cmd);
void SYSCLKConfig(uint32_t RCC_PLLMULL);
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
    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    /* Init LED GPIO */
    LEDInit(LED1);
    /* Enable the LSI source */
    RCC_EnableLsi(ENABLE);
    LPTIMNVIC_Config(ENABLE);
    RCC_ConfigLPTIMClk(RCC_LPTIMCLK_SRC_LSI);
    RCC_EnableRETPeriphClk(RCC_RET_PERIPH_LPTIM,ENABLE);
    
    /* Enable interrupt   */
    LPTIM_SetPrescaler(LPTIM,LPTIM_PRESCALER_DIV1);
    LPTIM_EnableIT_CMPM(LPTIM);
    /* config lptim ARR and compare register */ 
    LPTIM_Enable(LPTIM);   
    LPTIM_SetAutoReload(LPTIM,65000);
    LPTIM_SetCompare(LPTIM,60000);    
    LPTIM_StartCounter(LPTIM,LPTIM_OPERATING_MODE_CONTINUOUS);              
    DBG_ConfigPeriph(DBG_STOP, ENABLE);
    while (1)
    {
        //PWR_EnterSLEEPMode(0, PWR_SLEEPENTRY_WFI); 
        PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI,PWR_CTRL3_RAM1RET);
        Ledlink(LED1);	
        delay(30);
    }
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
 * @brief LPTIM Interrupt.
 * @param Cmd Interrupt enable or disable
 */
void LPTIMNVIC_Config(FunctionalState Cmd)
{
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;

    EXTI_ClrITPendBit(EXTI_LINE24);
    EXTI_InitStructure.EXTI_Line = EXTI_LINE24;
#ifdef __TEST_SEVONPEND_WFE_NVIC_DIS__
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
#else
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
#endif
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);

    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = LPTIM_WKUP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = Cmd;
    NVIC_Init(&NVIC_InitStructure);
}
/**
 * @brief  Configures system clock after wake-up from low power mode: enable HSE, PLL
 *         and select PLL as system clock source.
 */

void SYSCLKConfig(uint32_t RCC_PLLMULL)
{
    __IO uint32_t StartUpCounter = 0, HSEStartUpStatus = 0;

    // reset RCC with the default values
    RCC_DeInit();

    RCC_ConfigHse(RCC_HSE_ENABLE);
    HSEStartUpStatus = RCC_WaitHseStable();

    if (HSEStartUpStatus == SUCCESS)
    {
//----------------------------------------------------------------------//
    //The following two steps are required to operate flash 
    FLASH_PrefetchBufSet(FLASH_PrefetchBuf_EN);        
    FLASH_SetLatency(FLASH_LATENCY_2);
//----------------------------------------------------------------------//
        
    // set different clock trees frequency division
    RCC_ConfigHclk(RCC_SYSCLK_DIV1);        
    RCC_ConfigPclk2(RCC_HCLK_DIV2); 
    RCC_ConfigPclk1(RCC_HCLK_DIV4);
    
//-------------------the main frequence-------------------//
    // set PLLclock resource from HSE and the PLL factor
    // PLLCLK = 8MHz * pllmul
    RCC_ConfigPll(RCC_PLL_SRC_HSE_DIV2, RCC_PLLMULL,RCC_PLLDIVCLK_ENABLE);
//--------------------------------------------------------------------//

    RCC_EnablePll(ENABLE);
    while (RCC_GetFlagStatus(RCC_CTRL_FLAG_PLLRDF) == RESET)
    {
    }

    RCC_ConfigSysclk(RCC_SYSCLK_SRC_PLLCLK);
    while (RCC_GetSysclkSrc() != 0x0C)
    {
    }
    }
    else
    { 
        // if HSE enable to fail ,the process will come here.Then the MCU clock resoure is HSI
        while(1)
        {}
    }
}

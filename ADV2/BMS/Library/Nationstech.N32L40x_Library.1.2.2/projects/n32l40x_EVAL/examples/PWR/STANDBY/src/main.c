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
#include "log.h"
#include "User_LED_Config.h"

/** @addtogroup PWR_STANDBY
 * @{
 */

/**
 * @brief  Delay.
 * @param  set the delay time .
 *   This parameter can be one of following parameters:
 *     @arg nCount
 */
void Delay(u32 nCount)
{
    u32 index = 0;
    for (index = (34000 * nCount); index != 0; index--)
    {
    }
}

/**
 * @brief  Wakeup_Pin_Config.
 */
void Wakeup_Pin_Config(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    GPIO_InitStructure.Pin        = GPIO_PIN_0;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Pull  = GPIO_Pull_Down;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
}



/**
 * @brief  Main program.
 */
int main(void)
{
    LEDInit(LED1_PORT,LED1_PIN);
    Wakeup_Pin_Config();
    log_init();   
    log_info("\r\n MCU Reset!\r\n");
    /* Enable PWR and BKP clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    /* Enable WKUP pin */
    PWR_WakeUpPinEnable(WAKEUP_PIN1,ENABLE);
    DBG_ConfigPeriph(DBG_STDBY,ENABLE);
    Delay(2000);
    while (1)
    {
        /* Check if the Wake-Up flag is set */
        if (PWR_GetFlagStatus(1,PWR_STBY_FLAG) != RESET)
        {
            /* Clear Wake Up flag */
            PWR_ClearFlag(PWR_STBY_FLAG);
        }
                /* Check if the Wake-Up flag is set */
        if (PWR_GetFlagStatus(1,PWR_WKUP1_FLAG) != RESET)
        {
            /* Clear Wake Up flag */
            PWR_ClearFlag(PWR_WKUP1_FLAG);
        }
        /* Delay a long time */
        Delay(600);
        LEDBlink(LED1_PORT,LED1_PIN);
        log_info("\r\n  MCU Goto Standby!\r\n");
        /* Request to enter STANDBY mode */
        PWR_EnterSTANDBYMode(PWR_STOPENTRY_WFI,PWR_CTRL3_RAM2RET);
    }
}



/**
 * @}
 */

/**
 * @}
 */

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
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "n32l40x.h"
#include "User_Usart_Config.h"
#include "User_LED_Config.h"
#include "User_Systick_Config.h"
#include "User_Can_Config.h"


/** @addtogroup Power Mode
 * @{
 */

/**
 * @brief  Main program.
 */
int main(void)
{
    LEDInit(LED1_PORT, LED1_PIN);
    LEDInit(LED3_PORT, LED3_PIN);
    LEDOn(LED1_PORT,LED1_PIN);
    LEDOn(LED3_PORT,LED3_PIN);
    USART1_Init();
    NVIC_Configuration();
    Systick_MS_Config(SystemCoreClock);
    printf("\r\n MCU Reset!\r\n");
    Tx_Frame_Message_Init();
    /* Configures CAN IOs */
    CAN_GPIO_Config();
    /* Configures CAN */
    CAN_Config();
    while (1)
    {
       CAN_Recieve_Process();
       CAN_Tx_Process();
    }
}


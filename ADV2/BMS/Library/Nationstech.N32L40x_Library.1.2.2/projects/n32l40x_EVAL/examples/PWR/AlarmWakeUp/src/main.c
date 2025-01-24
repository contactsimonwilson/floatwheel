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
#include "n32l40x_rtc.h"
#include "n32l40x_pwr.h"
#include "User_RTC_Config.h"
#include "User_LED_Config.h"

/** @addtogroup RTC_Calendar
 * @{
 */

/**
 * @brief  Delay function.
 */
void delay(vu32 nCount)
{
    vu32 index = 0;
    for (index = (34000 * nCount); index != 0; index--)
    {
    }
}

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

    /* Initialize LEDs and USART on n32l40x-EVAL board */
    LEDInit(LED1_PORT,LED1_PIN);
    LEDOn(LED1_PORT,LED1_PIN);
    log_init();
    log_info("RTC Config");
    /* RTC time and Date default Value */
    RTC_DateAndTimeDefaultVale();
    /* RTC Clock Select, 1: HSE  2:LSE 3: LSI */
    RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE_LSE, true, true);
    RTC_PrescalerConfig();
    /* RTC Date time and Alarm value set */
    RTC_DateRegulate();
    RTC_TimeRegulate();
    RTC_AlarmRegulate(RTC_A_ALARM);
    /* Enable RTC Alarm Interrupt */
    EXTI18_RTCAlarm_Configuration(ENABLE);
    /* Enable PWR clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    DBG_ConfigPeriph(DBG_SLEEP, ENABLE);
    while (1)
    {
       /* Turn on LED and prin some flag imformation */
       LEDOn(LED1_PORT,LED1_PIN);
       delay(200);
       printf("\r\n start low power! \r\n");
       /* Request to enter STOP mode with regulator in low power mode*/
       PWR_EnterSLEEPMode(0, PWR_STOPENTRY_WFI);
       printf("\r\n exit low power! \r\n");
    }
}

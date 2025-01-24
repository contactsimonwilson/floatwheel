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
#include "n32l40x.h"
#include <stdio.h>
#include <stdint.h>
#include "main.h"
#include "log.h"
#include "User_LED_Config.h"
#include "User_RTC_Config.h"
#include "User_RTCBKP_Config.h"

/** @addtogroup RTC_Calendar
 * @{
 */

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
    /* Initialize LEDs on n32l40x-EVAL board */
    LEDInit(LED1_PORT, LED1_PIN);
    LEDOff(LED1_PORT,LED1_PIN);
    /* Initialize USART,TX: PC10 RX: PC11*/
    log_init();
    log_info("\r\n RTC Init \r\n ");
    /* RTC date time alarm default value*/
    RTC_DateAndTimeDefaultVale();
    /* Enable the PWR clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    /* Allow access to RTC */
    PWR_BackupAccessEnable(ENABLE);
    if (USER_WRITE_BKP_DAT1_DATA != BKP_ReadBkpData(BKP_DAT1) )
    {
        /* RTC clock source select */
        if(SUCCESS==RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE_LSE, true))
        {
           /* RTC clock source select */
           RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE_LSE, true);
           RTC_PrescalerConfig();
           /* RTC date time and alarm regulate*/
           RTC_DateRegulate();
           RTC_TimeRegulate();
           RTC_AlarmRegulate(RTC_A_ALARM);
           BKP_WriteBkpData(BKP_DAT1, USER_WRITE_BKP_DAT1_DATA);
           log_info("\r\n RTC Init Success\r\n");
        }
        else
        {
           log_info("\r\n RTC Init Faile\r\n");
        }
    }
    /* Alarm out select option*/
#if (RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_IRQ) // 1.Alarm interrupt test
    RTC_ClrIntPendingBit(RTC_INT_ALRA);
    EXTI18_RTCAlarm_Configuration(ENABLE);
#elif(RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_OUTPUT) // 2.Alarm out test
    /* Alarm output I/O config */
    #if (RTC_ALARM_OUT_TYPE_OPEN_DRAIN == RTC_ALARM_OUT_TYPE)   
       RTC_ConfigOutputType(RTC_OUTPUT_OPENDRAIN);
    #elif(RTC_ALARM_OUT_TYPE_PULL_PUSH == RTC_ALARM_OUT_TYPE)    
       RTC_ConfigOutputType(RTC_OUTPUT_PUSHPULL);
    #endif
    /* Alarm output I/O polarity */
    RTC_ConfigOutput(RTC_OUTPUT_ALA, RTC_OUTPOL_LOW);
#endif
    while (1);
}


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
#include "n32l40x.h"
#include "n32l40x_rtc.h"
#include "User_LED_Config.h"
#include "User_RTC_Config.h"
#include "User_Sysclock_Config.h"
#include "log.h"
#include "User_RTCBKP_Config.h"

/**
 * @brief  Delay function.
 *     @arg nCount
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
    /* Initialize LEDs on n32l40x-EVAL board */
    LEDInit(LED1_PORT,LED1_PIN);
    LEDOff(LED1_PORT,LED1_PIN);
    /* Initialize USART,TX: PC10 RX: PC11*/
    log_init();
    log_info("\r\n RTC Init \r\n");
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
           RTC_PrescalerConfig();
           /* Adjust time by values entered by the user on the hyperterminal */
           RTC_DateRegulate();
           RTC_TimeRegulate();
           /* wake up clock select */
           RTC_ConfigWakeUpClock(RTC_WKUPCLK_CK_SPRE_16BITS);
           /* wake up timer value */
           RTC_SetWakeUpCounter(4);
           BKP_WriteBkpData(BKP_DAT1, USER_WRITE_BKP_DAT1_DATA);
           log_info("\r\n RTC Init Success\r\n");
        }
        else
        {
            log_info("\r\n RTC Init Faile\r\n");
        }
    }
#if (RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_IRQ) // 1.WakeUp interrupt test
    EXTI_ClrITPendBit(EXTI_LINE20);
    EXTI20_RTCWKUP_Configuration(ENABLE);
    /* Enable the RTC Wakeup Interrupt */
    RTC_ClrIntPendingBit(RTC_INT_WUT);
    RTC_ConfigInt(RTC_INT_WUT, ENABLE);
    RTC_EnableWakeUp(ENABLE);
    DBG_ConfigPeriph(DBG_STOP, ENABLE);
    while (1)
    {
        /* Insert a long delay */
        delay(20);
        /* when system clock HSE is selected,advise that the system clock configure as SYSCLK_PLLSRC_HSE,
        when exit the stop2,system clock can configure back as SYSCLK_PLLSRC_HSE_PLLDIV2 */
        SetSysClockToPLL(SystemCoreClock,SYSCLK_PLLSRC_HSE);
        /* Request to enter STOP2 mode*/
        PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI,PWR_CTRL3_RAM1RET|PWR_CTRL3_RAM2RET); 
        SetSysClockToPLL(SystemCoreClock,SYSCLK_PLLSRC_HSE_PLLDIV2);
        /* Insert a long delay */
        delay(20);
        log_init();
        log_info("\r\n Stop2 Wakeup From RTC \r\n");
        RTC_TimeShow();
        LEDBlink(LED1_PORT,LED1_PIN);
    }
#elif(RTC_ALARM_TEST_TYPE   ==  RTC_ALARM_TEST_TYPE_OUTPUT) // 2.WakeUp output test
    /* Set the output type (open-drain output + push-pull output).
       When setting OD, external  should be added pull-up resistor to PC13*/
    #if (RTC_ALARM_OUT_TYPE_OPEN_DRAIN == RTC_ALARM_OUT_TYPE)   
       RTC_ConfigOutputType(RTC_OUTPUT_OPENDRAIN);
    #elif(RTC_ALARM_OUT_TYPE_PULL_PUSH == RTC_ALARM_OUT_TYPE)  
       RTC_ConfigOutputType(RTC_OUTPUT_PUSHPULL);
    #endif
    RTC_ConfigOutput(RTC_OUTPUT_WKUP, RTC_OUTPOL_LOW);
    RTC_EnableWakeUp(ENABLE);
    while (1)
    {
       if (RTC_GetFlagStatus(RTC_FLAG_WTF) == SET)
       {
          RTC_ClrFlag(RTC_FLAG_WTF);
       }
    }
#endif
}

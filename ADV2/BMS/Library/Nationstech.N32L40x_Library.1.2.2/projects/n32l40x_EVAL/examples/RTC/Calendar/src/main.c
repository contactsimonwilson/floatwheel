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
#include "n32l40x.h"
#include "User_LED_Config.h"
#include "User_RTC_Config.h"
#include "User_RTCBKP_Config.h"

/**
 * @brief  config the EXTI interrupt.
 */
void EXTI_PA7_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Enable the AFIO Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
    /* Select the GPIO - configuration used for floating in */
    GPIO_InitStructure.Pin        = GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    GPIO_ConfigEXTILine(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE7);
    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line    = EXTI_LINE7;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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
    LEDInit(LED1_PORT, LED1_PIN);
    LEDOff(LED1_PORT, LED1_PIN);
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
           log_info("\r\n RTC configured....");
           /* Adjust time by values entered by the user on the hyperterminal */
           RTC_DateRegulate();
           RTC_TimeRegulate();
           BKP_WriteBkpData(BKP_DAT1, USER_WRITE_BKP_DAT1_DATA);
           log_info("\r\n RTC Init Success\r\n");
       }
       else
       {
           log_info("\r\n RTC Init Faile\r\n");
       }
    }
    /* Configure the PA11 pin to generate an EXTI interrupt
       in which the calendar value is printed (externally feed
       the 1HZ signal output on PC13 to PA11 to produce a 1s EXTI interrupt)*/
    EXTI_ClrITPendBit(EXTI_LINE7);
    EXTI_PA7_Configuration();
    /* Calibrate output 1Hz signal */
    RTC_ConfigCalibOutput(RTC_CALIB_OUTPUT_1HZ);
    /* Calibrate output config,push pull */
    RTC_ConfigOutputType(RTC_OUTPUT_PUSHPULL);
    /* Calibrate output enable*/
    RTC_EnableCalibOutput(ENABLE);
    log_info("\r\n RTC Config end....");
    while (1);
}

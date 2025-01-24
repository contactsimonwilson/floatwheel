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

/** @addtogroup RTC_TAMPER
 * @{
 */


/**
 * @brief  Configures LED GPIO.
 * @param Led Specifies the Led to be configured.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 */
void TamperInputIoInit(void)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Enable the GPIO_LED Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.Pin        = GPIO_PIN_13;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  Configure the tamper interruput,EXTI19.
 */
 void TAMPER_INT_Configuration(FunctionalState cmd)
{
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    EXTI_ClrITPendBit(EXTI_LINE19);
    EXTI_InitStructure.EXTI_Line                          = EXTI_LINE19;
    EXTI_InitStructure.EXTI_Mode                          = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger                       = EXTI_Trigger_Rising; 
    EXTI_InitStructure.EXTI_LineCmd                       = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                    = TAMPER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = cmd;
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
    /* Initialize USART,TX: PC10 RX: PC11*/
    log_init();
    log_info("\r\n RTC Init \r\n");
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
           BKP_WriteBkpData(BKP_DAT1, USER_WRITE_BKP_DAT1_DATA);
           log_info("\r\n RTC Init Success\r\n");
        }
        else
        {
           log_info("\r\n RTC Init Faile\r\n");
        }
    }
    /*Tamper GPIO Initialize,PC13*/
    TamperInputIoInit();
    /*Configure Tamper GPIO trigger mode*/
    RTC_TamperTriggerConfig(RTC_TAMPER_1, RTC_TamperTrigger_HighLevel);
    /*Configure the valib number of scanning times*/
    RTC_TamperFilterConfig(RTC_TamperFilter_2Sample);
    /*Configure scanning frequence*/
    RTC_TamperSamplingFreqConfig(RTC_TamperSamplingFreq_RTCCLK_Div256);
    /*Configure precharge duration time*/
    RTC_TamperPinsPrechargeDuration(RTC_TamperPrechargeDuration_1RTCCLK);
    EXTI_ClrITPendBit(EXTI_LINE19);
    /*Configure tamper interruput,EXTI_LINE19*/
    TAMPER_INT_Configuration(ENABLE);
    RTC_ClrIntPendingBit(RTC_INT_TAMP1);
    /*Enable tamper interruput*/
    RTC_TamperIECmd(RTC_TAMPER1_INT, ENABLE);
    /*Enable tamper1 */
    RTC_TamperCmd(RTC_TAMPER_1, ENABLE);
    while (1)
    {
    }
}

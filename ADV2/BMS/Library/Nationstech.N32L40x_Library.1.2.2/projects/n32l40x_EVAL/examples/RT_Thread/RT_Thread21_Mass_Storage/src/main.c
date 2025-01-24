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

#include <rtthread.h>
#include "drv_gpio.h"
#include "pin.h"
#include "drv_usart.h"
#include "serial.h"
#include "main.h"

#ifdef RT_USING_DFS
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>
#include <rtgui/calibration.h>
#endif

ALIGN(RT_ALIGN_SIZE)
/* Pull up controller register */
#define DP_CTRL ((__IO unsigned*)(0x40001824))
#define _ClrDPCtrl() (*DP_CTRL = (*DP_CTRL) & (~0x8000000));
#define _EnPortPullup() (*DP_CTRL = (*DP_CTRL) | 0x02000000);
#define _DisPortPullup() (*DP_CTRL = (*DP_CTRL) & 0xFDFFFFFF);

extern void msc_flash_init(void);

/**
 * @brief  Main program
 */
int main(void)
{
    msc_flash_init();
    while(1)
    {
        rt_thread_delay(50);
    }
}

/**
 * @brief  Configures the USB interrupts.
 */
void USB_Interrupts_Config(void)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    
    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USB interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = USB_LP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USB Wake-up interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = USBWakeUp_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure the EXTI line 17 connected internally to the USB IP */
    EXTI_ClrITPendBit(EXTI_LINE17);
    EXTI_InitStructure.EXTI_Line = EXTI_LINE17; 
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
}

/**
 * @brief  Configures USB Clock input (48MHz).
 */
ErrorStatus Set_USBClock(uint32_t sysclk)
{
    ErrorStatus status = SUCCESS;

    switch(sysclk)
    {
        case SYSCLK_VALUE_48MHz: 
            RCC_ConfigUsbClk(RCC_USBCLK_SRC_PLLCLK_DIV1);
            break;

        case SYSCLK_VALUE_72MHz: 
            RCC_ConfigUsbClk(RCC_USBCLK_SRC_PLLCLK_DIV1_5);
            break;

        case SYSCLK_VALUE_96MHz: 
            RCC_ConfigUsbClk(RCC_USBCLK_SRC_PLLCLK_DIV2);
            break;

        default:
            status = ERROR;
            break;
    }

    return status;
}

/**
 * @brief  Configures USB Clock input (48MHz).
 * @param  sysclk: system clock.
 * @return USBClock set Status.
 */
ErrorStatus USB_Config(uint32_t sysclk)
{
    ErrorStatus status = SUCCESS;

    USB_Interrupts_Config();

    if(Set_USBClock(sysclk) == SUCCESS)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USB, ENABLE);
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }

    return status;
}

/**
 * @brief  Configures USB Clock input (48MHz).
 */
void usb_dc_low_level_init(void)
{
    /* Flash clock init*/
    FLASH_ClockInit();
    /* Configurate USB interrupt */
    USB_Interrupts_Config();
    /* Set USB Clock 48MHz*/
    USB_Config(SYSCLK_VALUE_48MHz);
    /* Enable pull up */
    _EnPortPullup();
}


/*@}*/

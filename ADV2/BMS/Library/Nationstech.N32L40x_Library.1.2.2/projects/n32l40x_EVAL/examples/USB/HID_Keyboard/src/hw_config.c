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
 * @file hw_config.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"

 /**
 * @brief  Configures the gpio for keyboard.
 */
void Cfg_KeyIO(void)
{
    GPIO_InitType GPIO_InitStructure;

    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);

    GPIO_InitStruct(&GPIO_InitStructure);
    
    GPIO_InitStructure.Pin = GPIO_PIN_7;

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;

    GPIO_InitStructure.GPIO_Pull = GPIO_Pull_Up;

    GPIO_InitPeripheral(GPIOC, &GPIO_InitStructure);
}
 
 /**
 * @brief  Configures Main system clocks & power.
 */
void Set_System(void)
{
    RCC_DeInit();

    /*Enable HSE*/
    RCC->CTRL |= RCC_CTRL_HSEEN;
    while((RCC->CTRL & RCC_CTRL_HSERDF) != RCC_CTRL_HSERDF);

    /*Set PLL MUL*/
    RCC_ConfigPll(RCC_PLL_SRC_HSE_DIV1, RCC_PLL_MUL_6, RCC_PLLDIVCLK_DISABLE);
    /*Enable PLL*/
    RCC->CTRL |= RCC_CTRL_PLLEN;
    while((RCC->CTRL & RCC_CTRL_PLLRDF) != RCC_CTRL_PLLRDF); 

    /*Set AHB/APB1/APB2*/
    RCC->CFG |= RCC_CFG_AHBPRES_DIV1;
    RCC->CFG |= RCC_CFG_APB1PRES_DIV2;
    RCC->CFG |= RCC_CFG_APB2PRES_DIV1;

    FLASH->AC &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
    FLASH->AC |= (uint32_t)(FLASH_AC_LATENCY_3);

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_PLL;
    while ((RCC->CFG & RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_PLL) 
    {
    }
}

/**
 * @brief  Configures USB Clock input (48MHz).
 * @param  sysclk: system clock.
 * @return USBClock set Status.
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
 * @brief  Power-off system clocks and power while entering suspend mode.
 */
void Enter_LowPowerMode(void)
{
    /* Set the device state to suspend */
    bDeviceState = SUSPENDED;
}

/**
 * @brief  Restores system clocks and power while exiting suspend mode.
 */
void Leave_LowPowerMode(void)
{
    USB_DeviceMess* pInfo = &Device_Info;

    /* Set the device state to the correct state */
    if (pInfo->CurrentConfiguration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
    else
    {
        bDeviceState = ATTACHED;
    }
}

/**
 * @brief Configures the USB interrupts.
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
 * @param  sysclk: system clock.
 * @return USBClock set Status.
 */
ErrorStatus USB_Config(uint32_t sysclk)
{
    ErrorStatus status = SUCCESS;

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
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

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
 * @file hw_config.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H

#include "n32l40x.h"

/* Includes ------------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define BULK_MAX_PACKET_SIZE  0x00000040

/* Exported define -----------------------------------------------------------*/
#define SYSCLK_VALUE_48MHz            ((uint32_t)48000000)
#define SYSCLK_VALUE_72MHz            ((uint32_t)72000000)
#define SYSCLK_VALUE_96MHz            ((uint32_t)96000000)
#define SYSCLK_VALUE_108MHz           ((uint32_t)108000000)
#define PCLK2_VALUE_72MHz             ((uint32_t)72000000)
#define PCLK2_VALUE_48MHz             ((uint32_t)48000000)

//#define USB_LOW_PWR_MGMT_SUPPORT

/* Exported functions ------------------------------------------------------- */
void Set_System(void);
ErrorStatus Set_USBClock(uint32_t sysclk);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void Led_Config(void);
void Led_RW_ON(void);
void Led_RW_OFF(void);
void USB_Configured_LED(void);
void USB_NotConfigured_LED(void);
void USB_Cable_Config (FunctionalState NewState);
void Get_SerialNum(void);
void MAL_Config(void);
void Cfg_KeyIO(void);
ErrorStatus USB_Config(uint32_t sysclk);
/* External variables --------------------------------------------------------*/

#endif  /*__HW_CONFIG_H*/


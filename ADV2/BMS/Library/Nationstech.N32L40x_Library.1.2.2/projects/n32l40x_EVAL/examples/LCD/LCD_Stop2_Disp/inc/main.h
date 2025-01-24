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
 * @file main.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x.h"
#include <stdio.h>
#include <stdint.h>

//#define N32L436MBL_EVB_V1_0

#define LCD_START_COM   (LCD_RAM1_COM4)
 
//#define LCD_LOWPOWER_DEBUG

#define KEY_PORT_CLOCK          (RCC_APB2_PERIPH_GPIOD)
#define KEY_PORT                (GPIOD)
#define KEY_PIN                 (GPIO_PIN_13)

/*for udd_wait_type*/
#define UDD_WAIT_INT            (0x55u) /*After write LCD register,do not wait.if refresh is finish, the UDD interrupt is generated */
#define UDD_WAIT_BLOCK          (0xAAu) /*After write LCD register,wait until refresh is finish, the LCD interrupt is not used*/

#if     (defined(N32L436MBL_EVB_V1_0))
/*  PC10:D14    PC11:D15    PC12:D16*/
#define LED_PORT_CLOCK          (RCC_APB2_PERIPH_GPIOC)
#define LED_PORT                (GPIOC)
#define RTC_INT_LED             (GPIO_PIN_10)
#define UDD_INT_LED             (GPIO_PIN_11)
#define MCU_RUN_LED             (GPIO_PIN_12)
#define LED_PIN                 (RTC_INT_LED | UDD_INT_LED | MCU_RUN_LED)

#else
/*  PD4:D14     PD5:D15     PD6:D16*/
#define LED_PORT_CLOCK          (RCC_APB2_PERIPH_GPIOD)
#define LED_PORT                (GPIOD)
#define RTC_INT_LED             (GPIO_PIN_4)
#define UDD_INT_LED             (GPIO_PIN_5)
#define MCU_RUN_LED             (GPIO_PIN_6)
#define LED_PIN                 (RTC_INT_LED | UDD_INT_LED | MCU_RUN_LED)

#endif

#define USE_STATUS_LED
#ifdef  USE_STATUS_LED
    #define RTC_INT_LED_ON      (LED_PORT->PBSC = RTC_INT_LED)
    #define RTC_INT_LED_OFF     (LED_PORT->PBC  = RTC_INT_LED)
    #define UDD_INT_LED_ON      (LED_PORT->PBSC = UDD_INT_LED)
    #define UDD_INT_LED_OFF     (LED_PORT->PBC  = UDD_INT_LED)
    #define MCU_RUN_LED_ON      (LED_PORT->PBSC = MCU_RUN_LED)
    #define MCU_RUN_LED_OFF     (LED_PORT->PBC  = MCU_RUN_LED)
    #define ALL_LED_ON          (LED_PORT->PBSC = LED_PIN)
    #define ALL_LED_OFF         (LED_PORT->PBC  = LED_PIN)
#else
    #define RTC_INT_LED_ON 
    #define RTC_INT_LED_OFF
    #define UDD_INT_LED_ON 
    #define UDD_INT_LED_OFF
    #define MCU_RUN_LED_ON 
    #define MCU_RUN_LED_OFF
    #define ALL_LED_ON     
    #define ALL_LED_OFF    
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

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

#define BOARD_N32G435   0
#define BOARD_N32L436   1

#define BOARD_TYPE      BOARD_N32L436
#define BOARD_V1_0
//#define BOARD_V1_1

#define LCD_8COM_USED
#ifdef  LCD_8COM_USED
#define LCD_START_COM   (LCD_RAM1_COM4)
#else
#define LCD_START_COM   (LCD_RAM1_COM0)
#endif

//#define LCD_LOWPOWER_DEBUG

#define LCD_LOWPOWER_TEST
#ifdef  LCD_LOWPOWER_TEST
    /*base mode define*/
    #define LCD_LOWPOWER_SLEEP      (0x1U)
    #define LCD_LOWPOWER_LSLEEP     (0x2U)
    #define LCD_LOWPOWER_STOP2      (0x4U)
    #define LCD_LOWPOWER_WAKEUP     (0x8U)

    /*extend mode for user test*/
    #define LCD_STAY_IN_SLEEP       (LCD_LOWPOWER_SLEEP)
    #define LCD_STAY_IN_LSLEEP      (LCD_LOWPOWER_LSLEEP)
    #define LCD_STAY_IN_STOP2       (LCD_LOWPOWER_STOP2)
    
    #define LCD_WAKEUP_FROM_STOP2   (LCD_LOWPOWER_STOP2|LCD_LOWPOWER_WAKEUP)
    #define LCD_WAKEUP_FROM_SLEEP   (LCD_LOWPOWER_SLEEP|LCD_LOWPOWER_WAKEUP)
    #define LCD_WAKEUP_FROM_LSLEEP  (LCD_LOWPOWER_LSLEEP|LCD_LOWPOWER_WAKEUP)

    #define LCD_LOWPOWER_LCD_WAKE   (LCD_LOWPOWER_WAKEUP|LCD_LOWPOWER_SLEEP   \
                                    |LCD_LOWPOWER_LSLEEP|LCD_LOWPOWER_STOP2)

    #define LCD_LOWPOWER_KEY_WAKE   (LCD_LOWPOWER_SLEEP|LCD_LOWPOWER_LSLEEP|LCD_LOWPOWER_STOP2)
                                    
    /*user test switch*/
    #define LCD_LOW_POWER_MODE      LCD_LOWPOWER_KEY_WAKE
#endif

/*Delay time*/
#define SHORT_DELAY_TIME_SHIFT      (4)
#define MIDDLE_DELAY_TIME_SHIFT     (3)
#define LONG_DELAY_TIME_SHIFT       (2)


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

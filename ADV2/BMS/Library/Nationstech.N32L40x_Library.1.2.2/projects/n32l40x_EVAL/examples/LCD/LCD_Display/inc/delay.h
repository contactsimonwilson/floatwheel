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
 * @file delay.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __DELAY_H__
#define __DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"


/** @defgroup SYS_TICK_FREQ Tick Frequency
  * @{
  */
  
#define  SYS_MAX_DELAY              0xFFFFFFFFU
  
#define  SYS_TICK_FREQ_10HZ         100U
#define  SYS_TICK_FREQ_100HZ        10U
#define  SYS_TICK_FREQ_1KHZ         1U
#define  SYS_TICK_FREQ_DEFAULT      SYS_TICK_FREQ_1KHZ

#define IS_TICKFREQ(__FREQ__) (((__FREQ__) == SYS_TICK_FREQ_10HZ)  || \
                               ((__FREQ__) == SYS_TICK_FREQ_100HZ) || \
                               ((__FREQ__) == SYS_TICK_FREQ_1KHZ))

typedef enum
{
    RT_Ok       = 0x00,
    RT_Error    = 0x01,
    RT_Busy     = 0x02,
    RT_TimeOut  = 0x03
}RunTime_StatusType;



__WEAK RunTime_StatusType SYS_InitTick(uint32_t TickPriority);
RunTime_StatusType SYS_SetTickFreq(uint32_t Freq);
uint32_t GetTickFreq(void);
__WEAK void SYS_Delay(uint32_t Delay);
__WEAK void SYS_IncTick(void);

#ifdef __cplusplus
}
#endif

#endif
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

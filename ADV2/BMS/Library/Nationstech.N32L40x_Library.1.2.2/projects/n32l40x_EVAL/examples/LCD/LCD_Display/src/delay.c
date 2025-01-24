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
 * @file delay.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "delay.h"

__IO uint32_t uwTick;
uint32_t uwTickFreq = SYS_TICK_FREQ_DEFAULT;

__WEAK RunTime_StatusType SYS_InitTick(uint32_t TickPriority)
{
    RunTime_StatusType status;
    
    
    return status;
}

__WEAK void SYS_IncTick(void)
{
    uwTick += uwTickFreq;
}

__WEAK uint32_t SYS_GetTick(void)
{
    return uwTick;
}

RunTime_StatusType SYS_SetTickFreq(uint32_t Freq)
{
    RunTime_StatusType status = RT_Ok;
    assert_param(IS_TICKFREQ(Freq));
    if(uwTickFreq != Freq)
    {
        status = SYS_InitTick(Freq);
        if(status == RT_Ok)
        {
            uwTickFreq = Freq;
        }
    }
    return status;
}


uint32_t GetTickFreq(void)
{
    return uwTickFreq;
}

__WEAK void SYS_Delay(uint32_t Delay)
{
    uint32_t tickStart = SYS_GetTick();
    uint32_t wait = Delay;
    if(wait < SYS_MAX_DELAY)
    {
        wait +=(uint32_t)(uwTickFreq);
    }
    while((SYS_GetTick() - tickStart) < wait)
    {
    }
}
    


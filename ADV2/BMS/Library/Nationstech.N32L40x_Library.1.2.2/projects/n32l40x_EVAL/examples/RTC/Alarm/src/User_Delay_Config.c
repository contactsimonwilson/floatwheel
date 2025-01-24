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

#include "n32l40x.h"
#include "User_Delay_Config.h"

static u8   max_ms=155;
static u32  fac_us=0;
static u32  fac_ms=0;


/**
 * @brief  Initializes the systick for delay time.
 *         the systick clock is HCLK
 */
void User_Delay_init(void)
{
    /*Select HCLK as Systick clock*/
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    /* Systick Count for Microsecond*/
    fac_us = (SystemCoreClock / (1000000));
    /* Systick Count for Millisecond*/
    fac_ms = (fac_us * 1000);
}



/**
 * @brief  Delay for Microsecond.
 * @param nus is delay Microsecond count.
 */
void User_Delay_us(uint32_t nus)
{
    u32 temp;
    /*Reload the Millisecond Counts*/
    SysTick->LOAD=nus*fac_us;
    /*Clear the Systick Value register*/
    SysTick->VAL=0x00;
    /*Enable Systick*/
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
    do
    {
        temp = SysTick->CTRL;
    }
    while((temp&0x01) && !(temp&(1<<16)));
    /*Close Systick when the time is up*/
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
    /*Clear the Systick value register*/
    SysTick->VAL =0X00;
}


/**
 * @brief  Delay for Millisecond in this file.
 * @param nms is delay Millisecond count.
 */
static void User_Delay_ms(u32 nms)
{
    u32 temp;
    /*Reload the Microsecond Counts*/
    SysTick->LOAD=(u32)nms*fac_ms;
    /*Clear the Systick Value register*/
    SysTick->VAL =0x00;
    /*Enable Systick*/
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
    do
    {
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));
    /*Close Systick when the time is up*/
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
    /*Clear the Systick value register*/
    SysTick->VAL =0X00;
}


/**
 * @brief  Delay for Millisecond for User.
 * @param nms is delay Millisecond count.
 */
void User_Delay_xms(u32 nms)
{
    u16 i;
    u16 count_1 = (nms / max_ms);
    u16 count_2 = (nms % max_ms);
    if(0 == count_1)
    {
        User_Delay_ms(nms);
    }
    else
    {
        for(i=0;i<count_1;i++)
        {
            User_Delay_ms(max_ms);
        }
        if(count_2 != 0)
        {
            User_Delay_ms(count_2);
        }
    }
}

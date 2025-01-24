/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OPT
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OPT CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OPT SERVICES; LOSS OF USE, DATA,
 * OPT PROFITS; OPT BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OPT TORT (INCLUDING
 * NEGLIGENCE OPT OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file delay.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "delay.h"

static uint32_t fac_us=0;
static uint32_t fac_ms=0;
static uint8_t  max_ms=116;

/**
 * @brief  us delay  program function.
 * @param nus: the setting us value.
 *   note: The system clock should be an integer multiple of 1M .
 *   It is ensure accuracy .
 */
void systick_delay_us(u32 nus)
{       
    u32 temp;       
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);    //select system clock   
    SysTick->LOAD=nus*(SystemCoreClock/1000000); //time relode           
    SysTick->VAL=0x00;        //clear timer value
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;  //Start countdown  
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//wait for the time reach 
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //close the count
    SysTick->VAL =0X00;       //clear timer value    
}

/**
 * @brief  us delay  program function.
 * @param nus: the setting us value.
 *   note: The system clock should be an integer multiple of 1M .
 *   It is ensure accuracy .
 */
void systick_delay_ms(u16 nms)
{                 
    u32 temp;
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);  //select system clock   
    SysTick->LOAD=(u32)nms*((SystemCoreClock/1000000)*1000);//time relode(SysTick->LOAD is 24bit)
    SysTick->VAL =0x00;           //clear timer value
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //Start countdown  
    do
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));//wait for the time reach    
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //close the count
    SysTick->VAL =0X00;       //clear timer value               
} 

void delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	fac_us=SystemCoreClock/1000000;
    fac_ms=fac_us*1000;
}

void delay_us(uint32_t nus)
{
    uint32_t temp;
    SysTick->LOAD=nus*fac_us;
    SysTick->VAL=0x00;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
    do
    {
        temp = SysTick->CTRL;
    }
    while((temp&0x01) && !(temp&(1<<16)));

    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL =0X00;
}

//144M,nms<=116
void delay_ms(uint32_t nms)
{
    uint32_t temp;
    SysTick->LOAD=(uint32_t)nms*fac_ms;
    SysTick->VAL=0x00;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
    do
    {
        temp = SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));

    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL =0X00;
}

void delay_xms(uint32_t nms)
{
    uint16_t i;
    uint16_t count_1 = nms/max_ms;
    uint16_t count_2 = nms%max_ms;

    if(0 == count_1)
    {
        delay_ms(nms);
    }
    else
    {
        for(i=0;i<count_1;i++)
        {
            delay_ms(max_ms);
        }

        if(count_2 != 0)
        {
            delay_ms(count_2);
        }
    }
}

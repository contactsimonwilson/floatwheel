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
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "delay.h"

static uint32_t  fac_us=0;	 //us延时倍乘数			   
static uint32_t  fac_ms=0;	 //ms延时倍乘数
static uint8_t   max_ms=116;

//初始化延迟函数
//SYSTICK的时钟固定为HCLK时钟
//SYSCLK:系统时钟
void delay_init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//选择外部时钟HCLK
    fac_us=SystemCoreClock/1000000;						//为系统时钟
    fac_ms=fac_us*1000;									//代表每个ms需要的systick时钟数   
}


//延时nus
//nus为要延时的us数.		    								   
void delay_us(uint32_t nus)
{
    uint32_t temp;	    	 
    SysTick->LOAD=nus*fac_us; 					//时间加载	  		 
    SysTick->VAL=0x00;        					//清空计数器
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
    do
    {
        temp = SysTick->CTRL;
    }
    while((temp&0x01) && !(temp&(1<<16)));		//等待时间到达

    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
    SysTick->VAL =0X00;      					//清空计数器	 
}

//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=(0xffffff/SYSCLK)*1000
//SYSCLK单位为Hz,nms单位为ms
//对144M条件下,nms<=116
void delay_ms(uint32_t nms)
{
    uint32_t temp;
    SysTick->LOAD=(uint32_t)nms*fac_ms;				//时间加载(SysTick->LOAD为24bit)
    SysTick->VAL =0x00;							//清空计数器
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
    do
    {
        temp=SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
    SysTick->VAL =0X00;       					//清空计数器	  	    
}

//ms级别延时函数使用这个
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

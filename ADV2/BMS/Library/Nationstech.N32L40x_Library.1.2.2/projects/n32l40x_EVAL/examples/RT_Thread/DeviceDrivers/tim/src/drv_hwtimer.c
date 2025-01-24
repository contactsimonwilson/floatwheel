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
 * @file drv_hwtimer.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

#include "drv_hwtimer.h"
#include "n32l40x_rcc.h"

#ifdef RT_USING_HWTIMER

#if !defined(RT_USING_HWTIMER1) && !defined(RT_USING_HWTIMER2) && !defined(RT_USING_HWTIMER3) \
    && !defined(RT_USING_HWTIMER4) && !defined(RT_USING_HWTIMER5) && !defined(RT_USING_HWTIMER8) \
	&& !defined(RT_USING_HWTIMER9)
    #error "Please define at least one RT_USING_HWTIMERx"
    /* this driver can be disabled at menuconfig -> Hardware Drivers Config -> On-chip Peripheral Drivers -> Enable HWTIMER */
#endif

static struct n32l40x_hwtimer_config hwtimer_config[] =
{
#ifdef RT_USING_HWTIMER1
    {
        "timer1",
        TIM1,
        TIM1_UP_IRQn,
    },
#endif
#ifdef RT_USING_HWTIMER2
    {
        "timer2",
        TIM2,
        TIM2_IRQn,
    },
#endif
#ifdef RT_USING_HWTIMER3
    {
        "timer3",
        TIM3,
        TIM3_IRQn,
    },
#endif
#ifdef RT_USING_HWTIMER4
    {
        "timer4",
        TIM4,
        TIM4_IRQn,
    },
#endif
#ifdef RT_USING_HWTIMER5
    {
        "timer5",
        TIM5,
        TIM5_IRQn,
    },
#endif
#ifdef RT_USING_HWTIMER8
    {
        "timer8",
        TIM8,
        TIM8_UP_IRQn,
    },
#endif
#ifdef RT_USING_HWTIMER9
    {
        "timer9",
        TIM9,
        TIM9_IRQn,
    },
#endif
};
uint8_t tim1_count = 0, tim2_count = 0, tim3_count = 0, tim4_count = 0,tim5_count = 0, tim8_count = 0, tim9_count = 0;
static void caculate_tim_count()
{
    uint8_t count = 0;
#ifdef RT_USING_HWTIMER1
    tim1_count = count;
    count++;
#endif
#ifdef RT_USING_HWTIMER2
    tim2_count = count;
    count++;
#endif
#ifdef RT_USING_HWTIMER3
    tim3_count = count;
    count++;
#endif    
#ifdef RT_USING_HWTIMER4
    tim4_count = count;
    count++;
#endif    
#ifdef RT_USING_HWTIMER5
    tim5_count = count;
    count++;
#endif    
#ifdef RT_USING_HWTIMER8
    tim8_count = count;
    count++;
#endif
#ifdef RT_USING_HWTIMER9
    tim9_count = count;
#endif
}

#define BITS(start, end)             ((0xFFFFFFFFUL << (start)) & (0xFFFFFFFFUL >> (31U - (uint32_t)(end)))) 
#define GET_BITS(regval, start, end) (((regval) & BITS((start),(end))) >> (start))

static struct n32l40x_hwtimer hwtimer_obj[sizeof(hwtimer_config) / sizeof(hwtimer_config[0])] = {0};

static rt_err_t n32l40x_hwtimer_control(rt_hwtimer_t *timer, rt_uint32_t cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct n32l40x_hwtimer_config *config;
    RCC_ClocksType RCC_ClockFreq;
    RT_ASSERT(timer != RT_NULL);

    config = (struct n32l40x_hwtimer_config *)timer->parent.user_data;

    RCC_GetClocksFreqValue(&RCC_ClockFreq);
    
    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
    {
        uint32_t clk;
        uint8_t clkpre;
        uint32_t pre;
        if (config->timer_periph != TIM1 && config->timer_periph != TIM8)
        {
            clk = RCC_ClockFreq.Pclk1Freq;
            clkpre = GET_BITS(RCC->CFG, 8, 10);
        }
        else
        {
            clk = RCC_ClockFreq.Pclk2Freq;
            clkpre = GET_BITS(RCC->CFG, 11, 13);
        }
        if (clkpre >= 4)
        {
            clk = clk * 2;
        }
        pre = (clk / * ((uint32_t *)args)) - 1;        
        TIM_ConfigPrescaler(config->timer_periph, pre, TIM_PSC_RELOAD_MODE_IMMEDIATE);
        config->timer_periph->EVTGEN |= TIM_EVTGEN_UDGN;
    }
    break;
    case HWTIMER_CTRL_STOP:
        TIM_Enable(config->timer_periph, DISABLE);
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    return err;
}

static rt_uint32_t n32l40x_hwtimer_count_get(rt_hwtimer_t *timer)
{
    rt_uint32_t CurrentTimer_Count;
    struct n32l40x_hwtimer_config *config;
    RT_ASSERT(timer != RT_NULL);

    config = (struct n32l40x_hwtimer_config *)timer->parent.user_data;

    CurrentTimer_Count = TIM_GetCnt(config->timer_periph);

    return CurrentTimer_Count;
}

/**
 * @brief  Configures the NVIC for TIM.
 */
void TIM_NVIC_Config(IRQn_Type IRQn, uint8_t PreemptionPriority, uint8_t SubPriority,FunctionalState cmd)
{
    NVIC_InitType NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel                   = IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = cmd;
    if(cmd)
    {
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority        = SubPriority;
    }
    NVIC_Init(&NVIC_InitStructure);
}


static void n32l40x_hwtimer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    struct n32l40x_hwtimer_config *config;
    TIM_TimeBaseInitType TIM_TimeBaseStructure;
    RCC_ClocksType RCC_ClockFreq;
    RT_ASSERT(timer != RT_NULL);
    config = (struct n32l40x_hwtimer_config *)timer->parent.user_data;

    if (state == 1)
    {
        uint32_t clk;
        uint8_t clkpre;
        uint32_t pre;
        
        RCC_GetClocksFreqValue(&RCC_ClockFreq);
        TIM_DeInit(config->timer_periph);
        
        if (config->timer_periph != TIM1 && config->timer_periph != TIM8)
        {
            clk = RCC_ClockFreq.Pclk1Freq;
            clkpre = GET_BITS(RCC->CFG, 8, 10);
        }
        else
        {
            clk = RCC_ClockFreq.Pclk2Freq;
            clkpre = GET_BITS(RCC->CFG, 11, 13);
        }
        if (clkpre >= 4)
        {
            clk = clk * 2;
        }
        pre = (clk / 10000) - 1;
        
        /* Time Base configuration */
        TIM_TimeBaseStructure.Prescaler = pre;
        TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
        TIM_TimeBaseStructure.Period    = 10000 - 1;
        TIM_TimeBaseStructure.ClkDiv    = TIM_CLK_DIV1;
        TIM_TimeBaseStructure.RepetCnt  = 0;
        
        if (timer->info->cntmode == HWTIMER_CNTMODE_UP)
        {
            TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
        }
        else
        {
            TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_DOWN;
        }
        TIM_InitTimeBase(config->timer_periph, &TIM_TimeBaseStructure);
        /* set the TIMx priority */
        TIM_NVIC_Config(config->irqn, 3, 0, ENABLE);
        /* clear update flag */
        TIM_ClearFlag(config->timer_periph, TIM_FLAG_UPDATE);
    }
    else
    {
        TIM_Enable(config->timer_periph, DISABLE);
        TIM_ConfigInt(config->timer_periph, TIM_INT_UPDATE, ENABLE);
        TIM_NVIC_Config(config->irqn, 3, 0, DISABLE);
    }
}

static rt_err_t n32l40x_hwtimer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    struct n32l40x_hwtimer_config *config;
    RT_ASSERT(timer != RT_NULL);
    config = (struct n32l40x_hwtimer_config *)timer->parent.user_data;
    
    /* set tim cnt */
    TIM_SetCnt(config->timer_periph, 0);
    /* set tim arr */
    TIM_SetAutoReload(config->timer_periph, cnt - 1);
    
    if (mode == HWTIMER_MODE_ONESHOT)
    {
        TIM_SelectOnePulseMode(config->timer_periph, TIM_OPMODE_SINGLE);
    }
    else
    {
        TIM_SelectOnePulseMode(config->timer_periph, TIM_OPMODE_REPET);
    }

    /* start timer */
    TIM_ConfigInt(config->timer_periph, TIM_INT_UPDATE, ENABLE);
    /* TIM counter enable */
    TIM_Enable(config->timer_periph, ENABLE);
    
    TIM_NVIC_Config(config->irqn, 3, 0, ENABLE);

    return RT_EOK;
}

static void n32l40x_hwtimer_stop(rt_hwtimer_t *timer)
{
    struct n32l40x_hwtimer_config *config;
    RT_ASSERT(timer != RT_NULL);
    config = (struct n32l40x_hwtimer_config *)timer->parent.user_data;

    TIM_Enable(config->timer_periph, DISABLE);

    TIM_NVIC_Config(config->irqn, 3, 0, DISABLE);
}

static const struct rt_hwtimer_ops n32l40x_hwtimer_ops =
{
    .init = n32l40x_hwtimer_init,
    .start = n32l40x_hwtimer_start,
    .stop = n32l40x_hwtimer_stop,
    .count_get = n32l40x_hwtimer_count_get,
    .control = n32l40x_hwtimer_control,
};

static const struct rt_hwtimer_info n32l40x_hwtimer_info =
{
    1000000,            /* the maximum count frequency can be set */
    2000,               /* the minimum count frequency can be set */
    0xFFFF,
    HWTIMER_CNTMODE_UP,
};

/**
  * @brief  This function handles TIM interrupts requests.
  * @param  htim TIM  handle
  * @retval None
  */
void TIM_IRQHandler(TIM_Module* timer_periph)
{
  /* Capture compare 1 event */
  if(TIM_GetFlagStatus(timer_periph, TIM_FLAG_CC1) != RESET)
  {
    if(TIM_GetIntStatus(timer_periph, TIM_INT_CC1) !=RESET)
    {
      {
        TIM_ClrIntPendingBit(timer_periph, TIM_INT_CC1);
      }
    }
  }
  /* Capture compare 2 event */
  if(TIM_GetFlagStatus(timer_periph, TIM_FLAG_CC2) != RESET)
  {
    if(TIM_GetIntStatus(timer_periph, TIM_INT_CC2) !=RESET)
    {
      TIM_ClrIntPendingBit(timer_periph, TIM_INT_CC2);
    }
  }
  /* Capture compare 3 event */
  if(TIM_GetFlagStatus(timer_periph, TIM_FLAG_CC3) != RESET)
  {
    if(TIM_GetIntStatus(timer_periph, TIM_INT_CC3) !=RESET)
    {
      TIM_ClrIntPendingBit(timer_periph, TIM_INT_CC3);
    }
  }
  /* Capture compare 4 event */
  if(TIM_GetFlagStatus(timer_periph, TIM_FLAG_CC4) != RESET)
  {
    if(TIM_GetIntStatus(timer_periph, TIM_INT_CC4) !=RESET)
    {
      TIM_ClrIntPendingBit(timer_periph, TIM_INT_CC4);
    }
  }
  /* TIM Update event */
  if(TIM_GetFlagStatus(timer_periph, TIM_FLAG_UPDATE) != RESET)
  {
    if(TIM_GetIntStatus(timer_periph, TIM_INT_UPDATE) !=RESET)
    {
      TIM_ClrIntPendingBit(timer_periph, TIM_INT_UPDATE);
    }
  }
  /* TIM Break input event */
  if(TIM_GetFlagStatus(timer_periph, TIM_FLAG_BREAK) != RESET)
  {
    if(TIM_GetIntStatus(timer_periph, TIM_INT_BREAK) !=RESET)
    {
      TIM_ClrIntPendingBit(timer_periph, TIM_INT_BREAK);
    }
  }
  /* TIM Trigger detection event */
  if(TIM_GetFlagStatus(timer_periph, TIM_FLAG_TRIG) != RESET)
  {
    if(TIM_GetIntStatus(timer_periph, TIM_INT_TRIG) !=RESET)
    {
      TIM_ClrIntPendingBit(timer_periph, TIM_INT_TRIG);
    }
  }
  /* TIM commutation event */
  if(TIM_GetFlagStatus(timer_periph, TIM_FLAG_COM) != RESET)
  {
    if(TIM_GetIntStatus(timer_periph, TIM_INT_COM) !=RESET)
    {
      TIM_ClrIntPendingBit(timer_periph, TIM_INT_COM);
    }
  }
}

#ifdef RT_USING_HWTIMER1

void TIM1_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
//    TIM_IRQHandler(hwtimer_obj[0].config->timer_periph);
    
    TIM_ClrIntPendingBit(hwtimer_obj[tim1_count].config->timer_periph, TIM_INT_UPDATE);
    rt_device_hwtimer_isr(&hwtimer_obj[tim1_count].time_device);
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif

#ifdef RT_USING_HWTIMER2

void TIM2_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(hwtimer_obj[tim2_count].config->timer_periph, TIM_INT_UPDATE);
    rt_device_hwtimer_isr(&hwtimer_obj[tim2_count].time_device);
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif

#ifdef RT_USING_HWTIMER3

void TIM3_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(hwtimer_obj[tim3_count].config->timer_periph, TIM_INT_UPDATE);
    rt_device_hwtimer_isr(&hwtimer_obj[tim3_count].time_device);
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif

#ifdef RT_USING_HWTIMER4

void TIM4_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(hwtimer_obj[tim4_count].config->timer_periph, TIM_INT_UPDATE);
    rt_device_hwtimer_isr(&hwtimer_obj[tim4_count].time_device);
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif

#ifdef RT_USING_HWTIMER5

void TIM5_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(hwtimer_obj[tim5_count].config->timer_periph, TIM_INT_UPDATE);
    rt_device_hwtimer_isr(&hwtimer_obj[tim5_count].time_device);
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif

#ifdef RT_USING_HWTIMER8

void TIM8_UP_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(hwtimer_obj[tim8_count].config->timer_periph, TIM_INT_UPDATE);
    rt_device_hwtimer_isr(&hwtimer_obj[tim8_count].time_device);
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif

#ifdef RT_USING_HWTIMER9

void TIM9_IRQHandler(void)
{
    /* enter interrupt */
    rt_interrupt_enter();
    TIM_ClrIntPendingBit(hwtimer_obj[tim9_count].config->timer_periph, TIM_INT_UPDATE);
    rt_device_hwtimer_isr(&hwtimer_obj[tim9_count].time_device);
    /* leave interrupt */
    rt_interrupt_leave();
}

#endif

int rt_hwtimer_init(void)
{
    int i = 0;
    int result = RT_EOK;

#ifdef RT_USING_HWTIMER1
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1, ENABLE);
#endif
#ifdef RT_USING_HWTIMER2
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM2, ENABLE);
#endif
#ifdef RT_USING_HWTIMER3
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM3, ENABLE);
#endif
#ifdef RT_USING_HWTIMER4
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM4, ENABLE);
#endif
#ifdef RT_USING_HWTIMER5
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM5, ENABLE);
#endif
#ifdef RT_USING_HWTIMER8
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM8, ENABLE);
#endif
#ifdef RT_USING_HWTIMER9
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM9, ENABLE);
#endif

    caculate_tim_count();
    for (i = 0; i < sizeof(hwtimer_obj) / sizeof(hwtimer_obj[0]); i++)
    {
        hwtimer_obj[i].time_device.info = &n32l40x_hwtimer_info;
        hwtimer_obj[i].time_device.ops  = &n32l40x_hwtimer_ops;
        hwtimer_obj[i].config = &hwtimer_config[i];
        rt_device_hwtimer_register(&hwtimer_obj[i].time_device, \
                                   hwtimer_obj[i].config->name, hwtimer_obj[i].config);
    }

    return result;

}

INIT_DEVICE_EXPORT(rt_hwtimer_init);

#endif /* RT_USING_HWTIMER */

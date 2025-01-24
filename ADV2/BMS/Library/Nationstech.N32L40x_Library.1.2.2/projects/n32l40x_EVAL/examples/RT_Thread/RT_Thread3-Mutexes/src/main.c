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
 * @file main.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

#include <rtthread.h>
#include "drv_gpio.h"
#include "pin.h"
#include "drv_usart.h"
#include "serial.h"

#ifdef RT_USING_DFS
/* dfs filesystem:ELM filesystem init */
#include <dfs_elm.h>
/* dfs Filesystem APIs */
#include <dfs_fs.h>
#endif

#ifdef RT_USING_RTGUI
#include <rtgui/rtgui.h>
#include <rtgui/rtgui_server.h>
#include <rtgui/rtgui_system.h>
#include <rtgui/driver.h>
#include <rtgui/calibration.h>
#endif

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t thread1_stack[ 512 ], thread2_stack[ 512 ];

static struct rt_thread thread1;
static struct rt_thread thread2;

static struct rt_mutex static_mutex;
static rt_mutex_t dynamic_mutex = RT_NULL;

/**
 * @brief  thread1 entry
 */
void thread1_entry(void* parameter)
{
    rt_err_t result;
    rt_tick_t tick;

    rt_thread_delay(5);
    /* 1. static mutex demo */
    rt_kprintf("thread1 try to get static mutex, wait 10 ticks.\n");

    /* get Tick */
    tick = rt_tick_get();
    result = rt_mutex_take(&static_mutex, 10);

    if (result == -RT_ETIMEOUT)
    {
        if (rt_tick_get() - tick != 10)
        {
            return;
        }
        rt_kprintf("thread1 take static mutex timeout\n");
    }
    else
    {
        /* thread2 got static mutex, and it will get it for a long time, thread1 can not get static mutex in 10 ticks */
        rt_kprintf("thread1 take a static mutex, failed.\n");
        return;
    }

    /* wait static mutex forever*/
    rt_kprintf("thread1 try to get static mutex, wait forever.\n");
    result = rt_mutex_take(&static_mutex, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        /* print fail log */
        rt_kprintf("thread1 take a static mutex, failed.\n");
        return;
    }
    rt_kprintf("thread1 take a staic mutex, done.\n");
    
    rt_mutex_release(&static_mutex);
    
    /* 2. dynamic mutex demo */

    /* try to get dynamic mutex, wait 10 ticks */
    rt_kprintf("thread1 try to get dynamic mutex, wait 10 ticks.\n");

    tick = rt_tick_get();
    result = rt_mutex_take(dynamic_mutex, 10);
    if (result == -RT_ETIMEOUT)
    {
        if (rt_tick_get() - tick != 10)
        {
            rt_mutex_delete(dynamic_mutex);
            return;
        }
        rt_kprintf("thread1 take dynamic mutex timeout\n");
    }
    else
    {
        /* thread1 got dynamic mutex, and it will get it for a long time, thread1 can not get dynamic mutex in 10 ticks */
        rt_kprintf("thread1 take a dynamic mutex, failed.\n");
        rt_mutex_delete(dynamic_mutex);
        return;
    }

    /* wait dynamic mutex forever*/
    rt_kprintf("thread1 try to get dynamic mutex, wait forever.\n");
    result = rt_mutex_take(dynamic_mutex, RT_WAITING_FOREVER);
    if (result != RT_EOK)
    {
        /* print fail log */
        rt_kprintf("thread1 take a dynamic mutex, failed.\n");
        rt_mutex_delete(dynamic_mutex);
        return;
    }

    rt_kprintf("thread1 take a dynamic mutex, done.\n");
    /* delete dynamic mutex */
    rt_mutex_delete(dynamic_mutex);
}

/**
 * @brief  thread2 entry
 */
void thread2_entry(void* parameter)
{
    /* 1. static mutex test */
    rt_kprintf("thread2 try to get static mutex\n");
    rt_mutex_take(&static_mutex, 10);
    rt_kprintf("thread2 got static mutex\n");
    rt_thread_delay(RT_TICK_PER_SECOND);
    rt_kprintf("thread2 release static mutex\n");
    rt_mutex_release(&static_mutex);

    /* 2. dynamic mutex test */
    rt_kprintf("thread2 try to get dynamic mutex\n");
    rt_mutex_take(dynamic_mutex, 10);
    rt_kprintf("thread2 got dynamic mutex\n");
    rt_thread_delay(RT_TICK_PER_SECOND);
    rt_kprintf("thread2 release dynamic mutex\n");
    rt_mutex_release(dynamic_mutex);

}

#ifdef RT_USING_RTGUI
rt_bool_t cali_setup(void)
{
    rt_kprintf("cali setup entered\n");
    return RT_FALSE;
}

void cali_store(struct calibration_data *data)
{
    rt_kprintf("cali finished (%d, %d), (%d, %d)\n",
               data->min_x,
               data->max_x,
               data->min_y,
               data->max_y);
}
#endif /* RT_USING_RTGUI */

/**
 * @brief  Main program
 */
int main(void)
{
    rt_err_t result;

    /* init static mutex */
    result = rt_mutex_init(&static_mutex, "smutex", RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_kprintf("init static mutex failed.\n");
    }

    /* create dynamic mutex */
    dynamic_mutex = rt_mutex_create("dmutex", RT_IPC_FLAG_FIFO);
    if (dynamic_mutex == RT_NULL)
    {
        rt_kprintf("create dynamic mutex failed.\n");
    }

    /* init thread1 */
    result = rt_thread_init(&thread1,
                            "thread1",
                            thread1_entry, RT_NULL,
                            (rt_uint8_t*)&thread1_stack[0], sizeof(thread1_stack), 5, 5);

    if (result == RT_EOK)
    {
        rt_thread_startup(&thread1);
    }

    /* init thread2 */
    result = rt_thread_init(&thread2,
                            "thread2",
                            thread2_entry, RT_NULL,
                            (rt_uint8_t*)&thread2_stack[0], sizeof(thread2_stack), 4, 5);

    if (result == RT_EOK)
    {
        rt_thread_startup(&thread2);
    }
    while(1)
    {
        rt_thread_delay(50);
    }
}


/*@}*/

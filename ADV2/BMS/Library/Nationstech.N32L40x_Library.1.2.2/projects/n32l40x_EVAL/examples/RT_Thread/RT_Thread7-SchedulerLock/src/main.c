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

volatile rt_uint32_t  g_tmp = 0;
/**
 * @brief  thread1 thread entry
 */
static void thread1_entry(void* parameter)
{
    rt_uint32_t i;

    /* scheduler lock, when scheduler locked, can not switch to another thread, only respond to interrupt */
    rt_enter_critical();
    
    /* delay 10ms */
    rt_thread_delay(1);
    
    rt_kprintf("g_tmp=:%d \r\n", g_tmp);
    for(i=0; i<100000; i++)
    {
        g_tmp++;
    }
    rt_kprintf("g_tmp=:%d \r\n", g_tmp);

    /* scheduler unlock */
    rt_exit_critical();
}

/**
 * @brief  thread2 thread entry
 */
static void thread2_entry(void* parameter)
{
    /* delay 10ms */ 
    rt_thread_delay(1);
    g_tmp++;
	  
	  rt_kprintf("g_tmp=:%d \r\n", g_tmp);
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

    /* init thread1 */
    result = rt_thread_init(&thread1, "thread1", thread1_entry, RT_NULL, (rt_uint8_t*)&thread1_stack[0], sizeof(thread1_stack), 5, 5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&thread1);
    }
    /* init thread2 */
    result = rt_thread_init(&thread2, "thread2", thread2_entry, RT_NULL, (rt_uint8_t*)&thread2_stack[0], sizeof(thread2_stack), 3, 5);
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

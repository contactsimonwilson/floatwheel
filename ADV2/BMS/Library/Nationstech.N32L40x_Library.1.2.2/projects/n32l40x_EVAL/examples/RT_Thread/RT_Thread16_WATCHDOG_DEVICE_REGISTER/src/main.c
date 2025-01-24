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
static rt_uint8_t test0_stack[ 512 ], test1_stack[ 512 ];

static struct rt_thread test0_thread;
static struct rt_thread test1_thread;

#define LED1_PIN        GET_PIN(A,  8)
#define LED2_PIN        GET_PIN(B,  4)

#define WDT_DEVICE_NAME    "wdt" 

rt_device_t wdg_dev;

static void idle_hook(void)
{
    /* the idle thread callback function feed the dog */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
//	rt_kprintf("Feed Dog!\n");  
}

/**
 * @brief  test0 thread entry
 */
static void test0_thread_entry(void* parameter)
{
    while(1)
    {
        rt_thread_delay(25);    //delay 250ms
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_delay(25);    //delay 250ms
        rt_pin_write(LED1_PIN, PIN_LOW);
    }
}

/**
 * @brief  test1 thread entry
 */
static void test1_thread_entry(void* parameter)
{
    rt_err_t result;
    
    wdg_dev = rt_device_find(WDT_DEVICE_NAME);
    
    if(RT_EOK == rt_device_init(wdg_dev))
    {
        rt_uint16_t timeout = 250;        /* timeout value, unit: ms */
        char device_name[RT_NAME_MAX];
        
        rt_strncpy(device_name, WDT_DEVICE_NAME, RT_NAME_MAX);
        
        /* set watchdog timeout value */
        result = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
        if (result != RT_EOK)
        {
            rt_kprintf("set %s timeout failed!\n", device_name);   
            return;
        }
        /* start watchdog */
        result = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
        if (result != RT_EOK)
        {
            rt_kprintf("start %s failed!\n", device_name);
            return;
        }
        /* set the idle thread callback function */
        rt_thread_idle_sethook(idle_hook);
    }
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

    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);

    /* init test0 thread */
    result = rt_thread_init(&test0_thread, "test0", test0_thread_entry, RT_NULL, (rt_uint8_t*)&test0_stack[0], sizeof(test0_stack), 4, 5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&test0_thread);
    }
    /* init test1 thread */
    result = rt_thread_init(&test1_thread, "test1", test1_thread_entry, RT_NULL, (rt_uint8_t*)&test1_stack[0], sizeof(test1_stack), 5, 5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&test1_thread);
    }

    while(1)
    {
        rt_thread_delay(50);
    }
}

/*@}*/

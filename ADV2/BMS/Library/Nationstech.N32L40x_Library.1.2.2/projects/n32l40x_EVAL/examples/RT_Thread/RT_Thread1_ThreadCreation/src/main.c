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
static rt_uint8_t led1_stack[ 512 ], led2_stack[ 512 ];

static struct rt_thread led1_thread;
static struct rt_thread led2_thread;

#define LED1_PIN        GET_PIN(A,  8)
#define LED2_PIN        GET_PIN(B,  4)

/**
 * @brief  led0 thread entry
 */
static void led1_thread_entry(void* parameter)
{
    while(1)
    {
        rt_thread_delay(50);    //delay 500ms
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_delay(50);    //delay 500ms
        rt_pin_write(LED1_PIN, PIN_LOW);
    }
}

/**
 * @brief  led1 thread entry
 */
static void led2_thread_entry(void* parameter)
{
    while(1)
    {
        rt_thread_delay(25);    //delay 250ms
        rt_pin_write(LED2_PIN, PIN_HIGH);
        rt_thread_delay(25);    //delay 250ms
        rt_pin_write(LED2_PIN, PIN_LOW);
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
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);

    /* init led0 thread */
    result = rt_thread_init(&led1_thread, "led1", led1_thread_entry, RT_NULL, (rt_uint8_t*)&led1_stack[0], sizeof(led1_stack), 4, 5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&led1_thread);
    }
    /* init led1 thread */
    result = rt_thread_init(&led2_thread, "led2", led2_thread_entry, RT_NULL, (rt_uint8_t*)&led2_stack[0], sizeof(led2_stack), 5, 5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&led2_thread);
    }

    while(1)
    {
        rt_thread_delay(50);
    }
}

/*@}*/

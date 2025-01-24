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
static rt_uint8_t test_stack[ 512 ];
static rt_uint8_t key_stack[512];

static struct rt_thread test_thread;
static struct rt_thread key_thread;

struct rt_event event;

#define KEY1_PIN        GET_PIN(A,  4)
#define KEY2_PIN        GET_PIN(A,  5)
#define KEY3_PIN        GET_PIN(A,  6)


#define KEY1  rt_pin_read(KEY1_PIN)
#define KEY2  rt_pin_read(KEY2_PIN)
#define KEY3  rt_pin_read(KEY3_PIN)
 
#define KEY1_PRES   1
#define KEY2_PRES   2
#define KEY3_PRES   3

#define EVENT_FLAG1 (1 << 0)
#define EVENT_FLAG2 (1 << 1)
#define EVENT_FLAG3 (1 << 2)

/**
 * @brief  scan key
 */
uint8_t KEY_Scan(uint8_t mode)
{
    static uint8_t key_up = 1;
    if(mode)
	{
		key_up = 1;  
	}
    if(key_up && (KEY1 == 0 || KEY2 == 0 || KEY3 == 0))
    {
        rt_thread_delay(1);
        key_up = 0;
        if(KEY1 == 0)
		{
			return KEY1_PRES;
		}
        else if(KEY2 == 0)
		{
			return KEY2_PRES;
		}
        else if(KEY3 == 0)
		{
			return KEY3_PRES;
		}
    }
	else if(KEY1 == 1 && KEY2 == 1 && KEY3 == 1)
	{
		key_up = 1;
	}
    return 0;
}

/**
 * @brief  test thread entry
 */
static void test_thread_entry(void* parameter)
{
    rt_uint32_t evt;
    while(1)
    {
        /* recv event */
        if (rt_event_recv(&event, (EVENT_FLAG1 | EVENT_FLAG2), RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, 10, &evt) == RT_EOK)
        {
            rt_kprintf("test: AND recv event 0x%x\r\n", evt);
        }
        
        if (rt_event_recv(&event, EVENT_FLAG3, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, 10, &evt) == RT_EOK)
        {
           rt_kprintf("test:OR recv event 0x%x\r\n", evt);
        }
    }
}

/**
 * @brief  key thread entry
 */
void key_thread_entry(void* parameter)
{
    rt_uint8_t key;

    rt_pin_mode(KEY1_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY2_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(KEY3_PIN, PIN_MODE_INPUT_PULLUP);

    while(1)
    {
        key = KEY_Scan(0);
        switch(key)
        {
            case KEY1_PRES:
                rt_event_send(&event, EVENT_FLAG1);
                rt_kprintf("key: send event1\r\n");
                break;
						
            case KEY2_PRES:
                rt_event_send(&event, EVENT_FLAG2);
                rt_kprintf("key: send event2\r\n");
                break;
						
            case KEY3_PRES:
                rt_event_send(&event, EVENT_FLAG3);
                rt_kprintf("key: send event3\r\n");
                break;

            default:
                break;
            
        }
        rt_thread_delay(5);
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

    /* init event */
    result = rt_event_init(&event, "event", RT_IPC_FLAG_FIFO);
    if (result != RT_EOK)
    {
        rt_kprintf("init event failed.\r\n");
    }

    /* init test thread */
    result = rt_thread_init(&test_thread, "test", test_thread_entry, RT_NULL, (rt_uint8_t*)&test_stack[0], sizeof(test_stack), 4, 5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&test_thread);
    }

    /* init key thread */
    result = rt_thread_init(&key_thread, "key", key_thread_entry, RT_NULL, (rt_uint8_t*)&key_stack[0], sizeof(key_stack), 3, 5);
    {
        rt_thread_startup(&key_thread);
    }
    while(1)
    {
        rt_thread_delay(50);
    }
}


/*@}*/

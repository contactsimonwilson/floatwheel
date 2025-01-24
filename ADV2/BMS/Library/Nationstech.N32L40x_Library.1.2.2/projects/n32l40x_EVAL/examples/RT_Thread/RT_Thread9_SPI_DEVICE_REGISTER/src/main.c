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
#include "spi_flash_w25q.h"

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
static rt_uint8_t test0_stack[ 512 ], test1_stack[ 2048 ];

static struct rt_thread test0_thread;
static struct rt_thread test1_thread;

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

TestStatus Buffercmp8bit(uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength);
TestStatus Buffercmp16bit(uint16_t* pBuffer, uint16_t* pBuffer1, uint16_t BufferLength);
TestStatus Buffercmp32bit(uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength);
TestStatus TransferStatus1 = FAILED, TransferStatus2 = PASSED;;

#define LED1_PIN        GET_PIN(A,  8)
#define LED2_PIN        GET_PIN(B,  4)

#define FLASH_WriteAddress  0x100000

/**
 * @brief  test0 thread entry
 */
static void test0_thread_entry(void* parameter)
{
    while(1)
    {
        rt_thread_delay(250);    //delay 250ms
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_delay(250);    //delay 250ms
        rt_pin_write(LED1_PIN, PIN_LOW);
    }
}

/**
 * @brief  test1 thread entry
 */
static void test1_thread_entry(void* parameter)
{
    rt_device_t storage_dev;   
    uint32_t device_id = 0;
    rt_uint32_t index = FLASH_WriteAddress;
    uint8_t data1[300] = {0};
    uint8_t data2[300] = {0};
    uint16_t i = 0x0;
    
    for(i=0;i<sizeof(data1);i++)
    {
        data1[i] = i;
    }
    
    /* register flash device */
    rt_flash_register(0);
    
    storage_dev = rt_device_find("Flash");
    
    if(RT_EOK == rt_device_open(storage_dev, 0))//open flash device
    {
        device_id = rt_device_control(storage_dev, RT_CMD_W25_READ_ID, RT_NULL);
        if(device_id == sFLASH_W25Q128_ID)
        {
            /* erase sector flash */
            rt_device_control(storage_dev, RT_CMD_W25_ERASE_SECTOR, &index);
            /* write flash */
            rt_device_write(storage_dev, FLASH_WriteAddress, data1, 300);
            /* read flash */
            rt_device_read(storage_dev, FLASH_WriteAddress, data2, 300); 
            
            TransferStatus1 = Buffercmp8bit(data1, data2, 300);
            
            /* erase sector flash */
            rt_device_control(storage_dev, RT_CMD_W25_ERASE_SECTOR, &index);
            /* read flash */
            rt_device_read(storage_dev, FLASH_WriteAddress, data2, 300);
            
            /* Check the correctness of erasing operation dada */
            for (i = 0; i < 300; i++)
            {
                if (data2[i] != 0xFF)
                {
                    TransferStatus2 = FAILED;
                }
            }
            if (TransferStatus1 == PASSED && TransferStatus2 == PASSED)
            {
                rt_kprintf("the write and read data are the same,SPI FLASH test pass\r\n");
            }
            else
            {
                rt_kprintf("the write and read data are different,SPI FLASH test fail\r\n");
            }
        }        
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

/**
 * @brief  Compares two buffers.
 * @param  pBuffer, pBuffer1: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer identical to pBuffer1
 *         FAILED: pBuffer differs from pBuffer1
 */
TestStatus Buffercmp8bit(uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer, pBuffer1: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer identical to pBuffer1
 *         FAILED: pBuffer differs from pBuffer1
 */
TestStatus Buffercmp16bit(uint16_t* pBuffer, uint16_t* pBuffer1, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer, pBuffer1: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer identical to pBuffer1
 *         FAILED: pBuffer differs from pBuffer1
 */
TestStatus Buffercmp32bit(uint32_t* pBuffer, uint32_t* pBuffer1, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;
}



/*@}*/

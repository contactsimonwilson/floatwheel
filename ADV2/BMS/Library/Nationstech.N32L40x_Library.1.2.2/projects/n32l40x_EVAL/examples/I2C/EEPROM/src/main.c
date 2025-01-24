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
#include "n32l40x.h"
#include "i2c_eeprom.h"
#include "log.h"
/** @addtogroup N32L40X_StdPeriph_Examples
 * @{
 */

/** @addtogroup I2C_EEPROM
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} Status;

uint8_t tx_buf[TEST_EEPROM_SIZE] = {0};
uint8_t rx_buf[TEST_EEPROM_SIZE] = {0};
volatile Status test_status      = FAILED;

Status Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
 * @brief   Main program
 */
int main(void)
{
    uint16_t i = 0;

    log_init();
    log_info("this is a I2C EEPROM demo\r\n");
    /* Initialize the I2C EEPROM driver ----------------------------------------*/
    I2C_EE_Init();

    /* Fill the buffer to send */
    for (i = 0; i < TEST_EEPROM_SIZE; i++)
    {
        tx_buf[i] = i;
    }
    log_info("Write to I2C EEPROM\r\n");
    /* First write in the memory followed by a read of the written data --------*/
    /* Write to I2C EEPROM from TEST_EEPROM_ADDR */
    I2C_EE_WriteBuffer(tx_buf, TEST_EEPROM_ADDR, TEST_EEPROM_SIZE);

    log_info("Read from I2C EEPROM\r\n");
    /* Read from I2C EEPROM from sEE_READ_ADDRESS1 */
    I2C_EE_ReadBuffer(rx_buf, TEST_EEPROM_ADDR, TEST_EEPROM_SIZE);

    /* Check if the data written to the memory is read correctly */
    test_status = Buffercmp(tx_buf, rx_buf, TEST_EEPROM_SIZE);

    if (test_status == PASSED)
    {
        log_info("the write and read data are the same,I2C EEPROM test pass\r\n");
    }
    else
    {
        log_info("the write and read data are different,I2C EEPROM test fail\r\n");
    }

    while (1)
    {
    }
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer, pBuffer1: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer identical to pBuffer1
 *         FAILED: pBuffer differs from pBuffer1
 */
Status Buffercmp(uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength)
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
 * @}
 */

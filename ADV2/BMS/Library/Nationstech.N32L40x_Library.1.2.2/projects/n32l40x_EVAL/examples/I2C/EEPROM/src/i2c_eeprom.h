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
 * @file i2c_eeprom.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __I2C_EEPROM_H__
#define __I2C_EEPROM_H__

#include "n32l40x.h"
#include <stdio.h>

typedef enum i2c_state
{
    COMM_DONE       = 0, /// done successfully
    COMM_PRE        = 1,
    COMM_IN_PROCESS = 2,
    COMM_EXIT       = 3 /// exit since failure
} I2C_STATE;

typedef enum i2c_direction
{
    Transmitter = 0x00,
    Receiver    = 0x01
} I2C_DIRECTION;

/**
 * PROCESS MODE
 * 0=polling
 * 1=interrupt
 * 2=DMA
 */
#define PROCESS_MODE 1

#define I2C1_TEST
//#define I2C1_REMAP

#ifdef I2C1_TEST
#define I2Cx I2C1
#ifdef I2C1_REMAP
#define I2Cx_SCL_PIN GPIO_PIN_8
#define I2Cx_SDA_PIN GPIO_PIN_9
#define GPIOx        GPIOB
#else
#define I2Cx_SCL_PIN GPIO_PIN_6
#define I2Cx_SDA_PIN GPIO_PIN_7
#define GPIOx        GPIOB
#endif
#define I2Cx_peripheral_clk_en() RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE)
#define I2Cx_scl_clk_en()        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE)
#define I2Cx_sda_clk_en()        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE)
#endif

#define TEST_EEPROM_SIZE 256
#define TEST_EEPROM_ADDR 0x00
#define I2C_Speed        400000
#define EEPROM_ADDRESS   0xA0
#define I2C_PageSize     8 /// eeprom IC type AT24C02
#define sEE_FLAG_TIMEOUT ((uint32_t)0x1000)
#define sEE_LONG_TIMEOUT ((uint32_t)(100 * sEE_FLAG_TIMEOUT))

/** Maximum number of trials for sEE_WaitEepromStandbyState() function */
#define sEE_MAX_TRIALS_NUMBER 150
#define FALSE                 0
#define TRUE                  1

void I2C_EE_Init(void);
void I2C_EE_WriteBuffer(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite);
void I2C_EE_WriteOnePage(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite);
void I2C_EE_PageWrite(u8* pBuffer, u16 WriteAddr, u16 NumByteToWrite);
void I2C_EE_WriteOnePageCompleted(void);

void I2C_EE_ReadBuffer(u8* pBuffer, u16 ReadAddr, u16 NumByteToRead);
void I2C_EE_WaitOperationIsCompleted(void);
void I2C_EE_WaitEepromStandbyState(void);

void i2c1_evt_handle(void);
void i2c1_err_handle(void);
void i2c1_send_dma_handle(void);
void i2c1_receive_dma_handle(void);

#endif /* __I2C_EEPROM_H__ */

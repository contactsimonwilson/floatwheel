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
 * @file drv_i2c.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

#ifndef __DRV_I2C__
#define __DRV_I2C__

#include "i2c.h"

/* hardware I2C1  define*/
#define I2C1_SCL_GPIO_PORT   GPIOB
#define I2C1_SCL_PIN         GPIO_PIN_8
#define I2C1_SCL_AF          GPIO_AF4_I2C1
#define I2C1_SDA_GPIO_PORT   GPIOB
#define I2C1_SDA_PIN         GPIO_PIN_9
#define I2C1_SDA_AF          GPIO_AF4_I2C1

/* hardware I2C2  define*/
#define I2C2_SCL_GPIO_PORT   GPIOB
#define I2C2_SCL_PIN         GPIO_PIN_10
#define I2C2_SCL_AF          GPIO_AF6_I2C2
#define I2C2_SDA_GPIO_PORT   GPIOB
#define I2C2_SDA_PIN         GPIO_PIN_11
#define I2C2_SDA_AF          GPIO_AF6_I2C2

struct rt_i2c_bus
{
    struct rt_i2c_bus_device parent;
    rt_uint32_t i2c_periph;
};

int rt_hw_i2c_init(void);

#endif

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
 * @file drv_spi.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

#ifndef N32L40X_SPI_H_INCLUDED
#define N32L40X_SPI_H_INCLUDED

#include "n32l40x.h"
#include "n32l40x_spi.h"
#include "rtconfig.h"

#ifdef RT_USING_SPI1
#define SPI1_SCK_PIN             GPIO_PIN_5 /* PA.05 */
#define SPI1_SCK_GPIO_PORT       GPIOA      /* GPIOA */
#define SPI1_SCK_GPIO_CLK        RCC_APB2_PERIPH_GPIOA
#define SPI1_MISO_PIN            GPIO_PIN_6 /* PA.06 */
#define SPI1_MISO_GPIO_PORT      GPIOA      /* GPIOA */
#define SPI1_MISO_GPIO_CLK       RCC_APB2_PERIPH_GPIOA
#define SPI1_MOSI_PIN            GPIO_PIN_7 /* PA.07 */
#define SPI1_MOSI_GPIO_PORT      GPIOA      /* GPIOA */
#define SPI1_MOSI_GPIO_CLK       RCC_APB2_PERIPH_GPIOA
#endif  /* RT_USING_SPI1 */

#ifdef RT_USING_SPI2
#define SPI2_SCK_PIN             GPIO_PIN_13 /* PB.13 */
#define SPI2_SCK_GPIO_PORT       GPIOB      /* GPIOB */
#define SPI2_SCK_GPIO_CLK        RCC_APB2_PERIPH_GPIOB
#define SPI2_MISO_PIN            GPIO_PIN_14 /* PB.14 */
#define SPI2_MISO_GPIO_PORT      GPIOB      /* GPIOB */
#define SPI2_MISO_GPIO_CLK       RCC_APB2_PERIPH_GPIOB
#define SPI2_MOSI_PIN            GPIO_PIN_15 /* PB.15 */
#define SPI2_MOSI_GPIO_PORT      GPIOB      /* GPIOB */
#define SPI2_MOSI_GPIO_CLK       RCC_APB2_PERIPH_GPIOB
#endif  /* RT_USING_SPI2 */

struct w25qxx_spi_cs
{
    GPIO_Module* GPIOx;
    uint32_t GPIO_Pin;
};

int rt_hw_spi_init(void);

#endif /* N32L40X_SPI_H_INCLUDED */

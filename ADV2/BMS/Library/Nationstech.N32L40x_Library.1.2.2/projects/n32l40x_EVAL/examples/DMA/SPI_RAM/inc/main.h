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
 * @file main.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#define SPI_MASTER                SPI1
#define SPI_MASTER_CLK            RCC_APB2_PERIPH_SPI1
#define SPI_MASTER_GPIO           GPIOA
#define SPI_MASTER_GPIO_CLK       RCC_APB2_PERIPH_GPIOA
#define SPI_MASTER_PIN_SCK        GPIO_PIN_5
#define SPI_MASTER_PIN_MISO       GPIO_PIN_6
#define SPI_MASTER_PIN_MOSI       GPIO_PIN_7
#define SPI_MASTER_DMA            DMA
#define SPI_MASTER_DMA_CLK        RCC_AHB_PERIPH_DMA
#define SPI_MASTER_RX_DMA_CHANNEL DMA_CH2
#define SPI_MASTER_RX_DMA_FLAG    DMA_FLAG_TC2
#define SPI_MASTER_TX_DMA_CHANNEL DMA_CH3
#define SPI_MASTER_TX_DMA_FLAG    DMA_FLAG_TC3

#define SPI_SLAVE                SPI2
#define SPI_SLAVE_CLK            RCC_APB2_PERIPH_SPI2
#define SPI_SLAVE_GPIO           GPIOB
#define SPI_SLAVE_GPIO_CLK       RCC_APB2_PERIPH_GPIOB
#define SPI_SLAVE_PIN_SCK        GPIO_PIN_13
#define SPI_SLAVE_PIN_MISO       GPIO_PIN_14
#define SPI_SLAVE_PIN_MOSI       GPIO_PIN_15
#define SPI_SLAVE_DMA            DMA
#define SPI_SLAVE_DMA_CLK        RCC_AHB_PERIPH_DMA
#define SPI_SLAVE_RX_DMA_CHANNEL DMA_CH4
#define SPI_SLAVE_RX_DMA_FLAG    DMA_FLAG_TC4
#define SPI_SLAVE_TX_DMA_CHANNEL DMA_CH5
#define SPI_SLAVE_TX_DMA_FLAG    DMA_FLAG_TC5

#endif /* __MAIN_H__ */

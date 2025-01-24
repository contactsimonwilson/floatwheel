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

#include "n32l40x.h"
#include "n32l40x_conf.h"

#define SPI_MASTER                SPI1
#define SPI_MASTER_CLK            RCC_APB2_PERIPH_SPI1
#define SPI_MASTER_GPIO           GPIOA
#define SPI_MASTER_GPIO_CLK       RCC_APB2_PERIPH_GPIOA
#define SPI_MASTER_PIN_NSS        GPIO_PIN_4
#define SPI_MASTER_PIN_SCK        GPIO_PIN_5
#define SPI_MASTER_PIN_MISO       GPIO_PIN_6
#define SPI_MASTER_PIN_MOSI       GPIO_PIN_7

#define SPI_MASTER_Rx_DMA_Channel DMA_CH3
#define SPI_MASTER_Rx_DMA_FLAG    DMA_FLAG_TC3
#define SPI_MASTER_Tx_DMA_Channel DMA_CH4
#define SPI_MASTER_Tx_DMA_FLAG    DMA_FLAG_TC4

#define SPI_SLAVE                SPI2
#define SPI_SLAVE_CLK            RCC_APB2_PERIPH_SPI2
#define SPI_SLAVE_GPIO           GPIOB
#define SPI_SLAVE_GPIO_CLK       RCC_APB2_PERIPH_GPIOB
#define SPI_SLAVE_PIN_NSS        GPIO_PIN_12
#define SPI_SLAVE_PIN_SCK        GPIO_PIN_13
#define SPI_SLAVE_PIN_MISO       GPIO_PIN_14
#define SPI_SLAVE_PIN_MOSI       GPIO_PIN_15

#define SPI_SLAVE_Rx_DMA_Channel DMA_CH1
#define SPI_SLAVE_Rx_DMA_FLAG    DMA_FLAG_TC1
#define SPI_SLAVE_Tx_DMA_Channel DMA_CH2
#define SPI_SLAVE_Tx_DMA_FLAG    DMA_FLAG_TC2

#define SPI_SLAVE_DR_Base           SPI2_BASE+0x0c //0x40013C0C
#define SPI_MASTER_DR_Base          SPI1_BASE+0x0c //0x4001300C

/* Uncomment the line corresponding to the desired System clock (SYSCLK)
   frequency (after reset the HSI is used as SYSCLK source) */
//#define SYSCLK_HSI
//#define SYSCLK_HSE
#define SYSCLK_PLLHSI_FREQ_24MHz
//#define SYSCLK_PLLHSI_FREQ_36MHz
//#define SYSCLK_PLLHSI_FREQ_48MHz
//#define SYSCLK_PLLHSI_FREQ_56MHz
//#define SYSCLK_PLLHSI_FREQ_72MHz
//#define SYSCLK_PLLHSI_FREQ_96MHz
//#define SYSCLK_PLLHSE_FREQ_24MHz
//#define SYSCLK_PLLHSE_FREQ_36MHz
//#define SYSCLK_PLLHSE_FREQ_48MHz
//#define SYSCLK_PLLHSE_FREQ_56MHz
//#define SYSCLK_PLLHSE_FREQ_72MHz
//#define SYSCLK_PLLHSE_FREQ_96MHz
//#define SYSCLK_PLLHSE_FREQ_144MHz

#endif /* __MAIN_H__ */

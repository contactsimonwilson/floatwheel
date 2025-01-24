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
 * @file spi_flash.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __SPI_FLASH_H__
#define __SPI_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif
    
#include <rtthread.h>
#include "n32l40x.h"

/** @addtogroup Utilities
 * @{
 */

/** @addtogroup
 * @{
 */

/** @addtogroup Common
 * @{
 */

/** @addtogroup SPI_FLASH
 * @{
 */

/** @addtogroup SPI_FLASH_Exported_Types
 * @{
 */
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Exported_Constants
 * @{
 */
/**
 * @brief  SPI Flash supported commands
 */

/* constants definitions */
/* SPI and I2S parameter struct definitions */
typedef struct
{   
    uint32_t device_mode;                                                       /*!< SPI master or slave */
    uint32_t trans_mode;                                                        /*!< SPI transtype */
    uint32_t frame_size;                                                        /*!< SPI frame size */
    uint32_t nss;                                                               /*!< SPI NSS control by handware or software */
    uint32_t endian;                                                            /*!< SPI big endian or little endian */
    uint32_t clock_polarity_phase;                                              /*!< SPI clock phase and polarity */
    uint32_t prescale;                                                          /*!< SPI prescale factor */
}spi_parameter_struct; 

#if defined(RT_USING_SPI1)	
    #define W25Q_SPI_DEVICE_NAME     "spi10"
#endif
	
#if defined(RT_USING_SPI2)
	#define W25Q_SPI_DEVICE_NAME     "spi20"
#endif

typedef enum
{
    RT_CMD_W25_ERASE_SECTOR = 1,
    RT_CMD_W25_ERASE_CHIP = 2,
    RT_CMD_W25_READ_ID = 3,
} W25_COMMAND;
 
#define sFLASH_CMD_WRITE 0x02 /*!< Write to Memory instruction */
#define sFLASH_CMD_WRSR  0x01 /*!< Write Status Register instruction */
#define sFLASH_CMD_WREN  0x06 /*!< Write enable instruction */
#define sFLASH_CMD_READ  0x03 /*!< Read from Memory instruction */
#define sFLASH_CMD_RDSR  0x05 /*!< Read Status Register instruction  */
#define sFLASH_CMD_RDID  0x9F /*!< Read identification */
#define sFLASH_CMD_SE    0xD8 /*!< Sector Erase instruction */
#define sFLASH_CMD_BE    0xC7 /*!< Bulk Erase instruction */

#define sFLASH_WIP_FLAG 0x01 /*!< Write In Progress (WIP) flag */

#define sFLASH_DUMMY_BYTE   0xA5
#define sFLASH_SPI_PAGESIZE 0x100

#define sFLASH_W25Q128_ID   0xEF17
#define sFLASH_M25P64_ID    0x202017

#define sFLASH_SPI1              SPI1
#define SPI1_NSS_PIN             GPIO_PIN_4 /* PA.04 */
#define SPI1_NSS_PORT            GPIOA      /* GPIOA */
#define SPI1_NSS_PORT_CLK        RCC_APB2_PERIPH_GPIOA

#define sFLASH_SPI2              SPI2
#define SPI2_NSS_PIN             GPIO_PIN_12 /* PB.12 */
#define SPI2_NSS_PORT            GPIOB       /* GPIOB */
#define SPI2_NSS_PORT_CLK        RCC_APB2_PERIPH_GPIOB


rt_err_t rt_flash_register(rt_uint8_t flag);

#ifdef __cplusplus
}
#endif

#endif
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

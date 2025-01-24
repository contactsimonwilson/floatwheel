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
#include "main.h"
#include "spi_flash.h"

/** @addtogroup N32L40X_StdPeriph_Examples
 * @{
 */

/** @addtogroup SPI_FLASH
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define FLASH_WriteAddress  0x700000
#define FLASH_ReadAddress   FLASH_WriteAddress
#define FLASH_SectorToErase FLASH_WriteAddress

#define LED1 GPIO_PIN_4
#define LED2 GPIO_PIN_5

#define sFLASH_ID sFLASH_W25Q128_ID

#define BufferSize (countof(Tx_Buffer) - 1)

#define countof(a) (sizeof(a) / sizeof(*(a)))

uint8_t Tx_Buffer[] = "N32L40X SPI Firmware Library Example: communication with an W25Q128 SPI FLASH";
uint8_t Rx_Buffer[BufferSize];
__IO uint8_t Index                  = 0x0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = PASSED;
__IO uint32_t FlashID = 0;

TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

/**
 * @brief  Configures LED GPIO.
 * @param Led Specifies the Led to be configured.
 *   This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else if (GPIOx == GPIOD)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    }


    /* Configure the GPIO pin */
    if (Pin <= GPIO_PIN_ALL)
    {
        GPIO_InitStruct(&GPIO_InitStructure);
        GPIO_InitStructure.Pin        = Pin;
        GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
        GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
        // GPIOx->PBSC = Pin;
    }
}

/**
 * @brief  Turns selected Led on.
 * @param Led Specifies the Led to be set on.
 */
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}
/**
 * @brief  Turns selected Led Off.
 * @param Led Specifies the Led to be set off.
 */
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

/**
 * @brief  Toggles the selected Led.
 * @param Led Specifies the Led to be toggled.
 */
void LedBlink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

/**
 * @brief  Main program.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32l40x.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32l40x.c file
       */

    LedInit(GPIOD, LED1 | LED2);
    LedOff(GPIOD, LED1 | LED2);

    /* Initialize the SPI FLASH driver */
    sFLASH_Init();

    /* Get SPI Flash ID */
    FlashID = sFLASH_ReadID();

    /* Check the SPI Flash ID */
    if (FlashID == sFLASH_ID)
    {
        /* OK: Turn on LED1 */
        LedOn(GPIOD, LED1);
        /* Perform a write in the Flash followed by a read of the written data */
        /* Erase SPI FLASH Sector to write on */
        sFLASH_EraseSector(FLASH_SectorToErase);

        /* Write Tx_Buffer data to SPI FLASH memory */
        sFLASH_WriteBuffer(Tx_Buffer, FLASH_WriteAddress, BufferSize);

        /* Read data from SPI FLASH memory */
        sFLASH_ReadBuffer(Rx_Buffer, FLASH_ReadAddress, BufferSize);

        /* Check the correctness of written dada */
        TransferStatus1 = Buffercmp(Tx_Buffer, Rx_Buffer, BufferSize);
        /* TransferStatus1 = PASSED, if the transmitted and received data by SPI1
           are the same */
        /* TransferStatus1 = FAILED, if the transmitted and received data by SPI1
           are different */

        /* Perform an erase in the Flash followed by a read of the written data */
        /* Erase SPI FLASH Sector to write on */
        sFLASH_EraseSector(FLASH_SectorToErase);

        /* Read data from SPI FLASH memory */
        sFLASH_ReadBuffer(Rx_Buffer, FLASH_ReadAddress, BufferSize);

        /* Check the correctness of erasing operation dada */
        for (Index = 0; Index < BufferSize; Index++)
        {
            if (Rx_Buffer[Index] != 0xFF)
            {
                TransferStatus2 = FAILED;
            }
        }
        /* TransferStatus2 = PASSED, if the specified sector part is erased */
        /* TransferStatus2 = FAILED, if the specified sector part is not well erased */
    }
    else
    {
        /* Error: Turn on LED2 */
        LedOn(GPIOD, LED2);
    }

    while (1)
    {
    }
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer1 identical to pBuffer2
 *         FAILED: pBuffer1 differs from pBuffer2
 */
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer1 != *pBuffer2)
        {
            return FAILED;
        }

        pBuffer1++;
        pBuffer2++;
    }

    return PASSED;
}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param file pointer to the source file name
 * @param line assert_param error line source number
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}

#endif

/**
 * @}
 */

/**
 * @}
 */

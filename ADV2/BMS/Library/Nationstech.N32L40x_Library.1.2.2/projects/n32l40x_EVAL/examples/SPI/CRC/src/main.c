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

/** @addtogroup N32L40X_StdPeriph_Examples
 * @{
 */

/** @addtogroup SPI_CRC
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define BufferSize 32
#define SPICRC

SPI_InitType SPI_InitStructure;
uint16_t SPI1_Buffer_Tx[BufferSize] = {0x0102, 0x0304, 0x0506, 0x0708, 0x090A, 0x0B0C, 0x0D0E, 0x0F10,
                                       0x1112, 0x1314, 0x1516, 0x1718, 0x191A, 0x1B1C, 0x1D1E, 0x1F20,
                                       0x2122, 0x2324, 0x2526, 0x2728, 0x292A, 0x2B2C, 0x2D2E, 0x2F30,
                                       0x3132, 0x3334, 0x3536, 0x3738, 0x393A, 0x3B3C, 0x3D3E, 0x3F40};
uint16_t SPI2_Buffer_Tx[BufferSize] = {0x5152, 0x5354, 0x5556, 0x5758, 0x595A, 0x5B5C, 0x5D5E, 0x5F60,
                                       0x6162, 0x6364, 0x6566, 0x6768, 0x696A, 0x6B6C, 0x6D6E, 0x6F70,
                                       0x7172, 0x7374, 0x7576, 0x7778, 0x797A, 0x7B7C, 0x7D7E, 0x7F80,
                                       0x8182, 0x8384, 0x8586, 0x8788, 0x898A, 0x8B8C, 0x8D8E, 0x8F90};
uint16_t SPI1_Buffer_Rx[BufferSize], SPI2_Buffer_Rx[BufferSize];
uint32_t TxIdx = 0, RxIdx = 0;
__IO uint16_t CRC1Value = 0, CRC2Value = 0;
volatile TestStatus TransferStatus1 = FAILED, TransferStatus2 = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength);

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

    /* System clocks configuration ---------------------------------------------*/
    RCC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* SPI1 configuration ------------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_DOUBLELINE_FULLDUPLEX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_16BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_8;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    /* SPI2 configuration ------------------------------------------------------*/
    SPI_InitStructure.SpiMode = SPI_MODE_SLAVE;
    SPI_Init(SPI2, &SPI_InitStructure);

    /* Enable SPI1 CRC calculation */
    SPI_EnableCalculateCrc(SPI1, ENABLE);
    /* Enable SPI2 CRC calculation */
    SPI_EnableCalculateCrc(SPI2, ENABLE);

    /* Enable SPI1 */
    SPI_Enable(SPI1, ENABLE);
    /* Enable SPI2 */
    SPI_Enable(SPI2, ENABLE);

    /* Transfer procedure */
    while (TxIdx < BufferSize - 1)
    {
        /* Wait for SPI1 Tx buffer empty */
        while (SPI_I2S_GetStatus(SPI1, SPI_I2S_TE_FLAG) == RESET)
            ;
        /* Send SPI2 data */
        SPI_I2S_TransmitData(SPI2, SPI2_Buffer_Tx[TxIdx]);
        /* Send SPI1 data */
        SPI_I2S_TransmitData(SPI1, SPI1_Buffer_Tx[TxIdx++]);
        /* Wait for SPI2 data reception */
        while (SPI_I2S_GetStatus(SPI2, SPI_I2S_RNE_FLAG) == RESET)
            ;
        /* Read SPI2 received data */
        SPI2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI2);
        /* Wait for SPI1 data reception */
        while (SPI_I2S_GetStatus(SPI1, SPI_I2S_RNE_FLAG) == RESET)
            ;
        /* Read SPI1 received data */
        SPI1_Buffer_Rx[RxIdx++] = SPI_I2S_ReceiveData(SPI1);
    }

    /* Wait for SPI1 Tx buffer empty */
    while (SPI_I2S_GetStatus(SPI1, SPI_I2S_TE_FLAG) == RESET)
        ;
    /* Wait for SPI2 Tx buffer empty */
    while (SPI_I2S_GetStatus(SPI2, SPI_I2S_TE_FLAG) == RESET)
        ;

    /* Send last SPI2_Buffer_Tx data */
    SPI_I2S_TransmitData(SPI2, SPI2_Buffer_Tx[TxIdx]);
    /* Enable SPI2 CRC transmission */
    SPI_TransmitCrcNext(SPI2);
    /* Send last SPI1_Buffer_Tx data */
    SPI_I2S_TransmitData(SPI1, SPI1_Buffer_Tx[TxIdx]);
    /* Enable SPI1 CRC transmission */
    SPI_TransmitCrcNext(SPI1);

    /* Wait for SPI1 last data reception */
    while (SPI_I2S_GetStatus(SPI1, SPI_I2S_RNE_FLAG) == RESET)
        ;
    /* Read SPI1 last received data */
    SPI1_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI1);

    /* Wait for SPI2 last data reception */
    while (SPI_I2S_GetStatus(SPI2, SPI_I2S_RNE_FLAG) == RESET)
        ;
    /* Read SPI2 last received data */
    SPI2_Buffer_Rx[RxIdx] = SPI_I2S_ReceiveData(SPI2);

    /* Wait for SPI1 data reception: CRC transmitted by SPI2 */
    while (SPI_I2S_GetStatus(SPI1, SPI_I2S_RNE_FLAG) == RESET)
        ;
    /* Wait for SPI2 data reception: CRC transmitted by SPI1 */
    while (SPI_I2S_GetStatus(SPI2, SPI_I2S_RNE_FLAG) == RESET)
        ;

    /* Check the received data with the send ones */
    TransferStatus1 = Buffercmp(SPI2_Buffer_Rx, SPI1_Buffer_Tx, BufferSize);
    TransferStatus2 = Buffercmp(SPI1_Buffer_Rx, SPI2_Buffer_Tx, BufferSize);
    /* TransferStatus1, TransferStatus2 = PASSED, if the data transmitted and received
       are correct */
    /* TransferStatus1, TransferStatus2 = FAILED, if the data transmitted and received
       are different */

    /* Test on the SPI1 CRC Error flag */
    if ((SPI_I2S_GetStatus(SPI1, SPI_CRCERR_FLAG)) == SET)
    {
        TransferStatus2 = FAILED;
    }

    /* Test on the SPI2 CRC Error flag */
    if ((SPI_I2S_GetStatus(SPI2, SPI_CRCERR_FLAG)) == SET)
    {
        TransferStatus1 = FAILED;
    }

    /* Read SPI1 received CRC value */
    CRC1Value = SPI_I2S_ReceiveData(SPI1);
    /* Read SPI2 received CRC value */
    CRC2Value = SPI_I2S_ReceiveData(SPI2);

    while (1)
    {
    }
}

/**
 * @brief  Configures the different system clocks.
 */
void RCC_Configuration(void)
{
    /* PCLK2 = HCLK/2 */
    RCC_ConfigPclk2(RCC_HCLK_DIV2);

    /* Enable peripheral clocks --------------------------------------------------*/
    /* GPIOA and GPIOB clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO , ENABLE);

    /* SPI1 and SPI2 Periph clock enable */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_SPI1 | RCC_APB2_PERIPH_SPI2, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);

    GPIO_InitStruct(&GPIO_InitStructure);
    /* Configure SPI1 pins: SCK, MISO and MOSI ---------------------------------*/
    /* Confugure SCK and MOSI pins as Alternate Function Push Pull */
    GPIO_InitStructure.Pin        = GPIO_PIN_5 | GPIO_PIN_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
    /* Confugure MISO pin as Input Floating  */
    GPIO_InitStructure.Pin       = GPIO_PIN_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Configure SPI2 pins: SCK, MISO and MOSI ---------------------------------*/
    /* Confugure SCK and MOSI pins as Input Floating */
    GPIO_InitStructure.Pin        = GPIO_PIN_13 | GPIO_PIN_15;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI2;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    /* Confugure MISO pin as Alternate Function Push Pull */
    GPIO_InitStructure.Pin       = GPIO_PIN_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer1, pBuffer2: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer1 identical to pBuffer2
 *         FAILED: pBuffer1 differs from pBuffer2
 */
TestStatus Buffercmp(uint16_t* pBuffer1, uint16_t* pBuffer2, uint16_t BufferLength)
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

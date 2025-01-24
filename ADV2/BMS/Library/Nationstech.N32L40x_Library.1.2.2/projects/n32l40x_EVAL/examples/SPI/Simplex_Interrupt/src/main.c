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

/** @addtogroup Simplex_Interrupt
 * @{
 */

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define BufferSize 32

SPI_InitType SPI_InitStructure;
uint8_t SPI_MASTER_Buffer_Tx[BufferSize] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                            0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
                                            0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
uint8_t SPI_SLAVE_Buffer_Rx[BufferSize];
__IO uint8_t TxIdx = 0, RxIdx = 0;
volatile TestStatus TransferStatus = FAILED;

void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);

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

    /* NVIC configuration ------------------------------------------------------*/
    NVIC_Configuration();

    /* GPIO configuration ------------------------------------------------------*/
    GPIO_Configuration();

    /* SPI_MASTER configuration ------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_TX;
    SPI_InitStructure.SpiMode       = SPI_MODE_MASTER;
    SPI_InitStructure.DataLen       = SPI_DATA_SIZE_8BITS;
    SPI_InitStructure.CLKPOL        = SPI_CLKPOL_LOW;
    SPI_InitStructure.CLKPHA        = SPI_CLKPHA_SECOND_EDGE;
    SPI_InitStructure.NSS           = SPI_NSS_SOFT;
    SPI_InitStructure.BaudRatePres  = SPI_BR_PRESCALER_4;
    SPI_InitStructure.FirstBit      = SPI_FB_MSB;
    SPI_InitStructure.CRCPoly       = 7;
    SPI_Init(SPI_MASTER, &SPI_InitStructure);

    /* SPI_SLAVE configuration -------------------------------------------------*/
    SPI_InitStructure.DataDirection = SPI_DIR_SINGLELINE_RX;
    SPI_InitStructure.SpiMode       = SPI_MODE_SLAVE;
    SPI_Init(SPI_SLAVE, &SPI_InitStructure);

    /* Enable SPI_MASTER TXE interrupt */
    SPI_I2S_EnableInt(SPI_MASTER, SPI_I2S_INT_TE, ENABLE);
    /* Enable SPI_SLAVE RXNE interrupt */
    SPI_I2S_EnableInt(SPI_SLAVE, SPI_I2S_INT_RNE, ENABLE);

    /* Enable SPI_SLAVE */
    SPI_Enable(SPI_SLAVE, ENABLE);
    /* Enable SPI_MASTER */
    SPI_Enable(SPI_MASTER, ENABLE);

    /* Transfer procedure */
    while (RxIdx < BufferSize)
    {
    }

    /* Check the correctness of written dada */
    TransferStatus = Buffercmp(SPI_SLAVE_Buffer_Rx, SPI_MASTER_Buffer_Tx, BufferSize);
    /* TransferStatus = PASSED, if the transmitted and received data
       are equal */
    /* TransferStatus = FAILED, if the transmitted and received data
       are different */

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

    /* Enable GPIO clock for SPI_MASTER and SPI_SLAVE */
    RCC_EnableAPB2PeriphClk(SPI_MASTER_GPIO_CLK | SPI_SLAVE_GPIO_CLK | RCC_APB2_PERIPH_AFIO, ENABLE);

    /* Enable SPI_MASTER and SPI_SLAVE Periph clock */
    RCC_EnableAPB2PeriphClk(SPI_MASTER_CLK | SPI_SLAVE_CLK, ENABLE);
}

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    
    /* Configure SPI_MASTER pins: SCK and MOSI ---------------------------------*/
    /* Configure SCK and MOSI pins as Alternate Function Push Pull */
    GPIO_InitStructure.Pin        = SPI_MASTER_PIN_SCK | SPI_MASTER_PIN_MOSI;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI1;
    GPIO_InitPeripheral(SPI_MASTER_GPIO, &GPIO_InitStructure);

    /* Configure SPI_SLAVE pins: SCK and MISO ---------------------------------*/
    /* Configure SCK pin as Input Floating */
    GPIO_InitStructure.Pin       = SPI_SLAVE_PIN_SCK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF0_SPI2;
    GPIO_InitPeripheral(SPI_SLAVE_GPIO, &GPIO_InitStructure);
    /* Configure MISO pin as Alternate Function Push Pull */
    GPIO_InitStructure.Pin       = SPI_SLAVE_PIN_MISO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(SPI_SLAVE_GPIO, &GPIO_InitStructure);
}

/**
 * @brief  Configure the nested vectored interrupt controller.
 */
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* 1 bit for pre-emption priority, 3 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* Configure and enable SPI_MASTER interrupt -------------------------------*/
    NVIC_InitStructure.NVIC_IRQChannel                   = SPI_MASTER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure and enable SPI_SLAVE interrupt --------------------------------*/
    NVIC_InitStructure.NVIC_IRQChannel                   = SPI_SLAVE_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_Init(&NVIC_InitStructure);
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

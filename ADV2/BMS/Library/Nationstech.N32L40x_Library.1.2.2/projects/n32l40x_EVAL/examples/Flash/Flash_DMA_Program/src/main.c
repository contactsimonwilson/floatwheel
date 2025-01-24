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
#include <stdio.h>
/**
 *  Flash_DMA_Program
 */

#define FLASH_PAGE_SIZE        ((uint16_t)0x800)
#define FLASH_WRITE_START_ADDR ((uint32_t)0x08010000)
#define FLASH_WRITE_END_ADDR   ((uint32_t)0x08018000)

#define FLASH_PROGRAM_TIMEOUT ((uint32_t)0x00002000)

#define BUFFER_SIZE (uint32_t)32

#ifdef  __IAR_ARM
uint32_t Flash_Data_Buffer[BUFFER_SIZE] __attribute__((section(".dma_test")));
#else
uint32_t Flash_Data_Buffer[BUFFER_SIZE] __attribute__((at(FLASH_WRITE_START_ADDR)));
#endif

const uint32_t SRAM_Data_Buffer[BUFFER_SIZE] = {
    0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10, 0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
    0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30, 0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
    0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50, 0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
    0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70, 0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

/**
 * @brief  Main program.
 */
int main(void)
{
    uint8_t Test_Result = 0;

    /* USART Init */
    USART_Config();
    printf("Flash DMA Program Test Start\r\n");
    /* Program FLASH - Transmit Data From SRAM To FLASH */

    /* Configures the Internal High Speed oscillator */
    if(FLASH_HSICLOCK_DISABLE == FLASH_ClockInit())
    {
        printf("HSI oscillator not yet ready\r\n");
        while(1);
    }

    /* Unlocks the FLASH Program Erase Controller */
    FLASH_Unlock();

    /* Erase */
    if (FLASH_COMPL == FLASH_EraseOnePage(FLASH_WRITE_START_ADDR))
    {
        /* Clear All pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);

        /* Wait for last operation to be completed */
        if (FLASH_COMPL == FLASH_WaitForLastOpt(FLASH_PROGRAM_TIMEOUT))
        {
            /* if the previous operation is completed, proceed to program the new data */
            FLASH->CTRL |= FLASH_CTRL_PG;

            /* Start DMA Program FLASH */
            DMA_Flash_SRAM_Config();

            /* Wait for last operation to be completed */
            while (FLASH_COMPL == FLASH_WaitForLastOpt(FLASH_PROGRAM_TIMEOUT))
            {
                /* Check */
                if (PASSED == Buffercmp(SRAM_Data_Buffer, Flash_Data_Buffer, BUFFER_SIZE))
                {
                    /* Test PASSED */
                    Test_Result = PASSED;
                    break;
                }
            }
        }
        else
        {
            /* Test Fail */
            Test_Result = FAILED;
        }
    }
    else
    {
        /* Test Fail */
        Test_Result = FAILED;
    }

    /* Locks the FLASH Program Erase Controller */
    FLASH_Lock();

    if (Test_Result == FAILED)
    {
        printf("Test_Result = FAILED\r\n");
    }
    else
    {
        printf("Test_Result = PASSED\r\n");
    }
    while (1)
    {
    }
}

/**
 * @brief  DMA_Flash_SRAM_Config.
 */
void DMA_Flash_SRAM_Config(void)
{
    DMA_InitType DMA_InitStructure;

    /* DMA1 channel6 configuration */
    RCC_EnableAHBPeriphClk(RCC_AHB_PERIPH_DMA, ENABLE);
    DMA_InitStructure.PeriphAddr     = (uint32_t)SRAM_Data_Buffer;
    DMA_InitStructure.MemAddr        = (uint32_t)Flash_Data_Buffer;
    DMA_InitStructure.Direction      = DMA_DIR_PERIPH_SRC;
    DMA_InitStructure.BufSize        = BUFFER_SIZE;
    DMA_InitStructure.PeriphInc      = DMA_PERIPH_INC_ENABLE;
    DMA_InitStructure.DMA_MemoryInc  = DMA_MEM_INC_ENABLE;
    DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_SIZE_WORD;
    DMA_InitStructure.MemDataSize    = DMA_MemoryDataSize_Word;
    DMA_InitStructure.CircularMode   = DMA_MODE_NORMAL;
    DMA_InitStructure.Priority       = DMA_PRIORITY_HIGH;
    DMA_InitStructure.Mem2Mem        = DMA_M2M_ENABLE;
    DMA_Init(DMA_CH6, &DMA_InitStructure);
    DMA_ClearFlag(DMA_FLAG_TC6, DMA);
    DMA_EnableChannel(DMA_CH6, ENABLE);
}

/**
 * @brief  Buffercmp.
 * @param  pBuffer1
 * @param  pBuffer2
 * @param  BufferLength
 */
uint8_t Buffercmp(const uint32_t* pBuffer1, uint32_t* pBuffer2, uint32_t BufferLength)
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

/**
 * @brief  USART_Config.
 */
void USART_Config(void)
{
    GPIO_InitType GPIO_InitStructure;
    USART_InitType USART_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
    
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);

    GPIO_InitStructure.Pin        = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate  = GPIO_AF4_USART1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.Pin       = GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Alternate  = GPIO_AF4_USART1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.BaudRate            = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
    USART_Init(USART1, &USART_InitStructure);

    USART_Enable(USART1, ENABLE);
}

/**
 * @}
 */

/**
 * @brief  Retargets the C library printf function to the USART1.
 * @param
 * @return
 */
int fputc(int ch, FILE* f)
{
    USART_SendData(USART1, (uint8_t)ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET)
        ;
    return (ch);
}

/*  */
/**
 * @brief  Retargets the C library scanf function to the USART1.
 * @param
 * @return
 */
int fgetc(FILE* f)
{
    while (USART_GetFlagStatus(USART1, USART_FLAG_RXDNE) == RESET)
        ;
    return (int)USART_ReceiveData(USART1);
}

/**
 * @}
 */

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
*          line: assert_param error line source number
 * @return None
 */
void assert_failed(const uint8_t* expr, const uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {}
}

/**
 * @}
 */
#endif

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
 *  Flash_Program
 */

#define FLASH_PAGE_SIZE        ((uint16_t)0x800)
#define FLASH_WRITE_START_ADDR ((uint32_t)0x08010000)
#define FLASH_WRITE_END_ADDR   ((uint32_t)0x08018000)

/**
 * @brief  Main program.
 */
int main(void)
{
    uint32_t Counter_Num = 0;
    uint32_t Erase_Data  = 0xCDEF89AB;
    /* USART Init */
    USART_Config();
    printf("Flash Program Test Start\r\n");
    /* Program FLASH */

    /* Configures the Internal High Speed oscillator */
    if(FLASH_HSICLOCK_DISABLE == FLASH_ClockInit())
    {
        printf("HSI oscillator not yet ready\r\n");
        while(1);
    }

    /* Unlocks the FLASH Program Erase Controller */
    FLASH_Unlock();

    /* Erase */
    if (FLASH_COMPL != FLASH_EraseOnePage(FLASH_WRITE_START_ADDR))
    {
        while(1)
        {
            printf("Flash EraseOnePage Error. Please Deal With This Error Promptly\r\n");
        }
    }

    /* Program */
    for (Counter_Num = 0; Counter_Num < FLASH_PAGE_SIZE; Counter_Num += 4)
    {
        if (FLASH_COMPL != FLASH_ProgramWord(FLASH_WRITE_START_ADDR + Counter_Num, Erase_Data))
        {
            while(1)
            {
                printf("Flash ProgramWord Error. Please Deal With This Error Promptly\r\n");
            }
        }
    }

    /* Locks the FLASH Program Erase Controller */
    FLASH_Lock();

    /* Check */
    for (Counter_Num = 0; Counter_Num < FLASH_PAGE_SIZE; Counter_Num += 4)
    {
        if (Erase_Data != (*(__IO uint32_t*)(FLASH_WRITE_START_ADDR + Counter_Num)))
        {
            printf("Flash Program Test Failed\r\n");
            break;
        }
    }

    printf("Flash Program Test End\r\n");

    while (1)
    {
    }
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

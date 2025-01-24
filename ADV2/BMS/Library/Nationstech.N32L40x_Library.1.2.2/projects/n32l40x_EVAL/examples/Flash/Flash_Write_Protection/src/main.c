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
 *  Flash_Write_Protection
 */

#define FLASH_PAGE_SIZE        ((uint16_t)0x800)
#define FLASH_WRITE_START_ADDR ((uint32_t)0x0800F000)
#define FLASH_WRITE_END_ADDR   ((uint32_t)0x08010000)

#define FLASH_PROTECTED_PAGES FLASH_WRP_Pages30to31 /* FLASH_WRITE_START_ADDR ~ FLASH_WRITE_END_ADDR */

/* Uncomment this line to Enable Write Protection */
#define WRITE_PROTECTION_ENABLE
/* Uncomment this line to Disable Write Protection */
//#define WRITE_PROTECTION_DISABLE

/**
 * @brief  Main program.
 */
int main(void)
{
    uint8_t Test_Result = 0;
    uint32_t WRPR_Value = 0xFFFFFFFF, ProtectedPages = 0, ProgramData = 0xCDEF89AB;
    /* USART Init */
    USART_Config();
    printf("Flash Write Protection Test Start\r\n");
    /* Write Protection */

    /* Configures the Internal High Speed oscillator */
    if(FLASH_HSICLOCK_DISABLE == FLASH_ClockInit())
    {
        printf("HSI oscillator not yet ready\r\n");
        while(1);
    }

    /* Unlocks the FLASH Program Erase Controller */
    FLASH_Unlock();

    /* Get pages already write protection */
    WRPR_Value = FLASH_GetWriteProtectionOB();

#ifdef WRITE_PROTECTION_DISABLE

    printf("Write Protection Disable\r\n");

    /* Get pages already write protected */
    ProtectedPages = ~(WRPR_Value | FLASH_PROTECTED_PAGES);

    /* Check if desired pages are already write protected */
    if ((WRPR_Value | (~FLASH_PROTECTED_PAGES)) != 0xFFFFFFFF)
    {
        /* Erase all the option Bytes */
        FLASH_EraseOB();

        /* Check if there is write protected pages */
        if (ProtectedPages != 0x0)
        {
            /* Restore write protected pages */
            FLASH_EnWriteProtection(ProtectedPages);
        }
        /* Generate System Reset to load the new option byte values */
        NVIC_SystemReset();
    }
#elif defined WRITE_PROTECTION_ENABLE

    printf("Write Protection Enable\r\n");

    /* Set write protected pages */
    ProtectedPages = (~WRPR_Value) | FLASH_PROTECTED_PAGES;

    /* Check if desired pages are not yet write protected */
    if (((~WRPR_Value) & FLASH_PROTECTED_PAGES) != FLASH_PROTECTED_PAGES)
    {
        /* Erase all the option Bytes */
        FLASH_EraseOB();

        /* Enable the pages write protection */
        FLASH_EnWriteProtection(ProtectedPages);

        /* Generate System Reset to load the new option byte values */
        NVIC_SystemReset();
    }
    else
    {
        /* FLASH Write Protection Test */
        printf("Flash Page Erase/Program\r\n");
        /* Clear All pending flags */
        FLASH_ClearFlag(FLASH_STS_CLRFLAG);

        /* Erase */
        if (FLASH_ERR_WRP == FLASH_EraseOnePage(FLASH_WRITE_START_ADDR))
        {
            /* Clear All pending flags */
            FLASH_ClearFlag(FLASH_STS_CLRFLAG);

            /* Program */
            if (FLASH_ERR_WRP == FLASH_ProgramWord(FLASH_WRITE_START_ADDR, ProgramData))
            {
                /* Check */
                if (ProgramData == (*(__IO uint32_t*)FLASH_WRITE_START_ADDR))
                {
                    /* Test Fail */
                    Test_Result = FAILED;
                }
                else
                {
                    /* Test PASSED */
                    Test_Result = PASSED;
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
    }

#endif

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

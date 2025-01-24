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
 *  Cortex-M4F BitBand
 */

#define DEMO_USART_BAUDRATE ((uint32_t)115200)

#define RAM_BASE    ((uint32_t)0x20000000)
#define RAM_BB_BASE ((uint32_t)0x22000000)

#define Data_ResetBit_BB(DataAddr, BitNumber)                                                                          \
    (*(__IO uint32_t*)(RAM_BB_BASE | ((DataAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)

#define Data_SetBit_BB(DataAddr, BitNumber)                                                                            \
    (*(__IO uint32_t*)(RAM_BB_BASE | ((DataAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define Data_GetBit_BB(DataAddr, BitNumber)                                                                            \
    (*(__IO uint32_t*)(RAM_BB_BASE | ((DataAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))

__IO uint32_t Data = 0, DataAddr = 0, DataBitValue = 0;

/**
 * @brief  Main program.
 */
int main(void)
{
    uint8_t i;

    /* USART Init */
    USART_Config();
    printf("Cortex-M4F BitBand \r\n");

    /* A mapping formula shows how to reference each word in the alias region to a
       corresponding bit in the bit-band region. The mapping formula is:
       bit_word_addr = bit_band_base + (byte_offset x 32) + (bit_number + 4)

       Parameter Description:
         bit_word_addr: The address of the word in the alias memory region that maps to the targeted bit.
         bit_band_base: The starting address of the alias region
         byte_offset:   The number of the byte in the bit-band region that contains the targeted bit
         bit_number:    The bit position (0-7) of the targeted bit */

    /* Get the variable address */
    DataAddr = (uint32_t)&Data;

    /* Modify variable bit using bit-band access */

    while (1)
    {
        for (i = 0; i < 32; i++)
        {
            /* Modify Data variable bit i */
            Data_SetBit_BB(DataAddr, i); /* Data = (0x00000001 << i) */
            printf("%d SetBit Data = 0x%08X \r\n", i, (unsigned int)DataBitValue);
            /* Get Data variable bit i value */
            DataBitValue = Data_GetBit_BB(DataAddr, i); /* DataBitValue = 0x00000001 */
            printf("%d SetBit DataBitValue = 0x%08X \r\n", i, (unsigned int)DataBitValue);

            Data_ResetBit_BB(DataAddr, i); /* Data = 0x00000000 */
            printf("%d ResetBit Data = 0x%08X \r\n", i, (unsigned int)DataBitValue);
            /* Get Data variable bit i value */
            DataBitValue = Data_GetBit_BB(DataAddr, i); /* DataBitValue = 0x00000000 */
            printf("%d ResetBit DataBitValue = 0x%08X \r\n", i, (unsigned int)DataBitValue);
        }
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

    USART_InitStructure.BaudRate            = DEMO_USART_BAUDRATE;
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

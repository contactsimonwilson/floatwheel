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
 *  Cortex-M4F MPU
 */

#define DEMO_USART_BAUDRATE ((uint32_t)115200)

#define ACCESS_PERMISSION

#define ARRAY_ADDRESS_START (0x20002000UL)
#define ARRAY_SIZE          (0x09UL << 0UL)
#define ARRAY_REGION_NUMBER (0x03UL << MPU_RNR_REGION_Pos)

/* Public define -------------------------------------------------------------*/
#define RAM_ADDRESS_START                    (0x20000000UL)
#define RAM_SIZE                             (0x19UL << 0UL)
#define PERIPH_ADDRESS_START                 (0x40000000)
#define PERIPH_SIZE                          (0x39UL << 0UL)
#define FLASH_ADDRESS_START                  (0x08000000)
#define FLASH_SIZE                           (0x27UL << 0UL)
#define portMPU_REGION_READ_WRITE            (0x03UL << MPU_RASR_AP_Pos)
#define portMPU_REGION_PRIVILEGED_READ_ONLY  (0x05UL << MPU_RASR_AP_Pos)
#define portMPU_REGION_READ_ONLY             (0x06UL << MPU_RASR_AP_Pos)
#define portMPU_REGION_PRIVILEGED_READ_WRITE (0x01UL << MPU_RASR_AP_Pos)
#define RAM_REGION_NUMBER                    (0x00UL << MPU_RNR_REGION_Pos)
#define FLASH_REGION_NUMBER                  (0x01UL << MPU_RNR_REGION_Pos)
#define PERIPH_REGION_NUMBER                 (0x02UL << MPU_RNR_REGION_Pos)

#if defined(__CC_ARM)
uint8_t privilegedreadonlyarray[32] __attribute__((at(0x20002000)));
#elif defined(__ICCARM__)
#pragma location = 0x20002000
__no_init uint8_t privilegedreadonlyarray[32];
#elif defined(__GNUC__)
uint8_t privilegedreadonlyarray[32] __attribute__((section(".ROarraySection")));
#elif defined(__TASKING__)
uint8_t privilegedreadonlyarray[32] __at(0x20002000);
#endif

/**
 * @brief  Main program.
 */
int main(void)
{
    /* USART Init */
    USART_Config();
    printf("Cortex-M4F MPU \r\n");

    /* Set MPU regions */
    MPU_SETUP();

#ifdef ACCESS_PERMISSION
    accesspermission();
#endif

    while (1)
    {
        printf("The access is permitted. \r\n");
    }
}

/**
 * @brief  Configures the main MPU regions.
 */
void MPU_SETUP(void)
{
    /* Disable MPU */
    MPU->CTRL &= ~MPU_CTRL_ENABLE_Msk;

    /* Configure RAM region as Region NÝ0, 8kB of size and R/W region */
    MPU->RNR  = RAM_REGION_NUMBER;
    MPU->RBAR = RAM_ADDRESS_START;
    MPU->RASR = RAM_SIZE | portMPU_REGION_READ_WRITE;

    /* Configure FLASH region as REGION NÝ1, 1MB of size and R/W region */
    MPU->RNR  = FLASH_REGION_NUMBER;
    MPU->RBAR = FLASH_ADDRESS_START;
    MPU->RASR = FLASH_SIZE | portMPU_REGION_READ_WRITE;

    /* Configure Peripheral region as REGION NÝ2, 0.5GB of size, R/W and Execute
    Never region */
    MPU->RNR  = PERIPH_REGION_NUMBER;
    MPU->RBAR = PERIPH_ADDRESS_START;
    MPU->RASR = PERIPH_SIZE | portMPU_REGION_READ_WRITE | MPU_RASR_XN_Msk;

    /* Enable the memory fault exception */
    SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;

    /* Enable MPU */
    MPU->CTRL |= MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_ENABLE_Msk;
}

/**
 * @brief  This function configure the access right using Cortex-M4 MPU regions.
 */
void accesspermission(void)
{

    /* Configure region for privilegedreadonlyarray as REGION NÝ3, 32byte and R
       only in privileged mode */
    MPU->RNR = ARRAY_REGION_NUMBER;
    MPU->RBAR |= ARRAY_ADDRESS_START;
    MPU->RASR |= ARRAY_SIZE | portMPU_REGION_PRIVILEGED_READ_ONLY;

    /* Read from privilegedreadonlyarray. This will not generate error */
    //privilegedreadonlyarray[0];

    /* Uncomment the following line to write to privilegedreadonlyarray. This will
       generate error */
    // privilegedreadonlyarray[0] = 'e';
}

/* Public functions */

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

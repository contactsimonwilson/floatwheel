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
 *  Cortex-M4F Mode Privilege
 */

#define DEMO_USART_BAUDRATE ((uint32_t)115200)

#define SP_PROCESS_SIZE          0x200 /* Process stack size */
#define SP_PROCESS               0x02  /* Process stack */
#define SP_MAIN                  0x00  /* Main stack */
#define THREAD_MODE_PRIVILEGED   0x00  /* Thread mode has privileged access */
#define THREAD_MODE_UNPRIVILEGED 0x01  /* Thread mode has unprivileged access */

/* clang-format off */
#if defined ( __CC_ARM   )
  __ASM void __SVC(void) 
  { 
    SVC 0x01 
    BX R14
  }
#elif defined ( __ICCARM__ )
  static __INLINE  void __SVC()                     { __ASM ("svc 0x01");}
#elif defined   (  __GNUC__  )
  static __INLINE void __SVC()                      { __ASM volatile ("svc 0x01");}
#endif
/* clang-format on */

__IO uint8_t PSPMemAlloc[SP_PROCESS_SIZE];
__IO uint32_t Index = 0, PSPValue = 0, CurrentStack = 0, ThreadMode = 0;

/**
 * @brief  Main program.
 */
int main(void)
{
    /* USART Init */
    USART_Config();
    printf("Cortex-M4F Mode Privilege \r\n");

    /* Switch Thread mode Stack from Main to Process */
    /* Initialize memory reserved for Process Stack */
    for (Index = 0; Index < SP_PROCESS_SIZE; Index++)
    {
        PSPMemAlloc[Index] = 0x00;
    }

    /* Set Process stack value */
    __set_PSP((uint32_t)PSPMemAlloc + SP_PROCESS_SIZE);

    /* Select Process Stack as Thread mode Stack */
    __set_CONTROL(SP_PROCESS);

    /* Get the Thread mode stack used */
    if ((__get_CONTROL() & 0x02) == SP_MAIN)
    {
        /* Main stack is used as the current stack */
        CurrentStack = SP_MAIN;
    }
    else
    {
        /* Process stack is used as the current stack */
        CurrentStack = SP_PROCESS;

        /* Get process stack pointer value */
        PSPValue = __get_PSP();
    }

    /* Switch Thread mode from privileged to unprivileged */
    /* Thread mode has unprivileged access */
    __set_CONTROL(THREAD_MODE_UNPRIVILEGED | SP_PROCESS);

    /* Unprivileged access mainly affect ability to:
        - Use or not use certain instructions such as MSR fields
        - Access System Control Space (SCS) registers such as NVIC and SysTick */

    /* Check Thread mode privilege status */
    if ((__get_CONTROL() & 0x01) == THREAD_MODE_PRIVILEGED)
    {
        /* Thread mode has privileged access  */
        ThreadMode = THREAD_MODE_PRIVILEGED;
    }
    else
    {
        /* Thread mode has unprivileged access*/
        ThreadMode = THREAD_MODE_UNPRIVILEGED;
    }

    /* Switch back Thread mode from unprivileged to privileged */
    /* Try to switch back Thread mode to privileged (Not possible, this can be
       done only in Handler mode) */
    __set_CONTROL(THREAD_MODE_PRIVILEGED | SP_PROCESS);

    /* Generate a system call exception, and in the INTSTS switch back Thread mode to privileged */
    __SVC();

    /* Check Thread mode privilege status */
    if ((__get_CONTROL() & 0x01) == THREAD_MODE_PRIVILEGED)
    {
        /* Thread mode has privileged access */
        ThreadMode = THREAD_MODE_PRIVILEGED;
    }
    else
    {
        /* Thread mode has unprivileged access */
        ThreadMode = THREAD_MODE_UNPRIVILEGED;
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

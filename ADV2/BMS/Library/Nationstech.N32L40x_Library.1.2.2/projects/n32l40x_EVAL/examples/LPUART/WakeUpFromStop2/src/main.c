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
#include <stdio.h>
#include "main.h"

/** @addtogroup N32L40x_StdPeriph_Examples
 * @{
 */

/** @addtogroup LPUART_WakeUpFromStop2
 * @{
 */

LPUART_InitType LPUART_InitStructure;

/* Buffer used for confirmation messages transmission */
uint8_t TxBuffer1[] = "Start bit detection wake-up successful";
uint8_t TxBuffer2[] = "RXNE detection wake-up successful";
uint8_t TxBuffer3[] = "A configurable received byte match wake-up successful";
uint8_t TxBuffer4[] = "A programmed 4-Byte frame match wake-up successful";
uint32_t WakeUpTrigger[] = {0x5A, 0x1E2D3C4B};

#define _STOP2_WAKEUP_DEBUG_
#ifdef _STOP2_WAKEUP_DEBUG_
uint32_t TRIMR0, TRIMR1, TRIMR2, TRIMR3, TRIMR4, TRIMR5, TRIMR6, TRIMR7, TRIMR8;
uint32_t MSICAL, MSITRIM;
void SetSysClock_HSE(void);
void AFEC_Configuration1(void);
void AFEC_Configuration2(void);
#endif

/**
 * @brief  Main program
 */
int main(void)
{
#ifdef _STOP2_WAKEUP_DEBUG_
    /* Configure the system clock to 8 MHz */
    SetSysClock_HSE(); //flash read latency=0
#endif

    /* Keep Debugger Connection during STOP2 Mode */
    DBG_ConfigPeriph(DBG_STOP, ENABLE);

    /* Configure the GPIO ports */
    GPIO_Configuration();

    /* System Clocks Configuration */
    RCC_Configuration(RCC_LPUARTCLK_SRC_LSE);

    /* Configure EXTI Line 23 */
    EXTI_Configuration();

    /* LPUART configuration ------------------------------------------------------*/
    LPUART_DeInit();
    LPUART_StructInit(&LPUART_InitStructure);
    LPUART_InitStructure.BaudRate            = 9600;
    LPUART_InitStructure.Parity              = LPUART_PE_NO;
    LPUART_InitStructure.RtsThreshold        = LPUART_RTSTH_FIFOFU;
    LPUART_InitStructure.HardwareFlowControl = LPUART_HFCTRL_NONE;
    LPUART_InitStructure.Mode                = LPUART_MODE_RX | LPUART_MODE_TX;
    /* Configure LPUART */
    LPUART_Init(&LPUART_InitStructure);

    /*##-1- Wake Up second step  ###############################################*/
    printf("\n\r##-1-Start Bit Detection Wake-Up##\n\r");
    /* Set the Wake-Up Event: specify wake-up on start bit */
    LPUART_ConfigWakeUpMethod(LPUART_WUSTP_STARTBIT);
    /* Enable the LPUART Wake UP from STOP2 Mode Interrupt */
    LPUART_ConfigInt(LPUART_INT_WUF, ENABLE);
    /* Enable MCU Wake-up by LPUART */
    LPUART_EnableWakeUpStop(ENABLE);
#ifdef _STOP2_WAKEUP_DEBUG_
    AFEC_Configuration1();
#endif
    /* Enter STOP2 Mode */
    PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI, PWR_CTRL3_RAM1RET | PWR_CTRL3_RAM2RET);
    /* ... STOP2 Mode ... */
#ifdef _STOP2_WAKEUP_DEBUG_
    AFEC_Configuration2();
#endif    
    /* Wake Up based on Start Bit Detection successful */
    LPUART_EnableWakeUpStop(DISABLE);
    /* Output a message on Hyperterminal using printf function */
    printf("\n\rStart bit detection wake-up successful\n\r");

    /*##-2- Wake Up second step  ###############################################*/
    printf("\n\r##-2-RXNE Detection Wake-Up##\n\r");
    /* Set the Wake-Up Event: specify wake-up on RXNE flag */
    LPUART_ConfigWakeUpMethod(LPUART_WUSTP_RXNE);
    /* Enable the LPUART Wake UP from STOP2 Mode Interrupt */
    LPUART_ConfigInt(LPUART_INT_WUF, ENABLE);
    /* Enable MCU Wake-Up by LPUART */
    LPUART_EnableWakeUpStop(ENABLE);
#ifdef _STOP2_WAKEUP_DEBUG_
    AFEC_Configuration1();
#endif
    /* Enter STOP2 Mode */
    PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI, PWR_CTRL3_RAM1RET | PWR_CTRL3_RAM2RET);
    /* ... STOP2 Mode ... */
#ifdef _STOP2_WAKEUP_DEBUG_
    AFEC_Configuration2();
#endif    
    /* Wake Up based on RXNE Detection successful */
    LPUART_EnableWakeUpStop(DISABLE);    
    /* Output a message on Hyperterminal using printf function */
    printf("\n\rRXNE detection wake-up successful\n\r");

    /*##-3- Wake Up second step  ###############################################*/
    printf("\n\r##-3-A Configurable Received Byte Match Wake-Up##\n\r");
    /* Set the Wake-Up Event: specify wake-up on a configurable received byte match */
    LPUART_ConfigWakeUpMethod(LPUART_WUSTP_BYTE);
    /* Set the Wake-Up Data */
    LPUART_ConfigWakeUpData(WakeUpTrigger[0]);
    /* Enable the LPUART Wake UP from STOP2 mode Interrupt */
    LPUART_ConfigInt(LPUART_INT_WUF, ENABLE);
    /* Enable MCU Wake-Up by LPUART */
    LPUART_EnableWakeUpStop(ENABLE);
#ifdef _STOP2_WAKEUP_DEBUG_
    AFEC_Configuration1();
#endif
    /* Enter STOP2 Mode */
    PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI, PWR_CTRL3_RAM1RET | PWR_CTRL3_RAM2RET);
    /* ... STOP2 Mode ... */
#ifdef _STOP2_WAKEUP_DEBUG_
    AFEC_Configuration2();
#endif   
    /* Wake Up based on a Configurable Received Byte Match successful */
    LPUART_EnableWakeUpStop(DISABLE);
    /* Output a message on Hyperterminal using printf function */
    printf("\n\rA configurable received byte match wake-up successful\n\r");

    /*##-4- Wake Up second step  ###############################################*/
    printf("\n\r##-4-A Programmed 4-Byte Frame Match Wake-Up##\n\r");
    /* Set the Wake-Up Event: specify wake-up on a programmed 4-Byte frame */
    LPUART_ConfigWakeUpMethod(LPUART_WUSTP_FRAME);
    /* Set the Wake-Up Data */
    LPUART_ConfigWakeUpData(WakeUpTrigger[1]);
    /* Enable the LPUART Wake UP from STOP2 mode Interrupt */
    LPUART_ConfigInt(LPUART_INT_WUF, ENABLE);
    /* Enable MCU Wake-Up by LPUART */
    LPUART_EnableWakeUpStop(ENABLE);
#ifdef _STOP2_WAKEUP_DEBUG_
    AFEC_Configuration1();
#endif
    /* Enter STOP2 Mode */
    PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI, PWR_CTRL3_RAM1RET | PWR_CTRL3_RAM2RET);
    /* ... STOP2 Mode ... */
#ifdef _STOP2_WAKEUP_DEBUG_
    AFEC_Configuration2();
#endif   
    /* Wake Up based on a Programmed 4-Byte Frame Match successful */
    LPUART_EnableWakeUpStop(DISABLE);    
    /* Output a message on Hyperterminal using printf function */
    printf("\n\rA programmed 4-Byte frame match wake-up successful\n\r");

    while (1)
    {
    }
}

/**
 * @brief  Configures LPUART clock.
 * @param  LPUART_CLK_SRC: specifies the LPUART clock source.
 */
void RCC_Configuration(uint32_t LPUART_CLK_SRC)
{
    switch(LPUART_CLK_SRC)
    {
        case RCC_LPUARTCLK_SRC_LSE:
        {
            RCC_EnableAPB1PeriphClk (RCC_APB1_PERIPH_PWR, ENABLE); 
            PWR->CTRL1 |= PWR_CTRL1_DRBP;
            /* Configures the External Low Speed oscillator (LSE) */
            RCC_ConfigLse(RCC_LSE_ENABLE,0x1FF);
            while (RCC_GetFlagStatus(RCC_LDCTRL_FLAG_LSERD) == RESET)
            {
            }
            /* Specifies the LPUART clock source, LSE selected as LPUART clock */
            RCC_ConfigLPUARTClk(RCC_LPUARTCLK_SRC_LSE);
        }
        break;
        case RCC_LPUARTCLK_SRC_HSI:
        {
            /* Configures the High Speed Internal RC clock (HSI) */
            RCC_ConfigHsi(RCC_HSI_ENABLE);
            while (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSIRDF) == RESET)
            {
            }
            /* Specifies the LPUART clock source, HSI selected as LPUART clock */
            RCC_ConfigLPUARTClk(RCC_LPUARTCLK_SRC_HSI);
        }
        break;
        case RCC_LPUARTCLK_SRC_SYSCLK:
        {
            /* Specifies the LPUART clock source, SYSCLK selected as LPUART clock */
            RCC_ConfigLPUARTClk(RCC_LPUARTCLK_SRC_SYSCLK);
        }
        break;
        default:
        {
            /* Specifies the LPUART clock source, APB1 selected as LPUART clock */
            RCC_ConfigLPUARTClk(RCC_LPUARTCLK_SRC_APB1);
        }
        break;
    }   
    
    /* Enable LPUART Clock */
    RCC_EnableRETPeriphClk(RCC_RET_PERIPH_LPUART, ENABLE);
}  

/**
 * @brief  Configures the different GPIO ports.
 */
void GPIO_Configuration(void)
{
    GPIO_InitType GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(LPUART_GPIO_CLK, ENABLE);       

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure LPUART Tx as alternate function push-pull */
    GPIO_InitStructure.Pin            = LPUART_TxPin;
    GPIO_InitStructure.GPIO_Mode      = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = LPUART_Tx_GPIO_AF;
    GPIO_InitPeripheral(LPUART_GPIO, &GPIO_InitStructure);

    /* Configure LPAURT Rx as alternate function push-pull and pull-up */
    GPIO_InitStructure.Pin            = LPUART_RxPin;  
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = LPUART_Rx_GPIO_AF;    
    GPIO_InitPeripheral(LPUART_GPIO, &GPIO_InitStructure);
}

/**
 * @brief  Configures the nested vectored interrupt controller.
 */
void NVIC_Configuration(void)
{
    NVIC_InitType NVIC_InitStructure;

    /* Configure the NVIC Preemption Priority Bits */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* Enable the LPUART Wakeup Interrupt through EXTI line 23 */
    NVIC_InitStructure.NVIC_IRQChannel                   = LPUART_WKUP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  Configure EXTI_LINE23 as EXTI_Line and set the Priority.
 */
void EXTI_Configuration(void)
{    
    EXTI_InitType EXTI_InitStructure;

    /* Configure NVIC */
    NVIC_Configuration();
    
    EXTI_InitStruct(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line	  = EXTI_LINE23;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
}

#ifdef _STOP2_WAKEUP_DEBUG_
void SetSysClock_HSE(void)
{	
    RCC_DeInit();

    RCC_ConfigHse(RCC_HSE_ENABLE);
    while (RCC_GetFlagStatus(RCC_CTRL_FLAG_HSERDF) == RESET)
    {
    }

    FLASH_SetLatency(FLASH_LATENCY_0);

    /* HCLK = SYSCLK */
    RCC->CFG |= (uint32_t)RCC_CFG_AHBPRES_DIV1;
    /* PCLK2 = HCLK/2 */
    RCC->CFG |= (uint32_t)RCC_CFG_APB2PRES_DIV1;
    /* PCLK1 = HCLK/4 */
    RCC->CFG |= (uint32_t)RCC_CFG_APB1PRES_DIV1;

    RCC_ConfigSysclk(RCC_SYSCLK_SRC_HSE);
    while(RCC_GetSysclkSrc() != 0x08)
    {
    }		
}

void AFEC_Configuration1(void)
{
//    SetSysClock_HSE(); //flash read latency=0
    TRIMR0 = AFEC->TRIMR0;
    TRIMR1 = AFEC->TRIMR1;
    TRIMR2 = AFEC->TRIMR2;
    TRIMR3 = AFEC->TRIMR3;
    TRIMR4 = AFEC->TRIMR4;
    TRIMR5 = AFEC->TRIMR5;
    TRIMR6 = AFEC->TRIMR6;
    TRIMR7 = AFEC->TRIMR7;
    TRIMR8 = AFEC->TRIMR8;
}

void AFEC_Configuration2(void)
{
    MSICAL = (RCC->CTRLSTS & 0x7f80) >> 7;
    MSITRIM = (0x48 - MSICAL) & 0xff;
    RCC->CTRLSTS &= 0xFF807FFF;
    RCC->CTRLSTS |= MSITRIM << 15;
    AFEC->TRIMR0 = TRIMR0;
    AFEC->TRIMR1 = TRIMR1;
    AFEC->TRIMR2 = TRIMR2;
    AFEC->TRIMR3 = TRIMR3;
    AFEC->TRIMR4 = TRIMR4;
    AFEC->TRIMR5 = TRIMR5;
    AFEC->TRIMR6 = TRIMR6;
    AFEC->TRIMR7 = TRIMR7;
    AFEC->TRIMR8 = TRIMR8;
    RCC->CTRLSTS |= 0x1E8000;
}
#endif

/**
 * @brief  Inserts a delay time.
 * @param nCount specifies the delay time length.
 */
void Delay(__IO uint32_t nCount)
{
    /* Decrement nCount value */
    for (; nCount != 0; nCount--)
        ;
}

/* retarget the C library printf function to the LPUART */
int fputc(int ch, FILE* f)
{
    LPUART_SendData((uint8_t)ch);
    while (LPUART_GetFlagStatus(LPUART_FLAG_TXC) == RESET)
        ;
    LPUART_ClrFlag(LPUART_FLAG_TXC);      

    return (ch);
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

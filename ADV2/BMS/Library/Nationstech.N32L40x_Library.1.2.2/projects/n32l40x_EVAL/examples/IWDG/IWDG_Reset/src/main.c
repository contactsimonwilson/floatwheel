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
#include "n32l40x.h"
#include "main.h"
#include "log.h"
#include "User_LED_Config.h"

/** @addtogroup n32l40x_StdPeriph_Examples
 * @{
 */

/** @addtogroup
 * @{
 */

#define LSI_TIM_MEASURE

__IO uint32_t TimingDelay = 0;
__IO uint32_t LsiFreq     = 40000;
extern __IO uint16_t CaptureNumber;

/**
 * @brief  Inserts a delay time.
 * @param nTime specifies the delay time length, in milliseconds.
 */
void Delayms(__IO uint32_t nTime)
{
    TimingDelay = nTime;
    while (TimingDelay != 0);
}


#ifdef LSI_TIM_MEASURE
/**
 * @brief  Configures TIM9 to measure the LSI oscillator frequency.
 */
void TIM9_ConfigForLSI(void)
{
    NVIC_InitType NVIC_InitStructure;
    TIM_ICInitType TIM_ICInitStructure;
    /* Enable TIM9 clocks */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM9, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    /* Enable the TIM9 Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = TIM9_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    /* Configure TIM9 prescaler */
    TIM_ConfigPrescaler(TIM9, 0, TIM_PSC_RELOAD_MODE_IMMEDIATE);
    /* Connect internally the TM9_CH3 PB14 Input Capture to the LSI clock output */
    GPIO_ConfigPinRemap(GPIOB_PORT_SOURCE, GPIO_PIN_SOURCE14, GPIO_AF1_TIM9);
    /* TIM9 configuration: Input Capture mode
       The LSI oscillator is connected to TIM9 CH3
       The Rising edge is used as active edge,
       The TIM9 CCDAT3 is used to compute the frequency value */
    TIM_ICInitStructure.Channel     = TIM_CH_3;
    TIM_ICInitStructure.IcPolarity  = TIM_IC_POLARITY_RISING;
    TIM_ICInitStructure.IcSelection = TIM_IC_SELECTION_DIRECTTI;
    TIM_ICInitStructure.IcPrescaler = TIM_IC_PSC_DIV8;
    TIM_ICInitStructure.IcFilter    = 0;
    TIM_ICInit(TIM9, &TIM_ICInitStructure);
    TIM9->CTRL1 |= TIM_CTRL1_C3SEL;
    /* TIM9 Counter Enable */
    TIM_Enable(TIM9, ENABLE);
    /* Reset the flags */
    TIM9->STS = 0;
    /* Enable the CC3 Interrupt Request */
    TIM_ConfigInt(TIM9, TIM_INT_CC3, ENABLE);
}
#endif



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
    log_init();
    LEDInit(LED1_PORT,LED1_PIN);
    LEDInit(LED2_PORT,LED2_PIN);
    LEDOff(LED1_PORT,LED1_PIN);
    LEDOff(LED2_PORT,LED2_PIN);
    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
       /* Capture error */
       while (1);
    }
    /* Check if the system has resumed from IWDG reset */
    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_IWDGRSTF) != RESET)
    {
       /* IWDGRST flag set */
       /* Turn on LED1 */
       LEDOn(LED1_PORT,LED1_PIN);
       log_info("\r\n IWDG Reset! \r\n");
       /* Clear reset flags */
       RCC_ClrFlag();
    }
    else
    {
       /* IWDGRST flag is not set */
       /* Turn off LED1 */
       LEDOff(LED1_PORT,LED1_PIN);
       log_info("\r\n IWDG Not Reset! \r\n");
    }
#ifdef LSI_TIM_MEASURE
    /* Enable the LSI OSC */
    RCC_EnableLsi(ENABLE);
    /* Wait till LSI is ready */
    while (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_LSIRD) == RESET)
    {
    }
    /* TIM Configuration -------------------------------------------------------*/
    TIM9_ConfigForLSI();
    /* Wait until the TIM9 get 3 LSI edges */
    while (CaptureNumber != 3)
    {
    }
    /* Disable TIM9 CC3 Interrupt Request */
    TIM_ConfigInt(TIM9, TIM_INT_CC3, DISABLE);
#endif
    /* IWDG timeout equal to 250 ms (the timeout may varies due to LSI frequency dispersion) */
    /* Enable write access to IWDG_PR and IWDG_RLR registers */
    IWDG_WriteConfig(IWDG_WRITE_ENABLE);
    /* IWDG counter clock: LSI/32 */
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV32);
    /* Set counter reload value to obtain 250ms IWDG TimeOut.
       Counter Reload Value = 250ms/IWDG counter clock period
                            = 250ms / (LSI/32)
                            = 0.25s / (LsiFreq/32)
                            = LsiFreq/(32 * 4)
                            = LsiFreq/128 */
    IWDG_CntReload(LsiFreq / 128);
    /* Reload IWDG counter */
    IWDG_ReloadKey();
    /* Enable IWDG (the LSI oscillator will be enabled by hardware) */
    IWDG_Enable();
    while (1)
    {
       /* Toggle LED2 */
       LEDBlink(LED2_PORT, LED2_PIN);
       /* Insert 249 ms delay */
       Delayms(249);
       /* Reload IWDG counter */
       IWDG_ReloadKey();
    }
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

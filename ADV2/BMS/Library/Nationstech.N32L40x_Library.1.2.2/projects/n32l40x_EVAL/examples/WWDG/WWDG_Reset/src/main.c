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
#include "n32l40x.h"
#include "User_LED_Config.h"

/** @addtogroup n32l40x_StdPeriph_Examples
 * @{
 */

/** @addtogroup WWDG_Reset
 * @{
 */

__IO uint32_t TimingDelay = 0;

/**
 * @brief  Inserts a delay time.
 * @param nTime specifies the delay time length, in milliseconds.
 */
void Delay(__IO uint32_t nTime)
{
    TimingDelay = nTime;
    while (TimingDelay != 0)
    {
    }
}

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
    RCC_ClocksType temp;
    DBG_ConfigPeriph(DBG_WWDG_STOP,ENABLE);
    LEDInit(LED1_PORT,LED1_PIN);
    LEDInit(LED2_PORT,LED2_PIN);
    /* Check if the system has resumed from WWDG reset */
    if (RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_WWDGRSTF) != RESET)
    {
      /* WWDGRST flag set */
      /* Turn on LED1 */
      LEDOn(LED1_PORT,LED1_PIN);
      /* Clear reset flags */
      RCC_ClrFlag();
    }
    else
    {
      /* WWDGRST flag is not set */
      /* Turn off LED1 */
      LEDOff(LED1_PORT,LED1_PIN);
    }
    /* Setup SysTick Timer for 1 msec interrupts  */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
      /* Capture error */
      while (1);
    }
    /* WWDG configuration */
    /* Enable WWDG clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_WWDG, ENABLE);
    RCC_GetClocksFreqValue(&temp);
    /* WWDG clock counter = (PCLK1(16MHz)/4096)/8 = 488 Hz (~2049 us)  */
    WWDG_SetPrescalerDiv(WWDG_PRESCALER_DIV8);
    /* Set Window value to 80; WWDG counter should be refreshed only when the counter
      is below 80 (and greater than 64) otherwise a reset will be generated */
    WWDG_SetWValue(80);
    /*Enable WWDG and set counter value to 127, WWDG timeout = ~2049 us * (127-63) = 131.136 ms
      In this case the refresh window is: ~2049 us * (127-80) = 96.3 ms < refresh window < ~2049us * 64 = 131.136 ms*/
    WWDG_Enable(127);
    while (1)
    {
      /* Toggle LED2 */
      LEDBlink(LED2_PORT,LED2_PIN);
      Delay(110);
      /* Update WWDG counter */
      WWDG_SetCnt(127);
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

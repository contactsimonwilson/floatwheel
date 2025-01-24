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
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "n32l40x_flash.h"

__IO uint8_t PrevXferComplete = 1;
__IO uint32_t TimingDelay     = 0;
u8 key_buffer[8]              = {0};
u8* Ep1DataPtr                = 0;
extern u8* EpOutDataPtrTmp;
extern u8* EpInDataPtrTmp;
/** @addtogroup DAC_OneChanneloutputNoiseWave
 * @{
 */

void Delay(__IO uint32_t nCount);

/**
 * @brief  Main program.
 */
int main(void)
{
    Cfg_KeyIO();
    Set_System();

    if(USB_Config(SYSCLK_VALUE_48MHz) == SUCCESS)
    {
        USB_Init();

        while (bDeviceState != CONFIGURED)
        {
        }

        while (1)
        {
            if (PrevXferComplete)
            {
                if ((GPIOC->PID & GPIO_PIN_7) == 0)
                {
                    key_buffer[2] = 0x04;
                    if (key_buffer[2] != 0)
                    {
                        PrevXferComplete = 0;
                        Ep1DataPtr       = key_buffer;
                        USB_SilWrite(EP1_IN, Ep1DataPtr, 8);
                        Ep1DataPtr    = EpInDataPtrTmp;
                        key_buffer[2] = 0;
                    }
                }
            }
        }
    }
    
    while(1);
}

/**
 * @brief  delay count.
 * @param  nCount: delay count cycle.
 */
void Delay(__IO uint32_t nCount)
{
    TimingDelay = nCount;
    for (; nCount != 0; nCount--)
        ;
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
* @param   expr: If expr is false, it calls assert_failed function which reports
 *         the name of the source file and the source line number of the call
 *         that failed. If expr is true, it returns no value.
 * @param  file: pointer to the source file name.
 * @param  line: assert_param error line source number.
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

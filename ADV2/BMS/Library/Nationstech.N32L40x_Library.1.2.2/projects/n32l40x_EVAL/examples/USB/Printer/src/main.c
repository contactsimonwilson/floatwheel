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


__IO uint8_t PrevXferComplete = 1;
__IO uint32_t TimingDelay     = 0;
u8 key_buffer[8]              = {0};
u8* Ep1DataPtr                = 0;


uint8_t m_tx_flag;
uint8_t m_rx_flag;

uint8_t m_tx_len;
uint8_t m_rx_len;

uint8_t m_tx_buf[64];
uint8_t m_rx_buf[64];


extern u8* EpOutDataPtrTmp;
extern u8* EpInDataPtrTmp;


/** @addtogroup DAC_OneChanneloutputNoiseWave
 * @{
 */

/**
 * @brief   Inserts a delay time.
 * @param   nCount: specifies the delay time length.
 */
void Delay(__IO uint32_t nCount)
{
    TimingDelay = nCount;
    for (; nCount != 0; nCount--);
}

/**
 * @brief   Inserts a delay time.
 * @param   ms: delay time.
 */
void m_delay_ms(uint32_t ms)
{
    for(; ms!=0; ms--)
    {
        Delay(14400);
    }
}

/**
 * @brief  send bulk data
 * @param   buf: data pointer.
 * @param   len: data length.
 * @return  send SUCCEED or FAILED.
 */
uint8_t m_BulkData_send(uint8_t *buf, uint8_t len)
{
    uint8_t i, timeout = 0;

    while(m_tx_flag)
    {
        if(++timeout >= 10)
        {
            return 0xff;   // failed
        }
        Delay(1440);
    }

    for(i=0; i<len; i++)
    {
        m_tx_buf[i] = buf[i];
    }

    m_tx_flag = 1;
    m_tx_len = len;
    return 0x00;        //success
}

/**
 * @brief  Main program.
 */
int main(void)
{
    Set_System();

    if(USB_Config(SYSCLK_VALUE_48MHz) == SUCCESS)
    {
        USB_Init();

        while (bDeviceState != CONFIGURED)
        {
        }
    }

    while (1)
    {
        if (m_rx_flag)
        {
            m_rx_flag = 0;
            m_BulkData_send(m_rx_buf, m_rx_len);
        }
    }
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

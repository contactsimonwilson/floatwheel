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
#include <stdio.h>
#include <stdint.h>
#include "User_LED_Config.h"
#include "User_Key_Config.h"
#include "User_Sysclock_Config.h"
#include "log.h"
#include "main.h"

/**
 * @brief  Delay function.
 *     @arg nCount
 */
void delay(vu32 nCount)
{
    vu32 index = 0;
    for (index = (34000 * nCount); index != 0; index--)
    {
    }
}


/**
 * @brief  SRAM2 Reset function.
 */
void SRAM2_Reset(void)
{
    uint8_t* p_sram2=(uint8_t*)SRAM2_START_ADDR;
    uint32_t i =0;
    for(i=0;i<SRAM2_SIZE;i++)
    {
        *(p_sram2+i) = 0;
    }
}


/**
 * @brief  Main program.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32l40x_xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32l40x.c file
       */
    log_init();
    log_info("\r\n MCU Reset! \r\n");
    LEDInit(LED1_PORT,LED1_PIN);
    LEDOff(LED1_PORT,LED1_PIN);
    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    /* Initialize Key button Interrupt to wakeUp stop */
    KeyInputExtiInit(KEY_INPUT_PORT, KEY_INPUT_PIN);
    /*  Enable the DBG_STOP to keep debug in low power  */
    DBG_ConfigPeriph(DBG_STOP, ENABLE);
    while (1)
    {
       /* Insert a long delay */
       delay(120);
       log_info("\r\n MCU Prepare Enter Stop2 Mode Core Stop Run \r\n");
       /* when system clock div4 is selected,advise that the system clock configure as SYSCLK_PLLSRC_HSEDIV2,
        when exit the stop2,system clock can configure back as SYSCLK_PLLSRC_HSE_PLLDIV2 */
       SetSysClockToPLL(SystemCoreClock,SYSCLK_PLLSRC_HSEDIV2);
       /* Request to enter STOP2 mode,and config SRAM1 retain*/
       PWR_EnterSTOP2Mode(PWR_STOPENTRY_WFI,PWR_CTRL3_RAM1RET); 
       /*Reset SRAM2 when wake up from stop2 mode*/
       SRAM2_Reset();
       /*multiply System Clock Frequency*/
       SetSysClockToPLL(SystemCoreClock,SYSCLK_PLLSRC_HSE_PLLDIV2);
       log_init();
       log_info("\r\n MCU Run In Run Mode Sysclock From PLL(64MHz) \r\n");
       LEDBlink(LED1_PORT,LED1_PIN);
    }
}

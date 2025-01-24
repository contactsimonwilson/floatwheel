/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include <stdio.h>
#include "main.h"
#include "smartcard.h"
uint8_t F_HotReset = 0;

static void System_Init(void)
{
    log_init();
    delay_init();
    log_info("System Init Finish!\r\n");
}
void SC__HotReset_handle(void)
{
    SC_InitStructure SC_InitCfg;
    SC_State SCState = SC_POWER_OFF;
    SC_ADPU_Commands SC_ADPU;
    SC_ADPU_Responce SC_Responce;
    USART_InitType USART_InitStructure;
    RCC_ClocksType RCC_ClocksStatus;
    F_HotReset = 1;
    log_info("USARTx Smart_Card Hot_Reset\r\n");
    SC_Reset(Bit_RESET);
    delay_xms(10);
    SC_Reset(Bit_SET);
    SC_InitCfg.Clk_Div   = 4;    //SC_USART Clock set to (PCLK1 = SC_USART MHZ / Clk_Div)MHz 
    SC_InitCfg.GT        = 16;
    SC_InitCfg.StopBits  = 3;
    SC_InitCfg.Parity    = 1;
    SC_InitCfg.NackEn    = 0;    // 0 - Disable NACK, 1 - Enable NACK
    SCState = SC_POWER_ON;
    SC_APDU_Init(&SC_ADPU, 0x00, SC_GET_A2R, 0x00, 0x00, 0x00, NULL, NULL);
    RCC_GetClocksFreqValue(&RCC_ClocksStatus);
    /*reset BaudRate*/
    USART_InitStructure.BaudRate            = RCC_ClocksStatus.Pclk1Freq / (372 * ((SC_USART->GTP & (uint16_t)0x00FF) * 2));
    USART_InitStructure.WordLength          = USART_WL_9B;
    USART_InitStructure.StopBits            = USART_STPB_1_5;
    USART_InitStructure.Parity              = USART_PE_EVEN;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_Init(SC_USART, &USART_InitStructure);
    while(SCState != SC_ACTIVE_ON_T0)
    {
        SC_Handler(&SCState, &SC_ADPU, &SC_Responce, &SC_InitCfg);
    }
    log_info("USARTx Smart_Card Hot_Reset Finish\r\n");
    F_HotReset = 0;
}
void Test_PSAM(void)
{
    int i = 0;
    SC_InitStructure SC_InitCfg;
    SC_State SCState = SC_POWER_OFF;
    SC_ADPU_Commands SC_ADPU;
    SC_ADPU_Responce SC_Responce;
    log_info("USARTx Smart_Card Test Start\r\n");
    SC_InitCfg.Clk_Div   = 4;    //SC_USART Clock set to (PCLK1 = SC_USART MHZ / Clk_Div) MHz
    SC_InitCfg.GT        = 16;
    SC_InitCfg.StopBits  = 3;
    SC_InitCfg.Parity    = 1;
    SC_InitCfg.NackEn    = 0;    // 0 - Disable NACK, 1 - Enable NACK
    SCState = SC_POWER_ON;
    SC_APDU_Init(&SC_ADPU, 0x00, SC_GET_A2R, 0x00, 0x00, 0x00, NULL, 0);
    while(SCState != SC_ACTIVE_ON_T0)
    {
        SC_Handler(&SCState, &SC_ADPU, &SC_Responce, &SC_InitCfg);
    }
    /* Apply the Procedure Type Selection (PTS) */
    SC_PTSConfig();
    SC_APDU_Init(&SC_ADPU, 0x00, 0x84, 0x00, 0x00, 0x00, NULL, 8);
    SC_Handler(&SCState, &SC_ADPU, &SC_Responce, &SC_InitCfg);
    for(i = 0; i < SC_ADPU.Body.LE; i++)
    {
        log_info("\r\n SC_Responce.Data[%d] = 0x%02x \r\n", i, SC_Responce.Data[i]);
    }
    printf("\r\n SC_Responce.SW1 = 0x%02x \r\n", SC_Responce.SW1);
    printf("\r\n SC_Responce.SW2 = 0x%02x \r\n", SC_Responce.SW2);
    if((SC_Responce.SW1 == 0x90) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard command normally completed \r\n");
        log_info("get rand success!\r\n");
        for(i = 0; i < SC_ADPU.Body.LE; i++)
        {
            printf("%02x ", SC_Responce.Data[i]);
        }
        log_info("\r\n");
    }
    else if((SC_Responce.SW1 == 0x6E) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard CLA not supported \r\n");
    }
    else if((SC_Responce.SW1 == 0x6D) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard CLA supported, but INS not programmed or invalid \r\n");
    }
    else if((SC_Responce.SW1 == 0x6B) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard CLA INS supported, but P1 P2 incorrect \r\n");
    }
    else if((SC_Responce.SW1 == 0x67) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard CLA INS P1 P2 supported, but P3 incorrect \r\n");
    }
    else if((SC_Responce.SW1 == 0x6F) && (SC_Responce.SW2 == 0x00))
    {
        log_info("\r\n SmartCard command not supported and no precise diagnosis given \r\n");
    }
    SC__HotReset_handle();
    SC_DeInit();
}
/**
 * @brief  Main program
 */
int main(void)
{
    System_Init();
	  Test_PSAM();
	  log_info("PSAM test finish\r\n");
    while (1)
    {
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

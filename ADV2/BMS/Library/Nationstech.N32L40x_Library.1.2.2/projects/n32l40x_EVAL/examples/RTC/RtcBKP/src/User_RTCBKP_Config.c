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
 * @file User_RTCBKP_Config.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l40x.h"
#include "n32l40x_rtc.h"
#include "User_RTCBKP_Config.h"

uint32_t Write_Backup_Datas[BACKUP_REGISTER_SIZE]={0x12345678,0x12345679,0x1234567A,0x1234567B,0x1234567C,\
                                                   0x1234567D,0x1234567E,0x1234567F,0x12345680,0x12345681,\
                                                   0x12345682,0x12345683,0x12345684,0x12345685,0x12345686,\
                                                   0x12345687,0x12345688,0x12345689,0x1234568A,0x1234568B};

uint16_t BKP_Datas[BACKUP_REGISTER_SIZE]={BKP_DAT1, BKP_DAT2, BKP_DAT3, BKP_DAT4, BKP_DAT5, \
                                          BKP_DAT6, BKP_DAT7, BKP_DAT8, BKP_DAT9, BKP_DAT10,\
                                          BKP_DAT11,BKP_DAT12,BKP_DAT13,BKP_DAT14,BKP_DAT15,\
                                          BKP_DAT16,BKP_DAT17,BKP_DAT18,BKP_DAT19,BKP_DAT20};

uint32_t Read_Backup_Datas[BACKUP_REGISTER_SIZE]={0x00};

/** @addtogroup BKP
 * @brief BKP driver modules
 * @{
 */

/**
 * @brief RTC Backup Initialize.
 */
void User_RTCBKP_Init(void)
{
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    /* Allow access to RTC */
    PWR_BackupAccessEnable(ENABLE);
    RCC_EnableRtcClk(DISABLE);
    /* Enable the LSE OSC32_IN PC14 
       LSI is turned off here to ensure that only one clock is turned on */
    RCC_EnableLsi(DISABLE);  
    RCC_ConfigLse(RCC_LSE_ENABLE,0x1FF);
    while (RCC_GetFlagStatus(RCC_LDCTRL_FLAG_LSERD) == RESET){}
    RCC_ConfigRtcClk(RCC_RTCCLK_SRC_LSE);
    /* Enable the RTC Clock */
    RCC_EnableRtcClk(ENABLE);
    RTC_WaitForSynchro();
}

/**
 * @brief  Writes user data to the specified Data Backup Register.
 * @param BKP_DAT specifies the Data Backup Register.
 *   This parameter can be BKP_DATx where x:[1, 20]
 * @param Data data to write
 */
void BKP_WriteBkpData(uint32_t BKP_DAT, uint32_t Data)
{
    __IO uint32_t tmp = 0;
    /* Check the parameters */
    assert_param(IS_BKP_DAT(BKP_DAT));
    tmp = (uint32_t)&RTC->BKP1R;
    tmp += BKP_DAT;
    *(__IO uint32_t*)tmp = Data;
}

/**
 * @brief  Reads data from the specified Data Backup Register.
 * @param BKP_DAT specifies the Data Backup Register.
 *   This parameter can be BKP_DATx where x:[1, 20]
 * @return The content of the specified Data Backup Register
 */
uint32_t BKP_ReadBkpData(uint32_t BKP_DAT)
{
    __IO uint32_t tmp = 0;
    uint32_t value = 0;
    /* Check the parameters */
    assert_param(IS_BKP_DAT(BKP_DAT));
    tmp = (uint32_t)&RTC->BKP1R;
    tmp += BKP_DAT;
    value = (*(__IO uint32_t*)tmp);
    return value;
}


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
 * @file n32l43x_bkp.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __USER_RTCBKP_CONFIG_H__
#define __USER_RTCBKP_CONFIG_H__


/** @addtogroup Data_Backup_Register
 * @{
 */

#define  BKP_DAT1     ((uint16_t)0x0000)
#define  BKP_DAT2     ((uint16_t)0x0004)
#define  BKP_DAT3     ((uint16_t)0x0008)
#define  BKP_DAT4     ((uint16_t)0x000C)
#define  BKP_DAT5     ((uint16_t)0x0010)
#define  BKP_DAT6     ((uint16_t)0x0014)
#define  BKP_DAT7     ((uint16_t)0x0018)
#define  BKP_DAT8     ((uint16_t)0x001C)
#define  BKP_DAT9     ((uint16_t)0x0020)
#define  BKP_DAT10    ((uint16_t)0x0024)
#define  BKP_DAT11    ((uint16_t)0x0028)
#define  BKP_DAT12    ((uint16_t)0x002C)
#define  BKP_DAT13    ((uint16_t)0x0030)
#define  BKP_DAT14    ((uint16_t)0x0034)
#define  BKP_DAT15    ((uint16_t)0x0038)
#define  BKP_DAT16    ((uint16_t)0x003C)
#define  BKP_DAT17    ((uint16_t)0x0040)
#define  BKP_DAT18    ((uint16_t)0x0044)
#define  BKP_DAT19    ((uint16_t)0x0048)
#define  BKP_DAT20    ((uint16_t)0x004C)

#define  IS_BKP_DAT(DAT)                                                                                    \
             (((DAT) == BKP_DAT1)  || ((DAT) == BKP_DAT2)  || ((DAT) == BKP_DAT3)  || ((DAT) == BKP_DAT4)   \
           || ((DAT) == BKP_DAT5)  || ((DAT) == BKP_DAT6)  || ((DAT) == BKP_DAT7)  || ((DAT) == BKP_DAT8)   \
           || ((DAT) == BKP_DAT9)  || ((DAT) == BKP_DAT10) || ((DAT) == BKP_DAT11) || ((DAT) == BKP_DAT12)  \
           || ((DAT) == BKP_DAT13) || ((DAT) == BKP_DAT14) || ((DAT) == BKP_DAT15) || ((DAT) == BKP_DAT16)  \
           || ((DAT) == BKP_DAT17) || ((DAT) == BKP_DAT18) || ((DAT) == BKP_DAT19) || ((DAT) == BKP_DAT20) )

#define  BACKUP_REGISTER_SIZE             20
#define  USER_WRITE_BKP_DAT1_DATA         0xA5A5

extern uint16_t BKP_Datas[BACKUP_REGISTER_SIZE];
extern uint32_t Write_Backup_Datas[BACKUP_REGISTER_SIZE];
extern uint32_t Read_Backup_Datas[BACKUP_REGISTER_SIZE];

extern void BKP_WriteBkpData(uint32_t BKP_DAT, uint32_t Data);
extern uint32_t BKP_ReadBkpData(uint32_t BKP_DAT);
extern void User_RTCBKP_Init(void);


#endif /* __USER_RTCBKP_CONFIG_H__ */
/**
 * @}
 */


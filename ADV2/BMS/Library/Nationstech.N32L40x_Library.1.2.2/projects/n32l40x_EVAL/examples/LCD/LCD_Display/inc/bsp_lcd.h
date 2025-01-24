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
 * @file bsp_lcd.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GLASS_LCD_H
#define _GLASS_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup BSP
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup BSP_LCD_Exported_Types Exported Types
  * @{
  */

/**
  * @brief LCD Glass point
  * Warning: element values correspond to LCD Glass point.
  */
#define POINT_OFF   (0U)
#define POINT_ON    (1U)

/**
  * @brief LCD special mark config type
  * Warning: none
  */
#define CLEAR_MARK  (0U)
#define SET_MARK    (1U)

/**
  * @brief Flag of LCD special mark
  * Warning: Just for LCD GDC0689TP-11
  */
#define LCD_MARK_T1_REPAIR                  (0x00000001)

#define LCD_MARK_W1_BATLEVEL_OFF            (0x00000002)
#define LCD_MARK_W2_BATLEVEL_1_4            (0x00000004)
#define LCD_MARK_W3_BATLEVEL_1_2            (0x00000008)
#define LCD_MARK_W4_BATLEVEL_3_4            (0x00000010)
#define LCD_MARK_W5_BATLEVEL_FULL           (0x00000020)

#define LCD_MARK_L1_SIGNAL_LEVEL1           (0x00000040)
#define LCD_MARK_L2_SIGNAL_LEVEL2           (0x00000080)
#define LCD_MARK_L3_SIGNAL_LEVEL3           (0x00000100)
#define LCD_MARK_L4_SIGNAL_LEVEL4           (0x00000200)

#define LCD_MARK_COL1_LITTLE_COL            (0x00000400)
#define LCD_MARK_COL2_BIG_COL_1ST           (0x00000800)
#define LCD_MARK_COL3_BIG_COL_2ND           (0x00001000)

#define LCD_MARK_S1_UNIT_MV                 (0x00002000)
#define LCD_MARK_S2_UNIT_NM                 (0x00004000)
#define LCD_MARK_S3_UNIT_KG                 (0x00008000)
#define LCD_MARK_S4_UNIT_G                  (0x00010000)
#define LCD_MARK_S5_UNIT_MM                 (0x00020000)
#define LCD_MARK_S6_UNIT_UE                 (0x00040000)
#define LCD_MARK_S7_UNIT_KPA                (0x00080000)
#define LCD_MARK_S8_UNIT_MPA                (0x00100000)
#define LCD_MARK_S9_UNIT_OC                 (0x00200000)

#define LCD_MARK_MASK       (0x003FFFFF)
#define MAX_LCD_MARK        (22)

/**
  * @brief Constant of LCD char('8' seven segment)
  * Warning: Just for LCD GDC0689TP-11
  */
#define MIN_LCD_CHAR            (1)
#define MAX_LCD_CHAR            (10)

#define LCD_BIGCHAR_START       (5)
#define LCD_BIGCHAR_NOPOINT     (10)
#define LCD_LITTLECHAR_NOPOINT  (4)

#define LCD_COL1_LITTLE_CHAR_POS    (2)
#define LCD_COL2_BIG1_CHAR_POS      (6)
#define LCD_COL3_BIG2_CHAR_POS      (8)

/**
  * @brief com number of LCD special mark,0~3 specifies COM1~4 in GDC0689TP-11 spec
  * Warning: Just for LCD GDC0689TP-11
  */
#define LCD_COMNUM_T1_REPAIR                (2U)

#define LCD_COMNUM_W1_BATLEVEL_OFF          (3U)
#define LCD_COMNUM_W2_BATLEVEL_1_4          (3U)
#define LCD_COMNUM_W3_BATLEVEL_1_2          (2U)
#define LCD_COMNUM_W4_BATLEVEL_3_4          (1U)
#define LCD_COMNUM_W5_BATLEVEL_FULL         (0U)

#define LCD_COMNUM_L1_SIGNAL_LEVEL1         (0U)
#define LCD_COMNUM_L2_SIGNAL_LEVEL2         (1U)
#define LCD_COMNUM_L3_SIGNAL_LEVEL3         (2U)
#define LCD_COMNUM_L4_SIGNAL_LEVEL4         (3U)

#define LCD_COMNUM_COL1_LITTLE_COL          (0U)
#define LCD_COMNUM_COL2_BIG_COL_1ST         (0U)
#define LCD_COMNUM_COL3_BIG_COL_2ND         (1U)

#define LCD_COMNUM_S1_UNIT_MV               (3U)
#define LCD_COMNUM_S2_UNIT_NM               (2U)
#define LCD_COMNUM_S3_UNIT_KG               (1U)
#define LCD_COMNUM_S4_UNIT_G                (0U)
#define LCD_COMNUM_S5_UNIT_MM               (0U)
#define LCD_COMNUM_S6_UNIT_UE               (1U)
#define LCD_COMNUM_S7_UNIT_KPA              (2U)
#define LCD_COMNUM_S8_UNIT_MPA              (3U)
#define LCD_COMNUM_S9_UNIT_OC               (3U)

/**
  * @brief Segment number of LCD special mark
  * Warning: Just for LCD GDC0689TP-11
  */
#define LCD_SEGNUM_T1_REPAIR                (18U)

#define LCD_SEGNUM_W1_BATLEVEL_OFF          (18U)
#define LCD_SEGNUM_W2_BATLEVEL_1_4          (19U)
#define LCD_SEGNUM_W3_BATLEVEL_1_2          (19U)
#define LCD_SEGNUM_W4_BATLEVEL_3_4          (19U)
#define LCD_SEGNUM_W5_BATLEVEL_FULL         (19U)

#define LCD_SEGNUM_L1_SIGNAL_LEVEL1         (20U)
#define LCD_SEGNUM_L2_SIGNAL_LEVEL2         (20U)
#define LCD_SEGNUM_L3_SIGNAL_LEVEL3         (20U)
#define LCD_SEGNUM_L4_SIGNAL_LEVEL4         (20U)

#define LCD_SEGNUM_COL1_LITTLE_COL          (23U)
#define LCD_SEGNUM_COL2_BIG_COL_1ST         (18U)
#define LCD_SEGNUM_COL3_BIG_COL_2ND         (18U)

#if (BOARD_TYPE == BOARD_N32G435)
#define LCD_SEGNUM_S1_UNIT_MV               (24U)
#define LCD_SEGNUM_S2_UNIT_NM               (24U)
#define LCD_SEGNUM_S3_UNIT_KG               (24U)
#define LCD_SEGNUM_S4_UNIT_G                (24U)

#elif   (BOARD_TYPE == BOARD_N32L436)
#define LCD_SEGNUM_S1_UNIT_MV               (13U)
#define LCD_SEGNUM_S2_UNIT_NM               (13U)
#define LCD_SEGNUM_S3_UNIT_KG               (13U)
#define LCD_SEGNUM_S4_UNIT_G                (13U)

#else
#error  "Invalid board type"
#endif

#define LCD_SEGNUM_S5_UNIT_MM               (14U)
#define LCD_SEGNUM_S6_UNIT_UE               (14U)
#define LCD_SEGNUM_S7_UNIT_KPA              (14U)
#define LCD_SEGNUM_S8_UNIT_MPA              (14U)
#define LCD_SEGNUM_S9_UNIT_OC               (12U)

/**
  * @brief Segment number of LCD char
  * Warning: Just for LCD GDC0689TP-11
  */
#define LCD_SEGNUM_CHAR1_0                  (33U)
#define LCD_SEGNUM_CHAR1_1                  (34U)

#define LCD_SEGNUM_CHAR2_0                  (35U)
#define LCD_SEGNUM_CHAR2_1                  (0U)

#define LCD_SEGNUM_CHAR3_0                  (1U)
#define LCD_SEGNUM_CHAR3_1                  (6U)

#define LCD_SEGNUM_CHAR4_0                  (5U)
#define LCD_SEGNUM_CHAR4_1                  (23U)

#define LCD_SEGNUM_CHAR5_0                  (21U)
#define LCD_SEGNUM_CHAR5_1                  (36U)

#define LCD_SEGNUM_CHAR6_0                  (37U)
#define LCD_SEGNUM_CHAR6_1                  (38U)

#define LCD_SEGNUM_CHAR7_0                  (2U)
#define LCD_SEGNUM_CHAR7_1                  (3U)

#define LCD_SEGNUM_CHAR8_0                  (4U)
#define LCD_SEGNUM_CHAR8_1                  (22U)

#define LCD_SEGNUM_CHAR9_0                  (10U)
#define LCD_SEGNUM_CHAR9_1                  (39U)

#define LCD_SEGNUM_CHAR10_0                 (11U)
#define LCD_SEGNUM_CHAR10_1                 (12U)

/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup BSP_LCD_Exported_Functions Exported Functions
  * @{
  */
void BSP_LCD_GLASS_Init(void);
void BSP_LCD_GLASS_DisplayString(uint8_t* ptr,uint8_t position);
void BSP_LCD_GLASS_Clear(void);
void BSP_LCD_GLASS_ConfigMark(uint32_t setMark,uint32_t clearMark);
void BSP_LCD_GLASS_ShowAll(void);

    
/**
  * @}
  */


/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif

/************************ (C) COPYRIGHT Nations Technologies Inc *****END OF FILE****/

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
 * @file n32l40x_opamp.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32L40X_OPAMPMP_H__
#define __N32L40X_OPAMPMP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x.h"
#include <stdbool.h>

/** @addtogroup n32l40x_StdPeriph_Driver
 * @{
 */

/** @addtogroup OPAMP
 * @{
 */

/** @addtogroup OPAMP_Exported_Constants
 * @{
 */
typedef enum
{
    OPAMP1 = 0,
    OPAMP2 = 4,
} OPAMPX;

// OPAMP_CS
typedef enum
{
    OPAMP2_CS_TIMSRCSEL_TIM1CC6  = (0x0L << 24), 
    OPAMP2_CS_TIMSRCSEL_TIM8CC6  = (0x1L << 24),
}OPAMP2_CS_TIMSRCSEL;
typedef enum
{
    OPAMP1_CS_VPSSEL_PA1        = (0x00L << 19),
    OPAMP1_CS_VPSSEL_PA5        = (0x01L << 19),
    OPAMP1_CS_VPSSEL_PA4        = (0x02L << 19),
    OPAMP1_CS_VPSSEL_PA7        = (0x03L << 19),    
    OPAMP1_CS_VPSSEL_NC         = (0x04L << 19),
    
    OPAMP2_CS_VPSSEL_PA7        = (0x00L << 19),
    OPAMP2_CS_VPSSEL_PA4        = (0x01L << 19),
    OPAMP2_CS_VPSSEL_PB14       = (0x02L << 19),
    OPAMP2_CS_VPSSEL_PD13       = (0x03L << 19),
    OPAMP2_CS_VPSSEL_NC         = (0x04L << 19),
} OPAMP_CS_VPSSEL;
typedef enum
{
    OPAMP1_CS_VMSSEL_PA3    = (0x00L << 17),
    OPAMP1_CS_VMSSEL_PC5    = (0x01L << 17),
    OPAMP1_CS_VMSSEL_NC     = (0x02L << 17),
    OPAMP1_CS_VMSSEL_FLOAT  = (0x03L << 17),
    
    OPAMP2_CS_VMSSEL_PC5    = (0x00L << 17),
    OPAMP2_CS_VMSSEL_PB0    = (0x01L << 17),
    OPAMP2_CS_VMSSEL_PA5    = (0x02L << 17),
    OPAMP2_CS_VMSSEL_FLOAT  = (0x03L << 17),
} OPAMP_CS_VMSSEL;

typedef enum
{
    OPAMP1_CS_VPSEL_PA1     = (0x00L << 8),
    OPAMP1_CS_VPSEL_PA5     = (0x01L << 8),
    OPAMP1_CS_VPSEL_PA4     = (0x02L << 8),
    OPAMP1_CS_VPSEL_PA7     = (0x03L << 8),
    OPAMP1_CS_VPSEL_NC      = (0x04L << 8),
    
    OPAMP2_CS_VPSEL_PA7     = (0x00L << 8),
    OPAMP2_CS_VPSEL_PA4     = (0x01L << 8),
    OPAMP2_CS_VPSEL_PB14    = (0x02L << 8),
    OPAMP2_CS_VPSEL_PD13    = (0x03L << 8),
    OPAMP2_CS_VPSEL_NC      = (0x04L << 8),
} OPAMP_CS_VPSEL;
typedef enum
{
    OPAMP1_CS_VMSEL_PA3     = (0x00L << 6),
    OPAMP1_CS_VMSEL_PC5     = (0x01L << 6),
    OPAMPx_CS_VMSEL_NC      = (0x02L << 6),
    OPAMPx_CS_VMSEL_FLOAT   = (0x03L << 6),
    
    OPAMP2_CS_VMSEL_PC5     = (0x00L << 6),
    OPAMP2_CS_VMSEL_PB0     = (0x01L << 6),
    OPAMP2_CS_VMSEL_PA5     = (0x02L << 6),
    OPAMP2_CS_VMSEL_FLOAT   = (0x03L << 6),
} OPAMP_CS_VMSEL;
typedef enum
{
    OPAMP_CS_PGA_GAIN_2  = (0x00 << 3),
    OPAMP_CS_PGA_GAIN_4  = (0x01 << 3),
    OPAMP_CS_PGA_GAIN_8  = (0x02 << 3),
    OPAMP_CS_PGA_GAIN_16 = (0x03 << 3),
    OPAMP_CS_PGA_GAIN_32 = (0x04 << 3),
} OPAMP_CS_PGA_GAIN;
typedef enum
{
    OPAMP_CS_EXT_OPAMP = (0x00 << 1),
    OPAMP_CS_PGA_EN    = (0x02 << 1),
    OPAMP_CS_FOLLOW    = (0x03 << 1),
} OPAMP_CS_MOD;

// bit mask
#define OPAMP_CS_EN_MASK           (0x01L << 0)
#define OPAMP_CS_MOD_MASK          (0x03L << 1)
#define OPAMP_CS_PGA_GAIN_MASK     (0x07L << 3)
#define OPAMP_CS_VMSEL_MASK        (0x03L << 6)
#define OPAMP_CS_VPSEL_MASK        (0x07L << 8)
#define OPAMP_CS_CALON_MASK        (0x01L << 11)
#define OPAMP_CS_TSTREF_MASK       (0x01L << 13)
#define OPAMP_CS_CALOUT_MASK       (0x01L << 14)
#define OPAMP_CS_RANGE_MASK        (0x01L << 15)
#define OPAMP_CS_TCMEN_MASK        (0x01L << 16)
#define OPAMP_CS_VMSEL_SECOND_MASK (0x03L << 17)
#define OPAMP_CS_VPSEL_SECOND_MASK (0x07L << 19)
#define OPAMP_CS_OPAMP2_TIMSRCSEL  (0x01L << 24)
/** @addtogroup OPAMP_LOCK
 * @{
 */
#define OPAMP_LOCK_1 0x01L
#define OPAMP_LOCK_2 0x02L
/**
 * @}
 */
/**
 * @}
 */

/**
 * @brief  OPAMP Init structure definition
 */

typedef struct
{
    OPAMP2_CS_TIMSRCSEL Opa2SrcSel; /*only for opa2 can sel,opa1 always TIM1_CC6*/
    
    FunctionalState TimeAutoMuxEn; /*call ENABLE or DISABLE */

    FunctionalState HighVolRangeEn; /*call ENABLE or DISABLE ,low range VDDA < 2.4V,high range VDDA >= 2.4V*/

    OPAMP_CS_PGA_GAIN Gain; /*see @EM_PGA_GAIN */

    OPAMP_CS_MOD Mod; /*see @EM_OPAMP_MOD*/
} OPAMP_InitType;

/** @addtogroup OPAMP_Exported_Functions
 * @{
 */

void OPAMP_DeInit(void);
void OPAMP_StructInit(OPAMP_InitType* OPAMP_InitStruct);
void OPAMP_Init(OPAMPX OPAMPx, OPAMP_InitType* OPAMP_InitStruct);
void OPAMP_Enable(OPAMPX OPAMPx, FunctionalState en);
void OPAMP_SetPgaGain(OPAMPX OPAMPx, OPAMP_CS_PGA_GAIN Gain);
void OPAMP_SetVpSecondSel(OPAMPX OPAMPx, OPAMP_CS_VPSSEL VpSSel);
void OPAMP_SetVmSecondSel(OPAMPX OPAMPx, OPAMP_CS_VMSSEL VmSSel);
void OPAMP_SetVpSel(OPAMPX OPAMPx, OPAMP_CS_VPSEL VpSel);
void OPAMP_SetVmSel(OPAMPX OPAMPx, OPAMP_CS_VMSEL VmSel);
bool OPAMP_IsCalOutHigh(OPAMPX OPAMPx);
void OPAMP_CalibrationEnable(OPAMPX OPAMPx, FunctionalState en);
void OPAMP_SetLock(uint32_t Lock); // see @OPAMP_LOCK
/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*__N32L40X_ADC_H */
       /**
        * @}
        */
       /**
        * @}
        */

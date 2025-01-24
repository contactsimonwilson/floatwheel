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
 * @file bsp_Tim_38K.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __BSP_TIM_38K_H__
#define __BSP_TIM_38K_H__

#include "n32l40x.h"
#include "n32l40x_lptim.h"

#if 1
#define ADVANCE_TIM               TIM1
#define ADVANCE_TIM_APBxClock_FUN RCC_EnableAPB2PeriphClk
#define ADVANCE_TIM_CLK           RCC_LPTIMCLK_SRC_APB1
#define ADVANCE_TIM_Period        (210 - 1)
#define ADVANCE_TIM_Prescaler     LPTIM_PRESCALER_DIV1
#define ADVANCE_TIM_Pulse     		(105 - 1)

#endif
#if 1
#define PORTx				GPIOC
#define PORTx_CLK		RCC_APB2_PERIPH_GPIOC
#define PORTx_PIN		GPIO_PIN_1
#endif

#define digitalHi(p, i)                                                                                                \
    {                                                                                                                  \
        p->PBSC = i;                                                                                                   \
    }
#define digitalLo(p, i)                                                                                                \
    {                                                                                                                  \
        p->PBC = i;                                                                                                    \
    }
#define digitalToggle(p, i)                                                                                            \
    {                                                                                                                  \
        p->POD ^= i;                                                                                                   \
    }

void ADVANCE_TIM_Init(void);

#endif /* __BSP_TIM_38K_H__ */

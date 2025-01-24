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
 * @file usb_endp.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_istr.h"

uint8_t Receive_Buffer[2];
extern __IO uint8_t PrevXferComplete;
extern u8* Ep1DataPtr;
extern u8 key_buffer[8];

/**
 * @brief  EP1 OUT Callback Routine.
 */
void EP1_OUT_Callback(void)
{
}

/**
 * @brief  EP1 IN Callback Routine.
 */
void EP1_IN_Callback(void)
{
    _SetEPTxStatus(ENDP1, EP_TX_NAK);
    PrevXferComplete = 1;
    Ep1DataPtr       = key_buffer;
    USB_SilWrite(EP1_IN, Ep1DataPtr, 8);
    _SetEPTxStatus(ENDP1, EP_TX_VALID);
}
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

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
 * @file usb_pwr.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __USB_PWR_H__
#define __USB_PWR_H__
#include "usb_core.h"
#include "usb_type.h"

typedef enum _RESUME_STATE
{
    RESUME_EXTERNAL,
    RESUME_INTERNAL,
    RESUME_LATER,
    RESUME_WAIT,
    RESUME_START,
    RESUME_ON,
    RESUME_OFF,
    RESUME_ESOF
} RESUME_STATE;

typedef enum _DEVICE_STATE
{
    UNCONNECTED,
    ATTACHED,
    POWERED,
    SUSPENDED,
    ADDRESSED,
    CONFIGURED
} DEVICE_STATE;

void Suspend(void);
void Resume_Init(void);
void Resume(RESUME_STATE eResumeSetVal);
USB_Result PowerOn(void);
USB_Result PowerOff(void);

extern __IO uint32_t bDeviceState; /* USB device status */
extern __IO bool fSuspendEnabled;  /* true when suspend is possible */

#endif /*__USB_PWR_H__*/

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

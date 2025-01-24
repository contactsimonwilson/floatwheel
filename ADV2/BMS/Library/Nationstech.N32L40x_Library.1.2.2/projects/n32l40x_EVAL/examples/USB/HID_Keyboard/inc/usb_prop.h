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
 * @file usb_prop.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __USB_PROP_H__
#define __USB_PROP_H__
#include "stdint.h"
#include "usb_core.h"

typedef enum _HID_REQUESTS
{
    GET_REPORT = 1,
    GET_IDLE,
    GET_PROTOCOL,

    SET_REPORT = 9,
    SET_IDLE,
    SET_PROTOCOL
} HID_REQUESTS;

void CustomHID_init(void);
void CustomHID_Reset(void);
void CustomHID_SetConfiguration(void);
void CustomHID_SetDeviceAddress(void);
void CustomHID_Status_In(void);
void CustomHID_Status_Out(void);
USB_Result CustomHID_Data_Setup(uint8_t);
USB_Result CustomHID_NoData_Setup(uint8_t);
USB_Result CustomHID_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t* CustomHID_GetDeviceDescriptor(uint16_t);
uint8_t* CustomHID_GetConfigDescriptor(uint16_t);
uint8_t* CustomHID_GetStringDescriptor(uint16_t);
USB_Result CustomHID_SetProtocol(void);
uint8_t* CustomHID_GetProtocolValue(uint16_t Length);
USB_Result CustomHID_SetProtocol(void);
uint8_t* CustomHID_GetReportDescriptor(uint16_t Length);
uint8_t* CustomHID_GetHIDDescriptor(uint16_t Length);

/* Exported define -----------------------------------------------------------*/
#define CustomHID_GetConfiguration USB_ProcessNop
//#define CustomHID_SetConfiguration          USB_ProcessNop
#define CustomHID_GetInterface       USB_ProcessNop
#define CustomHID_SetInterface       USB_ProcessNop
#define CustomHID_GetStatus          USB_ProcessNop
#define CustomHID_ClearFeature       USB_ProcessNop
#define CustomHID_SetEndPointFeature USB_ProcessNop
#define CustomHID_SetDeviceFeature   USB_ProcessNop
//#define CustomHID_SetDeviceAddress          USB_ProcessNop

#define REPORT_DESCRIPTOR 0x22

#endif /* __USB_PROP_H__ */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

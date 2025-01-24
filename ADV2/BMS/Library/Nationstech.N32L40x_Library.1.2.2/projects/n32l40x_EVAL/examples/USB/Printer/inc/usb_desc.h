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
 * @file usb_desc.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __USB_DESC_H__
#define __USB_DESC_H__
#include "stdint.h"

/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE          0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE   0x02
#define USB_STRING_DESCRIPTOR_TYPE          0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE       0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE        0x05

#define Printer_SIZ_DESC                    0x32
#define Printer_OFF_DESC                    0x12



#define Printer_SIZ_REPORT_DESC             41

#define Printer_SIZ_STRING_LANGID           4
#define Printer_SIZ_STRING_VENDOR           36
#define Printer_SIZ_STRING_PRODUCT          34
#define Printer_SIZ_STRING_SERIAL           28

#define STANDARD_ENDPOINT_DESC_SIZE         0x09


#define CONFIG_DESC_SIZE                    67
 




extern const uint8_t Printer_DeviceDescriptor[];
extern const uint8_t Printer_ConfigDescriptor[];
//extern const uint8_t Printer_ReportDescriptor[];
extern const uint8_t Printer_StringLangID[];
extern const uint8_t Printer_StringVendor[];
extern const uint8_t Printer_StringProduct[];
extern uint8_t Printer_StringSerial[];

#endif /* __USB_DESC_H__ */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

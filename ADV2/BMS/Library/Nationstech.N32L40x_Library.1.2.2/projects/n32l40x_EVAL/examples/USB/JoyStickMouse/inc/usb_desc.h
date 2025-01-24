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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define HID_DESCRIPTOR_TYPE                     0x21
#define JOYSTICK_SIZ_HID_DESC                   0x09
#define JOYSTICK_OFF_HID_DESC                   0x12

#define JOYSTICK_SIZ_DEVICE_DESC                18
#define JOYSTICK_SIZ_CONFIG_DESC                34
#define JOYSTICK_SIZ_REPORT_DESC                74
#define JOYSTICK_SIZ_STRING_LANGID              4
#define JOYSTICK_SIZ_STRING_VENDOR              38
#define JOYSTICK_SIZ_STRING_PRODUCT             34
#define JOYSTICK_SIZ_STRING_SERIAL              26

#define STANDARD_ENDPOINT_DESC_SIZE             0x09

/* Exported functions ------------------------------------------------------- */
extern const uint8_t Joystick_DeviceDescriptor[JOYSTICK_SIZ_DEVICE_DESC];
extern const uint8_t Joystick_ConfigDescriptor[JOYSTICK_SIZ_CONFIG_DESC];
extern const uint8_t Joystick_ReportDescriptor[JOYSTICK_SIZ_REPORT_DESC];
extern const uint8_t Joystick_StringLangID[JOYSTICK_SIZ_STRING_LANGID];
extern const uint8_t Joystick_StringVendor[JOYSTICK_SIZ_STRING_VENDOR];
extern const uint8_t Joystick_StringProduct[JOYSTICK_SIZ_STRING_PRODUCT];
extern uint8_t Joystick_StringSerial[JOYSTICK_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */


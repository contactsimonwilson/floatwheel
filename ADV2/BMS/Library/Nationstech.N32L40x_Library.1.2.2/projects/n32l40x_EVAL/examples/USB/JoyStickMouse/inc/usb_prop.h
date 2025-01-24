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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_PROP_H
#define __USB_PROP_H
#include "stdint.h"
#include "usb_core.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef enum _HID_REQUESTS
{
  GET_REPORT = 1,
  GET_IDLE,
  GET_PROTOCOL,

  SET_REPORT = 9,
  SET_IDLE,
  SET_PROTOCOL
} HID_REQUESTS;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Joystick_init(void);
void Joystick_Reset(void);
void Joystick_SetConfiguration(void);
void Joystick_SetDeviceAddress (void);
void Joystick_Status_In (void);
void Joystick_Status_Out (void);
USB_Result Joystick_Data_Setup(uint8_t);
USB_Result Joystick_NoData_Setup(uint8_t);
USB_Result Joystick_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *Joystick_GetDeviceDescriptor(uint16_t );
uint8_t *Joystick_GetConfigDescriptor(uint16_t);
uint8_t *Joystick_GetStringDescriptor(uint16_t);
USB_Result Joystick_SetProtocol(void);
uint8_t *Joystick_GetProtocolValue(uint16_t Length);
USB_Result Joystick_SetProtocol(void);
uint8_t *Joystick_GetReportDescriptor(uint16_t Length);
uint8_t *Joystick_GetHIDDescriptor(uint16_t Length);

/* Exported define -----------------------------------------------------------*/
#define Joystick_GetConfiguration          USB_ProcessNop
//#define Joystick_SetConfiguration          USB_ProcessNop
#define Joystick_GetInterface              USB_ProcessNop
#define Joystick_SetInterface              USB_ProcessNop
#define Joystick_GetStatus                 USB_ProcessNop
#define Joystick_ClearFeature              USB_ProcessNop
#define Joystick_SetEndPointFeature        USB_ProcessNop
#define Joystick_SetDeviceFeature          USB_ProcessNop
//#define Joystick_SetDeviceAddress          USB_ProcessNop

#define REPORT_DESCRIPTOR                  0x22

#endif /* __USB_PROP_H */


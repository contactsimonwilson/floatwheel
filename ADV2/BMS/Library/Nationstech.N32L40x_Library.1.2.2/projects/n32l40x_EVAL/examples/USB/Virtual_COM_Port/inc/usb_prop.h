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
#ifndef __usb_prop_H
#define __usb_prop_H

#include "stdint.h"
#include "usb_core.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
typedef struct
{
  uint32_t bitrate;
  uint8_t format;
  uint8_t paritytype;
  uint8_t datatype;
}LINE_CODING;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/

#define Virtual_Com_Port_GetConfiguration          USB_ProcessNop
//#define Virtual_Com_Port_SetConfiguration          USB_ProcessNop
#define Virtual_Com_Port_GetInterface              USB_ProcessNop
#define Virtual_Com_Port_SetInterface              USB_ProcessNop
#define Virtual_Com_Port_GetStatus                 USB_ProcessNop
#define Virtual_Com_Port_ClearFeature              USB_ProcessNop
#define Virtual_Com_Port_SetEndPointFeature        USB_ProcessNop
#define Virtual_Com_Port_SetDeviceFeature          USB_ProcessNop
//#define Virtual_Com_Port_SetDeviceAddress          USB_ProcessNop

#define SEND_ENCAPSULATED_COMMAND   0x00
#define GET_ENCAPSULATED_RESPONSE   0x01
#define SET_COMM_FEATURE            0x02
#define GET_COMM_FEATURE            0x03
#define CLEAR_COMM_FEATURE          0x04
#define SET_LINE_CODING             0x20
#define GET_LINE_CODING             0x21
#define SET_CONTROL_LINE_STATE      0x22
#define SEND_BREAK                  0x23

/* Exported functions ------------------------------------------------------- */
void Virtual_Com_Port_init(void);
void Virtual_Com_Port_Reset(void);
void Virtual_Com_Port_SetConfiguration(void);
void Virtual_Com_Port_SetDeviceAddress (void);
void Virtual_Com_Port_Status_In (void);
void Virtual_Com_Port_Status_Out (void);
USB_Result Virtual_Com_Port_Data_Setup(uint8_t);
USB_Result Virtual_Com_Port_NoData_Setup(uint8_t);
USB_Result Virtual_Com_Port_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *Virtual_Com_Port_GetDeviceDescriptor(uint16_t );
uint8_t *Virtual_Com_Port_GetConfigDescriptor(uint16_t);
uint8_t *Virtual_Com_Port_GetStringDescriptor(uint16_t);

uint8_t *Virtual_Com_Port_GetLineCoding(uint16_t Length);
uint8_t *Virtual_Com_Port_SetLineCoding(uint16_t Length);

#endif /* __usb_prop_H */


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


/**---------- HID CLASS REQUESTS ----------*/
//#define   GET_REPORT                  0x01
//#define   GET_IDLE                    0x02
//#define   GET_PROTOCOL                0x03

//#define   SET_REPORT                  0x09
//#define   SET_IDLa                    0x0a
//#define   SET_PROTOCOL                0x0b

typedef enum
{
    GET_REPORT = 1,
    GET_IDLE,
    GET_PROTOCOL,

    SET_REPORT = 9,
    SET_IDLE,
    SET_PROTOCOL
}REQUESTS;


/**---------- CDC CLASS REQUESTS ----------*/
#define SEND_ENCAPSULATED_COMMAND   0x00
#define GET_ENCAPSULATED_RESPONSE   0x01
#define SET_COMM_FEATURE            0x02
#define GET_COMM_FEATURE            0x03
#define CLEAR_COMM_FEATURE          0x04

#define SET_LINE_CODING             0x20
#define GET_LINE_CODING             0x21
#define SET_CONTROL_LINE_STATE      0x22
#define SEND_BREAK                  0x23


#define GET_DEVICE_ID               0x00
#define GET_PORT_STATUS             0x01
#define SOFT_RESET                  0x02




void Printer_init(void);
void Printer_Reset(void);
void Printer_SetConfiguration(void);
void Printer_SetDeviceAddress(void);
void Printer_Status_In(void);
void Printer_Status_Out(void);
USB_Result Printer_Data_Setup(uint8_t);
USB_Result Printer_NoData_Setup(uint8_t);
USB_Result Printer_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t* Printer_GetDeviceDescriptor(uint16_t);
uint8_t* Printer_GetConfigDescriptor(uint16_t);
uint8_t* Printer_GetStringDescriptor(uint16_t);
USB_Result Printer_SetProtocol(void);
uint8_t* Printer_GetProtocolValue(uint16_t Length);
USB_Result Printer_SetProtocol(void);
uint8_t* Printer_GetReportDescriptor(uint16_t Length);
uint8_t* Printer_GetDescriptor(uint16_t Length);
uint8_t *USB_Printer_ID(uint16_t Length);
/* Exported define -----------------------------------------------------------*/
#define Printer_GetConfiguration USB_ProcessNop
//#define Printer_SetConfiguration          USB_ProcessNop
#define Printer_GetInterface       USB_ProcessNop
#define Printer_SetInterface       USB_ProcessNop
#define Printer_GetStatus          USB_ProcessNop
#define Printer_ClearFeature       USB_ProcessNop
#define Printer_SetEndPointFeature USB_ProcessNop
#define Printer_SetDeviceFeature   USB_ProcessNop
//#define Printer_SetDeviceAddress          USB_ProcessNop

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

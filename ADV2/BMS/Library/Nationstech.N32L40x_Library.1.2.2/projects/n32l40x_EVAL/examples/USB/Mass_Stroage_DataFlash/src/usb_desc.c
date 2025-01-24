/******************** (C) COPYRIGHT 2020 Nations Technologies Inc ********************
* File Name          : usb_desc.c
* Author             : Nations
* Version            : V1.2.2
* Date               : 09/03/2020
* Description        : Descriptors for Mass Storage Device
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
 * @file usb_desc.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
/* Includes ------------------------------------------------------------------*/
#include "usb_desc.h"

const uint8_t MASS_DeviceDescriptor[MASS_SIZ_DEVICE_DESC] =
{
    0x12,   /* bLength  */
    0x01,   /* bDescriptorType */
    0x00,   /* bcdUSB, version 2.00 */
    0x02,
    0x00,   /* bDeviceClass : each interface define the device class */
    0x00,   /* bDeviceSubClass */
    0x00,   /* bDeviceProtocol */
    0x40,   /* bMaxPacketSize0 0x40 = 64 */
    0xF5,   /*idVendor (0x19F5)*/
    0x19,
    0x20,   /* idProduct */
    0x57,
    0x00,   /* bcdDevice 2.00*/
    0x02,
    1,              /* index of string Manufacturer  */
    /**/
    2,              /* index of string descriptor of product*/
    /* */
    3,              /* */
    /* */
    /* */
    0x01    /*bNumConfigurations */
};

const uint8_t MASS_ConfigDescriptor[MASS_SIZ_CONFIG_DESC] =
{

    0x09,   /* bLength: Configuation Descriptor size */
    0x02,   /* bDescriptorType: Configuration */
    MASS_SIZ_CONFIG_DESC,

    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    /*      Configuration value */
    0x00,   /* iConfiguration: */
    /*      Index of string descriptor */
    /*      describing the configuration */
    0xC0,   /* bmAttributes: */
    /*      bus powered */
    100,   /* MaxPower 100 mA */

    /*****************Interface Descirptor*******************/

    0x09, //bLength
    0x04, //bDescriptorType
    0x00, //bInterfaceNumber
    0x00, //bAlternateSetting
    0x02, //bNumEndpoints
    0x08, //bInterfaceClass
    0x06, //bInterfaceSubClass
    0x50, //bInterfaceProtocol
    4, //iConfiguration

/* iInterface: */
    /* 18 */
    0x07,   /*Endpoint descriptor length = 7*/
    0x05,   /*Endpoint descriptor type */
    0x81,   /*Endpoint address (IN, address 1) */
    0x02,   /*Bulk endpoint type */
    0x40,   /*Maximum packet size (64 bytes) */
    0x00,
    0x00,   /*Polling interval in milliseconds */

    /* 25 */
    0x07,   /*Endpoint descriptor length = 7 */
    0x05,   /*Endpoint descriptor type */
    0x02,   /*Endpoint address (OUT, address 2) */
    0x02,   /*Bulk endpoint type */
    0x40,   /*Maximum packet size (64 bytes) */
    0x00,
    0x00     /*Polling interval in milliseconds*/
    /*32*/
};
const uint8_t MASS_StringLangID[MASS_SIZ_STRING_LANGID] =
{
    MASS_SIZ_STRING_LANGID,
    0x03,
    0x09,
    0x04
}
;      /* LangID = 0x0409: U.S. English */
const uint8_t MASS_StringVendor[MASS_SIZ_STRING_VENDOR] =
{
    MASS_SIZ_STRING_VENDOR, /* Size of manufaturer string */
    0x03,           /* bDescriptorType = String descriptor */
    /* Manufacturer: "NATIONS" */
    'N', 0, 'A', 0, 'T', 0, 'I', 0, 'O', 0, 'N', 0, 'S', 0
};
const uint8_t MASS_StringProduct[MASS_SIZ_STRING_PRODUCT] =
{
    MASS_SIZ_STRING_PRODUCT,
    0x03,
    /* Product name: "N32L40x:USB Mass Storage" */
    'N', 0, '3', 0, '2', 0, 'L', 0, '4', 0, '0', 0, 'x', 0, ' ', 0, 
    'S', 0, 't', 0, 'o', 0, 'r', 0, 'a', 0, 'g', 0, 'e', 0

};

uint8_t MASS_StringSerial[MASS_SIZ_STRING_SERIAL] =
{
    MASS_SIZ_STRING_SERIAL,
    0x03,
    /* N23L40x */
    'N', 0, '3', 0, '2', 0, 'L', 0, '4', 0, '0', 0, 'x', 0,
};
const uint8_t MASS_StringInterface[MASS_SIZ_STRING_INTERFACE] =
{
    MASS_SIZ_STRING_INTERFACE,
    0x03,
    /* Interface 0: "NATIONS Mass" */
    'N', 0, 'A', 0, 'T', 0, 'I', 0, 'O', 0, 'N', 'S', 0, ' ', 0, 'M', 0, 'a', 0, 's', 0, 's', 0
};


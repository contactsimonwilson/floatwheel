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
 * @file usb_desc.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "usb_lib.h"
#include "usb_desc.h"

/*---------- USB Standard Device Descriptor ----------*/
const uint8_t Printer_DeviceDescriptor[18] = 
{
    0x12,   /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,   /* bDescriptorType */  
    0x00,
    0x02,   /* bcdUSB = 2.00 */
    0x00,   /* bDeviceClass: CDC */ 
    0x00,   /* bDeviceSubClass */
    0x00,   /* bDeviceProtocol */
    0x40,   /* bMaxPacketSize0 */
    0xf5,   /*idVendor (0x19F5)*/ //f5
    0x19,   //19
    0x45,   /*idProduct = (0x3245)*/ //45
    0x32,   //32 
    0x00,
    0x02,   /* bcdDevice = 2.00 */
    1,              /* Index of string descriptor describing manufacturer */
    2,              /* Index of string descriptor describing product */
    3,              /* Index of string descriptor describing the device's serial number */
    0x01    /* bNumConfigurations */
};      


/*---------- USB Configuration Descriptor ----------*/
const uint8_t Printer_ConfigDescriptor[CONFIG_DESC_SIZE] = 
{
    /**---------- Configure ----------*/
    0x09,               /* bLength              */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,          /* bDescriptorType      */
    CONFIG_DESC_SIZE,   /* wTotalLength         */
    0x00,         
    0x01,               /* bNumInterfaces       */
    0x01,               /* bConfigurationValue  */
    0x00,               /* iConfiguration       */
    0xC0,               /* bmAttributes         */
    0x32,               /* MaxPower             */

    /**---------- ONE INTERFACE descriptor ----------*/
    0x09,               /* bLength              */
    USB_INTERFACE_DESCRIPTOR_TYPE,              /* bDescriptorType      */
    0x00,               /* bInterfaceNumber     */
    0x00,               /* bAlternateSetting    */
    0x02,               /* bNumEndpoints        */
    0x07,               /* bInterfaceClass   07:printer   */
    0x01,               /* bInterfaceSubClass : 1=BOOT, 0=no boot */
    0x02,               /* nInterfaceProtocol : 0=none, 1=keyboard, 2=mouse */
    0x00,               /* iInterface           */

    /* ENDPOINT descriptor */
    0x07,               /* bLength          */
    USB_ENDPOINT_DESCRIPTOR_TYPE,           /* bDescriptorType  */
    0x82,               /* In bEndpointAddress EP2IN*/
    0x02,               /* bulk             */
    EP2_IN_SIZE,        /* wMaxPacketSize   */
    0x00,
    0x00, /* bInterval        */

    /* ENDPOINT descriptor */
    0x07,               /* bLength          */
    USB_ENDPOINT_DESCRIPTOR_TYPE,           /* bDescriptorType  */
    0x02,               /* Out bEndpointAddress  EP2OUT*/
    0x02,               /* bulk             */
    EP2_OUT_SIZE,       /* wMaxPacketSize   */
    0x00,
    0x00,               /* bInterval        */
};

/*---------- USB String Descriptors (optional) ----------*/
const uint8_t Printer_StringLangID[Printer_SIZ_STRING_LANGID] = 
{
    Printer_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,       /* LangID = 0x0409: SB_EP7R_STAT_RX_1.S. English */
    0x04
}; 


/**----------  ----------*/
const uint8_t Printer_StringVendor[Printer_SIZ_STRING_VENDOR] = 
{
    Printer_SIZ_STRING_VENDOR,  /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE, /* bDescriptorType*/
    /* Manufacturer: "NATIONS" */
    'N', 0,
    'A', 0,
    'T', 0,
    'I', 0,
    'O', 0,
    'N', 0,
    'S', 0
};

/**----------  ----------*/
const uint8_t Printer_StringProduct[Printer_SIZ_STRING_PRODUCT] = 
{
    Printer_SIZ_STRING_PRODUCT, /* bLength */
    USB_STRING_DESCRIPTOR_TYPE, /* bDescriptorType */
    'N', 0,
    '3', 0,
    '2', 0,
    'l', 0,
    '4', 0,
    '0', 0,
    'x', 0,
    'C', 0,
    'u', 0,
    's', 0,
    't', 0,
    'm', 0,
    ' ', 0,
    'P', 0,
    'R', 0,
    'I', 0};

/**----------  ----------*/
uint8_t Printer_StringSerial[Printer_SIZ_STRING_SERIAL] = 
{
    Printer_SIZ_STRING_SERIAL,  /* bLength */
    USB_STRING_DESCRIPTOR_TYPE, /* bDescriptorType */
    'N', 0,
    '3', 0,
    '2', 0,
    'l', 0,
    '4', 0,
    '0', 0,
    'x', 0
};



/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

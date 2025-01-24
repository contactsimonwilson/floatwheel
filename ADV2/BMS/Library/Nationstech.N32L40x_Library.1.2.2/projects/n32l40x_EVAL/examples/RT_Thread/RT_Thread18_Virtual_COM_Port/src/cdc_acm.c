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
 * @file cdc_acm.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */


#include "usbd_core.h"
#include "usbd_cdc.h"
#include "rtthread.h"

/*!< endpoint address */
#define CDC_IN_EP  0x81
#define CDC_OUT_EP 0x02
#define CDC_INT_EP 0x83

#define USBD_VID           0x19F5
#define USBD_PID           0x5740
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

/*!< config descriptor size */
#define USB_CONFIG_SIZE (9 + CDC_ACM_DESCRIPTOR_LEN)

/*!< global descriptor */
static const uint8_t cdc_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x02, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x02, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, 0x02),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x10,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'N', 0x00,                  /* wcChar0 */
    'A', 0x00,                  /* wcChar1 */
    'T', 0x00,                  /* wcChar2 */
    'I', 0x00,                  /* wcChar3 */
    'O', 0x00,                  /* wcChar4 */
    'N', 0x00,                  /* wcChar5 */
    'S', 0x00,                  /* wcChar6 */

    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x1A,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'N', 0x00,                  /* wcChar0 */
    '3', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    'L', 0x00,                  /* wcChar3 */
    '4', 0x00,                  /* wcChar4 */
    '0', 0x00,                  /* wcChar5 */
    'x', 0x00,                  /* wcChar6 */
    ' ', 0x00,                  /* wcChar7 */
    'P', 0x00,                  /* wcChar8 */
    'o', 0x00,                  /* wcChar9 */
    'r', 0x00,                  /* wcChar10 */
    't', 0x00,                  /* wcChar11 */

    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x10,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'N', 0x00,                  /* wcChar0 */
    '3', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    'L', 0x00,                  /* wcChar3 */
    '4', 0x00,                  /* wcChar4 */
    '0', 0x00,                  /* wcChar5 */
    'X', 0x00,                  /* wcChar6 */

    0x00
};

/*!< class */
usbd_class_t cdc_class;
/*!< interface one */
usbd_interface_t cdc_cmd_intf;
/*!< interface two */
usbd_interface_t cdc_data_intf;

/* function ------------------------------------------------------------------*/
void usbd_cdc_acm_out(uint8_t ep)
{
    uint8_t data[64];
    uint32_t read_byte;
    uint8_t i;

    usbd_ep_read(ep, data, 64, &read_byte);
    for (i = 0; i < read_byte; i++) {
        rt_kprintf("%02x ", data[i]);
    }
    rt_kprintf("\r\n");
    rt_kprintf("read len:%d\r\n", read_byte);
    usbd_ep_read(ep, NULL, 0, NULL);
}

void usbd_cdc_acm_in(uint8_t ep)
{
    rt_kprintf("in\r\n");
}

/*!< endpoint call back */
usbd_endpoint_t cdc_out_ep = {
    .ep_addr = CDC_OUT_EP,
    .ep_cb = usbd_cdc_acm_out
};

usbd_endpoint_t cdc_in_ep = {
    .ep_addr = CDC_IN_EP,
    .ep_cb = usbd_cdc_acm_in
};

/* function ------------------------------------------------------------------*/
void cdc_acm_init(void)
{
    usbd_desc_register(cdc_descriptor);
    /*!< add interface */
    usbd_cdc_add_acm_interface(&cdc_class, &cdc_cmd_intf);
    usbd_cdc_add_acm_interface(&cdc_class, &cdc_data_intf);
    /*!< interface add endpoint */
    usbd_interface_add_endpoint(&cdc_data_intf, &cdc_out_ep);
    usbd_interface_add_endpoint(&cdc_data_intf, &cdc_in_ep);

    usbd_initialize();
}

volatile uint8_t dtr_enable = 0;

void usbd_cdc_acm_set_dtr(bool dtr)
{
    if (dtr) {
        dtr_enable = 1;
    } else {
        dtr_enable = 0;
    }
}

void cdc_acm_data_send_with_dtr_test(void)
{
    uint8_t data_buffer[10] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A };
    usbd_ep_write(CDC_IN_EP, data_buffer, 10, NULL);
}

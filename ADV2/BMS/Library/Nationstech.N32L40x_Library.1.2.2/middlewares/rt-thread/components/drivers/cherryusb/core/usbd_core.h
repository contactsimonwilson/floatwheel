/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * @file usbd_core.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
 
 
#ifndef _USBD_CORE_H
#define _USBD_CORE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usb_util.h"
#include "usb_def.h"
#include "usb_dc.h"

enum usbd_event_type {
    /** USB error reported by the controller */
    USBD_EVENT_ERROR,
    /** USB reset */
    USBD_EVENT_RESET,
    /** Start of Frame received */
    USBD_EVENT_SOF,
    /** USB connection established, hardware enumeration is completed */
    USBD_EVENT_CONNECTED,
    /** USB configuration done */
    USBD_EVENT_CONFIGURED,
    /** USB connection suspended by the HOST */
    USBD_EVENT_SUSPEND,
    /** USB connection lost */
    USBD_EVENT_DISCONNECTED,
    /** USB connection resumed by the HOST */
    USBD_EVENT_RESUME,

    /** USB interface selected */
    USBD_EVENT_SET_INTERFACE,
    /** USB interface selected */
    USBD_EVENT_SET_REMOTE_WAKEUP,
    /** USB interface selected */
    USBD_EVENT_CLEAR_REMOTE_WAKEUP,
    /** Set Feature ENDPOINT_HALT received */
    USBD_EVENT_SET_HALT,
    /** Clear Feature ENDPOINT_HALT received */
    USBD_EVENT_CLEAR_HALT,
    /** setup packet received */
    USBD_EVENT_SETUP_NOTIFY,
    /** ep0 in packet received */
    USBD_EVENT_EP0_IN_NOTIFY,
    /** ep0 out packet received */
    USBD_EVENT_EP0_OUT_NOTIFY,
    /** ep in packet except ep0 received */
    USBD_EVENT_EP_IN_NOTIFY,
    /** ep out packet except ep0 received */
    USBD_EVENT_EP_OUT_NOTIFY,
    /** Initial USB connection status */
    USBD_EVENT_UNKNOWN
};

/**
 * @brief Callback function signature for the USB Endpoint status
 */
typedef void (*usbd_endpoint_callback)(uint8_t ep);

/**
 * @brief Callback function signature for class specific requests
 *
 * Function which handles Class specific requests corresponding to an
 * interface number specified in the device descriptor table. For host
 * to device direction the 'len' and 'payload_data' contain the length
 * of the received data and the pointer to the received data respectively.
 * For device to host class requests, 'len' and 'payload_data' should be
 * set by the callback function with the length and the address of the
 * data to be transmitted buffer respectively.
 */
typedef int (*usbd_request_handler)(struct usb_setup_packet *setup,
                                    uint8_t **data, uint32_t *transfer_len);

/* callback function pointer structure for Application to handle events */
typedef void (*usbd_notify_handler)(uint8_t event, void *arg);

typedef struct usbd_endpoint {
    usb_slist_t list;
    uint8_t ep_addr;
    usbd_endpoint_callback ep_cb;
} usbd_endpoint_t;

typedef struct usbd_interface {
    usb_slist_t list;
    /** Handler for USB Class specific commands*/
    usbd_request_handler class_handler;
    /** Handler for USB Vendor specific commands */
    usbd_request_handler vendor_handler;
    /** Handler for USB custom specific commands */
    usbd_request_handler custom_handler;
    /** Handler for USB event notify commands */
    usbd_notify_handler notify_handler;
    uint8_t intf_num;
    usb_slist_t ep_list;
} usbd_interface_t;

typedef struct usbd_class {
    usb_slist_t list;
    const char *name;
    usb_slist_t intf_list;
} usbd_class_t;

void usbd_event_notify_handler(uint8_t event, void *arg);

void usbd_desc_register(const uint8_t *desc);
void usbd_msosv1_desc_register(struct usb_msosv1_descriptor *desc);
void usbd_msosv2_desc_register(struct usb_msosv2_descriptor *desc);
void usbd_bos_desc_register(struct usb_bos_descriptor *desc);
void usbd_class_register(usbd_class_t *devclass);
void usbd_class_add_interface(usbd_class_t *devclass, usbd_interface_t *intf);
void usbd_interface_add_endpoint(usbd_interface_t *intf, usbd_endpoint_t *ep);
bool usb_device_is_configured(void);

int usbd_initialize(void);

#ifdef __cplusplus
}
#endif

#endif

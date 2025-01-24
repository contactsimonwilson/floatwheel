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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_CONF_H
#define __USB_CONF_H

/*-------------------------------------------------------------*/
/* EP_NUM */
/* defines how many endpoints are used by the device */
/*-------------------------------------------------------------*/
#define EP_NUM                          (3)

/*-------------------------------------------------------------*/
/* --------------   Buffer Description Table  -----------------*/
/*-------------------------------------------------------------*/
/* buffer table base address */

#define BTABLE_ADDRESS      (0x00)

/* EP0  */
/* rx/tx buffer base address */
#define ENDP0_RXADDR        (0x18)
#define ENDP0_TXADDR        (0x58)

/* EP1  */
/* tx buffer base address */
#define ENDP1_TXADDR        (0x98)

/* EP2  */
/* Rx buffer base address */
#define ENDP2_RXADDR        (0xD8)


/* ISTR events */
/* IMR_MSK */
/* mask defining which events has to be handled */
/* by the device application software */
#define IMR_MSK (CTRL_CTRSM  | CTRL_WKUPM | CTRL_SUSPDM | CTRL_ERRORM  | CTRL_SOFM \
                 | CTRL_ESOFM | CTRL_RSTM )

/* CTR service routines */
/* associated to defined endpoints */
//#define  EP1_IN_Callback   USB_ProcessNop
#define  EP2_IN_Callback   USB_ProcessNop
#define  EP3_IN_Callback   USB_ProcessNop
#define  EP4_IN_Callback   USB_ProcessNop
#define  EP5_IN_Callback   USB_ProcessNop
#define  EP6_IN_Callback   USB_ProcessNop
#define  EP7_IN_Callback   USB_ProcessNop


#define  EP1_OUT_Callback   USB_ProcessNop
//#define  EP2_OUT_Callback   USB_ProcessNop
#define  EP3_OUT_Callback  USB_ProcessNop
#define  EP4_OUT_Callback   USB_ProcessNop
#define  EP5_OUT_Callback   USB_ProcessNop
#define  EP6_OUT_Callback   USB_ProcessNop
#define  EP7_OUT_Callback   USB_ProcessNop

#endif /* __USB_CONF_H */


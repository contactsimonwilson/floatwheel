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
 * @file usb_istr.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_pwr.h"
#include "usb_istr.h"

__IO uint16_t wIstr;            /* STS register last read value */
__IO uint8_t bIntPackSOF   = 0; /* SOFs received between 2 consecutive packets */
__IO uint32_t esof_counter = 0; /* expected SOF counter */
__IO uint32_t wCNTR        = 0;

/* function pointers to non-control endpoints service routines */
void (*pEpInt_IN[7])(void) = {
    EP1_IN_Callback,
    EP2_IN_Callback,
    EP3_IN_Callback,
    EP4_IN_Callback,
    EP5_IN_Callback,
    EP6_IN_Callback,
    EP7_IN_Callback,
};

void (*pEpInt_OUT[7])(void) = {
    EP1_OUT_Callback,
    EP2_OUT_Callback,
    EP3_OUT_Callback,
    EP4_OUT_Callback,
    EP5_OUT_Callback,
    EP6_OUT_Callback,
    EP7_OUT_Callback,
};

/**
 * @brief  STS events interrupt service routine
 */
void USB_Istr(void)
{
    uint32_t i=0;
    __IO uint32_t EP[8];

    wIstr = _GetISTR();

#if (IMR_MSK & STS_CTRS)
    if (wIstr & STS_CTRS & wInterrupt_Mask)
    {
        /* servicing of the endpoint correct transfer interrupt */
        /* clear of the CTR flag into the sub */
        USB_CorrectTransferLp();
#ifdef CTR_CALLBACK
        CTR_Callback();
#endif
    }
#endif
    /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & STS_RST)
    if (wIstr & STS_RST & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_RST);
        Device_Property.Init();
        Device_Property.Reset();
#ifdef RESET_CALLBACK
        RESET_Callback();
#endif
    }
#endif
    /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & STS_DOVR)
    if (wIstr & STS_DOVR & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_DOVR);
#ifdef DOVR_CALLBACK
        DOVR_Callback();
#endif
    }
#endif
    /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & STS_ERROR)
    if (wIstr & STS_ERROR & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_ERROR);
#ifdef ERR_CALLBACK
        ERR_Callback();
#endif
    }
#endif
    /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & STS_WKUP)
    if (wIstr & STS_WKUP & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_WKUP);
        Resume(RESUME_EXTERNAL);
#ifdef WKUP_CALLBACK
        WKUP_Callback();
#endif
    }
#endif
    /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & STS_SUSPD)
    if (wIstr & STS_SUSPD & wInterrupt_Mask)
    {
        /* check if SUSPEND is possible */
        if (fSuspendEnabled)
        {
            Suspend();
        }
        else
        {
            /* if not possible then resume after xx ms */
            Resume(RESUME_LATER);
        }
        /* clear of the STS bit must be done after setting of CTRL_FSUSPD */
        _SetISTR((uint16_t)CLR_SUSPD);
#ifdef SUSP_CALLBACK
        SUSP_Callback();
#endif
    }
#endif
    /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & STS_SOF)
    if (wIstr & STS_SOF & wInterrupt_Mask)
    {
        _SetISTR((uint16_t)CLR_SOF);
        bIntPackSOF++;

#ifdef SOF_CALLBACK
        SOF_Callback();
#endif
    }
#endif
    /*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#if (IMR_MSK & STS_ESOF)
    if (wIstr & STS_ESOF & wInterrupt_Mask)
    {
        /* clear ESOF flag in STS */
        _SetISTR((uint16_t)CLR_ESOF);

        if ((_GetFNR() & FN_RXDP) != 0)
        {
            /* increment ESOF counter */
            esof_counter++;

            /* test if we enter in ESOF more than 3 times with FSUSP =0 and RXDP =1=>> possible missing SUSP flag*/
            if ((esof_counter > 3) && ((_GetCNTR() & CTRL_FSUSPD) == 0))
            {
                /* this a sequence to apply a force RESET*/

                /*Store CTRL value */
                wCNTR = _GetCNTR();

                /*Store endpoints registers status */
                for (i = 0; i < 8; i++)
                    EP[i] = _GetENDPOINT(i);

                /*apply FRES */
                wCNTR |= CTRL_FRST;
                _SetCNTR(wCNTR);

                /*clear FRES*/
                wCNTR &= ~CTRL_FRST;
                _SetCNTR(wCNTR);

                /*poll for RESET flag in STS*/
                while ((_GetISTR() & STS_RST) == 0)
                    ;

                /* clear RESET flag in STS */
                _SetISTR((uint16_t)CLR_RST);

                /*restore Enpoints*/
                for (i = 0; i < 8; i++)
                    _SetENDPOINT(i, EP[i]);

                esof_counter = 0;
            }
        }
        else
        {
            esof_counter = 0;
        }

        /* resume handling timing is made with ESOFs */
        Resume(RESUME_ESOF); /* request without change of the machine state */

#ifdef ESOF_CALLBACK
        ESOF_Callback();
#endif
    }
#endif
} /* USB_Istr */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

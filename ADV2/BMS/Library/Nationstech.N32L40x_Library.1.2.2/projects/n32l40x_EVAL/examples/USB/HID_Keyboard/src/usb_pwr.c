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
 * @file usb_pwr.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_pwr.h"
#include "hw_config.h"

__IO uint32_t bDeviceState = UNCONNECTED; /* USB device status */
__IO bool fSuspendEnabled  = true;        /* true when suspend is possible */
__IO uint32_t EP[8];

struct
{
    __IO RESUME_STATE eState;
    __IO uint8_t bESOFcnt;
} ResumeS;

__IO uint32_t remotewakeupon = 0;

/* Extern function prototypes ------------------------------------------------*/

/**
 * @brief  USB PowerOn.
 */
USB_Result PowerOn(void)
{
    uint16_t wRegVal;

    /*** CNTR_PWDN = 0 ***/
    wRegVal = CTRL_FRST;
    _SetCNTR(wRegVal);

    /*** CTRL_FRST = 0 ***/
    wInterrupt_Mask = 0;
    _SetCNTR(wInterrupt_Mask);
    /*** Clear pending interrupts ***/
    _SetISTR(0);
    /*** Set interrupt mask ***/
    wInterrupt_Mask = CTRL_RSTM | CTRL_SUSPDM | CTRL_WKUPM;
    _SetCNTR(wInterrupt_Mask);

    return Success;
}

/**
 * @brief  USB PowerOff.
 */
USB_Result PowerOff()
{
    /* disable all interrupts and force USB reset */
    _SetCNTR(CTRL_FRST);
    /* clear interrupt status register */
    _SetISTR(0);
    /* switch-off device */
    _SetCNTR(CTRL_FRST + CTRL_PD);
    /* sw variables reset */
    /* ... */

    return Success;
}

/**
 * @brief  USB Suspend.
 */
void Suspend(void)
{
    uint32_t i = 0;
    uint16_t wCNTR;
        
    /* suspend preparation */
    /* ... */

#if (XTALLESS == 1)
    RCC->APB1PRST |= RCC_APB1PRST_UCDRRST;
    RCC->APB1PRST &= ~RCC_APB1PRST_UCDRRST;
#endif

    /*Store CTRL value */
    wCNTR = _GetCNTR();

    /* This a sequence to apply a force RESET to handle a robustness case */

    /*Store endpoints registers status */
    for (i = 0; i < 8; i++)
        EP[i] = _GetENDPOINT(i);

    /* unmask RESET flag */
    wCNTR |= CTRL_RSTM;
    _SetCNTR(wCNTR);

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

    /* Now it is safe to enter macrocell in suspend mode */
    wCNTR |= CTRL_FSUSPD;
    _SetCNTR(wCNTR);

    /* force low-power mode in the macrocell */
    wCNTR = _GetCNTR();
    wCNTR |= CTRL_LP_MODE;
    _SetCNTR(wCNTR);

#ifdef USB_LOW_PWR_MGMT_SUPPORT
    /* Request to enter SLEEP mode*/
    PWR_EnterSLEEPMode(SLEEP_OFF_EXIT, PWR_SLEEPENTRY_WFI);
#endif  /* USB_LOW_PWR_MGMT_SUPPORT */
}

/**
 * @brief  Handles wake-up restoring normal operations.
 */
void Resume_Init(void)
{
    uint16_t wCNTR;

    /* ------------------ ONLY WITH BUS-POWERED DEVICES ---------------------- */
    /* restart the clocks */
    /* ...  */

    /* CTRL_LP_MODE = 0 */
    wCNTR = _GetCNTR();
    wCNTR &= (~CTRL_LP_MODE);
    _SetCNTR(wCNTR);

#ifdef USB_LOW_PWR_MGMT_SUPPORT      
    /* restore full power */
    /* ... on connected devices */
    Leave_LowPowerMode();
#endif /* USB_LOW_PWR_MGMT_SUPPORT */

    /* reset FSUSP bit */
    _SetCNTR(IMR_MSK);

    /* reverse suspend preparation */
    /* ... */
}

/**
 * @brief  USB Resume,This is the state machine handling resume operations and
 *         timing sequence. The control is based on the Resume structure
 *         variables and on the ESOF interrupt calling this subroutine
 *         without changing machine state.
 * @param  eResumeSetVal: a state machine value (RESUME_STATE)
 *         RESUME_ESOF doesn't change ResumeS.eState allowing
 *         decrementing of the ESOF counter in different states.
 */
void Resume(RESUME_STATE eResumeSetVal)
{
    uint16_t wCNTR;

    if (eResumeSetVal != RESUME_ESOF)
        ResumeS.eState = eResumeSetVal;
    switch (ResumeS.eState)
    {
    case RESUME_EXTERNAL:
        if (remotewakeupon == 0)
        {
            Resume_Init();
            ResumeS.eState = RESUME_OFF;
        }
        else /* RESUME detected during the RemoteWAkeup signalling => keep RemoteWakeup handling*/
        {
            ResumeS.eState = RESUME_ON;
        }
        break;
    case RESUME_INTERNAL:
        Resume_Init();
        ResumeS.eState = RESUME_START;
        remotewakeupon = 1;
        break;
    case RESUME_LATER:
        ResumeS.bESOFcnt = 2;
        ResumeS.eState   = RESUME_WAIT;
        break;
    case RESUME_WAIT:
        ResumeS.bESOFcnt--;
        if (ResumeS.bESOFcnt == 0)
            ResumeS.eState = RESUME_START;
        break;
    case RESUME_START:
        wCNTR = _GetCNTR();
        wCNTR |= CTRL_RESUM;
        _SetCNTR(wCNTR);
        ResumeS.eState   = RESUME_ON;
        ResumeS.bESOFcnt = 10;
        break;
    case RESUME_ON:
        ResumeS.bESOFcnt--;
        if (ResumeS.bESOFcnt == 0)
        {
            wCNTR = _GetCNTR();
            wCNTR &= (~CTRL_RESUM);
            _SetCNTR(wCNTR);
            ResumeS.eState = RESUME_OFF;
            remotewakeupon = 0;
        }
        break;
    case RESUME_OFF:
    case RESUME_ESOF:
    default:
        ResumeS.eState = RESUME_OFF;
        break;
    }
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

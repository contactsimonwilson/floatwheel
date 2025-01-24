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
 * @file usb_prop.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_bot.h"
#include "hw_config.h"
#include "memory.h"
#include "mass_mal.h"
#include "usb_prop.h"

extern uint32_t Max_Lun;

USB_Device Device_Table =
{
    EP_NUM,
    1
};

DEVICE_PROP Device_Property =
{
    MASS_init,
    MASS_Reset,
    MASS_Status_In,
    MASS_Status_Out,
    MASS_Data_Setup,
    MASS_NoData_Setup,
    MASS_Get_Interface_Setting,
    MASS_GetDeviceDescriptor,
    MASS_GetConfigDescriptor,
    MASS_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
};

USER_STANDARD_REQUESTS User_Standard_Requests =
{
    Mass_Storage_GetConfiguration,
    Mass_Storage_SetConfiguration,
    Mass_Storage_GetInterface,
    Mass_Storage_SetInterface,
    Mass_Storage_GetStatus,
    Mass_Storage_ClearFeature,
    Mass_Storage_SetEndPointFeature,
    Mass_Storage_SetDeviceFeature,
    Mass_Storage_SetDeviceAddress
};

USB_OneDescriptor Device_Descriptor =
{
    (uint8_t*)MASS_DeviceDescriptor,
    MASS_SIZ_DEVICE_DESC
};

USB_OneDescriptor Config_Descriptor =
{
    (uint8_t*)MASS_ConfigDescriptor,
    MASS_SIZ_CONFIG_DESC
};

USB_OneDescriptor String_Descriptor[5] =
{
    {(uint8_t*)MASS_StringLangID, MASS_SIZ_STRING_LANGID},
    {(uint8_t*)MASS_StringVendor, MASS_SIZ_STRING_VENDOR},
    {(uint8_t*)MASS_StringProduct, MASS_SIZ_STRING_PRODUCT},
    {(uint8_t*)MASS_StringSerial, MASS_SIZ_STRING_SERIAL},
    {(uint8_t*)MASS_StringInterface, MASS_SIZ_STRING_INTERFACE},
};

/* Extern variables ----------------------------------------------------------*/
extern unsigned char Bot_State;
extern Bulk_Only_CBW CBW;

/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief Mass Storage init routine.
 */
void MASS_init()
{
    pInformation->CurrentConfiguration = 0;

    /* Connect the device */
    PowerOn();

    /* USB interrupts initialization */
    /* clear pending interrupts */
    _SetISTR(0);
    wInterrupt_Mask = IMR_MSK;
    /* set interrupts mask */
    _SetCNTR(wInterrupt_Mask);

    bDeviceState = UNCONNECTED;
}

/**
 * @brief Mass Storage reset routine.
 */
void MASS_Reset()
{
    /* Set the device as not configured */
    Device_Info.CurrentConfiguration = 0;

    /* Current Feature initialization */
    pInformation->CurrentFeature = MASS_ConfigDescriptor[7];

    USB_SetBuftab(BTABLE_ADDRESS);

    /* Initialize Endpoint 0 */
    USB_SetEpType(ENDP0, EP_CONTROL);
    SetEPTxStatus(ENDP0, EP_TX_NAK);
    USB_SetEpRxAddr(ENDP0, ENDP0_RXADDR);
    USB_SetEpRxCnt(ENDP0, Device_Property.MaxPacketSize);
    USB_SetEpTxAddr(ENDP0, ENDP0_TXADDR);
    USB_ClrStsOut(ENDP0);
    USB_SetEpRxValid(ENDP0);

    /* Initialize Endpoint 1 */
    USB_SetEpType(ENDP1, EP_BULK);
    USB_SetEpTxAddr(ENDP1, ENDP1_TXADDR);
    SetEPTxStatus(ENDP1, EP_TX_NAK);
    SetEPRxStatus(ENDP1, EP_RX_DIS);

    /* Initialize Endpoint 2 */
    USB_SetEpType(ENDP2, EP_BULK);
    USB_SetEpRxAddr(ENDP2, ENDP2_RXADDR);
    USB_SetEpRxCnt(ENDP2, Device_Property.MaxPacketSize);
    SetEPRxStatus(ENDP2, EP_RX_VALID);
    SetEPTxStatus(ENDP2, EP_TX_DIS);

    /* Set the device to response on default address */
    USB_SetDeviceAddress(0);

    bDeviceState = ATTACHED;

    CBW.dSignature = BOT_CBW_SIGNATURE;
    Bot_State = BOT_IDLE;
}

/**
 * @brief Handle the SetConfiguration request.
 */
void Mass_Storage_SetConfiguration(void)
{
    if (pInformation->CurrentConfiguration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;

        USB_ClrDattogTx(ENDP1);
        USB_ClrDattogRx(ENDP2);
        Bot_State = BOT_IDLE; /* set the Bot state machine to the IDLE state */
    }
}

/**
 * @brief Handle the ClearFeature request.
 */
void Mass_Storage_ClearFeature(void)
{
    /* when the host send a CBW with invalid signature or invalid length the two
       Endpoints (IN & OUT) shall stall until receiving a Mass Storage Reset     */
    if (CBW.dSignature != BOT_CBW_SIGNATURE)
        Bot_Abort(BOTH_DIR);
}

/**
 * @brief Udpade the device state to addressed.
 */
void Mass_Storage_SetDeviceAddress (void)
{
    bDeviceState = ADDRESSED;
}

/**
 * @brief Mass Storage Status IN routine.
 */
void MASS_Status_In(void)
{
    return;
}

/**
 * @brief Mass Storage Status OUT routine.
 */
void MASS_Status_Out(void)
{
    return;
}

/**
 * @brief  Handle the data class specific requests.
 * @param  RequestNo: request number.
 * @return UnSupport or Success.
 */
USB_Result MASS_Data_Setup(uint8_t RequestNo)
{
    uint8_t    *(*CopyRoutine)(uint16_t);

    CopyRoutine = NULL;
    if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
            && (RequestNo == GET_MAX_LUN) && (pInformation->USBwValue == 0)
            && (pInformation->USBwIndex == 0) && (pInformation->USBwLength == 0x01))
    {
        CopyRoutine = Get_Max_Lun;
    }
    else
    {
        return UnSupport;
    }

    if (CopyRoutine == NULL)
    {
        return UnSupport;
    }

    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    pInformation->Ctrl_Info.Usb_wOffset = 0;
    (*CopyRoutine)(0);

    return Success;

}

/**
 * @brief  Handle the no data class specific requests.
 * @param  RequestNo: request number.
 * @return UnSupport or Success.
 */
USB_Result MASS_NoData_Setup(uint8_t RequestNo)
{
    if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
            && (RequestNo == MASS_STORAGE_RESET) && (pInformation->USBwValue == 0)
            && (pInformation->USBwIndex == 0) && (pInformation->USBwLength == 0x00))
    {
        /* Initialize Endpoint 1 */
        USB_ClrDattogTx(ENDP1);

        /* Initialize Endpoint 2 */
        USB_ClrDattogRx(ENDP2);

        /*intialise the CBW signature to enable the clear feature*/
        CBW.dSignature = BOT_CBW_SIGNATURE;
        Bot_State = BOT_IDLE;

        return Success;
    }
    return UnSupport;
}

/**
 * @brief  Test the interface and the alternate setting according to the supported one.
 * @param  Interface: interface.
 * @param  AlternateSetting: alternate Setting.
 * @return UnSupport or Success.
 */
USB_Result MASS_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
    if (AlternateSetting > 0)
    {
        return UnSupport;/* in this application we don't have AlternateSetting*/
    }
    else if (Interface > 0)
    {
        return UnSupport;/*in this application we have only 1 interfaces*/
    }
    return Success;
}

/**
 * @brief   Gets the device descriptor.
 * @param   Length:Length.
 * @return  The address of the device descriptor.
 */
uint8_t *MASS_GetDeviceDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Device_Descriptor );
}

/**
 * @brief   Gets the configuration descriptor.
 * @param   Length:Length.
 * @return The address of the configuration descriptor.
 */
uint8_t *MASS_GetConfigDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Config_Descriptor );
}

/**
 * @brief   Gets the string descriptors according to the needed index.
 * @param   Length:Length.
 * @return  The address of the string descriptors.
 */
uint8_t *MASS_GetStringDescriptor(uint16_t Length)
{
    uint8_t wValue0 = pInformation->USBwValue0;

    if (wValue0 > 5)
    {
        return NULL;
    }
    else
    {
        return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
    }
}

/**
 * @brief   Handle the Get Max Lun request.
 * @param   Length:Length.
 * @return  max lun.
 */
uint8_t *Get_Max_Lun(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = LUN_DATA_LENGTH;
        return 0;
    }
    else
    {
        return((uint8_t*)(&Max_Lun));
    }
}


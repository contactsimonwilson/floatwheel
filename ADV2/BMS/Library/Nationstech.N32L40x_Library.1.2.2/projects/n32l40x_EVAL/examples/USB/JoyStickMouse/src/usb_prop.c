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
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "hw_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t ProtocolValue;

/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

USB_Device Device_Table =
{
    EP_NUM,
    1
};

DEVICE_PROP Device_Property =
{
    Joystick_init,
    Joystick_Reset,
    Joystick_Status_In,
    Joystick_Status_Out,
    Joystick_Data_Setup,
    Joystick_NoData_Setup,
    Joystick_Get_Interface_Setting,
    Joystick_GetDeviceDescriptor,
    Joystick_GetConfigDescriptor,
    Joystick_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
};
USER_STANDARD_REQUESTS User_Standard_Requests =
{
    Joystick_GetConfiguration,
    Joystick_SetConfiguration,
    Joystick_GetInterface,
    Joystick_SetInterface,
    Joystick_GetStatus,
    Joystick_ClearFeature,
    Joystick_SetEndPointFeature,
    Joystick_SetDeviceFeature,
    Joystick_SetDeviceAddress
};

USB_OneDescriptor Device_Descriptor = {(uint8_t*)Joystick_DeviceDescriptor, JOYSTICK_SIZ_DEVICE_DESC};

USB_OneDescriptor Config_Descriptor = {(uint8_t*)Joystick_ConfigDescriptor, JOYSTICK_SIZ_CONFIG_DESC};

USB_OneDescriptor Joystick_Report_Descriptor = {(uint8_t *)Joystick_ReportDescriptor, JOYSTICK_SIZ_REPORT_DESC};

USB_OneDescriptor Mouse_Hid_Descriptor = {(uint8_t*)Joystick_ConfigDescriptor + JOYSTICK_OFF_HID_DESC, JOYSTICK_SIZ_HID_DESC};

USB_OneDescriptor String_Descriptor[4] = {{(uint8_t*)Joystick_StringLangID, JOYSTICK_SIZ_STRING_LANGID},
                                          {(uint8_t*)Joystick_StringVendor, JOYSTICK_SIZ_STRING_VENDOR},
                                          {(uint8_t*)Joystick_StringProduct, JOYSTICK_SIZ_STRING_PRODUCT},
                                          {(uint8_t*)Joystick_StringSerial, JOYSTICK_SIZ_STRING_SERIAL}};

/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Joystick Mouse init routine.
 */
void Joystick_init(void)
{
    pInformation->CurrentConfiguration = 0;
    /* Connect the device */
    PowerOn();

    /* Perform basic device initialization operations */
    USB_SilInit();

    bDeviceState = UNCONNECTED;
}

/**
 * @brief   Joystick Mouse reset routine.
 */
void Joystick_Reset(void)
{
    /* Set Joystick_DEVICE as not configured */
    pInformation->CurrentConfiguration = 0;
    pInformation->CurrentInterface = 0;/*the default Interface*/

    /* Current Feature initialization */
    pInformation->CurrentFeature = Joystick_ConfigDescriptor[7];
    USB_SetBuftab(BTABLE_ADDRESS);
    /* Initialize Endpoint 0 */
    USB_SetEpType(ENDP0, EP_CONTROL);
    SetEPTxStatus(ENDP0, EP_TX_STALL);
    USB_SetEpRxAddr(ENDP0, ENDP0_RXADDR);
    USB_SetEpTxAddr(ENDP0, ENDP0_TXADDR);
    USB_ClrStsOut(ENDP0);
    USB_SetEpRxCnt(ENDP0, Device_Property.MaxPacketSize);
    USB_SetEpRxValid(ENDP0);

    /* Initialize Endpoint 1 */
    USB_SetEpType(ENDP1, EP_INTERRUPT);
    USB_SetEpTxAddr(ENDP1, ENDP1_TXADDR);
    USB_SetEpTxCnt(ENDP1, 4);
    SetEPRxStatus(ENDP1, EP_RX_DIS);
    SetEPTxStatus(ENDP1, EP_TX_NAK);

    /* Set this device to response on default address */
    USB_SetDeviceAddress(0);
    bDeviceState = ATTACHED;
}

/**
 * @brief   Update the device state to configured.
 */
void Joystick_SetConfiguration(void)
{
    USB_DeviceMess *pInfo = &Device_Info;

    if (pInfo->CurrentConfiguration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
}

/**
 * @brief   Update the device state to addressed.
 */
void Joystick_SetDeviceAddress (void)
{
    bDeviceState = ADDRESSED;
}

/**
 * @brief   Joystick status IN routine.
 */
void Joystick_Status_In(void)
{}

/**
 * @brief   Joystick status OUT routine.
 */
void Joystick_Status_Out (void)
{}

/**
 * @brief  Handle the data class specific requests.
 * @param  RequestNo : Request number.
 * @return USB_UNSUPPORT or USB_SUCCESS.
 */
USB_Result Joystick_Data_Setup(uint8_t RequestNo)
{
    uint8_t *(*CopyRoutine)(uint16_t);

    CopyRoutine = NULL;
    if ((RequestNo == GET_DESCRIPTOR)
      && (Type_Recipient == (STANDARD_REQUEST | INTERFACE_RECIPIENT))
      && (pInformation->USBwIndex0 == 0))
    {
        if (pInformation->USBwValue1 == REPORT_DESCRIPTOR)
        {
            CopyRoutine = Joystick_GetReportDescriptor;
        }
        else if (pInformation->USBwValue1 == HID_DESCRIPTOR_TYPE)
        {
            CopyRoutine = Joystick_GetHIDDescriptor;
        }
    } /* End of GET_DESCRIPTOR */

    /*** GET_PROTOCOL ***/
    else if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
           && RequestNo == GET_PROTOCOL)
    {
        CopyRoutine = Joystick_GetProtocolValue;
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
 * @brief  handle the no data class specific requests
 * @param  RequestNo : Request number.
 * @return USB_UNSUPPORT or USB_SUCCESS.
 */
USB_Result Joystick_NoData_Setup(uint8_t RequestNo)
{
    if ((Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
      && (RequestNo == SET_PROTOCOL))
    {
        return Joystick_SetProtocol();
    }

    else
    {
        return UnSupport;
    }
}

/**
 * @brief   Gets the device descriptor.
 * @param   Length : Length
 * @return  The address of the device descriptor.
 */
uint8_t *Joystick_GetDeviceDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/**
 * @brief   Gets the configuration descriptor.
 * @param   Length : Length
 * @return The address of the configuration descriptor.
 */
uint8_t *Joystick_GetConfigDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/**
 * @brief   Gets the string descriptors according to the needed index
 * @param   Length : Length
 * @return  The address of the string descriptors.
 */
uint8_t *Joystick_GetStringDescriptor(uint16_t Length)
{
    uint8_t wValue0 = pInformation->USBwValue0;
    if (wValue0 > 4)
    {
        return NULL;
    }
    else
    {
        return Standard_GetDescriptorData(Length, &String_Descriptor[wValue0]);
    }
}

/**
 * @brief   Gets the report descriptor.
 * @param   Length : Length
 * @return  The address of the report descriptor.
 */
uint8_t *Joystick_GetReportDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Joystick_Report_Descriptor);
}

/**
 * @brief   Gets the HID descriptor.
 * @param   Length : Length
 * @return   The address of the configuration descriptor.
 */
uint8_t *Joystick_GetHIDDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Mouse_Hid_Descriptor);
}

/**
 * @brief   Tests the interface and the alternate setting according to the supported one.
 * @param   Interface£ºinterface number.
 * @param   AlternateSetting : Alternate Setting number.
 * @return  USB_SUCCESS or USB_UNSUPPORT.
 */
USB_Result Joystick_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
    if (AlternateSetting > 0)
    {
        return UnSupport;
    }
    else if (Interface > 0)
    {
        return UnSupport;
    }
    return Success;
}

/**
 * @brief   Joystick Set Protocol request routine.
 * @return  USB_SUCCESS.
 */
USB_Result Joystick_SetProtocol(void)
{
    uint8_t wValue0 = pInformation->USBwValue0;
    ProtocolValue = wValue0;
    return Success;
}

/**
 * @brief   Get the protocol value.
 * @param   Length : Length
 * @return  address of the protocol value.
 */
uint8_t *Joystick_GetProtocolValue(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = 1;
        return NULL;
    }
    else
    {
        return (uint8_t *)(&ProtocolValue);
    }
}


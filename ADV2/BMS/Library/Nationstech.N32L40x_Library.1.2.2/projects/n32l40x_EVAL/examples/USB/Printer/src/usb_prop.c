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
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"

uint32_t ProtocolValue;
__IO uint8_t EXTI_Enable;
__IO uint8_t Request = 0;
uint8_t Report_Buf[2];




/**---------- CDC REQUESTS FUNCTION ----------*/
uint8_t *Virtual_Com_Port_GetLineCoding(uint16_t Length);
uint8_t *Virtual_Com_Port_SetLineCoding(uint16_t Length);


typedef struct
{
    uint32_t    bitrate;
    uint8_t     format;
    uint8_t     paritytype;
    uint8_t     datatype;
}LINE_CODING;

LINE_CODING linecoding =
{
    115200,     /* baud rate*/
    0x00,       /* stop bits-1*/
    0x00,       /* parity - none*/
    0x08        /* no. of bits 8*/
};

uint8_t USB_Printer_IDString[103] = 
{
    0x00, 0x67,
    'M', 'A', 'N', 'U', 'F', 'A', 'C', 'T', 'U', 'R', 'E', 'R', ':',
    'N', 'S', '3', '2', ' ', 'D', 'E', 'V', 'I', 'C', 'E', '-', ';',
    'C', 'O', 'M', 'M', 'A', 'N', 'D', ' ', 'S', 'E', 'T', ':',
    'P', 'C', 'L', ',', 'M', 'P', 'L', ';',
    'M', 'O', 'D', 'E', 'L', ':',
    'L', 'a', 's', 'e', 'r', 'B', 'e', 'a', 'm', '?', ';',
    'C', 'O', 'M', 'M', 'E', 'N', 'T', ':',
    'G', 'o', 'o', 'd', ' ', '!', ';',
    'A', 'C', 'T', 'I', 'V', 'E', ' ', 'C', 'O', 'M', 'M', 'A', 'N', 'D', ' ', 'S', 'E', 'T', ':',
    'P', 'C', 'L', ';'
};



/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

USB_Device Device_Table = {EP_NUM, 1};


/**---------- Device call back function ----------*/
DEVICE_PROP Device_Property = 
{
    Printer_init,
    Printer_Reset,
    Printer_Status_In,
    Printer_Status_Out,
    Printer_Data_Setup,
    Printer_NoData_Setup,
    Printer_Get_Interface_Setting,
    Printer_GetDeviceDescriptor,
    Printer_GetConfigDescriptor,
    Printer_GetStringDescriptor,
    0,
    0x40 /*MAX PACKET SIZE*/
};

/**---------- USB Standard requests function ----------*/
USER_STANDARD_REQUESTS User_Standard_Requests = 
{
    Printer_GetConfiguration,
    Printer_SetConfiguration,
    Printer_GetInterface,
    Printer_SetInterface,
    Printer_GetStatus,
    Printer_ClearFeature,
    Printer_SetEndPointFeature,
    Printer_SetDeviceFeature,
    Printer_SetDeviceAddress
};

/**---------- ----------*/
USB_OneDescriptor Device_Descriptor = 
{
    (uint8_t*)Printer_DeviceDescriptor, 
    18
};

/**---------- ----------*/
USB_OneDescriptor Config_Descriptor = 
{
    (uint8_t*)Printer_ConfigDescriptor, 
    CONFIG_DESC_SIZE
};

/**---------- ----------*/
//USB_OneDescriptor Printer_Report_Descriptor = 
//{
//(uint8_t*)Printer_ReportDescriptor, 
//Printer_SIZ_REPORT_DESC
//};


/**---------- ----------*/
USB_OneDescriptor Printer_Descriptor = 
{
    (uint8_t*)Printer_ConfigDescriptor + Printer_OFF_DESC,
    Printer_SIZ_DESC
};

/**---------- ----------*/
USB_OneDescriptor String_Descriptor[4] = 
{
    {(uint8_t*)Printer_StringLangID,    Printer_SIZ_STRING_LANGID},
    {(uint8_t*)Printer_StringVendor,    Printer_SIZ_STRING_VENDOR},
    {(uint8_t*)Printer_StringProduct,   Printer_SIZ_STRING_PRODUCT},
    {(uint8_t*)Printer_StringSerial,    Printer_SIZ_STRING_SERIAL}
};



/*Printer_SetReport_Feature function prototypes*/
uint8_t* Printer_SetReport_Feature(uint16_t Length);




/* Extern function prototypes ------------------------------------------------*/


extern void Get_SerialNum(void);

/**
 * @brief  Printer init routine.
 */
void Printer_init(void)
{
    /* Update the serial number string descriptor with the data from the unique
    ID*/
    Get_SerialNum();


    pInformation->CurrentConfiguration = 0;
    /* Connect the device */
    PowerOn();

    /* Perform basic device initialization operations */
    USB_SilInit();

    bDeviceState = UNCONNECTED;
}

/**
 * @brief  Printer reset routine.
 */
void Printer_Reset(void)
{
    /* Set Printer_DEVICE as not configured */
    pInformation->CurrentConfiguration = 0;
    pInformation->CurrentInterface     = 0; /*the default Interface*/

    /* Current Feature initialization */
    pInformation->CurrentFeature = Printer_ConfigDescriptor[7];

    USB_SetBuftab(BTABLE_ADDRESS);

    /* Initialize Endpoint 0 */
    USB_SetEpType(ENDP0, EP_CONTROL);
    SetEPTxStatus(ENDP0, EP_TX_STALL);
    USB_SetEpRxAddr(ENDP0, ENDP0_RXADDR);
    USB_SetEpTxAddr(ENDP0, ENDP0_TXADDR);
    USB_ClrStsOut(ENDP0);
    USB_SetEpRxCnt(ENDP0, Device_Property.MaxPacketSize);
    USB_SetEpRxValid(ENDP0);

    /* Initialize Endpoint 2 */
    USB_SetEpType(ENDP2, EP_BULK);
    USB_SetEpTxAddr(ENDP2, ENDP2_TXADDR);
    USB_SetEpRxAddr(ENDP2, ENDP2_RXADDR);
    USB_SetEpTxCnt(ENDP2, 0);
    USB_SetEpRxCnt(ENDP2, EP2_OUT_SIZE);
    SetEPRxStatus(ENDP2, EP_RX_VALID);
    SetEPTxStatus(ENDP2, EP_TX_VALID);

    /* Set this device to response on default address */
    USB_SetDeviceAddress(0);
    bDeviceState = ATTACHED;
}

/**
 * @brief  Update the device state to configured
 */
void Printer_SetConfiguration(void)
{
    if (pInformation->CurrentConfiguration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
}

/**
 * @brief  Update the device state to addressed.
 */
void Printer_SetDeviceAddress(void)
{
    bDeviceState = ADDRESSED;
}

/**
 * @brief  Printer status IN routine.
 */
void Printer_Status_In(void)
{
}

/**
 * @brief  Printer status OUT routine.
 */
void Printer_Status_Out(void)
{
}

/**
 * @brief  Handle the data class specific requests.
 * @param  RequestNo: Request number.
 * @return Success or UnSupport.
 */
USB_Result Printer_Data_Setup(uint8_t RequestNo)
{
    uint8_t    *(*CopyRoutine)(uint16_t);

    CopyRoutine = NULL;

    if(Type_Recipient == (CLASS_REQUEST & (REQUEST_TYPE | RECIPIENT)) )
    {
        if(RequestNo == GET_DEVICE_ID)
        {
            CopyRoutine = USB_Printer_ID;
        }
        else if (RequestNo == GET_PORT_STATUS)
        {
        }
        else if (RequestNo == SOFT_RESET)
        {
        }
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
 * @brief  Set Feature request handling
 * @param  Length: data length.
 * @return buf pointer
 */
uint8_t* Printer_SetReport_Feature(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = 2;
        return NULL;
    }
    else
    {
        return Report_Buf;
    }
}

/**
 * @brief   handle the no data class specific requests
 * @param   RequestNo: Request number.
 * @return  Success or UnSupport.
 */
USB_Result Printer_NoData_Setup(uint8_t RequestNo)
{
    if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
    {
        if (RequestNo == SET_COMM_FEATURE)
        {
            return Success;
        }
        else if (RequestNo == SET_CONTROL_LINE_STATE)
        {
            return Success;
        }
    }

  return UnSupport;
}

/**
 * @brief   Gets the device descriptor.
 * @param   Length:Length.
 * @return  The address of the device descriptors.
 */
uint8_t* Printer_GetDeviceDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Device_Descriptor);
}

/**
 * @brief   Gets the configuration descriptor.
 * @param   Length:Length.
 * @return  The address of the configuration descriptors.
 */
uint8_t* Printer_GetConfigDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Config_Descriptor);
}

/**
 * @brief   Gets the string descriptors according to the needed index
 * @param   Length:Length.
 * @return  The address of the string descriptors.
 */
uint8_t* Printer_GetStringDescriptor(uint16_t Length)
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
 * @param   Length:Length.
 * @return  The address of the report descriptors.
 */
//uint8_t* Printer_GetReportDescriptor(uint16_t Length)
//{
//    return Standard_GetDescriptorData(Length, &Printer_Report_Descriptor);
//}

/**
 * @brief   Gets the descriptor.
 * @param   Length:Length.
 * @return  The address of the descriptors.
 */
uint8_t* Printer_GetDescriptor(uint16_t Length)
{
    return Standard_GetDescriptorData(Length, &Printer_Descriptor);
}

/**
 * @brief   tests the interface and the alternate setting according to the
 *                  supported one.
 * @param   Interface : interface number.
 * @param   AlternateSetting : Alternate Setting number.
 * @return  Success or UnSupport.
 */
USB_Result Printer_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
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
 * @brief   Printer Set Protocol request routine.
 * @return  Success.
 */
USB_Result Printer_SetProtocol(void)
{
    uint8_t wValue0 = pInformation->USBwValue0;
    ProtocolValue   = wValue0;
    return Success;
}

/**
 * @brief   get the protocol value
 * @param   Length: Length.
 * @return  address of the protocol value.
 */
uint8_t* Printer_GetProtocolValue(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = 1;
        return NULL;
    }
    else
    {
        return (uint8_t*)(&ProtocolValue);
    }
}

/**
  * @brief  send the USB Printer ID .
  * @param  Length: LineCoding length
  * @return address of the printer ID string.
  */
uint8_t *USB_Printer_ID(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(USB_Printer_IDString);
        return NULL;
    }
    return(uint8_t *)&USB_Printer_IDString;
}




/**================================================================================
  * @brief  send the linecoding structure to the PC host.
  * @param  Length: LineCoding length
  * @retval linecodeing address pointer
  ================================================================================*/
uint8_t *Virtual_Com_Port_GetLineCoding(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return(uint8_t *)&linecoding;
}


/**================================================================================
  * @brief  Set the linecoding structure fields.
  * @param  Length: LineCoding length
  * @retval linecodeing address pointer
  ================================================================================*/
uint8_t *Virtual_Com_Port_SetLineCoding(uint16_t Length)
{
    if (Length == 0)
    {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
        return NULL;
    }
    return(uint8_t *)&linecoding;
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

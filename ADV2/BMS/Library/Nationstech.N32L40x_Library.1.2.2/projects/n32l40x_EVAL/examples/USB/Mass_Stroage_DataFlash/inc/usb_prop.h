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
 * @file usb_prop.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_PROP_H
#define __USB_PROP_H

#include "stdint.h"
#include "usb_core.h"

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define Mass_Storage_GetConfiguration          USB_ProcessNop
/* #define Mass_Storage_SetConfiguration          USB_ProcessNop*/
#define Mass_Storage_GetInterface              USB_ProcessNop
#define Mass_Storage_SetInterface              USB_ProcessNop
#define Mass_Storage_GetStatus                 USB_ProcessNop
/* #define Mass_Storage_ClearFeature              USB_ProcessNop*/
#define Mass_Storage_SetEndPointFeature        USB_ProcessNop
#define Mass_Storage_SetDeviceFeature          USB_ProcessNop
/*#define Mass_Storage_SetDeviceAddress          USB_ProcessNop*/

/* MASS Storage Requests*/
#define GET_MAX_LUN                0xFE
#define MASS_STORAGE_RESET         0xFF
#define LUN_DATA_LENGTH            1

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MASS_init(void);
void MASS_Reset(void);
void Mass_Storage_SetConfiguration(void);
void Mass_Storage_ClearFeature(void);
void Mass_Storage_SetDeviceAddress (void);
void MASS_Status_In (void);
void MASS_Status_Out (void);
USB_Result MASS_Data_Setup(uint8_t);
USB_Result MASS_NoData_Setup(uint8_t);
USB_Result MASS_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting);
uint8_t *MASS_GetDeviceDescriptor(uint16_t );
uint8_t *MASS_GetConfigDescriptor(uint16_t);
uint8_t *MASS_GetStringDescriptor(uint16_t);
uint8_t *Get_Max_Lun(uint16_t Length);


#endif /* __USB_PROP_H */


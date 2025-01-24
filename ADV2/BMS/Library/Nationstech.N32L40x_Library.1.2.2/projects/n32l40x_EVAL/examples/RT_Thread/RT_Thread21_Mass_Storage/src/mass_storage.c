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
 * @file mass_storage.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

/* include ------------------------------------------------------------------*/
#include "main.h"
#include "usbd_core.h"
#include "usbd_msc.h"

#define FLASH_START_ADDR    0x08010000  // Flash start address
#define FLASH_SIZE          0x10000
#define FLASH_PAGE_SIZE     0x800       // 2K per page
#define FLASH_WAIT_TIMEOUT  100000

#define MSC_IN_EP  0x81
#define MSC_OUT_EP 0x01

#define USBD_VID           0x19F5
#define USBD_PID           0x5770
#define USBD_MAX_POWER     100
#define USBD_LANGID_STRING 1033

#define USB_CONFIG_SIZE (9 + MSC_DESCRIPTOR_LEN)

const uint8_t msc_ram_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0x00, 0x00, 0x00, USBD_VID, USBD_PID, 0x0200, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x01, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    MSC_DESCRIPTOR_INIT(0x00, MSC_OUT_EP, MSC_IN_EP, 0x02),
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
    0x2c,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'N', 0x00,                  /* wcChar0 */
    '3', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    'L', 0x00,                  /* wcChar3 */
    '4', 0x00,                  /* wcChar4 */
    '0', 0x00,                  /* wcChar5 */
    'x', 0x00,                  /* wcChar6 */
    ' ', 0x00,                  /* wcChar7 */
    ' ', 0x00,                  /* wcChar8 */
    'M', 0x00,                  /* wcChar9 */
    'a', 0x00,                  /* wcChar10 */
    's', 0x00,                  /* wcChar11 */
    's', 0x00,                  /* wcChar12 */
    ' ', 0x00,                  /* wcChar13 */
    'S', 0x00,                  /* wcChar14 */
    't', 0x00,                  /* wcChar15 */
    'o', 0x00,                  /* wcChar16 */
    'r', 0x00,                  /* wcChar17 */
    'a', 0x00,                  /* wcChar18 */
    'g', 0x00,                  /* wcChar19 */
    'e', 0x00,                  /* wcChar20 */
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

#define BLOCK_SIZE  2048    //page size 2k
#define BLOCK_COUNT 32

void usbd_msc_get_cap(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
    *block_num = BLOCK_COUNT;
    *block_size = BLOCK_SIZE;
}
int usbd_msc_sector_read(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    uint16_t i;
    for( i=0; i < length; i+=4 )
    {
        buffer[i>>2] = ((vu32*)(FLASH_START_ADDR + sector*BLOCK_SIZE))[i>>2]; 
    }
    return 0;
}

int usbd_msc_sector_write(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    uint16_t i;
    for( i = 0; i < length; i += FLASH_PAGE_SIZE )
    { 
        if( FLASH_WaitForLastOpt(FLASH_WAIT_TIMEOUT) != FLASH_TIMEOUT )
        {
            FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR);
        }     
        FLASH_EraseOnePage(FLASH_START_ADDR + sector*BLOCK_SIZE + i); 
    }            

    for( i = 0; i < length; i+=4 )
    { 
        if( FLASH_WaitForLastOpt(FLASH_WAIT_TIMEOUT) != FLASH_TIMEOUT )
        {
            FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR); 
        } 
        FLASH_ProgramWord(FLASH_START_ADDR + sector*BLOCK_SIZE + i , buffer[i>>2]); 
    }
    return 0;
}

/* function ------------------------------------------------------------------*/
/**
  * @brief            msc_flash_init
  * @pre              none
  * @param[in]        none
  * @retval           none
  */
void msc_flash_init(void)
{
    usbd_desc_register(msc_ram_descriptor);
    usbd_msc_class_init(MSC_OUT_EP, MSC_IN_EP);
    usbd_initialize();
    FLASH_Unlock();
}

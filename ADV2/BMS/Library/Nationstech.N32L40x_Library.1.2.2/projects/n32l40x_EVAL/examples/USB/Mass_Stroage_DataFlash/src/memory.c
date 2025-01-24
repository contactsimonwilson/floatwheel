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
 * @file memory.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

/* Includes ------------------------------------------------------------------*/

#include "memory.h"
#include "usb_scsi.h"
#include "usb_bot.h"
#include "usb_regs.h"
#include "usb_mem.h"
#include "usb_conf.h"
#include "hw_config.h"
#include "mass_mal.h"
#include "usb_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t Block_Read_count = 0;
__IO uint32_t Block_offset;
__IO uint32_t Counter = 0;
uint32_t  Idx;
uint32_t Data_Buffer[BULK_MAX_PACKET_SIZE *4 *2]; /* 512 bytes*/
uint8_t TransferState = TXFR_IDLE;
/* Extern variables ----------------------------------------------------------*/
extern uint8_t Bulk_Data_Buff[BULK_MAX_PACKET_SIZE];  /* data buffer*/
extern uint16_t Data_Len;
extern uint8_t Bot_State;
extern Bulk_Only_CBW CBW;
extern Bulk_Only_CSW CSW;
extern uint32_t Mass_Memory_Size[2];
extern uint32_t Mass_Block_Size[2];

/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief   Handle the Read operation from the flash.
 * @param   lun: logical unit.
 * @param   Memory_Offset: memory offset.
 * @param   Transfer_Length: transfer data length.
 */
void Read_Memory(uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length)
{
    static uint32_t Offset, Length;

    if (TransferState == TXFR_IDLE )
    {
        Offset = Memory_Offset * Mass_Block_Size[lun];
        Length = Transfer_Length * Mass_Block_Size[lun];
        TransferState = TXFR_ONGOING;
    }

    if (TransferState == TXFR_ONGOING )
    {
        if (!Block_Read_count)
        {
            MAL_Read(lun ,
                     Offset ,
                     Data_Buffer,
                     Mass_Block_Size[lun]);

            USB_SilWrite(EP1_IN, (uint8_t *)Data_Buffer, BULK_MAX_PACKET_SIZE);

            Block_Read_count = Mass_Block_Size[lun] - BULK_MAX_PACKET_SIZE;
            Block_offset = BULK_MAX_PACKET_SIZE;
        }
        else
        {
            USB_SilWrite(EP1_IN, (uint8_t *)Data_Buffer + Block_offset, BULK_MAX_PACKET_SIZE);

            Block_Read_count -= BULK_MAX_PACKET_SIZE;
            Block_offset += BULK_MAX_PACKET_SIZE;
        }

        USB_SetEpTxCnt(ENDP1, BULK_MAX_PACKET_SIZE);
        SetEPTxStatus(ENDP1, EP_TX_VALID);  
        Offset += BULK_MAX_PACKET_SIZE;
        Length -= BULK_MAX_PACKET_SIZE;

        CSW.dDataResidue -= BULK_MAX_PACKET_SIZE;
    }
    
    if (Length == 0)
    {
        Block_Read_count = 0;
        Block_offset = 0;
        Offset = 0;
        Bot_State = BOT_DATA_IN_LAST;
        TransferState = TXFR_IDLE;
    }
}

/**
 * @brief   Handle the Write operation to the flash.
 * @param   lun: logical unit.
 * @param   Memory_Offset: memory offset.
 * @param   Transfer_Length: transfer data length.
 */
void Write_Memory (uint8_t lun, uint32_t Memory_Offset, uint32_t Transfer_Length)
{
    static uint32_t W_Offset, W_Length;

    uint32_t temp =  Counter + 64;

    if (TransferState == TXFR_IDLE )
    {
        W_Offset = Memory_Offset * Mass_Block_Size[lun];
        W_Length = Transfer_Length * Mass_Block_Size[lun];
        TransferState = TXFR_ONGOING;
    }

    if (TransferState == TXFR_ONGOING )
    {

        for (Idx = 0 ; Counter < temp; Counter++)
        {
            *((uint8_t *)Data_Buffer + Counter) = Bulk_Data_Buff[Idx++];
        }

        W_Offset += Data_Len;
        W_Length -= Data_Len;

        if (!(W_Length % Mass_Block_Size[lun]))
        {
            Counter = 0;
            MAL_Write(lun ,
                      W_Offset - Mass_Block_Size[lun],
                      Data_Buffer,
                      Mass_Block_Size[lun]);
        }

        CSW.dDataResidue -= Data_Len;
        SetEPRxStatus(ENDP2, EP_RX_VALID); /* enable the next transaction*/   
    }

    if ((W_Length == 0) || (Bot_State == BOT_CSW_Send))
    {
        Counter = 0;
        Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);
        TransferState = TXFR_IDLE;
    }
}

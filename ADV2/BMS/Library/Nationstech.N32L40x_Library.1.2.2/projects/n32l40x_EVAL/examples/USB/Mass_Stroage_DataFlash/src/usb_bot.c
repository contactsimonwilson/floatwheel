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
 * @file usb_bot.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

/* Includes ------------------------------------------------------------------*/
#include "usb_scsi.h"
#include "hw_config.h"
#include "usb_regs.h"
#include "usb_mem.h"
#include "usb_conf.h"
#include "usb_bot.h"
#include "memory.h"
#include "usb_lib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t Bot_State;
uint8_t Bulk_Data_Buff[BULK_MAX_PACKET_SIZE];  /* data buffer*/
uint16_t Data_Len;
Bulk_Only_CBW CBW;
Bulk_Only_CSW CSW;
uint32_t SCSI_LBA , SCSI_BlkLen;
extern uint32_t Max_Lun;
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief   Mass Storage IN transfer.
 */
void Mass_Storage_In (void)
{
  switch (Bot_State)
  {
    case BOT_CSW_Send:
    case BOT_ERROR:
      Bot_State = BOT_IDLE;
      SetEPRxStatus(ENDP2, EP_RX_VALID);/* enable the Endpoint to receive the next cmd*/
      if (USB_GetEpRxSts(EP2_OUT) == EP_RX_STALL)
      {
        SetEPRxStatus(EP2_OUT, EP_RX_VALID);/* enable the Endpoint to receive the next cmd*/
      }
      break;
    case BOT_DATA_IN:
      switch (CBW.CB[0])
      {
        case SCSI_READ10:
          SCSI_Read10_Cmd(CBW.bLUN , SCSI_LBA , SCSI_BlkLen);
          break;
      }
      break;
    case BOT_DATA_IN_LAST:
      Set_CSW (CSW_CMD_PASSED, SEND_CSW_ENABLE);

      SetEPRxStatus(ENDP2, EP_RX_VALID);
      break;
    default:
      break;
  }
}

/**
 * @brief   Mass Storage OUT transfer.
 */
void Mass_Storage_Out (void)
{
  uint8_t CMD;
  CMD = CBW.CB[0];

  Data_Len = USB_SilRead(EP2_OUT, Bulk_Data_Buff);

  switch (Bot_State)
  {
    case BOT_IDLE:
      CBW_Decode();
      break;
    case BOT_DATA_OUT:
      if (CMD == SCSI_WRITE10)
      {
        SCSI_Write10_Cmd(CBW.bLUN , SCSI_LBA , SCSI_BlkLen);
        break;
      }
      Bot_Abort(DIR_OUT);
      Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
      Set_CSW (CSW_PHASE_ERROR, SEND_CSW_DISABLE);
      break;
    default:
      Bot_Abort(BOTH_DIR);
      Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
      Set_CSW (CSW_PHASE_ERROR, SEND_CSW_DISABLE);
      break;
  }
}

/**
 * @brief   Decode the received CBW and call the related SCSI command.
 */
void CBW_Decode(void)
{
  uint32_t Counter;

  for (Counter = 0; Counter < Data_Len; Counter++)
  {
    *((uint8_t *)&CBW + Counter) = Bulk_Data_Buff[Counter];
  }
  CSW.dTag = CBW.dTag;
  CSW.dDataResidue = CBW.dDataLength;
  if (Data_Len != BOT_CBW_PACKET_LENGTH)
  {
    Bot_Abort(BOTH_DIR);
    /* reset the CBW.dSignature to disable the clear feature until receiving a Mass storage reset*/
    CBW.dSignature = 0;
    Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, PARAMETER_LIST_LENGTH_ERROR);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
    return;
  }

  if ((CBW.CB[0] == SCSI_READ10 ) || (CBW.CB[0] == SCSI_WRITE10 ))
  {
    /* Calculate Logical Block Address */
    SCSI_LBA = (CBW.CB[2] << 24) | (CBW.CB[3] << 16) | (CBW.CB[4] <<  8) | CBW.CB[5];
    /* Calculate the Number of Blocks to transfer */
    SCSI_BlkLen = (CBW.CB[7] <<  8) | CBW.CB[8];
  }

  if (CBW.dSignature == BOT_CBW_SIGNATURE)
  {
    /* Valid CBW */
    if ((CBW.bLUN > Max_Lun) || (CBW.bCBLength < 1) || (CBW.bCBLength > 16))
    {
      Bot_Abort(BOTH_DIR);
      Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_FIELED_IN_COMMAND);
      Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
    }
    else
    {
      switch (CBW.CB[0])
      {
        case SCSI_REQUEST_SENSE:
          SCSI_RequestSense_Cmd (CBW.bLUN);
          break;
        case SCSI_INQUIRY:
          SCSI_Inquiry_Cmd(CBW.bLUN);
          break;
        case SCSI_START_STOP_UNIT:
          SCSI_Start_Stop_Unit_Cmd(CBW.bLUN);
          break;
        case SCSI_ALLOW_MEDIUM_REMOVAL:
          SCSI_Start_Stop_Unit_Cmd(CBW.bLUN);
          break;
        case SCSI_MODE_SENSE6:
          SCSI_ModeSense6_Cmd (CBW.bLUN);
          break;
        case SCSI_MODE_SENSE10:
          SCSI_ModeSense10_Cmd (CBW.bLUN);
          break;
        case SCSI_READ_FORMAT_CAPACITIES:
          SCSI_ReadFormatCapacity_Cmd(CBW.bLUN);
          break;
        case SCSI_READ_CAPACITY10:
          SCSI_ReadCapacity10_Cmd(CBW.bLUN);
          break;
        case SCSI_TEST_UNIT_READY:
          SCSI_TestUnitReady_Cmd(CBW.bLUN);
          break;
        case SCSI_READ10:
          SCSI_Read10_Cmd(CBW.bLUN, SCSI_LBA , SCSI_BlkLen);
          break;
        case SCSI_WRITE10:
          SCSI_Write10_Cmd(CBW.bLUN, SCSI_LBA , SCSI_BlkLen);
          break;
        case SCSI_VERIFY10:
          SCSI_Verify10_Cmd(CBW.bLUN);
          break;
        case SCSI_FORMAT_UNIT:
          SCSI_Format_Cmd(CBW.bLUN);
          break;
          /*Unsupported command*/
        case SCSI_MODE_SELECT10:
          SCSI_Mode_Select10_Cmd(CBW.bLUN);
          break;
        case SCSI_MODE_SELECT6:
          SCSI_Mode_Select6_Cmd(CBW.bLUN);
          break;

        case SCSI_SEND_DIAGNOSTIC:
          SCSI_Send_Diagnostic_Cmd(CBW.bLUN);
          break;
        case SCSI_READ6:
          SCSI_Read6_Cmd(CBW.bLUN);
          break;
        case SCSI_READ12:
          SCSI_Read12_Cmd(CBW.bLUN);
          break;
        case SCSI_READ16:
          SCSI_Read16_Cmd(CBW.bLUN);
          break;
        case SCSI_READ_CAPACITY16:
          SCSI_READ_CAPACITY16_Cmd(CBW.bLUN);
          break;
        case SCSI_WRITE6:
          SCSI_Write6_Cmd(CBW.bLUN);
          break;
        case SCSI_WRITE12:
          SCSI_Write12_Cmd(CBW.bLUN);
          break;
        case SCSI_WRITE16:
          SCSI_Write16_Cmd(CBW.bLUN);
          break;
        case SCSI_VERIFY12:
          SCSI_Verify12_Cmd(CBW.bLUN);
          break;
        case SCSI_VERIFY16:
          SCSI_Verify16_Cmd(CBW.bLUN);
          break;

        default:
        {
          Bot_Abort(BOTH_DIR);
          Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
          Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
        }
      }
    }
  }
  else
  {
    /* Invalid CBW */
    Bot_Abort(BOTH_DIR);
    Set_Scsi_Sense_Data(CBW.bLUN, ILLEGAL_REQUEST, INVALID_COMMAND);
    Set_CSW (CSW_CMD_FAILED, SEND_CSW_DISABLE);
  }
}

/**
 * @brief   Send the request response to the PC HOST.
 * @param   Data_Pointer: point to the data to transfer.
 * @param   Data_Len: the number of Bytes to transfer.
 */
void Transfer_Data_Request(uint8_t* Data_Pointer, uint16_t Data_Len)
{
  USB_SilWrite(EP1_IN, Data_Pointer, Data_Len);

    SetEPTxStatus(ENDP1, EP_TX_VALID);
    
  Bot_State = BOT_DATA_IN_LAST;
  CSW.dDataResidue -= Data_Len;
  CSW.bStatus = CSW_CMD_PASSED;
}

/**
 * @brief   Set the SCW with the needed fields.
 * @param   CSW_Status: CSW_Status this filed can be CSW_CMD_PASSED,CSW_CMD_FAILED or CSW_PHASE_ERROR.
 * @param   Send_Permission: send permission.
 */
void Set_CSW (uint8_t CSW_Status, uint8_t Send_Permission)
{
  CSW.dSignature = BOT_CSW_SIGNATURE;
  CSW.bStatus = CSW_Status;

  USB_SilWrite(EP1_IN, ((uint8_t *)& CSW), CSW_DATA_LENGTH);

  Bot_State = BOT_ERROR;
  if (Send_Permission)
  {
    Bot_State = BOT_CSW_Send;
    SetEPTxStatus(ENDP1, EP_TX_VALID);
  }
}

/**
 * @brief   Stall the needed Endpoint according to the selected direction.
 * @param   Direction: Endpoint direction IN, OUT or both directions.
 */
void Bot_Abort(uint8_t Direction)
{
  switch (Direction)
  {
    case DIR_IN :
      SetEPTxStatus(ENDP1, EP_TX_STALL);
      break;
    case DIR_OUT :
      SetEPRxStatus(ENDP2, EP_RX_STALL);
      break;
    case BOTH_DIR :
      SetEPTxStatus(ENDP1, EP_TX_STALL);
      SetEPRxStatus(ENDP2, EP_RX_STALL);
      break;
    default:
      break;
  }
}


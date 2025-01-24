/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * @file lin_master.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include "lin_master.h"

M_LIN_EX_MSG M_TxMsg;

//set frame data
void SetFrameMsg(M_LIN_EX_MSG *dst_Msg, M_LIN_EX_MSG src_Msg)
{
    int i = 0;
    Memset(dst_Msg, 0, sizeof(M_LIN_EX_MSG));
    dst_Msg->Check = src_Msg.Check;
    dst_Msg->DataLen = src_Msg.DataLen;
    dst_Msg->Sync = src_Msg.Sync;
    dst_Msg->PID = src_Msg.PID;
    for(i = 0; i < src_Msg.DataLen; i++)
    {
        dst_Msg->Data[i] = src_Msg.Data[i];
    }
}

//set PID
void SetFramePID(M_LIN_EX_MSG *src_Msg)
{
    uint8_t p0 = 0, p1 = 0;
    uint8_t LIN_ID = src_Msg->PID, PID = 0x00;
    p0 = (LIN_ID & 0x01) ^ ((LIN_ID & 0x02) >> 1) ^ ((LIN_ID & 0x04) >> 2) ^ ((LIN_ID & 0x10) >> 4);
    p0 = p0 & 0x01;
    p1 = ~(((LIN_ID & 0x02) >> 1) ^ ((LIN_ID & 0x08) >> 3) ^ ((LIN_ID & 0x10) >> 4) ^ ((LIN_ID & 0x20) >> 5));
    p1 = p1 & 0x01;
    PID = (p1 << 7) | (p0 << 6) | LIN_ID;
    src_Msg->PID = PID;
    log_info("p0 = %02x;p1 = %02x;PID = %02x\r\n", p0, p1, PID);
}

//get checksum
uint8_t MasterGetCheckSum(uint8_t *pData, uint8_t len)
{
    uint16_t check_sum_temp = 0;
    uint8_t i;
    for(i = 0; i < len; i++)
    {
        check_sum_temp += pData[i];
        if(check_sum_temp > 0xFF)
        {
            check_sum_temp -= 0xFF;
        }
    }
    return (~check_sum_temp) & 0xFF;
}

//set checksum
void SetFrameChacksum(M_LIN_EX_MSG *Msg)
{
    uint8_t CheckSum = 0;
    uint8_t len = Msg->DataLen;
    if(Msg->Check)
    {
        CheckSum = MasterGetCheckSum(&Msg->PID, len + 1);
    }
    else
    {
        CheckSum = MasterGetCheckSum(Msg->Data, len);
    }
    if(len < 8)
    {
        Msg->Data[len] = CheckSum;
    }
    else
    {
        Msg->Check = CheckSum;
    }
}
void MasterSendBytes(uint8_t *pBuf, uint8_t Len)
{
    USART_SendBreak(USARTz);
    while(Len--)
    {
        while(USART_GetFlagStatus(USARTz, USART_FLAG_TXC ) == RESET);
        USART_SendData(USARTz, *pBuf++);
     }
    while(USART_GetFlagStatus(USARTz, USART_FLAG_TXC ) == RESET);
}

//send data
void MasterSendFrame(M_LIN_EX_MSG     Msg)
{
    if(Msg.DataLen)
    {
        MasterSendBytes(&Msg.Sync, Msg.DataLen + 3);
    }
    else
    {
        MasterSendBytes(&Msg.Sync, 2);
    }
}

//frame type
void FrameHandle()
{
    uint8_t tmp_PID  = M_TxMsg.PID;
    SetFramePID(&M_TxMsg);
    switch (tmp_PID)
    {
    case 0x3C://主机请求帧
        SetFrameChacksum(&M_TxMsg);
        break;
    case 0x3D://从机应答帧
        M_TxMsg.DataLen = 0;
        break;
    default:
        break;
    }
    MasterSendFrame(M_TxMsg);
}

/**
  * @brief  Receives a new data while the time out not elapsed.
  * @param  None
  * @retval An ErrorStatus enumuration value:
  *          - SUCCESS: New data has been received
  *          - ERROR: time out was elapsed and no further data is received
  */
static ErrorStatus USART_ByteReceive(uint8_t *Data, uint32_t TimeOut)
{
    uint32_t Counter = 0;
    while((USART_GetFlagStatus(USARTz, USART_FLAG_RXDNE) == RESET) && (Counter != TimeOut))
    {
        Counter++;
    }
    if(Counter != TimeOut)
    {
        *Data = (uint8_t)USART_ReceiveData(USARTz);
        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}
uint32_t Master_RecData(uint8_t *pdata, uint8_t length)
{
    int i = 0;
    uint8_t Data = 0;
    uint32_t number = 0;
    while(i < length)
    {
        i++;
        if((USART_ByteReceive(&Data, SC_RECEIVE_TIMEOUT)) == SUCCESS)
        {
            pdata[number] = Data;
            number++;
        }
    }
    return number;
}

//wait ack
ErrorStatus WaitFrameRes(uint8_t *dst_data, uint8_t length)
{
    //int i = 0;
    int datalen = 0;
    uint8_t recv_data[16];
    uint8_t CheckSum = 0;
    datalen = Master_RecData(recv_data, 16);
    if(datalen)
    {
#if 0
        log_info("recv_data:");
        for(i = 1; i < datalen; i++)
        {
            log_info("0x%x\r\n", recv_data[i]);
        }
#endif
        CheckSum = MasterGetCheckSum(recv_data, datalen - 1);
        log_info("\r\nRecieve Responce:CheckSum = 0x%x\r\n", CheckSum);
        if(CheckSum == recv_data[datalen - 1])
        {
            if( (datalen - 2) > length)
            {
                Buffercopy(dst_data, &recv_data[1], length);
            }
            else
            {
                Buffercopy(dst_data, &recv_data[1], datalen - 2);
            }
            return SUCCESS;
         }
    }
    return ERROR;
}

void TestMasterReqFrame(void)
{
    int i = 0;
    M_LIN_EX_MSG CurLINTxMsg;
    CurLINTxMsg.Check = CLASSIC;
    CurLINTxMsg.DataLen = 8;
    CurLINTxMsg.Sync = 0x55;
    CurLINTxMsg.PID = 0x3C;
    for(i = 0; i < CurLINTxMsg.DataLen; i++)
    {
        CurLINTxMsg.Data[i] = 0x0F;
    }
    log_info("Set Master FrameMsg:ID = 0x%02x; ", CurLINTxMsg.PID);
    SetFrameMsg(&M_TxMsg, CurLINTxMsg);
    FrameHandle();
}

void TestSlaveResFrame(void)
{
    M_LIN_EX_MSG CurLINTxMsg;
    CurLINTxMsg.Check = CLASSIC;
    CurLINTxMsg.DataLen = 0;
    CurLINTxMsg.Sync = 0x55;
    CurLINTxMsg.PID = 0x3D;
    log_info("Set Slave FrameMsg:ID = 0x%02x; ", CurLINTxMsg.PID);
    SetFrameMsg(&M_TxMsg, CurLINTxMsg);
    FrameHandle();
}

void TestLinMaster(void)
#if 1
{
    int i = 0, count = 0;
    uint8_t recv_data[8];
    log_info("\r\nStart frame send test:\r\n");
    TestMasterReqFrame();
    delay_xms(20);
    log_info("\r\nTest frame have send,waitting for response.\r\n");
    while(count < 4)
    {
        Memset(recv_data, 0, 8);
        TestSlaveResFrame();
        if(WaitFrameRes(recv_data, 8) == SUCCESS)
        {
            log_info("\r\nRecv_data from slave:\r\n");
            for(i = 0; i < 8; i++)
            {
                log_info("recv_data[%d] = 0x%x\r\n", i, recv_data[i]);
            }
            log_info("Frame send test OK!\r\n");
            break;
        }
        else
        {
            log_info("slave no response!!\r\n");
            count++;
        }
    }
}

#endif

/**
 * @}
 */

/**
 * @}
 */

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
 * @file lin_driver.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "lin_driver.h"

LIN_STATE LinRxState = IDLE;
uint8_t LINRxDataIndex = 0;
LIN_EX_MSG LINRxDataBuffer[2];//双缓冲接收数据，可以减少数据出错概率
uint8_t IDType[64] = {ID_TYPE_SR};
uint8_t GotMsgFlag = 0;
LIN_EX_MSG *pLINMsg;
LIN_EX_MSG LINTxMsg;

void LIN_SendBytes(uint8_t *pBuf, uint8_t Len)
{
    while(Len--)
    {
        while(USART_GetFlagStatus(USARTz, USART_FLAG_TXC ) == RESET);
        USART_SendData(USARTz, *pBuf++);
    }
    while(USART_GetFlagStatus(USARTz, USART_FLAG_TXC ) == RESET);
}

uint8_t LIN_GetCheckSum(uint8_t *pData, uint8_t len)
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

void LIN_SetResp(uint8_t ID, uint8_t *pData, uint8_t Len, uint8_t CheckType)
{
    uint8_t i = 0;
    uint8_t CheckSum = 0;
    if(Len > 8)
    {
        Len = 8;
    }
    LINTxMsg.PID = GET_PID(ID);
    for(i = 0; i < Len; i++)
    {
        LINTxMsg.Data[i] = pData[i];
    }
    if(CheckType)
    {
        CheckSum = LIN_GetCheckSum(&LINTxMsg.PID, Len + 1);
    }
    else
    {
        CheckSum = LIN_GetCheckSum(LINTxMsg.Data, Len);
    }
    if(Len < 8)
    {
        LINTxMsg.Data[Len] = CheckSum;
    }
    else
    {
        LINTxMsg.Check = CheckSum;
    }
    LINTxMsg.DataLen = Len;
}

void LIN_EX_RxAsync(uint8_t data)
{
    switch(LinRxState)
    {
    case IDLE:
        break;
    case SYNCH:
        if(data == 0x55)
        {
            LINRxDataBuffer[LINRxDataIndex].Sync = 0x55;
            LinRxState = ID_LEN;
        }
        else
        {
            LinRxState = IDLE;
        }
        break;
    case ID_LEN:
        if(GET_PID(data) == data)
        {
            LINRxDataBuffer[LINRxDataIndex].PID = data;
            LINRxDataBuffer[LINRxDataIndex].DataLen = 0;
            if(IDType[data & 0x3F] == ID_TYPE_SR)
            {
                LinRxState = DATA_GET;
            }
            else
            {
                //接收到主机发送的帧头，从机模式发送数据
                if(((LINTxMsg.PID & 0x3F) == (data & 0x3F)) && (LINTxMsg.DataLen > 0))
                {
                    LIN_SendBytes(LINTxMsg.Data, LINTxMsg.DataLen + 1);
                    LINTxMsg.DataLen = 0;
                }
                LinRxState = IDLE;
            }
        }
        else
        {
            LinRxState = IDLE;
        }
        break;
    case DATA_GET:
        LINRxDataBuffer[LINRxDataIndex].Data[LINRxDataBuffer[LINRxDataIndex].DataLen] = data;
        LINRxDataBuffer[LINRxDataIndex].Check = data;
        LINRxDataBuffer[LINRxDataIndex].DataLen++;
        if(LINRxDataBuffer[LINRxDataIndex].DataLen >= 8)
        {
            LinRxState = CHECKSUM;
        }
        else
        {
            LinRxState = DATA_GET;
        }
        break;
    case CHECKSUM:
        LINRxDataBuffer[LINRxDataIndex].Check = data;
        pLINMsg = &LINRxDataBuffer[LINRxDataIndex];
        GotMsgFlag = 1;
        LINRxDataIndex = (LINRxDataIndex + 1) % 2;
        LinRxState = IDLE;
        break;
    default:
        break;
    }
}

void LIN_IRQHandler(void)
{
    //BREAK中断
    if(USART_GetIntStatus(USARTz, USART_INT_LINBD) == SET)
    {
        USART_ClrIntPendingBit(USART2, USART_INT_LINBD);//清除LIN间隔场检测标志位
        //读状态寄存器和数据寄存器是为了清除FE标志
        USARTz->STS;
        USARTz->DAT;
        LinRxState = SYNCH;
        return;
    }
    //接收数据中断
    if (USART_GetIntStatus(USARTz, USART_INT_RXDNE)  == SET)
    {
        USART_ClrIntPendingBit(USARTz, USART_INT_RXDNE); //清除接收中断标志位
        if(USART_GetIntStatus(USARTz, USART_INT_FEF) == RESET)
        {
            LIN_EX_RxAsync((uint8_t)USART_ReceiveData(USARTz));
        }
    }
}

/**
  * @brief  执行主机下发的命令
  * @param  pData 收到的数据，该函数会默认读取8字节数据
  * @param  pFunResp 命令响应函数指针,需要自己实现
  * @retval 无
  */
void BOOT_ExecutiveCommand(uint8_t *pData, FUN_RESP pFunResp)
#if 1
{
    int i = 0;
    log_info("BOOT_ExecutiveCommand\r\n");
    for( i = 0; i < 8; i++)
    {
        log_info("pData[%d] = %02x \r\n", i, pData[i]);
        pData[i] = 0x1;
    }
    pFunResp(pData, 8);
}
#endif
/**
  * @}
  */

/*********************************END OF FILE**********************************/


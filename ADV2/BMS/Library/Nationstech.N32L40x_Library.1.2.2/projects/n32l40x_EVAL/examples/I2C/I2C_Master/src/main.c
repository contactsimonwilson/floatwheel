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
 * @file main.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l40x.h"
#include "n32l40x_i2c.h"
#include "main.h"
#include "log.h"

/** @addtogroup N32L40X_StdPeriph_Examples
 * @{
 */

/** @addtogroup I2C_Master
 * @{
 */

#define TEST_BUFFER_SIZE  100
#define I2CT_FLAG_TIMEOUT ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))
#define I2C_MASTER_ADDR   0x30
#define I2C_SLAVE_ADDR    0x10

#ifdef NON_REENTRANT
static uint32_t Mutex_Flag = 0;
#endif

#define I2C1_TEST
#define I2C1_REMAP
#define I2Cx I2C1
#define I2Cx_SCL_PIN GPIO_PIN_8
#define I2Cx_SDA_PIN GPIO_PIN_9
#define GPIOx        GPIOB

uint8_t tx_buf[TEST_BUFFER_SIZE] = {0};
uint8_t rx_buf[TEST_BUFFER_SIZE] = {0};
volatile Status test_status      = FAILED;
static __IO uint32_t I2CTimeout;
static CommCtrl_t Comm_Flag = C_READY;
static uint8_t RCC_RESET_Flag = 0;

Status Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
void Memset(void* s, uint8_t c, uint32_t count);
void CommTimeOut_CallBack(ErrCode_t errcode);

void Delay(uint32_t nCount)
{
    uint32_t tcnt;
    while(nCount--)
    {
        tcnt = 64000 / 5;
        while (tcnt--){;}
    }
}

void Delay_us(uint32_t nCount)
{
    uint32_t tcnt;
    while (nCount--)
    {
        tcnt = 64 / 5;
        while (tcnt--){;}
    }
}

int i2c_master_init(void)
{
    I2C_InitType i2c1_master;
    GPIO_InitType i2c1_gpio;
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);

    /*PB8 -- SCL; PB9 -- SDA*/
    GPIO_InitStruct(&i2c1_gpio);
    i2c1_gpio.Pin               = GPIO_PIN_8 | GPIO_PIN_9;
    i2c1_gpio.GPIO_Slew_Rate    = GPIO_Slew_Rate_High;
    i2c1_gpio.GPIO_Mode         = GPIO_Mode_AF_OD;
    i2c1_gpio.GPIO_Alternate    = GPIO_AF4_I2C1;
    i2c1_gpio.GPIO_Pull         = GPIO_Pull_Up;	  
    GPIO_InitPeripheral(GPIOB, &i2c1_gpio);

    I2C_DeInit(I2C1);
    i2c1_master.BusMode     = I2C_BUSMODE_I2C;
    i2c1_master.FmDutyCycle = I2C_FMDUTYCYCLE_2;
    i2c1_master.OwnAddr1    = I2C_MASTER_ADDR;
    i2c1_master.AckEnable   = I2C_ACKEN;
    i2c1_master.AddrMode    = I2C_ADDR_MODE_7BIT;
    i2c1_master.ClkSpeed    = 100000; // 100K

    I2C_Init(I2C1, &i2c1_master);
    I2C_Enable(I2C1, ENABLE);
    return 0;
}

int i2c_master_send(uint8_t* data, int len)
{
    uint8_t* sendBufferPtr = data;
    
#ifdef NON_REENTRANT
    if (Mutex_Flag)
        return -1;
    else
        Mutex_Flag = 1;
#endif
    
    I2CTimeout             = I2CT_LONG_TIMEOUT;
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_BUSY);
        }
    }

    if (Comm_Flag == C_READY)
    {
        Comm_Flag = C_START_BIT;
        I2C_GenerateStart(I2C1, ENABLE);
    }
    
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_MODE_FLAG)) // EV5
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_MODE);
        }
    }

    I2C_SendAddr7bit(I2C1, I2C_SLAVE_ADDR, I2C_DIRECTION_SEND);
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_TXMODE_FLAG)) // EV6
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_TXMODE);
        }
    }
    Comm_Flag = C_READY;

    // send data
    while (len-- > 0)
    {
        I2C_SendData(I2C1, *sendBufferPtr++);
        I2CTimeout = I2CT_LONG_TIMEOUT;
        while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_DATA_SENDING)) // EV8
        {
            if ((I2CTimeout--) == 0)
            {
                CommTimeOut_CallBack(MASTER_SENDING);
            }
        }
    }

    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_DATA_SENDED)) // EV8-2
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_SENDED);
        }
    }
    
    if (Comm_Flag == C_READY)
    {
        Comm_Flag = C_STOP_BIT;
        I2C_GenerateStop(I2C1, ENABLE);
    }
    
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_BUSY);
        }
    }
    Comm_Flag = C_READY;
    
#ifdef NON_REENTRANT
    if (Mutex_Flag)
        Mutex_Flag = 0;
    else
        return -2;
#endif
    
    return 0;
}

int i2c_master_recv(uint8_t* data, int len)
{
    uint8_t* recvBufferPtr = data;
    
#ifdef NON_REENTRANT
    if (Mutex_Flag)
        return -1;
    else
        Mutex_Flag = 1;
#endif
    
    I2CTimeout             = I2CT_LONG_TIMEOUT;
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_BUSY);
        }
    }
    I2C_ConfigAck(I2C1, ENABLE);

    // send start
    if (Comm_Flag == C_READY)
    {
        Comm_Flag = C_START_BIT;
        I2C_GenerateStart(I2C1, ENABLE);
    }
    
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_MODE_FLAG)) // EV5
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_MODE);
        }
    }

    // send addr
    I2C_SendAddr7bit(I2C1, I2C_SLAVE_ADDR, I2C_DIRECTION_RECV);
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_RXMODE_FLAG)) // EV6
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_RXMODE);
        }
    }
    Comm_Flag = C_READY;

    // recv data
    if (len == 1)
    {
        I2C_ConfigAck(I2C1, DISABLE);
        (void)(I2C1->STS1); /// clear ADDR
        (void)(I2C1->STS2);
        if (Comm_Flag == C_READY)
        {
            Comm_Flag = C_STOP_BIT;
            I2C_GenerateStop(I2C1, ENABLE);
        }
        
        I2CTimeout = I2CT_LONG_TIMEOUT;
        while (!I2C_GetFlag(I2Cx, I2C_FLAG_RXDATNE))
        {
            if ((I2CTimeout--) == 0)
            {
                CommTimeOut_CallBack(MASTER_RECVD);
            }
        }
        *recvBufferPtr++ = I2C_RecvData(I2C1);
        len--;
    }
    else if (len == 2)
    {
        I2C1->CTRL1 |= 0x0800; /// set ACKPOS
        (void)(I2C1->STS1);
        (void)(I2C1->STS2);
        I2C_ConfigAck(I2C1, DISABLE);
        
        I2CTimeout = I2CT_LONG_TIMEOUT;
        while (!I2C_GetFlag(I2C1, I2C_FLAG_BYTEF))
        {
            if ((I2CTimeout--) == 0)
            {
                CommTimeOut_CallBack(MASTER_BYTEF);
            }
        }
        
        if (Comm_Flag == C_READY)
        {
            Comm_Flag = C_STOP_BIT;
            I2C_GenerateStop(I2C1, ENABLE);
        }
        
        *recvBufferPtr++ = I2C_RecvData(I2C1);
        len--;
        *recvBufferPtr++ = I2C_RecvData(I2C1);
        len--;
    }
    else
    {
        I2C_ConfigAck(I2C1, ENABLE);
        (void)(I2C1->STS1);
        (void)(I2C1->STS2);
        
        while (len)
        {
            if (len == 3)
            {
                I2CTimeout = I2CT_LONG_TIMEOUT;
                while (!I2C_GetFlag(I2C1, I2C_FLAG_BYTEF))
                {
                    if ((I2CTimeout--) == 0)
                    {
                        CommTimeOut_CallBack(MASTER_BYTEF);
                    }
                }
                I2C_ConfigAck(I2C1, DISABLE);
                *recvBufferPtr++ = I2C_RecvData(I2C1);
                len--;
                
                I2CTimeout = I2CT_LONG_TIMEOUT;
                while (!I2C_GetFlag(I2C1, I2C_FLAG_BYTEF))
                {
                    if ((I2CTimeout--) == 0)
                    {
                        CommTimeOut_CallBack(MASTER_BYTEF);
                    }
                }
                
                if (Comm_Flag == C_READY)
                {
                    Comm_Flag = C_STOP_BIT;
                    I2C_GenerateStop(I2C1, ENABLE);
                }
        
                *recvBufferPtr++ = I2C_RecvData(I2C1);
                len--;
                *recvBufferPtr++ = I2C_RecvData(I2C1);
                len--;
                
                break;
            }
            
            I2CTimeout = I2CT_LONG_TIMEOUT;
            while (!I2C_CheckEvent(I2C1, I2C_EVT_MASTER_DATA_RECVD_FLAG)) // EV7
            {
                if ((I2CTimeout--) == 0)
                {
                    CommTimeOut_CallBack(MASTER_RECVD);
                }
            }
            *recvBufferPtr++ = I2C_RecvData(I2C1);
            len--;
        }
    }
    
    I2CTimeout = I2CT_LONG_TIMEOUT;
    while (I2C_GetFlag(I2C1, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0)
        {
            CommTimeOut_CallBack(MASTER_BUSY);
        }
    }
    Comm_Flag = C_READY;
    
#ifdef NON_REENTRANT
    if (Mutex_Flag)
        Mutex_Flag = 0;
    else
        return -2;
#endif

    return 0;
}

/**
 * @brief   Main program
 */
int main(void)
{
    uint16_t i = 0;
    
    log_init();
    log_info("\nthis is a i2c master demo\r\n");
    /* Initialize the I2C EEPROM driver ----------------------------------------*/
    i2c_master_init();

    /* Fill the buffer to send */
    for (i = 0; i < TEST_BUFFER_SIZE; i++)
    {
        tx_buf[i] = i;
    }
    /* First write in the memory followed by a read of the written data --------*/
    /* Write data*/
    i2c_master_send(tx_buf, TEST_BUFFER_SIZE);
        
    /* Read data */
    i2c_master_recv(rx_buf, TEST_BUFFER_SIZE);
    
    /* Check if the data written to the memory is read correctly */
    test_status = Buffercmp(tx_buf, rx_buf, TEST_BUFFER_SIZE);
    if (test_status == PASSED)
    {
        log_info("i2c master test pass!\r\n");
    }
    else
    {
        log_info("i2c master test fail!\r\n");
    }
    /* test_status = PASSED, if the write and read data are the same  */
    /* test_status = FAILED, if the write and read data are different */
    while (1)
    {
    }
}

/**
 * @brief  Compares two buffers.
 * @param  pBuffer, pBuffer1: buffers to be compared.
 * @param BufferLength buffer's length
 * @return PASSED: pBuffer identical to pBuffer1
 *         FAILED: pBuffer differs from pBuffer1
 */
Status Buffercmp(uint8_t* pBuffer, uint8_t* pBuffer1, uint16_t BufferLength)
{
    while (BufferLength--)
    {
        if (*pBuffer != *pBuffer1)
        {
            return FAILED;
        }

        pBuffer++;
        pBuffer1++;
    }

    return PASSED;
}

/**
 * @brief memery set a value
 * @param s source
 * @param c value
 * @param count number
 * @return pointer of the memery
 */
void Memset(void* s, uint8_t c, uint32_t count)
{
    char* xs = (char*)s;

    while (count--)
    {
        *xs++ = c;
    }

    return;
}

void IIC_RestoreSlaveByClock(void)
{
    uint8_t i;
    GPIO_InitType i2cx_gpio;
    
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    GPIO_AFIOInitDefault();
    GPIO_DeInit(GPIOx);
    
    GPIO_InitStruct(&i2cx_gpio);
    i2cx_gpio.Pin               = I2Cx_SCL_PIN;
    i2cx_gpio.GPIO_Slew_Rate    = GPIO_Slew_Rate_High;
    i2cx_gpio.GPIO_Mode         = GPIO_Mode_Out_PP;
    i2cx_gpio.GPIO_Alternate    = GPIO_NO_AF;
    i2cx_gpio.GPIO_Pull         = GPIO_No_Pull;	  
    GPIO_InitPeripheral(GPIOx, &i2cx_gpio);
    
    for (i = 0; i < 9; i++)
    {
        GPIO_SetBits(GPIOx, I2Cx_SCL_PIN);
        Delay_us(5);
        GPIO_ResetBits(GPIOx, I2Cx_SCL_PIN);
        Delay_us(5);
    }
}
    
void SystemNVICReset(void)
{
    __set_FAULTMASK((uint32_t)1);
    log_info("***** NVIC system reset! *****\r\n");
    __NVIC_SystemReset();
}

void IIC_RCCReset(void)
{
    if (RCC_RESET_Flag >= 3)
    {
        SystemNVICReset();
    }
    else
    {
        RCC_RESET_Flag++;
        
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C1, ENABLE);
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C1, DISABLE);
        
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_I2C1, DISABLE );
        GPIOB->PMODE |= 0x000F0000;
        RCC_EnableAPB2PeriphClk( RCC_APB2_PERIPH_AFIO, DISABLE);
        RCC_EnableAPB2PeriphClk (RCC_APB2_PERIPH_GPIOB, DISABLE );
        
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C1, ENABLE);
        RCC_EnableAPB1PeriphReset(RCC_APB1_PERIPH_I2C1, DISABLE);
        
        IIC_RestoreSlaveByClock();
        
        log_info("***** IIC module by RCC reset! *****\r\n");
        i2c_master_init();
    }
}

void IIC_SWReset(void)
{
    GPIO_InitType i2cx_gpio;
    
    GPIO_InitStruct(&i2cx_gpio);
    i2cx_gpio.Pin               = I2Cx_SCL_PIN | I2Cx_SDA_PIN;
    i2cx_gpio.GPIO_Slew_Rate    = GPIO_Slew_Rate_High;
    i2cx_gpio.GPIO_Mode         = GPIO_Mode_Input;
    i2cx_gpio.GPIO_Alternate    = GPIO_NO_AF;
    i2cx_gpio.GPIO_Pull         = GPIO_No_Pull;	  
    GPIO_InitPeripheral(GPIOx, &i2cx_gpio);
    
    I2CTimeout = I2CT_LONG_TIMEOUT;
    for (;;)
    {
        if ((I2Cx_SCL_PIN | I2Cx_SDA_PIN) == (GPIOx->PID & (I2Cx_SCL_PIN | I2Cx_SDA_PIN)))
        {
            I2Cx->CTRL1 |= 0x8000;
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            I2Cx->CTRL1 &= ~0x8000;
            
            log_info("***** IIC module self reset! *****\r\n");
            break;
        }
        else
        {
            if ((I2CTimeout--) == 0)
            {
                IIC_RCCReset();
            }
        }
    }
}

void CommTimeOut_CallBack(ErrCode_t errcode)
{
    log_info("...ErrCode:%d\r\n", errcode);
    
#if (COMM_RECOVER_MODE == MODULE_SELF_RESET)
    IIC_SWReset();
#elif (COMM_RECOVER_MODE == MODULE_RCC_RESET)
    IIC_RCCReset();
#elif (COMM_RECOVER_MODE == SYSTEM_NVIC_RESET)
    SystemNVICReset();
#endif
}

/**
 * @}
 */

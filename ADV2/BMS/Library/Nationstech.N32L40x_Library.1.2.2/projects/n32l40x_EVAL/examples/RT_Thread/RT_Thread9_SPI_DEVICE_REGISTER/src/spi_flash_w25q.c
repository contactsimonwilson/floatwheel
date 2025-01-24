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
 * @file spi_flash.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
 
#include <rtthread.h>
#include "spi_flash_w25q.h"
#include "drv_spi.h"
#include "spi.h"
#include "pin.h"
#include "spi_flash_sfud.h"
#include "drv_gpio.h"

/** @addtogroup Utilities
 * @{
 */

/** @addtogroup
 * @{
 */

/** @addtogroup Common
 * @{
 */

/** @addtogroup SPI_FLASH
 * @brief
 * @{
 */

/** @addtogroup SPI_FLASH_Private_Types
 * @{
 */
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Defines
 * @{
 */
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Macros
 * @{
 */
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Variables
 * @{
 */
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Function_Prototypes
 * @{
 */
/**
 * @}
 */

/** @addtogroup SPI_FLASH_Private_Functions
 * @{
 */
 
/**
 * @brief  Sends a byte through the SPI interface and return the byte received
 *         from the SPI bus.
 * @param byte byte to send.
 * @return The value of the received byte.
 */
static uint8_t sFLASH_SendByte(uint8_t byte)
{
#if defined(RT_USING_SPI1)	
    /*!< Loop while DAT register in not emplty */
    while (SPI_I2S_GetStatus(sFLASH_SPI1, SPI_I2S_TE_FLAG) == RESET)
        ;
    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_TransmitData(sFLASH_SPI1, byte);
        
    /*!< Wait to receive a byte */
    while (SPI_I2S_GetStatus(sFLASH_SPI1, SPI_I2S_RNE_FLAG) == RESET)
        ;
    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(sFLASH_SPI1);
#endif
	
#if defined(RT_USING_SPI2)
	/*!< Loop while DAT register in not emplty */
    while (SPI_I2S_GetStatus(sFLASH_SPI2, SPI_I2S_TE_FLAG) == RESET)
        ;
    /*!< Send byte through the SPI1 peripheral */
    SPI_I2S_TransmitData(sFLASH_SPI2, byte);
        
    /*!< Wait to receive a byte */
    while (SPI_I2S_GetStatus(sFLASH_SPI2, SPI_I2S_RNE_FLAG) == RESET)
        ;
    /*!< Return the byte read from the SPI bus */
    return SPI_I2S_ReceiveData(sFLASH_SPI2);
#endif
}

/**
 * @brief  Reads a byte from the SPI Flash.
 * @note   This function must be used only if the Start_Read_Sequence function
 *         has been previously called.
 * @return Byte Read from the SPI Flash.
 */
uint8_t sFLASH_ReadByte(void)
{
    return (sFLASH_SendByte(sFLASH_DUMMY_BYTE));
}


/**
 * @brief  Polls the status of the Write In Progress (WIP) flag in the FLASH's
 *         status register and loop until write opertaion has completed.
 */
static rt_err_t sFLASH_WaitForWriteEnd(rt_device_t dev)
{
    struct rt_spi_device *spi_dev_w25q;
    rt_uint8_t w25x_read_status = sFLASH_CMD_RDSR;
    rt_uint8_t w25x_send_dummy_byte = sFLASH_DUMMY_BYTE;
    rt_uint8_t flashstatus = 0;
    
    spi_dev_w25q = (struct rt_spi_device*)rt_device_find(W25Q_SPI_DEVICE_NAME);
    
    if((dev->flag & RT_DEVICE_FLAG_RDONLY) == RT_DEVICE_FLAG_RDONLY)
    {
        struct rt_spi_message msg1, msg2, msg3;

        msg1.send_buf   = &w25x_read_status;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = RT_NULL;
        
        msg2.send_buf   = &w25x_send_dummy_byte;
        msg2.recv_buf   = &flashstatus;
        msg2.length     = 1;
        msg2.cs_take    = 1;
        msg2.cs_release = 0;
        msg2.next       = RT_NULL;
        
        rt_spi_transfer_message(spi_dev_w25q, &msg1);
        
        do
        {
            rt_spi_transfer_message(spi_dev_w25q, &msg2);
        }while((flashstatus & sFLASH_WIP_FLAG) == SET);
        
        msg3.send_buf   = RT_NULL;
        msg3.recv_buf   = RT_NULL;
        msg3.length     = 0;
        msg3.cs_take    = 0;
        msg3.cs_release = 1;
        msg3.next       = RT_NULL;
        
        rt_spi_transfer_message(spi_dev_w25q, &msg3);
        
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}

static uint32_t sFLASH_ReadId()
{
    struct rt_spi_device *spi_dev_w25q;
    rt_uint8_t w25x_read_id = 0x90;
    rt_uint8_t id[5] = {0};
    rt_uint32_t device_id;

    spi_dev_w25q = (struct rt_spi_device *)rt_device_find(W25Q_SPI_DEVICE_NAME);
    if (!spi_dev_w25q)
    {
        rt_kprintf("spi sample run failed! can't find %s device!\n", W25Q_SPI_DEVICE_NAME);
    }
    else
    {
        struct rt_spi_message msg1, msg2;

        msg1.send_buf   = &w25x_read_id;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = &msg2;

        msg2.send_buf   = RT_NULL;
        msg2.recv_buf   = id;
        msg2.length     = 5;
        msg2.cs_take    = 0;
        msg2.cs_release = 1;
        msg2.next       = RT_NULL;

        rt_spi_transfer_message(spi_dev_w25q, &msg1);
        rt_kprintf("use rt_spi_transfer_message() read w25q ID is:%x%x\n", id[3], id[4]);
    }
    device_id = (rt_uint16_t)id[4]<<8 | id[3];
    
    return device_id;
}

/**
 * @brief  Erases the specified FLASH sector.
 * @param SectorAddr address of the sector to erase.
 */
static rt_err_t sFLASH_EraseSector(rt_device_t dev, uint32_t SectorAddr)
{    
    struct rt_spi_device *spi_dev_w25q;    
    rt_uint8_t w25x_write_en = sFLASH_CMD_WREN;
    rt_uint8_t w25x_write_cmd = sFLASH_CMD_SE;
    rt_uint8_t addr[3] = {0};
    
    spi_dev_w25q = (struct rt_spi_device*)rt_device_find(W25Q_SPI_DEVICE_NAME);
    
    if((dev->flag & RT_DEVICE_FLAG_RDONLY) == RT_DEVICE_FLAG_RDONLY)
    {
        struct rt_spi_message msg1, msg2, msg3;

        msg1.send_buf   = &w25x_write_en;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 1;
        msg1.next       = &msg2;
        
        msg2.send_buf   = &w25x_write_cmd;
        msg2.recv_buf   = RT_NULL;
        msg2.length     = 1;
        msg2.cs_take    = 1;
        msg2.cs_release = 0;
        msg2.next       = &msg3;
        
        addr[0] = ((rt_uint32_t)SectorAddr & 0xFF0000) >> 16;
        addr[1] = ((rt_uint32_t)SectorAddr & 0xFF00) >> 8;
        addr[2] = ((rt_uint32_t)SectorAddr & 0xFF);
        
        msg3.send_buf   = addr;
        msg3.recv_buf   = RT_NULL;
        msg3.length     = 3;
        msg3.cs_take    = 1;
        msg3.cs_release = 1;
        msg3.next       = RT_NULL;        

        rt_spi_transfer_message(spi_dev_w25q, &msg1); 
        sFLASH_WaitForWriteEnd(dev);
        
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}

/**
 * @brief  Erases the entire FLASH.
 */
static rt_err_t sFLASH_EraseBulk(rt_device_t dev)
{
    struct rt_spi_device *spi_dev_w25q;    
    rt_uint8_t w25x_write_en = sFLASH_CMD_WREN;
    rt_uint8_t w25x_write_cmd = sFLASH_CMD_BE;
    
    spi_dev_w25q = (struct rt_spi_device*)rt_device_find(W25Q_SPI_DEVICE_NAME);
    
    if((dev->flag & RT_DEVICE_FLAG_RDONLY) == RT_DEVICE_FLAG_RDONLY)
    {
        struct rt_spi_message msg1, msg2;

        msg1.send_buf   = &w25x_write_en;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 1;
        msg1.next       = &msg2;
        
        msg2.send_buf   = &w25x_write_cmd;
        msg2.recv_buf   = RT_NULL;
        msg2.length     = 1;
        msg2.cs_take    = 1;
        msg2.cs_release = 1;
        msg2.next       = RT_NULL;
        
        rt_spi_transfer_message(spi_dev_w25q, &msg1); 
        sFLASH_WaitForWriteEnd(dev);
        
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}

/**
 * @brief  Writes more than one byte to the FLASH with a single WRITE cycle
 *         (Page WRITE sequence).
 * @note   The number of byte can't exceed the FLASH page size.
 * @param pBuffer pointer to the buffer  containing the data to be written
 *         to the FLASH.
 * @param WriteAddr FLASH's internal address to write to.
 * @param NumByteToWrite number of bytes to write to the FLASH, must be equal
 *         or less than "sFLASH_PAGESIZE" value.
 */
static rt_size_t sFLASH_WritePage(rt_device_t dev, uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    
    struct rt_spi_device *spi_dev_w25q;
    rt_uint8_t w25x_write_cmd = sFLASH_CMD_WRITE;
    rt_uint8_t w25x_write_en = sFLASH_CMD_WREN;
    rt_uint8_t addr[3] = {0};
    
    spi_dev_w25q = (struct rt_spi_device*)rt_device_find(W25Q_SPI_DEVICE_NAME);
    
    if((dev->flag & RT_DEVICE_FLAG_RDONLY) == RT_DEVICE_FLAG_RDONLY)
    {
        struct rt_spi_message msg1, msg2, msg3, msg4;

        msg1.send_buf   = &w25x_write_en;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 1;
        msg1.next       = &msg2;
        
        msg2.send_buf   = &w25x_write_cmd;
        msg2.recv_buf   = RT_NULL;
        msg2.length     = 1;
        msg2.cs_take    = 1;
        msg2.cs_release = 0;
        msg2.next       = &msg3;
        
        addr[0] = ((rt_uint32_t)WriteAddr & 0xFF0000) >> 16;
        addr[1] = ((rt_uint32_t)WriteAddr & 0xFF00) >> 8;
        addr[2] = ((rt_uint32_t)WriteAddr & 0xFF);
        
        msg3.send_buf   = addr;
        msg3.recv_buf   = RT_NULL;
        msg3.length     = 3;
        msg3.cs_take    = 0;
        msg3.cs_release = 0;
        msg3.next       = &msg4;
        
        msg4.send_buf   = pBuffer;
        msg4.recv_buf   = RT_NULL;
        msg4.length     = NumByteToWrite;
        msg4.cs_take    = 0;
        msg4.cs_release = 1;
        msg4.next       = RT_NULL;

        rt_spi_transfer_message(spi_dev_w25q, &msg1); 
        sFLASH_WaitForWriteEnd(dev);
        return NumByteToWrite;
    }
    else
    {
        return 0;
    }
}

/**
 * @brief  Writes block of data to the FLASH. In this function, the number of
 *         WRITE cycles are reduced, using Page WRITE sequence.
 * @param pBuffer pointer to the buffer  containing the data to be written
 *         to the FLASH.
 * @param WriteAddr FLASH's internal address to write to.
 * @param NumByteToWrite number of bytes to write to the FLASH.
 */
static void sFLASH_WriteBuffer(rt_device_t dev, uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
    uint8_t NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0, temp = 0;

    Addr        = WriteAddr % sFLASH_SPI_PAGESIZE;
    count       = sFLASH_SPI_PAGESIZE - Addr;
    NumOfPage   = NumByteToWrite / sFLASH_SPI_PAGESIZE;
    NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

    if (Addr == 0) /*!< WriteAddr is sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
            sFLASH_WritePage(dev, pBuffer, WriteAddr, NumByteToWrite);
        }
        else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            while (NumOfPage--)
            {
                sFLASH_WritePage(dev, pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += sFLASH_SPI_PAGESIZE;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }

            sFLASH_WritePage(dev, pBuffer, WriteAddr, NumOfSingle);
        }
    }
    else /*!< WriteAddr is not sFLASH_PAGESIZE aligned  */
    {
        if (NumOfPage == 0) /*!< NumByteToWrite < sFLASH_PAGESIZE */
        {
            if (NumOfSingle > count) /*!< (NumByteToWrite + WriteAddr) > sFLASH_PAGESIZE */
            {
                temp = NumOfSingle - count;

                sFLASH_WritePage(dev, pBuffer, WriteAddr, count);
                WriteAddr += count;
                pBuffer += count;

                sFLASH_WritePage(dev, pBuffer, WriteAddr, temp);
            }
            else
            {
                sFLASH_WritePage(dev, pBuffer, WriteAddr, NumByteToWrite);
            }
        }
        else /*!< NumByteToWrite > sFLASH_PAGESIZE */
        {
            NumByteToWrite -= count;
            NumOfPage   = NumByteToWrite / sFLASH_SPI_PAGESIZE;
            NumOfSingle = NumByteToWrite % sFLASH_SPI_PAGESIZE;

            sFLASH_WritePage(dev, pBuffer, WriteAddr, count);
            WriteAddr += count;
            pBuffer += count;

            while (NumOfPage--)
            {
                sFLASH_WritePage(dev, pBuffer, WriteAddr, sFLASH_SPI_PAGESIZE);
                WriteAddr += sFLASH_SPI_PAGESIZE;
                pBuffer += sFLASH_SPI_PAGESIZE;
            }

            if (NumOfSingle != 0)
            {
                sFLASH_WritePage(dev, pBuffer, WriteAddr, NumOfSingle);
            }
        }
    }
}

/**
 * @brief  Initiates a read data byte (READ) sequence from the Flash.
 *   This is done by driving the /CS line low to select the device, then the READ
 *   instruction is transmitted followed by 3 bytes address. This function exit
 *   and keep the /CS line low, so the Flash still being selected. With this
 *   technique the whole content of the Flash is read with a single READ instruction.
 * @param ReadAddr FLASH's internal address to read from.
 */
void sFLASH_StartReadSequence(rt_device_t dev, uint32_t ReadAddr)
{   
    struct rt_spi_device *spi_dev_w25q;    
    rt_uint8_t w25x_write_cmd = sFLASH_CMD_READ;
    rt_uint8_t addr[3] = {0};
    spi_dev_w25q = (struct rt_spi_device*)rt_device_find(W25Q_SPI_DEVICE_NAME);
    
    if((dev->flag & RT_DEVICE_FLAG_RDONLY) == RT_DEVICE_FLAG_RDONLY)
    {
        struct rt_spi_message msg1, msg2;

        msg1.send_buf   = &w25x_write_cmd;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = &msg2;
        
        addr[0] = ((rt_uint32_t)ReadAddr & 0xFF0000) >> 16;
        addr[1] = ((rt_uint32_t)ReadAddr & 0xFF00) >> 8;
        addr[2] = ((rt_uint32_t)ReadAddr & 0xFF);
        
        msg2.send_buf   = addr;
        msg2.recv_buf   = RT_NULL;
        msg2.length     = 3;
        msg2.cs_take    = 1;
        msg2.cs_release = 1;
        msg2.next       = RT_NULL;      

        rt_spi_transfer_message(spi_dev_w25q, &msg1);
    }
}

#define W25QXX_SPI1_NSS_PIN   GET_PIN(A, 4)
#define W25QXX_SPI2_NSS_PIN   GET_PIN(B, 12)

/**
  * Attach the spi device to SPI bus, this function must be used after initialization.
  */
rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, GPIO_Module *cs_gpiox, uint16_t cs_gpio_pin)
{
    struct rt_spi_device *spi_device;
    struct w25qxx_spi_cs* spi_cs;
    rt_err_t result;
        
    spi_device = (struct rt_spi_device *)rt_malloc(sizeof(struct rt_spi_device)); 
    RT_ASSERT(spi_device != RT_NULL);     
    
    /* NSS GPIO pin configuration */
#if defined(RT_USING_SPI1)	
    GPIOInit(SPI1_NSS_PORT, GPIO_Mode_Out_PP, GPIO_No_Pull, SPI1_NSS_PIN, GPIO_NO_AF);
    GPIO_SetBits(SPI1_NSS_PORT, SPI1_NSS_PIN);
#endif
	
#if defined(RT_USING_SPI2)
	GPIOInit(SPI2_NSS_PORT, GPIO_Mode_Out_PP, GPIO_No_Pull, SPI2_NSS_PIN, GPIO_NO_AF);
    GPIO_SetBits(SPI2_NSS_PORT, SPI2_NSS_PIN);
#endif
    
    /* attach cs */
    {
        spi_cs = (struct w25qxx_spi_cs *)rt_malloc(sizeof(struct w25qxx_spi_cs));
        RT_ASSERT(spi_cs != RT_NULL);
#if defined(RT_USING_SPI1)
        spi_cs->GPIOx    = SPI1_NSS_PORT;
		spi_cs->GPIO_Pin = W25QXX_SPI1_NSS_PIN;
#endif
		
#if defined(RT_USING_SPI2)
		spi_cs->GPIOx    = SPI2_NSS_PORT;
		spi_cs->GPIO_Pin = W25QXX_SPI2_NSS_PIN;
#endif
         
        result = rt_spi_bus_attach_device(spi_device, device_name, bus_name, (void *)spi_cs);
        if (result != RT_EOK)
        {
            rt_kprintf("%s attach to %s faild, %d\n", device_name, bus_name, result);
            return result;
        }
        else
        {
            rt_kprintf("%s attach to %s done\n", device_name, bus_name);
            return result; 
        }
    }
}

/**
 * @brief  Configures the different system clocks.
 */
static rt_err_t rt_flash_init(rt_device_t dev)
{
#if defined(RT_USING_SPI1)
        rt_hw_spi_device_attach("spi1", W25Q_SPI_DEVICE_NAME, SPI1_NSS_PORT, SPI1_NSS_PIN);
#endif
	
#if defined(RT_USING_SPI2)
		rt_hw_spi_device_attach("spi2", W25Q_SPI_DEVICE_NAME, SPI2_NSS_PORT, SPI2_NSS_PIN);
#endif
        
    if (RT_NULL == rt_sfud_flash_probe("W25Qxx", W25Q_SPI_DEVICE_NAME))
    {
        return -RT_ERROR;
    };
    return RT_EOK;
}

static rt_err_t rt_flash_open(rt_device_t dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_flash_close(rt_device_t dev)
{
    return RT_EOK;
}

/* SPI Dev device interface, compatible with RT-Thread 0.3.x/1.0.x */
static rt_size_t rt_flash_read(rt_device_t dev,
                                     rt_off_t    pos,
                                     void       *buffer,
                                     rt_size_t   size)
{    
    struct rt_spi_device *spi_dev_w25q;
    rt_uint8_t w25x_read_cmd = sFLASH_CMD_READ;
    rt_uint8_t addr[3] = {0};
    
    spi_dev_w25q = (struct rt_spi_device*)rt_device_find(W25Q_SPI_DEVICE_NAME);
    
    if((dev->flag & RT_DEVICE_FLAG_RDONLY) == RT_DEVICE_FLAG_RDONLY)
    {
        struct rt_spi_message msg1, msg2, msg3;

        msg1.send_buf   = &w25x_read_cmd;
        msg1.recv_buf   = RT_NULL;
        msg1.length     = 1;
        msg1.cs_take    = 1;
        msg1.cs_release = 0;
        msg1.next       = &msg2;
        
        addr[0] = ((rt_uint32_t)pos & 0xFF0000) >> 16;
        addr[1] = ((rt_uint32_t)pos & 0xFF00) >> 8;
        addr[2] = ((rt_uint32_t)pos & 0xFF);
        
        msg2.send_buf   = addr;
        msg2.recv_buf   = RT_NULL;
        msg2.length     = 3;
        msg2.cs_take    = 1;
        msg2.cs_release = 0;
        msg2.next       = &msg3;
        
        msg3.send_buf   = RT_NULL;
        msg3.recv_buf   = buffer;
        msg3.length     = size;
        msg3.cs_take    = 1;
        msg3.cs_release = 1;
        msg3.next       = RT_NULL;

        rt_spi_transfer_message(spi_dev_w25q, &msg1);  
        return size;
    }
    else
    {
        return 0;
    }
}

static rt_size_t rt_flash_write(rt_device_t dev,
                                      rt_off_t    pos,
                                      const void *buffer,
                                      rt_size_t   size)
{
        
    if((dev->flag & RT_DEVICE_FLAG_RDONLY) == RT_DEVICE_FLAG_RDONLY)
    {
        sFLASH_WriteBuffer(dev, (uint8_t*)buffer, pos, size);        
        return size;
    }
    else
    {
        return 0;
    }
}

static rt_err_t rt_flash_control(rt_device_t dev,
                                       int         cmd,
                                       void       *args)
{
   rt_err_t tmp=RT_ERROR;

    switch(cmd)
    {
        case RT_CMD_W25_READ_ID:
            tmp = sFLASH_ReadId();
            break;
        case RT_CMD_W25_ERASE_SECTOR:
            tmp = sFLASH_EraseSector(dev, *(uint32_t *)args);
            break;
        case RT_CMD_W25_ERASE_CHIP:
            tmp = sFLASH_EraseBulk(dev);
            break;
        default:
            break;
    }
        
    return tmp;
}



rt_err_t rt_flash_register(rt_uint8_t flag)
{
    static struct rt_device w25_dev;

    w25_dev.type = RT_Device_Class_Unknown;

    w25_dev.rx_indicate = RT_NULL;
    w25_dev.tx_complete = RT_NULL;

    w25_dev.init    = rt_flash_init;
    w25_dev.open    = rt_flash_open;
    w25_dev.close   = rt_flash_close;
    w25_dev.read    = rt_flash_read;
    w25_dev.write   = rt_flash_write;
    w25_dev.control = rt_flash_control;

    return rt_device_register(&w25_dev, "Flash", RT_DEVICE_FLAG_RDWR | flag);
}

/**
 * @}
 */

/**
 * @}
 */

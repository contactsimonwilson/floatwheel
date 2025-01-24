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
 * @file mass_mal.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
/* Includes ------------------------------------------------------------------*/


#include "mass_mal.h"
#include "n32l40x_flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define FLASH_START_ADDR    0x08010000// Flash start address
#define FLASH_SIZE          0x10000
#define FLASH_PAGE_SIZE     0x800 // 2K per page
#define FLASH_WAIT_TIMEOUT  100000

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t Mass_Memory_Size[2];
uint32_t Mass_Block_Size[2];
uint32_t Mass_Block_Count[2];

/* logic unit count; the first is 0 */
uint32_t Max_Lun = 0;

/**
 * @brief   Initializes the Media on the Nations.
 * @param   lun: logical unit.
 * @return  MAL_OK.
 */
uint16_t MAL_Init(uint8_t lun)
{
    FLASH_Unlock(); 
    return MAL_OK;
}

/**
 * @brief   Write sectors.
 * @param   lun: logical unit.
 * @param   Memory_Offset: memory offset.
 * @param   Writebuff: write buff pointer.
 * @param   Transfer_Length: transfer data length.
 * @return  MAL_OK or MAL_FAIL.
 */
uint16_t MAL_Write(uint8_t lun, uint32_t Memory_Offset, uint32_t *Writebuff, uint16_t Transfer_Length)
{
    uint16_t i;
    switch (lun)
    {
    case 0:
        for( i = 0; i < Transfer_Length; i += FLASH_PAGE_SIZE )
        { 
            if( FLASH_WaitForLastOpt(FLASH_WAIT_TIMEOUT) != FLASH_TIMEOUT )
            {
                FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR);
            }
            FLASH_EraseOnePage(FLASH_START_ADDR + Memory_Offset + i); 
        }
         
        for( i = 0; i < Transfer_Length; i+=4 )
        { 
            if( FLASH_WaitForLastOpt(FLASH_WAIT_TIMEOUT) != FLASH_TIMEOUT )
            {
                FLASH_ClearFlag(FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPERR); 
            } 
            FLASH_ProgramWord(FLASH_START_ADDR + Memory_Offset + i , Writebuff[i>>2]); 
        }
        break;
    case 1:
        break;
    default:
        return MAL_FAIL;
    }
    return MAL_OK;
}

/**
 * @brief   Write sectors.
 * @param   lun: logical unit.
 * @param   Memory_Offset: memory offset.
 * @param   Readbuff: read buff pointer.
 * @param   Transfer_Length: transfer data length.
 * @return  MAL_OK or MAL_FAIL.
 */
uint16_t MAL_Read(uint8_t lun, uint32_t Memory_Offset, uint32_t *Readbuff, uint16_t Transfer_Length)
{
    uint16_t i;
    switch (lun)
    {
    case 0:
        for( i=0; i < Transfer_Length; i+=4 )
        {
            Readbuff[i>>2] = ((vu32*)(FLASH_START_ADDR + Memory_Offset))[i>>2]; 
        }
        break;
    case 1:
        break;
    default:
        return MAL_FAIL;
    }
    return MAL_OK;
}

/**
 * @brief   Get status.
 * @param   lun: logical unit.
 * @return  MAL_OK or MAL_FAIL.
 */
uint16_t MAL_GetStatus (uint8_t lun)
{
    if (lun == 0)
    {
        Mass_Block_Count[0] = FLASH_SIZE/FLASH_PAGE_SIZE; 
        Mass_Block_Size[0] =  FLASH_PAGE_SIZE; 
        Mass_Memory_Size[0] = FLASH_SIZE; 
        return MAL_OK;
    }

    return MAL_FAIL;
}


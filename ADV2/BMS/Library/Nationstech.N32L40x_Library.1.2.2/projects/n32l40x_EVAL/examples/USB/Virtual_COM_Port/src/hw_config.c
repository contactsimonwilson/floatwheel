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
 * @file hw_config.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
/* Includes ------------------------------------------------------------------*/

#include "usb_lib.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "hw_config.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
USART_InitType USART_InitStructure;

uint8_t  USART_Rx_Buffer [USART_RX_DATA_SIZE]; 
uint32_t USART_Rx_ptr_in = 0;
uint32_t USART_Rx_ptr_out = 0;
uint32_t USART_Rx_length  = 0;
uint8_t  USB_Tx_State = 0;

/* Extern variables ----------------------------------------------------------*/
extern LINE_CODING linecoding;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Configures Main system clocks & power.
 */
void Set_System(void)
{
    RCC_DeInit();

    /*Enable HSE*/
    RCC->CTRL |= RCC_CTRL_HSEEN;
    while((RCC->CTRL & RCC_CTRL_HSERDF) != RCC_CTRL_HSERDF);

    /*Set PLL MUL*/
    RCC_ConfigPll(RCC_PLL_SRC_HSE_DIV1, RCC_PLL_MUL_6, RCC_PLLDIVCLK_DISABLE);
    /*Enable PLL*/
    RCC->CTRL |= RCC_CTRL_PLLEN;
    while((RCC->CTRL & RCC_CTRL_PLLRDF) != RCC_CTRL_PLLRDF); 

    /*Set AHB/APB1/APB2*/
    RCC->CFG |= RCC_CFG_AHBPRES_DIV1;
    RCC->CFG |= RCC_CFG_APB1PRES_DIV2;
    RCC->CFG |= RCC_CFG_APB2PRES_DIV1;

    FLASH->AC &= (uint32_t)((uint32_t)~FLASH_AC_LATENCY);
    FLASH->AC |= (uint32_t)(FLASH_AC_LATENCY_3);

    /* Select PLL as system clock source */
    RCC->CFG &= (uint32_t)((uint32_t) ~(RCC_CFG_SCLKSW));
    RCC->CFG |= (uint32_t)RCC_CFG_SCLKSW_PLL;
    while ((RCC->CFG & RCC_CFG_SCLKSTS) != RCC_CFG_SCLKSTS_PLL) 
    {
    }
}

/**
 * @brief  Configures USB Clock input (48MHz).
 * @param  sysclk: system clock.
 * @return USBClock set Status.
 */
ErrorStatus Set_USBClock(uint32_t sysclk)
{
    ErrorStatus status = SUCCESS;

    switch(sysclk)
    {
    case SYSCLK_VALUE_48MHz: 
        RCC_ConfigUsbClk(RCC_USBCLK_SRC_PLLCLK_DIV1);
        break;
        
    case SYSCLK_VALUE_72MHz: 
        RCC_ConfigUsbClk(RCC_USBCLK_SRC_PLLCLK_DIV1_5);
        break;
        
    case SYSCLK_VALUE_96MHz: 
        RCC_ConfigUsbClk(RCC_USBCLK_SRC_PLLCLK_DIV2);
        break;
        
    default:
        status = ERROR;
        break;
    }

    return status;
}

/**
 * @brief  Power-off system clocks and power while entering suspend mode.
 */
void Enter_LowPowerMode(void)
{
    /* Set the device state to suspend */
    bDeviceState = SUSPENDED;
}

/**
 * @brief  Restores system clocks and power while exiting suspend mode.
 */
void Leave_LowPowerMode(void)
{
    USB_DeviceMess *pInfo = &Device_Info;

    /* Set the device state to the correct state */
    if (pInfo->CurrentConfiguration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
    else
    {
        bDeviceState = ATTACHED;
    }
}

/**
  * @brief  Configures USART COM port.
  * @param  USART_InitStruct: pointer to a USART_InitType structure that
  *         contains the configuration information for the specified USART peripheral.
  */
void USART_COM_Init(USART_InitType* USART_InitStruct)
{
    GPIO_InitType GPIO_InitStructure;
    NVIC_InitType NVIC_InitStructure;

    /* Enable GPIO clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA | RCC_APB2_PERIPH_AFIO, ENABLE);
    /* Enable USART1 Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_USART1, ENABLE);

    /* Initialize GPIO_InitStructure */
    GPIO_InitStruct(&GPIO_InitStructure);

    /* Configure USART1 Tx as alternate function push-pull */
    GPIO_InitStructure.Pin = GPIO_PIN_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);


    /* Configure USART1 Rx as input floating */
    GPIO_InitStructure.Pin = GPIO_PIN_10;
    GPIO_InitStructure.GPIO_Pull      = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF4_USART1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel            = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd         = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
        
    /* USART1 configuration */
    USART_Init(USART1, USART_InitStruct);
  
    /* Enable the USART1 Receive interrupt */
    USART_ConfigInt(USART1, USART_INT_RXDNE, ENABLE);

    /* Enable USART1 */
    USART_Enable(USART1, ENABLE);
}

/**
 * @brief Configures the USB interrupts.
 */
void USB_Interrupts_Config(void)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_InitStructure;

    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USB interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = USB_LP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USB Wake-up interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                   = USBWakeUp_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    /* Configure the EXTI line 17 connected internally to the USB IP */
    EXTI_ClrITPendBit(EXTI_LINE17);
    EXTI_InitStructure.EXTI_Line = EXTI_LINE17; 
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
}

/**
 * @brief configure the UASRT with default values.
 */
void USART_Config_Default(void)
{
    /* USART1 default configuration */
    /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - Parity Odd
        - Hardware flow control disabled
        - Receive and transmit enabled
    */
    USART_InitStructure.BaudRate = 115200;
    USART_InitStructure.WordLength          = USART_WL_8B;
    USART_InitStructure.StopBits            = USART_STPB_1;
    USART_InitStructure.Parity              = USART_PE_NO;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode                = USART_MODE_RX | USART_MODE_TX;

    /* Configure and enable the USART1 */
    USART_COM_Init(&USART_InitStructure);
}

/**
 * @brief  Configure the USART according to the line coding structure.
 * @return TRUE or FALSE.
 */
bool USART_Config(void)
{
    /* set the Stop bit*/
    switch (linecoding.format)
    {
        case 0:
            USART_InitStructure.StopBits = USART_STPB_1;
            break;
        case 1:
            USART_InitStructure.StopBits = USART_STPB_1_5;
            break;
        case 2:
            USART_InitStructure.StopBits = USART_STPB_2;
            break;
        default :
            {
                USART_Config_Default();
                return (false);
            }
    }

    /* set the parity bit*/
    switch (linecoding.paritytype)
    {
        case 0:
            USART_InitStructure.Parity = USART_PE_NO;
            break;
        case 1:
            USART_InitStructure.Parity = USART_PE_EVEN;
            break;
        case 2:
            USART_InitStructure.Parity = USART_PE_ODD;
            break;
        default :
            {
                USART_Config_Default();
                return (false);
            }
    }

    /*set the data type : only 8bits and 9bits is supported */
    switch (linecoding.datatype)
    {
        case 0x07:
            /* With this configuration a parity (Even or Odd) should be set */
            USART_InitStructure.WordLength = USART_WL_8B;
            break;
        case 0x08:
            if (USART_InitStructure.Parity == USART_PE_NO)
            {
                USART_InitStructure.WordLength = USART_WL_8B;
            }
        	else 
            {
                USART_InitStructure.WordLength = USART_WL_9B;
            }
        break;
        default :
        {
            USART_Config_Default();
            return (false);
        }
    }

    USART_InitStructure.BaudRate = linecoding.bitrate;
    USART_InitStructure.HardwareFlowControl = USART_HFCTRL_NONE;
    USART_InitStructure.Mode = USART_MODE_RX | USART_MODE_TX;

    /* Configure and enable the USART */
    USART_COM_Init(&USART_InitStructure);

    return (true);
}

/**
 * @brief  send the received data from USB to the UART.
 * @param  data_buffer: data buffer pointer.
 * @param  Nb_bytes: data length.
 */
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes)
{
    uint32_t i;

    for (i = 0; i < Nb_bytes; i++)
    {
        USART_SendData(USART1, *(data_buffer + i));
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXDE) == RESET); 
    }  
}

/**
 * @brief  send data to USB.
 */
void Handle_USBAsynchXfer (void)
{
    uint16_t USB_Tx_ptr;
    uint16_t USB_Tx_length;

    if(USB_Tx_State != 1)
    {
        if (USART_Rx_ptr_out == USART_RX_DATA_SIZE)
        {
            USART_Rx_ptr_out = 0;
        }

        if(USART_Rx_ptr_out == USART_Rx_ptr_in) 
        {
            USB_Tx_State = 0; 
            return;
        }

        if(USART_Rx_ptr_out > USART_Rx_ptr_in) /* rollback */
        { 
            USART_Rx_length = USART_RX_DATA_SIZE - USART_Rx_ptr_out;
        }
        else 
        {
            USART_Rx_length = USART_Rx_ptr_in - USART_Rx_ptr_out;
        }

        if (USART_Rx_length > VIRTUAL_COM_PORT_DATA_SIZE)
        {
            USB_Tx_ptr = USART_Rx_ptr_out;
            USB_Tx_length = VIRTUAL_COM_PORT_DATA_SIZE;

            USART_Rx_ptr_out += VIRTUAL_COM_PORT_DATA_SIZE;
            USART_Rx_length -= VIRTUAL_COM_PORT_DATA_SIZE;
        }
        else
        {
            USB_Tx_ptr = USART_Rx_ptr_out;
            USB_Tx_length = USART_Rx_length;

            USART_Rx_ptr_out += USART_Rx_length;
            USART_Rx_length = 0;
        }
        USB_Tx_State = 1; 
        USB_CopyUserToPMABuf(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
        USB_SetEpTxCnt(ENDP1, USB_Tx_length);
        USB_SetEpTxValid(ENDP1);
    }
  
}

/**
 * @brief  send the received data from UART 0 to USB.
 */
void USART_To_USB_Send_Data(void)
{
    if (linecoding.datatype == 7)
    {
        USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(USART1) & 0x7F;
    }
    else if (linecoding.datatype == 8)
    {
        USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(USART1);
    }

    USART_Rx_ptr_in++;

    /* To avoid buffer overflow */
    if(USART_Rx_ptr_in == USART_RX_DATA_SIZE)
    {
        USART_Rx_ptr_in = 0;
    }
}

/**
 * @brief  Configures USB Clock input (48MHz).
 * @param  sysclk: system clock.
 * @return USBClock set Status.
 */
ErrorStatus USB_Config(uint32_t sysclk)
{
    ErrorStatus status = SUCCESS;

    if(Set_USBClock(sysclk) == SUCCESS)
    {
        RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_USB, ENABLE);
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }

    return status;
}



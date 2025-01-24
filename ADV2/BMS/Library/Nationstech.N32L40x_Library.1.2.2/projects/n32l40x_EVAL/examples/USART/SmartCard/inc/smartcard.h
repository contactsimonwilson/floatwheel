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
 * @file smartcard.h
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __SMARTCARD_H__
#define __SMARTCARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l40x.h"

/* Exported constants --------------------------------------------------------*/
#define T0_PROTOCOL        0x00  /* T0 protocol */
#define DIRECT             0x3B  /* Direct bit convention */
#define INDIRECT           0x3F  /* Indirect bit convention */
#define SETUP_LENGTH       20
#define HIST_LENGTH        20
#define LC_MAX             255 //20
#define SC_RECEIVE_TIMEOUT 0x4000  /* Direction to reader */

/* SC Tree Structure -----------------------------------------------------------
                              MasterFile
                           ________|___________
                          |        |           |
                        System   UserData     Note
------------------------------------------------------------------------------*/

#define _USART2_

#ifdef _USART2_
//------------------------------------------------------------------------//
#define SC_USART                 USART2
#define SC_USART_GPIO            GPIOA
#define SC_USART_CLK             RCC_APB1_PERIPH_USART2
#define SC_USART_GPIO_CLK        RCC_APB2_PERIPH_GPIOA
#define SC_USART_PIN_TX          GPIO_PIN_2
#define SC_USART_PIN_CK          GPIO_PIN_4
#define SC_USART_Tx_GPIO_AF      GPIO_AF4_USART2
#define SC_USART_Clk_GPIO_AF     GPIO_AF4_USART2
#define SC_USART_APBxClkCmd      RCC_EnableAPB1PeriphClk
#define SC_USART_IRQn            USART2_IRQn
#define SC_USART_IRQHandler      USART2_IRQHandler 

#define SC_USART_DMAx           DMA
#define SC_USART_DMAx_CLK       RCC_AHB_PERIPH_DMA
#define SC_USART_DR_Base        (USART2_BASE + 0x04)
#define SC_USART_Tx_DMA_Channel DMA_CH7
#define SC_USART_Tx_DMA_FLAG    DMA_FLAG_TC7
#define SC_USART_Tx_DMA_REMAP   DMA_REMAP_USART2_TX
#define SC_USART_Rx_DMA_Channel DMA_CH6
#define SC_USART_Rx_DMA_FLAG    DMA_FLAG_TC6
#define SC_USART_Rx_DMA_REMAP   DMA_REMAP_USART2_RX


#endif  // _TEST_7816_

//------------------------------------------------------------------------//
#define SC_PIN_RESET              GPIO_PIN_7
#define SC_PIN_RESET_GPIO         GPIOC
#define SC_PIN_RESET_GPIO_CLK     RCC_APB2_PERIPH_GPIOC

//------------------------------------------------------------------------//
// #define SC_DETECT_EXTI            EXTI_LINE7
// #define SC_DETECT_PIN             GPIOC_PORT_SOURCE //GPIO_PortSourceGPIOC
// #define SC_DETECT_GPIO            GPIO_PIN_SOURCE7
// #define SC_DETECT_IRQ             EXTI9_5_IRQn
// #define SC_DETECT_IRQHandler      EXTI9_5_IRQHandler   //xzy9_4->4_15



/* SC ADPU Command: Operation Code -------------------------------------------*/
#define SC_CLA_GSM11       0xA0

/*------------------------ Data Area Management Commands ---------------------*/
#define SC_SELECT_FILE     0xA4
#define SC_GET_RESPONCE    0xC0
#define SC_STATUS          0xF2
#define SC_UPDATE_BINARY   0xD6
#define SC_READ_BINARY     0xB0
#define SC_WRITE_BINARY    0xD0
#define SC_UPDATE_RECORD   0xDC
#define SC_READ_RECORD     0xB2

/*-------------------------- Administrative Commands -------------------------*/
#define SC_CREATE_FILE     0xE0

/*-------------------------- Safety Management Commands ----------------------*/
#define SC_VERIFY          0x20
#define SC_CHANGE          0x24
#define SC_DISABLE         0x26
#define SC_ENABLE          0x28
#define SC_UNBLOCK         0x2C
#define SC_EXTERNAL_AUTH   0x82
#define SC_GET_CHALLENGE   0x84

/*-------------------------- Answer to reset Commands ------------------------*/
#define SC_GET_A2R         0x00

/* SC STATUS: Status Code ----------------------------------------------------*/
#define SC_EF_SELECTED     0x9F
#define SC_DF_SELECTED     0x9F
#define SC_OP_TERMINATED   0x9000

/* Smartcard Voltage */
#define SC_VOLTAGE_5V      0
#define SC_VOLTAGE_3V      1



/*-------------------------- Answer to reset state ------------------------*/

#define TA_BIT          (1<<4)  /**< TAx presence bit (bit 4, 0x10) */
#define TB_BIT          (1<<5)  /**< TBx presence bit (bit 5, 0x20) */
#define TC_BIT          (1<<6)  /**< TCx presence bit (bit 6, 0x40) */
#define TD_BIT          (1<<7)  /**< TDx presence bit (bit 7, 0x80) */
#define STATE_PARSE_TS                            1
#define STATE_PARSE_T0                            2
#define STATE_PARSE_TA                            3
#define STATE_PARSE_TB                            4
#define STATE_PARSE_TC                            5
#define STATE_PARSE_TD                            6
#define STATE_PARSE_HIST_BYTES                    7
#define STATE_PARSE_TCK                           8
#define STATE_PARSE_END                           255

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    SC_POWER_ON = 0x00,
    SC_RESET_LOW = 0x01,
    SC_RESET_HIGH = 0x02,
    SC_ACTIVE = 0x03,
    SC_ACTIVE_ON_T0 = 0x04,
    SC_POWER_OFF = 0x05
} SC_State;

/* ATR structure - Answer To Reset -------------------------------------------*/
typedef struct
{
    uint8_t TS;               /* Bit Convention */
    uint8_t T0;               /* High nibble = Number of setup byte; low nibble = Number of historical byte */
    uint8_t T[SETUP_LENGTH];  /* Setup array */
    uint8_t H[HIST_LENGTH];   /* Historical array */
    uint8_t TCK;              /* TCK */
    uint8_t Tlength;          /* Setup array dimension */
    uint8_t Hlength;          /* Historical array dimension */
} SC_ATR;

/* ADPU-Header command structure ---------------------------------------------*/
typedef struct
{
    uint8_t CLA;  /* Command class */
    uint8_t INS;  /* Operation code */
    uint8_t P1;   /* Selection Mode */
    uint8_t P2;   /* Selection Option */
} SC_Header;

/* ADPU-Body command structure -----------------------------------------------*/
typedef struct
{
    uint8_t LC;           /* Data field length */
    uint8_t Data[LC_MAX];  /* Command parameters */
    uint8_t LE;           /* Expected length of data to be returned */
} SC_Body;

/* ADPU Command structure ----------------------------------------------------*/
typedef struct
{
    SC_Header Header;
    SC_Body Body;
} SC_ADPU_Commands;

/* SC response structure -----------------------------------------------------*/
typedef struct
{
    uint8_t Data[LC_MAX];  /* Data returned from the card */
    uint8_t SW1;          /* Command Processing status */
    uint8_t SW2;          /* Command Processing qualification */
} SC_ADPU_Responce;

/* SC Initial structure -----------------------------------------------------*/
typedef struct
{
    uint8_t Clk_Div;     /* USART Clk Div Value */
    uint8_t GT;          /* Guard Time*/
    uint8_t StopBits;  
    uint8_t Parity;
    uint8_t NackEn;
} SC_InitStructure;

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* APPLICATION LAYER ---------------------------------------------------------*/
void SC_Handler(SC_State *SCState, SC_ADPU_Commands *SC_ADPU, SC_ADPU_Responce *SC_Response, SC_InitStructure *SC_InitCfg);
void SC_PowerCmd(FunctionalState NewState);
void SC_Reset(Bit_OperateType ResetState);
void SC_DetectPinConfig(void);
void SC_ParityErrorHandler(void);
void SC_PTSConfig(void);

void SC_APDU_Init(SC_ADPU_Commands *SC_ADPU, uint8_t SC_APDU_CLA, uint8_t SC_APDU_INS, uint8_t SC_APDU_P1, uint8_t SC_APDU_P2,
 uint8_t SC_APDU_LC, uint8_t *SC_APDU_Data, uint8_t SC_APDU_LE);
void SC_DeInit(void);

#ifdef __cplusplus
}
#endif

#endif /* __SMARTCARD_H__ */
/**
 * @}
 */



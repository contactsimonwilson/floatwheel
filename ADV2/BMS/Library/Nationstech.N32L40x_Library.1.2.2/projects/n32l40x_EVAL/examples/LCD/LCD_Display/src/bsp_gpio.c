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
 * @file bsp_gpio.c
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */

/* Includes ------------------------------------------------------------------*/
#include "bsp_gpio.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup BSP_EVAL
  * @{
  */


/* Private variables ---------------------------------------------------------*/

/**
  * @brief  Init the GPIO used for LCD COMx and SEGx.
  * @param  None
  * @retval None
  */
#if  (BOARD_TYPE == BOARD_N32G435)
/*For board N32G435_EVB_V1.0 */
void LCD_GPIO_Init(void)
{
    GPIO_InitType  gpioinitstruct;

    /*Enable LCD GPIO Clocks*/
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_GPIOC|RCC_APB2_PERIPH_GPIOD, ENABLE);

    /*Init GPIO init struct*/
    GPIO_InitStruct(&gpioinitstruct);

    /*Configure peripheral GPIO output for LCD*/
    /* Port A : */
    /*  PA1: SEG0   PA2: SEG1   PA3: SEG2   PA6: SEG3
        PA7: SEG4   PA8: COM0   PA9: COM1   PA10:COM2   */
    gpioinitstruct.Pin    =   GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |  GPIO_PIN_6 
                            | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |  GPIO_PIN_10 ;
    gpioinitstruct.GPIO_Mode      = GPIO_Mode_Analog;
    gpioinitstruct.GPIO_Pull      = GPIO_No_Pull;
    gpioinitstruct.GPIO_Alternate = GPIO_AF10_LCD;
    GPIO_InitPeripheral(GPIOA, &gpioinitstruct);

    /* Port B */
    /*  PB0: SEG5   PB1: SEG6   PB10:SEG10  PB11:SEG11
        PB12:SEG12  PB14:SEG14      */
    gpioinitstruct.Pin    =   GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_10   | GPIO_PIN_11 
                            | GPIO_PIN_12 | GPIO_PIN_14;
    GPIO_InitPeripheral(GPIOB, &gpioinitstruct);

    /* Port C*/
    /*  PC0: SEG18  PC1: SEG19  PC2: SEG20  PC3: SEG21  
        PC4: SEG22  PC5: SEG23  PC13:SEG35  PC6: SEG24 */
    gpioinitstruct.Pin    =   GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2  | GPIO_PIN_3 
                            | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_13 | GPIO_PIN_6; 
    GPIO_InitPeripheral(GPIOC, &gpioinitstruct);

    /* Port D*/
    /*  PD1: SEG33  PD3: SEG34  PD8: SEG36  PD9: SEG37  
        PD10:SEG38  PD11:SEG39  */
    gpioinitstruct.Pin    =   GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_8  | GPIO_PIN_9 
                            | GPIO_PIN_10 | GPIO_PIN_11; 
    GPIO_InitPeripheral(GPIOD, &gpioinitstruct);

    /*PA15:COM3*/
    gpioinitstruct.Pin  = GPIO_PIN_15 ;
    gpioinitstruct.GPIO_Alternate   = GPIO_AF11_LCD;
    GPIO_InitPeripheral(GPIOA, &gpioinitstruct);
}

#elif   (BOARD_TYPE == BOARD_N32L436)
/*For board N32L436_EVB_V1.1 */
void LCD_GPIO_Init(void)
{
    GPIO_InitType  gpioinitstruct;

    /*Enable LCD GPIO Clocks*/
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_GPIOC|RCC_APB2_PERIPH_GPIOD, ENABLE);

    /*Init GPIO init struct*/
    GPIO_InitStruct(&gpioinitstruct);

    /*Configure peripheral GPIO output for LCD*/
    /* Port A : */
    /*  PA1: SEG0   PA2: SEG1   PA3: SEG2   PA6: SEG3
        PA7: SEG4   */
    gpioinitstruct.Pin    =   GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 |  GPIO_PIN_6 
                            | GPIO_PIN_7;
    gpioinitstruct.GPIO_Mode      = GPIO_Mode_Analog;
    gpioinitstruct.GPIO_Pull      = GPIO_No_Pull;
    gpioinitstruct.GPIO_Alternate = GPIO_AF10_LCD;
    GPIO_InitPeripheral(GPIOA, &gpioinitstruct);

    /* Port B */
    /*  PB0: SEG5   PB1: SEG6   PB10:SEG10  PB11:SEG11
        PB12:SEG12  PB13:SEG13  PB14:SEG14      */
    gpioinitstruct.Pin    =   GPIO_PIN_0  | GPIO_PIN_1  | GPIO_PIN_10   | GPIO_PIN_11 
                            | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14;
    GPIO_InitPeripheral(GPIOB, &gpioinitstruct);

    /* Port C*/
    /*  PC0: SEG18  PC1: SEG19  PC2: SEG20  PC3: SEG21  
        PC4: SEG22  PC5: SEG23  PC13:SEG35 */
    gpioinitstruct.Pin    =   GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2  | GPIO_PIN_3 
                            | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_13; 
    GPIO_InitPeripheral(GPIOC, &gpioinitstruct);

    /* Port D*/
    /*  PD1: SEG33  PD3: SEG34  PD8: SEG36  PD9: SEG37  
        PD10:SEG38  PD11:SEG39  */
    gpioinitstruct.Pin    =   GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_8  | GPIO_PIN_9 
                            | GPIO_PIN_10 | GPIO_PIN_11; 
    GPIO_InitPeripheral(GPIOD, &gpioinitstruct);

#ifdef     LCD_8COM_USED
#ifdef  BOARD_V1_0
    /* Port D*/
    /*  PD4:COM4    PD5:COM5    PD6:COM6    PD7:COM7  */
    gpioinitstruct.Pin    =   GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6  | GPIO_PIN_7; 
    GPIO_InitPeripheral(GPIOD, &gpioinitstruct);
#else
    gpioinitstruct.Pin    =   GPIO_PIN_2; 
    GPIO_InitPeripheral(GPIOD, &gpioinitstruct);
    
    gpioinitstruct.Pin    =   GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12; 
    GPIO_InitPeripheral(GPIOC, &gpioinitstruct);
#endif
#endif

}
#endif

/**
  * @brief  Init normal key
  * @param  None
  * @retval None
  */
void Key_GPIO_Init(void)
{
    GPIO_InitType  gpioinitstruct;

    /*Enable LCD GPIO Clocks*/
    RCC_EnableAPB2PeriphClk( RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_GPIOD
                            |RCC_APB2_PERIPH_AFIO, 
                             ENABLE);

    /*Init GPIO init struct*/
    GPIO_InitStruct(&gpioinitstruct);

    /* Port A*/
    /*PA5:KEY1*/
    gpioinitstruct.Pin    =    GPIO_PIN_5;
    gpioinitstruct.GPIO_Mode      = GPIO_Mode_IT_Rising;
    gpioinitstruct.GPIO_Pull      = GPIO_Pull_Down;
    gpioinitstruct.GPIO_Alternate = GPIO_NO_AF;
    GPIO_InitPeripheral(GPIOA, &gpioinitstruct);

    /*PD12:KEY2     PD13:KEY3 */
    gpioinitstruct.Pin    =   GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitPeripheral(GPIOD, &gpioinitstruct);

    GPIO_ConfigEXTILine(GPIOA_PORT_SOURCE,GPIO_PIN_SOURCE5);
    GPIO_ConfigEXTILine(GPIOD_PORT_SOURCE,GPIO_PIN_SOURCE12);
    GPIO_ConfigEXTILine(GPIOD_PORT_SOURCE,GPIO_PIN_SOURCE13);

    NVIC_InitType NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;

    NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI15_10_IRQn;
    NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Nations Technologies Inc *****END OF FILE****/


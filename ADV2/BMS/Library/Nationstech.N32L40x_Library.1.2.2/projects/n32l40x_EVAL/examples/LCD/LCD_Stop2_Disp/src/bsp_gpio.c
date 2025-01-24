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
/*For board N32L436MBL_EVB*/
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
    /*  PD0:SEG32   PD1: SEG33  PD3: SEG34  PD8: SEG36  PD9: SEG37  
        PD10:SEG38  PD11:SEG39  */
    gpioinitstruct.Pin    =   GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_8  | GPIO_PIN_9 
                            | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_0; 
    GPIO_InitPeripheral(GPIOD, &gpioinitstruct);

#if     (defined(N32L436MBL_EVB_V1_0))
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
}


/**
  * @brief  Init normal GPIO
  * @param  None
  * @retval None
  */
void GPIO_Init(void)
{
    GPIO_InitType  gpioinitstruct;

    /*Enable KEY port clock*/
    RCC_EnableAPB2PeriphClk( KEY_PORT_CLOCK,  ENABLE);
    
    /*Init GPIO init struct*/
    GPIO_InitStruct(&gpioinitstruct);

    /*KEY*/
    gpioinitstruct.Pin              = KEY_PIN;
    gpioinitstruct.GPIO_Mode        = GPIO_Mode_Input;
    gpioinitstruct.GPIO_Pull        = GPIO_Pull_Down;
    gpioinitstruct.GPIO_Alternate   = GPIO_NO_AF;
    GPIO_InitPeripheral(KEY_PORT, &gpioinitstruct);

#ifdef  USE_STATUS_LED
    /*Enable LED port clock*/
    RCC_EnableAPB2PeriphClk( LED_PORT_CLOCK,  ENABLE);
    
    /*LED*/
    MCU_RUN_LED_ON;
    RTC_INT_LED_OFF;
    UDD_INT_LED_OFF;
    
    gpioinitstruct.Pin              = LED_PIN;
    gpioinitstruct.GPIO_Mode        = GPIO_Mode_Out_PP;
    gpioinitstruct.GPIO_Pull        = GPIO_No_Pull;
    gpioinitstruct.GPIO_Alternate   = GPIO_NO_AF;
    gpioinitstruct.GPIO_Current     = GPIO_DC_2mA;
    gpioinitstruct.GPIO_Slew_Rate   = GPIO_Slew_Rate_High;
    GPIO_InitPeripheral(LED_PORT, &gpioinitstruct);
#endif
}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Nations Technologies Inc *****END OF FILE****/


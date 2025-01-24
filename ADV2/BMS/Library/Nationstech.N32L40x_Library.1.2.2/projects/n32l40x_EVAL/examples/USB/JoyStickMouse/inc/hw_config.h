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
 * @file hw_config.h
 * @author Nations
 * @version V1.2.2
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __HW_CONFIG_H__
#define __HW_CONFIG_H__

#include "n32l40x.h"
#include "usb_type.h"

//#define USB_LOW_PWR_MGMT_SUPPORT

/* Exported define -----------------------------------------------------------*/
#define SYSCLK_VALUE_48MHz            ((uint32_t)48000000)
#define SYSCLK_VALUE_72MHz            ((uint32_t)72000000)
#define SYSCLK_VALUE_96MHz            ((uint32_t)96000000)
#define SYSCLK_VALUE_108MHz           ((uint32_t)108000000)
#define PCLK2_VALUE_72MHz             ((uint32_t)72000000)
#define PCLK2_VALUE_48MHz             ((uint32_t)48000000)

#define CURSOR_STEP     20

#define DOWN            2
#define LEFT            3
#define RIGHT           4
#define UP              5


void Set_System(void);
ErrorStatus Set_USBClock(uint32_t sysclk);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nCount);
void Cfg_KeyIO(void);
ErrorStatus USB_Config(uint32_t sysclk);
uint8_t JoyState(void);
void Joystick_Send(uint8_t Keys);
void Cfg_KeyIO(void);
ErrorStatus USB_Config(uint32_t sysclk);

typedef enum 
{  
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY = 2,
  BUTTON_RIGHT = 3,
  BUTTON_LEFT = 4,
  BUTTON_UP = 5,
  BUTTON_DOWN = 6,
  BUTTON_SEL = 7
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

typedef enum 
{ 
  JOY_NONE = 0,
  JOY_SEL = 1,
  JOY_DOWN = 2,
  JOY_LEFT = 3,
  JOY_RIGHT = 4,
  JOY_UP = 5
} JOYState_TypeDef;

/* Button Defines Legacy */ 
#define Button_WAKEUP        BUTTON_WAKEUP
#define Button_TAMPER        BUTTON_TAMPER
#define Button_KEY           BUTTON_KEY
#define Button_RIGHT         BUTTON_RIGHT
#define Button_LEFT          BUTTON_LEFT
#define Button_UP            BUTTON_UP
#define Button_DOWN          BUTTON_DOWN
#define Button_SEL           BUTTON_SEL
#define Mode_GPIO            BUTTON_MODE_GPIO
#define Mode_EXTI            BUTTON_MODE_EXTI
#define Button_Mode_TypeDef  ButtonMode_TypeDef
#define JOY_CENTER           JOY_SEL
#define JOY_State_TypeDef    JOYState_TypeDef
#define Button_PORT          GPIOA

#define BUTTONn                          8

/**
 * @brief Wakeup push-button
 */
#define WAKEUP_BUTTON_PIN                GPIO_PIN_0
#define WAKEUP_BUTTON_GPIO_PORT          GPIOA
#define WAKEUP_BUTTON_GPIO_CLK           RCC_APB2_PERIPH_GPIOA
/**
 * @brief Tamper push-button
 */
#define TAMPER_BUTTON_PIN                GPIO_PIN_13
#define TAMPER_BUTTON_GPIO_PORT          GPIOC
#define TAMPER_BUTTON_GPIO_CLK           RCC_APB2_PERIPH_GPIOC
/**
 * @brief Key push-button
 */
#define KEY_BUTTON_PIN                   GPIO_PIN_9
#define KEY_BUTTON_GPIO_PORT             GPIOB
#define KEY_BUTTON_GPIO_CLK              RCC_APB2_PERIPH_GPIOB
/**
 * @brief Joystick Right push-button
 */
#define RIGHT_BUTTON_PIN                 GPIO_PIN_4
#define RIGHT_BUTTON_GPIO_PORT           GPIOA
#define RIGHT_BUTTON_GPIO_CLK            RCC_APB2_PERIPH_GPIOA
/**
 * @brief Joystick Left push-button
 */
#define LEFT_BUTTON_PIN                  GPIO_PIN_5
#define LEFT_BUTTON_GPIO_PORT            GPIOA
#define LEFT_BUTTON_GPIO_CLK             RCC_APB2_PERIPH_GPIOA
/**
 * @brief Joystick Up push-button
 */
#define UP_BUTTON_PIN                    GPIO_PIN_6
#define UP_BUTTON_GPIO_PORT              GPIOA
#define UP_BUTTON_GPIO_CLK               RCC_APB2_PERIPH_GPIOA
/**
 * @brief Joystick Down push-button
 */  
#define DOWN_BUTTON_PIN                  GPIO_PIN_7
#define DOWN_BUTTON_GPIO_PORT            GPIOA
#define DOWN_BUTTON_GPIO_CLK             RCC_APB2_PERIPH_GPIOA
/**
 * @brief Joystick Sel push-button
 */
#define SEL_BUTTON_PIN                   GPIO_PIN_12
#define SEL_BUTTON_GPIO_PORT             GPIOD
#define SEL_BUTTON_GPIO_CLK              RCC_APB2_PERIPH_GPIOA

#endif /*__HW_CONFIG_H__*/

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

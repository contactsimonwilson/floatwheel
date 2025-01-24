#include <stdio.h>
#include <stdint.h>
#include "n32l40x.h"
#include "User_Key_Config.h"



/**
 * @brief  Configures key GPIO.
 * @param GPIOx pointer the config port
 *   This parameter can be one of the following values:
 *   GPIOA~GPIOD
 * @param Pin
 *   This parameter can be one of the following values:
     GPIO_PIN_0~GPIO_PIN_15
 */
void KeyInputExtiInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Enable the GPIO Clock */
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    /*Configure the GPIO pin as input floating*/
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitStructure.GPIO_Pull = GPIO_No_Pull;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
    /*Configure key EXTI Line to key input  Pin*/
    GPIO_ConfigEXTILine(GPIOA_PORT_SOURCE, GPIO_PIN_SOURCE0);
    /*Configure key EXTI line*/
    EXTI_InitStructure.EXTI_Line = EXTI_LINE0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
    /*Set key input interrupt priority*/
    NVIC_InitStructure.NVIC_IRQChannel                   = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x05;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

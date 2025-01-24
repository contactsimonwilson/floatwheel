#include "n32l40x.h"
#include "User_LED_Config.h"

/**
 * @brief  Toggles the selected led.
 * @param GPIOx Specifies the led port to be toggled.
 *   This parameter can be one of following parameters:
 *     @arg LED1_PORT
 *     @arg LED2_PORT
 *     @arg LED3_PORT
 * @param Led Specifies the led to be toggled.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 */
void LEDBlink(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

/**
 * @brief  Turns selected Led on.
 * @param GPIOx Specifies the led port to be set on.
 *   This parameter can be one of following parameters:
 *     @arg LED1_PORT
 *     @arg LED2_PORT
 *     @arg LED3_PORT
 * @param Led Specifies the Led to be set on.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 */
void LEDOn(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}

/**
 * @brief  Turns selected led Off.
 * @param GPIOx Specifies the led port to be set off.
 *   This parameter can be one of following parameters:
 *     @arg LED1_PORT
 *     @arg LED2_PORT
 *     @arg LED3_PORT
 * @param Led Specifies the Led to be set off.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 */
void LEDOff(GPIO_Module* GPIOx,uint16_t Pin)
{
    GPIOx->PBC = Pin;
}

/**
 * @brief config the led pin .
 * @param GPIOx Specifies the led port to be configured.
 *   This parameter can be one of following parameters:
 *     @arg LED1_PORT
 *     @arg LED2_PORT
 *     @arg LED3_PORT
 * @param Pin Specifies the led pin to be configured.
 *   This parameter can be one of following parameters:
 *     @arg LED1
 *     @arg LED2
 *     @arg LED3
 */
void LEDInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Enable LED Port Clock */
    if(GPIOA==GPIOx)
    {
      RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if(GPIOB==GPIOx)
    {
      RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if(GPIOC==GPIOx)
    {
      RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else if(GPIOD==GPIOx)
    {
      RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
    }
    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
}

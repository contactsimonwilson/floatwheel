#include "gp2.h"

/*
	GP2	-> PB5
*/
void GP2_Init(void)
{
	GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
	
	GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = GPIO_PIN_5;
    GPIO_InitStructure.GPIO_Pull  = GPIO_Pull_Up;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Input;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	
	GPIO_ConfigEXTILine(GPIOB_PORT_SOURCE, GPIO_PIN_SOURCE5);
	
	EXTI_InitStructure.EXTI_Line    = EXTI_LINE5;
    EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel                   = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0x00;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


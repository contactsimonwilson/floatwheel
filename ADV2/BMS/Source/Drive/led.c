#include "led.h"

/*
	LED -> PA3
*/

//static void delay(uint32_t i)
//{
//	while(i--);
//}

/**************************************************
 * @brie  :LED_Init()
 * @note  :LED初始化
 * @param :无
 * @retval:无
 **************************************************/
void LED_Init(void)
{
	GPIO_InitType GPIO_InitStructure;

	GPIO_InitStruct(&GPIO_InitStructure);
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA,ENABLE);
	
    GPIO_InitStructure.Pin          = GPIO_PIN_3;	
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  	= GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	
	LED_ON;
	
//	while(1)
//	{
//		delay(833333);
//		
//		LED_FLIP;
//	}
}

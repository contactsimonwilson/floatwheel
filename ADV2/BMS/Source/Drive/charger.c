#include "charger.h"

/*
	CHARGER -> PA8
*/

/**************************************************
 * @brie  :Charger_Init()
 * @note  :Charger初始化
 * @param :无
 * @retval:无
 **************************************************/
void Charger_Init(void)
{
	GPIO_InitType GPIO_InitStructure;

	GPIO_InitStruct(&GPIO_InitStructure);

	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA,ENABLE);

	GPIO_InitStructure.Pin            	= GPIO_PIN_8;	
    GPIO_InitStructure.GPIO_Current 	= GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    	= GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  		= GPIO_Mode_Input;
	GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	
//	GPIO_InitStructure.Pin          = GPIO_PIN_4;	
//    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
//    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
//    GPIO_InitStructure.GPIO_Mode  	= GPIO_Mode_Out_PP;
//    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
//	
//	CHARGER_L;
}





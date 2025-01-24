#include "ldo.h"

/*
	LDO -> PB4
*/

/**************************************************
 * @brie  :LDO_Init()
 * @note  :LDO初始化
 * @param :无
 * @retval:无
 **************************************************/
void LDO_Init(void)
{
	GPIO_InitType GPIO_InitStructure;

	GPIO_InitStruct(&GPIO_InitStructure);
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB,ENABLE);

    GPIO_InitStructure.Pin          = GPIO_PIN_4;	
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_Pull_Down;
    GPIO_InitStructure.GPIO_Mode  	= GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);

	LDO_OFF;
}

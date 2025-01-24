#include "mos.h"

/*
	DSG  	-> PBO
	CHG  	-> PB1
	PDSG	-> PB3
	PCHG 	-> PA15
	CHARGER -> PA7
*/

/**************************************************
 * @brie  :MOS_Init()
 * @note  :MOS初始化
 * @param :无
 * @retval:无
 **************************************************/
void MOS_Init(void)
{
	GPIO_InitType GPIO_InitStructure;

	GPIO_InitStruct(&GPIO_InitStructure);
	
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA,ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB,ENABLE);
	
	GPIO_InitStructure.Pin            	= GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3;	
    GPIO_InitStructure.GPIO_Current 	= GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    	= GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  		= GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.Pin			  = GPIO_PIN_7|GPIO_PIN_15;
	GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	
	DSG_OFF;
	CHG_OFF;
	PDSG_OFF;
	PCHG_OFF;
	CHARG_OFF;
}

#include "power.h"


/**************************************************
 * @brie   :Power_Init()
 * @note   :电源初始化
 * @param  :无
 * @retval :无
 **************************************************/
void Power_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);	
	
	//PWR_EN
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//Charge
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	PWR_OFF;
//	CHARGE_OFF;
}



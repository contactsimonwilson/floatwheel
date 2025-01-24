#include "time6.h"

/**************************************************
 * @brie  :Time6_Init()
 * @note  :Time6初始化 产生1ms中断
 * @param :无
 * @retval:无
 **************************************************/
void Time6_Init(void)
{
	NVIC_InitType NVIC_InitStructure;
	TIM_TimeBaseInitType TIM_TimeBaseStructure;
	
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_TIM6, ENABLE);

    TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
    TIM_TimeBaseStructure.Period    = 1000-1;
    TIM_TimeBaseStructure.Prescaler = 32-1;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	
	TIM_InitTimeBase(TIM6, &TIM_TimeBaseStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel                   = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
    TIM_ConfigInt(TIM6, TIM_INT_UPDATE, ENABLE);
    TIM_Enable(TIM6, ENABLE);	
}

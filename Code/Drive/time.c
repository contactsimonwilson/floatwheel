#include "time.h"

/**************************************************
 * @brie   :Time6_Init()
 * @note   :定时器6初始化，1ms中断
 * @param  :无
 * @retval :无
 **************************************************/
void Time6_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 1000-1;
	TIM_TimeBaseStructure.TIM_Prescaler = 32-1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM6, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

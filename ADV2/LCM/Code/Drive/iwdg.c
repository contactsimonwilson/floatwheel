#include "iwdg.h"

/**************************************************
 * @brie   :IWDG_Init()
 * @note   :IWDG初始化
 * @param  :无
 * @retval :无
 **************************************************/
void IWDG_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_128);
	IWDG_SetReload(1000);   // (128 * 1000)/114K = 1S 左右
	IWDG_ReloadCounter();
	IWDG_Enable();
}

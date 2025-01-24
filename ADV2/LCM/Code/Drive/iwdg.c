#include "iwdg.h"

/**************************************************
 * @brie   :IWDG_Init()
 * @note   :IWDG��ʼ��
 * @param  :��
 * @retval :��
 **************************************************/
void IWDG_Init(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_128);
	IWDG_SetReload(1000);   // (128 * 1000)/114K = 1S ����
	IWDG_ReloadCounter();
	IWDG_Enable();
}

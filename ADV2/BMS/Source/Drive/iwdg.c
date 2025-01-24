#include "iwdg.h"

__IO uint32_t LsiFreq     = 40000;

/**************************************************
 * @brie  :IWDG_Init()
 * @note  :IWDG初始化
 * @param :无
 * @retval:无
 **************************************************/
void IWDG_Init(void)
{
    IWDG_WriteConfig(IWDG_WRITE_ENABLE);
    /* 40K/32 = 1250 (0.0008S) */
    IWDG_SetPrescalerDiv(IWDG_PRESCALER_DIV32);
    IWDG_CntReload(1250);
    IWDG_ReloadKey();
    IWDG_Enable();
}



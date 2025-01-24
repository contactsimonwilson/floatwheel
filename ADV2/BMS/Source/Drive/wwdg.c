#include "wwdg.h"

/**************************************************
 * @brie  :WWDG_Init()
 * @note  :WWDG初始化
 * @param :无
 * @retval:无
 **************************************************/
void WWDG_Init(void)
{
	RCC_ClocksType temp;
	/* WWDG configuration */
    /* Enable WWDG clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_WWDG, ENABLE);
    RCC_GetClocksFreqValue(&temp);
    /* WWDG clock counter = (PCLK1(16MHz)/4096)/8 = 488 Hz (~2049 us)  */
    WWDG_SetPrescalerDiv(WWDG_PRESCALER_DIV8);
    /* Set Window value to 80; WWDG counter should be refreshed only when the counter
      is below 80 (and greater than 64) otherwise a reset will be generated */
    WWDG_SetWValue(80);
    /*Enable WWDG and set counter value to 127, WWDG timeout = ~2049 us * (127-63) = 131.136 ms
      In this case the refresh window is: ~2049 us * (127-80) = 96.3 ms < refresh window < ~2049us * 64 = 131.136 ms*/
    WWDG_Enable(127);
}

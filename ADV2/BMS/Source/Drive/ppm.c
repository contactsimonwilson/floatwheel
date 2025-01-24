#include "ppm.h"

/*
	PPM -> PA9 TIM1_CH2
*/

/**************************************************
 * @brie  :ppm_rcc_config()
 * @note  :ppm_rcc_config
 * @param :无
 * @retval:无
 **************************************************/
static void ppm_rcc_config(void)
{
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA,ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_TIM1,ENABLE);
	RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO,ENABLE);
}	

/**************************************************
 * @brie  :ppm_gpio_config()
 * @note  :ppm_gpio_config
 * @param :无
 * @retval:无
 **************************************************/
static void ppm_gpio_config(void)
{
	GPIO_InitType GPIO_InitStructure;

    GPIO_InitStruct(&GPIO_InitStructure);
	
	GPIO_InitStructure.Pin          	= GPIO_PIN_9;	
    GPIO_InitStructure.GPIO_Current 	= GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    	= GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  		= GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Alternate 	= GPIO_AF2_TIM1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
	
}

/**************************************************
 * @brie  :ppm_time1_config()
 * @note  :ppm_time1_config
 * @param :无
 * @retval:无
 **************************************************/
static void ppm_time1_config(void)
{
	TIM_TimeBaseInitType TIM_TimeBaseStructure;

	TIM_InitTimBaseStruct(&TIM_TimeBaseStructure);
	
    TIM_TimeBaseStructure.Period    = 20000-1;
    TIM_TimeBaseStructure.Prescaler = 64-1;
    TIM_TimeBaseStructure.ClkDiv    = 0;
    TIM_TimeBaseStructure.CntMode   = TIM_CNT_MODE_UP;
	TIM_TimeBaseStructure.RepetCnt  = 0;
	
	TIM_InitTimeBase(TIM1, &TIM_TimeBaseStructure);
	
}

/**************************************************
 * @brie  :ppm_time1_config()
 * @note  :ppm_time1_config
 * @param :无
 * @retval:无
 **************************************************/
static void ppm_time1_oc_config(void)
{
	OCInitType TIM_OCInitStructure;
	
	TIM_InitOcStruct(&TIM_OCInitStructure);
	
	TIM_OCInitStructure.OcMode       = TIM_OCMODE_PWM2;
    TIM_OCInitStructure.OutputState  = TIM_OUTPUT_STATE_ENABLE;
    TIM_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_DISABLE;
    TIM_OCInitStructure.Pulse        = 1500;
    TIM_OCInitStructure.OcPolarity   = TIM_OC_POLARITY_LOW;
    TIM_OCInitStructure.OcNPolarity  = TIM_OCN_POLARITY_LOW;
    TIM_OCInitStructure.OcIdleState  = TIM_OC_IDLE_STATE_SET;
    TIM_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;
    TIM_InitOc2(TIM1, &TIM_OCInitStructure);
	
	TIM_Enable(TIM1, ENABLE);
	TIM_EnableCtrlPwmOutputs(TIM1, ENABLE);
}

/**************************************************
 * @brie  :PPM_Init()
 * @note  :PPM初始化
 * @param :无
 * @retval:无
 **************************************************/
void PPM_Init(void)
{
	ppm_rcc_config();
	ppm_gpio_config();
	ppm_time1_config();
	ppm_time1_oc_config();
	Set_PPM(1500);//1.5ms
}

/**************************************************
 * @brie  :Set_PPM()
 * @note  :	1.5-1ms对应0-10度翘头 
 *			1.5-2ms对应0-（-10度）翘头
 * @param :ppm_val
 * @retval:无
 **************************************************/
void Set_PPM(uint16_t ppm_val)
{
	if((ppm_val < 1000) || (ppm_val>2000))
	{
		return;
	}
	
	TIM_SetCmp2(TIM1,ppm_val);
}



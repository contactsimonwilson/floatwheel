#include "pwr.h"

/**************************************************
 * @brie  :PWR_Init()
 * @note  :PWR��ʼ��
 * @param :��
 * @retval:��
 **************************************************/
void PWR_Init(void)
{
	RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
}

/**************************************************
 * @brie  :Enter_Low_Power()
 * @note  :����͹���
 * @param :��
 * @retval:��
 **************************************************/
void Enter_Low_Power(void)
{
	PWR_WakeUpPinEnable(WAKEUP_PIN1,ENABLE);	//����
	PWR_WakeUpPinEnable(WAKEUP_PIN0,ENABLE);	//�����
//	DBG_ConfigPeriph(DBG_STDBY,ENABLE);
//	if (PWR_GetFlagStatus(1,PWR_STBY_FLAG) != RESET)
//	{
//		PWR_ClearFlag(PWR_STBY_FLAG);
//	}
//	if (PWR_GetFlagStatus(1,PWR_WKUP1_FLAG) != RESET)
//	{
//		PWR_ClearFlag(PWR_WKUP1_FLAG);
//	}
//	if (PWR_GetFlagStatus(1,PWR_WKUP0_FLAG) != RESET)
//	{
//		PWR_ClearFlag(PWR_WKUP0_FLAG);
//	}
	PWR_EnterSTANDBYMode(PWR_STOPENTRY_WFI,PWR_CTRL3_WKUP0EN|PWR_CTRL3_WKUP1EN);
}	



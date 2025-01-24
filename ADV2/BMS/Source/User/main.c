/**
  ******************************************************************************
  * @file       ： main.c
  * @author     :  FCZ
  * @version    ： V1.0.0
  * @date       ： 2024年08月03日
  * @brief      ： BMS VESC 
  * @mcu        :  N32L403K8Q7
  ******************************************************************************/
/*----------------------------------------------------------------------------
  更新日志:
  2024-08-03 V1.0.0:初始版本
  ----------------------------------------------------------------------------*/
#include "n32l40x.h"
#include "can.h"
#include "User_Delay_Config.h"
#include "vesc_can.h"
#include "led.h"
#include "ldo.h"
#include "mos.h"
#include "time6.h"
#include "ppm.h"
#include "led_app.h"
#include "DVC1124_init.h"
#include "pwr.h"
#include "key.h"
#include "key_app.h"
#include "vesc_can_app.h"
#include "DVC1124_app.h"
#include "power_app.h"
#include "charger.h"
#include "gp2.h"
#include "BMS_Protection.h"
#include "iwdg.h"

RCC_ClocksType System_Clock;
	
#define IWDG_DEBUG	1	//1编译看门狗 0不编译看门狗

/**************************************************
 * @brie  :main()
 * @note  :主函数
 * @param :无
 * @retval:无
 **************************************************/
int main(void)
{
	RCC_GetClocksFreqValue(&System_Clock);
	GP2_Init();
	User_Delay_init();
	User_Delay_xms(10);
	
	MOS_Init();
	LDO_Init();
	KEY_Init();
	Charger_Init();
	Power_On_Detection();	//开机检测
	LED_Init();
	CANM_Init();
	CAN_Config();
	DVC1124_Init();
	Time6_Init();
	PPM_Init();
	PWR_Init();
	User_Delay_xms(50);
	
	Flag.Software_Reset = 0;
	
	if(((RCC->CTRLSTS>>29)&1) == 1)	//看门狗复位
	{
		LED_ON;
#if IWDG_DEBUG		
		IWDG_Init();
#endif		
		LDO_ON;
		User_Delay_xms(50);
		DSG_ON;
		CHG_ON;
		PDSG_OFF;
		PCHG_OFF;
		CHARG_OFF;
		Set_PPM(1500);//1.5ms
		Flag.Software_Reset = 0;
		Flag.Power = 2;
	}
	else if(((RCC->CTRLSTS>>28)&1) == 1)	//软件复位
	{
#if IWDG_DEBUG			
		Flag.Power = 3;
#endif		
		Flag.Software_Reset = 1;
	
	}
	else 
	{
#if IWDG_DEBUG		
		IWDG_Init();
#endif		
	}
	RCC_ClrFlag();
	
	while(1)
	{
		LED_Task();
		KEY_Task();
		Power_Task();
		DVC1124_Task();
		VESC_CAN_Task();
		Charger_Task();
		BMS_Protection_Task();
		Automatic_Shutdown();
		IWDG_ReloadKey();
	}
}

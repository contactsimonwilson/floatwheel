#include "power_app.h"
#include "CellBalance.h"
#include "vesc_can.h"
#include "DVC1124_app.h"

/**************************************************
 * @brie  :Power_On_Detection()
 * @note  :开机检测
 * @param :无
 * @retval:无
 **************************************************/
void Power_On_Detection(void)
{
//	if((KEY1 == 0) && (CHARGER == 0))	//按键没按下，充电器没插入，关机
//	{
//		//Flag.Power = 3;	//上电后按键没按下，关机
//		KEY1_State = 1;
//	}
//	else
//	{
//		if((KEY1 == 1) && (CHARGER == 0))	//按键开机
//		{
//			KEY1_State = 1;
//			Flag.Key_Boot = 1;
//			Flag.Charger_Boot = 0;
//			Flag.Power = 0;
//		}
//		else if((KEY1 == 0) && (CHARGER == 1))	//充电器开机
//		{
//			Flag.Key_Boot = 0;
//			Flag.Charger_Boot = 1;
//			Flag.Power = 1;
//		}
//		else if((KEY1 == 1) && (CHARGER == 1))	//按键和充电器同时开机
//		{
//			KEY1_State = 1;
//			Flag.Key_Boot = 1;
//			Flag.Charger_Boot = 1;
//			Flag.Power = 0;
//		}
//	}
	 
	if(KEY1 == 1)	//按键开机
	{
		KEY1_State = 1;
		Flag.Key_Boot = 1;
		Flag.Charger_Boot = 0;
		Flag.Power = 0;	
	}
	else if(CHARGER == 1)	//充电器开机
	{
		User_Delay_xms(500);	//
		if((CHARGER == 1))	
		{
			Flag.Key_Boot = 0;
			Flag.Charger_Boot = 1;
			Flag.Power = 1;
		}
		else
		{
			Flag.Power = 3;	
		}
	}
	else	//按键没按下，充电器没插入
	{
//		for(i=0; i<14; i++)
//		{
//			User_Delay_xms(100);
//			if(CHARGER == 1)
//			{
//				val++;
//			}
//		}
//		
//		if(val >= 2)
//		{
//			KEY1_State = 1;
//		}
//		else
//		{
//			Flag.Power = 3;
//		}
		
		User_Delay_xms(500);
		if((CHARGER == 0) && (KEY1 == 0))
		{
			Flag.Power = 3;	
			//KEY1_State = 1;
		}
		else
		{
			KEY1_State = 1;
		}
		
	}
	
	if(Flag.Short_Circuit == 1)
	{
		Flag.Power = 3;	//短路直接关机
	}
}

/**************************************************
 * @brie  :Power_Boot_Step()
 * @note  :电源开机
 * @param :无
 * @retval:无
 **************************************************/
static void Power_Boot_Step(void)
{
	static uint8_t power_step = 0;
	
	switch(power_step)
	{
		case 0:
			Software_Counter_1ms.PWR_Boot = 0;
			power_step++;
		break;
		
		case 1:
			if(Software_Counter_1ms.PWR_Boot >= 200)
			{
				LDO_ON;
				Software_Counter_1ms.PWR_Boot = 0;
				power_step++;
			}
		break;
		
		case 2:
			if(Software_Counter_1ms.PWR_Boot >= 300)
			{
				PDSG_ON;
				PCHG_ON;
				Software_Counter_1ms.PWR_Boot = 0;
				power_step++;
			}
		break;
		
		case 3:
			if(Software_Counter_1ms.PWR_Boot >= 500)
			{
				DSG_ON;
				CHG_ON;
				PDSG_OFF;
				PCHG_OFF;
				power_step = 0;
				Flag.Power = 2;	//开机完成
			}
		break;
		
		default:
			
		break;
	}
}

/**************************************************
 * @brie  :Power_Task()
 * @note  :电源任务
 * @param :无
 * @retval:无
 **************************************************/
void Power_Task(void)
{
		
	switch(Flag.Power)
	{
		case 0:	//刚刚上电
			
		break;
		
		case 1://开机
			Power_Boot_Step();
		break;
		
		case 2://开机完成
			
		break;
		
		case 3://关机
			LED_OFF;
			LDO_OFF;
			DSG_OFF;
			CHG_OFF;
			PDSG_OFF;
			PCHG_OFF;
			CHARG_OFF;
			Flag.Key_Boot = 0;
		
			if((newBals != 0) && (Flag.Short_Circuit == 0))
			{
				LED_Flicker_Time = 1000;
				Flag.Power = 4;
				return;
			}
			
			if(Flag.Software_Reset == 0)
			{
				NVIC_SystemReset();
			}
			else 
			{
				Flag.Software_Reset = 0;
			}
			
			DVC1124_Sleep();
//			while(1);
			while(KEY1 == 1);
			User_Delay_xms(500);
			Enter_Low_Power();
		break;
		
		case 4:	//关机后继续平衡充
			if((newBals == 0) || (Flag.Short_Circuit == 1))		//平衡充结束
			{
				LED_OFF;
				
				if(Flag.Software_Reset == 0)
				{
					NVIC_SystemReset();
				}
				else 
				{
					Flag.Software_Reset = 0;
				}
			
				DVC1124_Sleep();				
				User_Delay_xms(10);
				Enter_Low_Power();
			}
		break;
		
		default:
			
		break;
	}
}

/**************************************************
 * @brie  :Charger_ON_Step()
 * @note  :充电器打开
 * @param :无
 * @retval:无
 **************************************************/
static void Charger_ON_Step(void)
{
	static uint8_t charger_step = 0;
	
	switch(charger_step)
	{
		case 0:
			Software_Counter_1ms.CHARGER_ON = 0;
			charger_step++;
		break;
		
		case 1:
			if(Software_Counter_1ms.CHARGER_ON >= 1000)
			{
				CHARG_ON;
				Flag.Charger_ON = 1;	//充电器开打完成

				charger_step = 0;
			}
		break;
		
		default:
			
		break;
	}
}

/**************************************************
 * @brie  :Charger_Task()
 * @note  :充电器任务
 * @param :无
 * @retval:无
 **************************************************/
void Charger_Task(void)
{
	if(CHARGER == 1)	//充电器插入
	{
		if(Flag.Power == 4)
		{
			LED_Flicker_Time = 500;
			Flag.Power = 1;
			//NVIC_SystemReset();
		}
		Flag.Charger_Boot = 1;
		VESC_CAN_DATA.pBMS_V_TOT->Charge_Input_Voltage.f = 84; 
	}
	else
	{
		
		Flag.Charger_Boot = 0;
		VESC_CAN_DATA.pBMS_V_TOT->Charge_Input_Voltage.f = 0; 
	}
	
	if(Flag.Charger_Boot == 0)	
	{
//		if((Flag.Key_Boot == 0) && (Flag.Power != 4))	//充电器开机的	
//		{
//			Flag.Power = 3;	//关机
//		}
//		else
//		{
//			CHARG_OFF;	//充电器拔出，不关机
//			Flag.Charger_ON = 0;
//		}
		CHARG_OFF;	//充电器拔出，不关机
		Flag.Charger_ON = 0;
	}
	else if(Flag.Power == 2)	//开机完成
	{
		if(Flag.Charger_ON == 0)
		{
			Charger_ON_Step();
		}
	}
	
}

/**************************************************
 * @brie  :Automatic_Shutdown()
 * @note  :自动关机
 * @param :无
 * @retval:无
 **************************************************/
void Automatic_Shutdown(void)
{
	//转速在±100，并且充电器没有插入，并且平衡充结束，30分钟后关机
	if(((VESC_CAN_RX_DATA.pSTATUS->Rpm < 100) && (VESC_CAN_RX_DATA.pSTATUS->Rpm > -100)) && (CHARGER == 0) && (newBals == 0))
	{
		if(Software_Counter_1ms.Power_Off >= 1800000)
		{
			Flag.Power = 3;
		}	
	}
	else
	{
		Software_Counter_1ms.Power_Off = 0;
	}
	
	if(VESC_CAN_DATA.pBMS_I->Input_Current_BMS_IC.f > 0.3f)	//放电电流大于0.3A，计数器清零
	{
		Software_Counter_1ms.Power_Off = 0;
	}	
}

	

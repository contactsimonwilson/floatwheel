#include "power_app.h"
#include "CellBalance.h"
#include "vesc_can.h"
#include "DVC1124_app.h"

/**************************************************
 * @brie  :Power_On_Detection()
 * @note  :Power on detection [�������]
 * @param :none [��]
 * @retval:none [��]
 **************************************************/
void Power_On_Detection(void)
{
//	if((KEY1 == 0) && (CHARGER == 0))	//The button is not pressed, the charger is not plugged in, and the power is turned off. [����û���£������û���룬�ػ�]
//	{
//		//Flag.Power = 3;	//After powering on, the button is not pressed and the machine shuts down. [�ϵ�󰴼�û���£��ػ�]
//		KEY1_State = 1;
//	}
//	else
//	{
//		if((KEY1 == 1) && (CHARGER == 0))	//Button to power on [��������]
//		{
//			KEY1_State = 1;
//			Flag.Key_Boot = 1;
//			Flag.Charger_Boot = 0;
//			Flag.Power = 0;
//		}
//		else if((KEY1 == 0) && (CHARGER == 1))	//Charger turned on [���������]
//		{
//			Flag.Key_Boot = 0;
//			Flag.Charger_Boot = 1;
//			Flag.Power = 1;
//		}
//		else if((KEY1 == 1) && (CHARGER == 1))	//The button and charger are turned on at the same time [�����ͳ����ͬʱ����]
//		{
//			KEY1_State = 1;
//			Flag.Key_Boot = 1;
//			Flag.Charger_Boot = 1;
//			Flag.Power = 0;
//		}
//	}
	 
	if(KEY1 == 1)	//Button to power on [��������]
	{
		KEY1_State = 1;
		Flag.Key_Boot = 1;
		Flag.Charger_Boot = 0;
		Flag.Power = 0;	
	}
	else if(CHARGER == 1)	//Charger turned on [���������]
	{
		User_Delay_xms(500);	
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
	else	//The button is not pressed and the charger is not plugged in. [����û���£������û����]
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
		Flag.Power = 3;	//Direct shutdown due to short circuit [��·ֱ�ӹػ�]
	}
}

/**************************************************
 * @brie  :Power_Boot_Step()
 * @note  :Power on [��Դ����]
 * @param :none [��]
 * @retval:none [��]
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
				Flag.Power = 2;	//Boot completed [�������]
			}
		break;
		
		default:
			
		break;
	}
}

/**************************************************
 * @brie  :Power_Task()
 * @note  :Power tasks [��Դ����]
 * @param :none [��]
 * @retval:none [��]
 **************************************************/
void Power_Task(void)
{
		
	switch(Flag.Power)
	{
		case 0:	//Just powered on [�ո��ϵ�]
			
		break;
		
		case 1://Power on [����]
			Power_Boot_Step();
		break;
		
		case 2://Boot completed [�������]
			
		break;
		
		case 3://Shut down [�ػ�]
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
		
		case 4:	//Continue balance charging after shutting down [�ػ������ƽ���]
			if((newBals == 0) || (Flag.Short_Circuit == 1))		//Balance charge ends [ƽ������]
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
 * @note  :Charger is on [�������]
 * @param :none [��]
 * @retval:none [��]
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
				Flag.Charger_ON = 1;	//The charger is turned on [������������]

				charger_step = 0;
			}
		break;
		
		default:
			
		break;
	}
}

/**************************************************
 * @brie  :Charger_Task()
 * @note  :Charger tasks [���������]
 * @param :none [��]
 * @retval:none [��]
 **************************************************/
void Charger_Task(void)
{
	if(CHARGER == 1)	//Charger plugged in [���������]
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
//		if((Flag.Key_Boot == 0) && (Flag.Power != 4))	//The charger is on [�����������]
//		{
//			Flag.Power = 3;	//Shut down [�ػ�]
//		}
//		else
//		{
//			CHARG_OFF;	//The charger is pulled out and the phone does not shut down. [������γ������ػ�]
//			Flag.Charger_ON = 0;
//		}
		CHARG_OFF;	//The charger is pulled out and the phone does not shut down. [������γ������ػ�]
		Flag.Charger_ON = 0;
	}
	else if(Flag.Power == 2)	//Boot completed [�������]
	{
		if(Flag.Charger_ON == 0)
		{
			Charger_ON_Step();
		}
	}
	
}

/**************************************************
 * @brie  :Automatic_Shutdown()
 * @note  :Automatic shutdown [�Զ��ػ�]
 * @param :none [��]
 * @retval:none [��]
 **************************************************/
void Automatic_Shutdown(void)
{
	//The rotation speed is ��100, and the charger is not plugged in, and the balance charge is completed, and it will shut down after 30 minutes. [ת���ڡ�100�����ҳ����û�в��룬����ƽ��������30���Ӻ�ػ�]
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
	
	if(VESC_CAN_DATA.pBMS_I->Input_Current_BMS_IC.f > 0.3f)	//The discharge current is greater than 0.3A and the counter is cleared. [�ŵ��������0.3A������������]
	{
		Software_Counter_1ms.Power_Off = 0;
	}	
}

	

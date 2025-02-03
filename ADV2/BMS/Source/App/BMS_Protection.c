#include "BMS_Protection.h"
#include "DVC11XX.h"
#include "flag.h"
#include "vesc_can.h"
#include "key.h"
#include "mos.h"
#include "CellBalance.h"
#include "charger.h"
#include "DVC1124_app.h"
#include "ppm.h"

/**************************************************
 * @brie  :BMS_Overvoltage_Protection()
 * @note  :Overvoltage protection [过压保护]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void BMS_Overvoltage_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0;
	
	if(g_AfeRegs.R0.bitmap.COV)		//Overvoltage protection [发生电池过压]
	{
		CHARG_OFF;					//Turn off the charger [关闭充电器]
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[3] = 9900;	//Overvoltage protection [错误代码]
		Flag.Overvoltage = 1;
		
		if(newBals == 0)	//Overvoltage protection lifting [过压保护解除]
		{
			Flag.Overvoltage = 0;
			if((CHARGER == 1) && (Flag.Charging_Overcurrent == 0)) //Overvoltage protection lifting [过压保护解除并且没有发生充电过流]
			{
				if((Flag.Overtemperature == 0) && (Flag.Lowtemperature == 0))	//Overvoltage protection is lifted and there is no charging overcurrent [没有发生过温和低温]
				{
					Flag.Charger_ON = 0;
				}
				
			}
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[3] = 0;	//Error code [错误代码]
			
			r0 = g_AfeRegs.R0.cleanflag;
			clean_flag &= ~(1<<6);
			g_AfeRegs.R0.cleanflag = clean_flag;
			
			while((!DVC11XX_WriteRegs(AFE_ADDR_R(0),1)) && (i < 10))
			{
				i++;
			}
			g_AfeRegs.R0.cleanflag = r0;
		}
	}
}

/**************************************************
 * @brie  :BMS_Undervoltage_Protection()
 * @note  :Arrears protection [欠压保护]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void BMS_Undervoltage_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0,val = 0;
	
	if(g_AfeRegs.R0.bitmap.CUV)		//Battery pressure occurs [发生电池欠压]
	{
		Flag.Undervoltage = 1;
		Flag.Cock_Head = 1; 		//Head tilted [翘头]
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[4] = 9900;	//Error code [错误代码]
		
		for(i=0;i<AFE_MAX_CELL_CNT;i++)
		{
			if(DVC_1124.Single_Voltage[i] < 3500)
			{
				val++;
			}
		}
		
		if(val == 0)	//All battery voltage is greater than 3.5V [所有电池电压均大于3.5V]
		{
			i = 0;
			
			if(Flag.Electric_Discharge_Overcurrent == 0)	//No discharge overcurrent [没有发生放电过流]
			{
				if(Flag.Lowtemperature == 1)
				{
					if(CHARGER == 1)	//Low temperature protection but charging [低温保护但是正在充电]
					{
						Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
					}
				}
				else
				{
					if(Flag.Overtemperature == 1)	
					{
						if(CHARGER == 1)	//High temperature protection but charging [高温保护但是正在充电]
						{
							Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
						}
					}
					else
					{
						Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
					}
				}				
			}
			
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[4] = 0;	//Error code [错误代码]
			
			r0 = g_AfeRegs.R0.cleanflag;
			clean_flag &= ~(1<<5);
			g_AfeRegs.R0.cleanflag = 0;
			
			while((!DVC11XX_WriteRegs(AFE_ADDR_R(0),1)) && (i < 10))
			{
				i++;
			}
			g_AfeRegs.R0.cleanflag = r0;
		}
	}
}

/**************************************************
 * @brie  :BMS_Discharge_Overcurrent_Protection()
 * @note  :Discharge overcurrent protection [放电过流保护]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void BMS_Discharge_Overcurrent_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0;
	static uint8_t lock = 0;
	
	//if(g_AfeRegs.R0.bitmap.OCD2)	//Level 2 discharge overcurrent occurs [发生2级放电过流]
	
	if(DVC_1124.Current_CC2 > 115)	//115A overcurrent [115A过流]
	{
		Flag.Electric_Discharge_Overcurrent = 1;
		Flag.Cock_Head = 1;		//Head tilted [翘头]
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[5] = 9900;	//Error code [错误代码]
		
		if(lock == 0)	//Trigger protection comes in for the first time [触发保护第一次进来]
		{
			if((VESC_CAN_RX_DATA.pSTATUS->Rpm > 100) || (VESC_CAN_RX_DATA.pSTATUS->Rpm < -100))		//Speed ??greater than ±100 [速度大于±100]
			{
				Software_Counter_1ms.Discharge_Overcurrent_Delay = 0;
			}
			else 	//Speed ??within ±100 [速度在±100以内]
			{
				Software_Counter_1ms.Discharge_Overcurrent_Delay = 0;
				lock = 1;
			}
		}
	
		if((Software_Counter_1ms.Discharge_Overcurrent_Delay >= 2000) && (lock == 1)) 	//The speed is ±100 and maintained for 2S [速度在±100并保持了2S]
		{
			lock = 0;
			
			if(Flag.Undervoltage == 0)	//No undervoltage occurred [没有发生欠压]
			{
				if(Flag.Lowtemperature == 1)
				{
					if(CHARGER == 1)	//Low temperature protection but charging [低温保护但是正在充电]
					{
						Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
					}
				}
				else
				{
					if(Flag.Overtemperature == 1)	
					{
						if(CHARGER == 1)	//High temperature protection but charging [高温保护但是正在充电]
						{
							Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
						}
					}
					else
					{
						Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
					}
				}		
			}
			
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[5] = 0;	//Error code [错误代码]
			
			r0 = g_AfeRegs.R0.cleanflag;
			clean_flag &= ~(1<<2);
			g_AfeRegs.R0.cleanflag = clean_flag;
			
			while((!DVC11XX_WriteRegs(AFE_ADDR_R(0),1)) && (i < 10))
			{
				i++;
			}
			g_AfeRegs.R0.cleanflag = r0;
		}
	}	
	else
	{
		Flag.Electric_Discharge_Overcurrent = 0;
		lock = 0;
		Software_Counter_1ms.Discharge_Overcurrent_Delay = 0;
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[5] = 0;	//Error code [错误代码]
		if(Flag.Undervoltage == 0)	//No undervoltage occurred [没有发生欠压]
		{
			if(Flag.Lowtemperature == 1)
			{
				if(CHARGER == 1)	//Low temperature protection but charging [低温保护但是正在充电]
				{
					Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
				}
			}
			else
			{
				if(Flag.Overtemperature == 1)	
				{
					if(CHARGER == 1)	//High temperature protection but charging [高温保护但是正在充电]
					{
						Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
					}
				}
				else
				{
					Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
				}
			}		
		}
	}
}

/**************************************************
 * @brie  :BMS_Charge_Overcurrent_Protection()
 * @note  :Charging overcurrent protection [充电过流保护]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void BMS_Charge_Overcurrent_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0;
	static uint8_t lock = 0;
	
	//if(g_AfeRegs.R0.bitmap.OCC2)	//Level 2 charging overcurrent occurs [发生2级充电过流]
	
	if(DVC_1124.Current_CC2 < -20)	//20A overcurrent [20A过流]
	{
		Flag.Charging_Overcurrent = 1;
		CHARG_OFF;					//Turn off charger [关闭充电器]
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[6] = 9900;	//Error code [错误代码]
		lock = 1;
		Software_Counter_1ms.Charge_Overcurrent_Delay = 0;
	}
	else if(DVC_1124.Current_CC2 > -1) //1 Amp [1A]
	{
		if(lock == 1)
		{
			if(Software_Counter_1ms.Charge_Overcurrent_Delay > 10000)
			{
				lock = 0;
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[6] = 0;	//Error code [错误代码]
				
				if((CHARGER == 1) && (Flag.Overvoltage == 0))	//The charger is plugged in and no overvoltage occurs [充电器插入并且没有发生过压]
				{
					if((Flag.Overtemperature == 0) && (Flag.Lowtemperature == 0))	//Mild and low temperatures have not occurred [没有发生过温和低温]
					{
						Flag.Charger_ON = 0;
					}
				}
				
				r0 = g_AfeRegs.R0.cleanflag;
				clean_flag &= ~(1<<1);
				g_AfeRegs.R0.cleanflag = clean_flag;
				
				while((!DVC11XX_WriteRegs(AFE_ADDR_R(0),1)) && (i < 10))
				{
					i++;
				}
				g_AfeRegs.R0.cleanflag = r0;
			}
		}
	}
}

/**************************************************
 * @brie  :BMS_Short_Circuit_Protection()
 * @note  :Short circuit protection [短路保护]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void BMS_Short_Circuit_Protection(void)
{
	if(g_AfeRegs.R0.bitmap.SCD)		//Discharge short circuit occurs [发生放电短路]
	{
		DSG_OFF;
		CHG_OFF;
		CHG_OFF;
		PDSG_OFF;
		PCHG_OFF;
		Flag.Power = 3;
		Flag.Short_Circuit = 1;
	}
}

/**************************************************
 * @brie  :BMS_Overtemperature_Protection()
 * @note  :Over temperature protection [过温保护]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void BMS_Overtemperature_Protection(void)
{
	static uint8_t lock = 0;
	
	if(lock == 0)	//No overheating occurred [没发生过温]
	{
		if( (DVC_1124.IC_Temp > 80.0f) ||
			(DVC_1124.GP3_Temp > 85.0f) ||
			(DVC_1124.GP1_Temp > 70.0f) ||
			(DVC_1124.GP4_Temp > 70.0f)
			) 
		{
			Flag.Overtemperature = 1;
			CHARG_OFF;					//Turn off charger [关闭充电器]
			Flag.Cock_Head = 1;			//Head tilted [翘头]
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[7] = 9900;	//Error code [错误代码]
			lock = 1;
		}
	}
	else	//Overheating has occurred [已经发生过温]
	{
		if( (DVC_1124.IC_Temp < 75.0f) &&
			(DVC_1124.GP3_Temp < 80.0f) &&
			(DVC_1124.GP1_Temp < 65.0f) &&
			(DVC_1124.GP4_Temp < 65.0f)
			) 
		{
			Flag.Overtemperature = 0;
			lock = 0;
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[7] = 0;	//Error code [错误代码 T9]
			
			if((Flag.Undervoltage == 0) && (Flag.Electric_Discharge_Overcurrent == 0))	//No undervoltage occurs. No discharge overcurrent occurs. [没有发生欠压 没有发生放电过流]
			{
				if(Flag.Lowtemperature == 1)
				{
					if(CHARGER == 1)	//Low temperature protection but charging [低温保护但是正在充电]
					{
						Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
					}
				}
				else
				{
					Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
				}		
			}
			
			if((CHARGER == 1) && (Flag.Overvoltage == 0) && (Flag.Charging_Overcurrent == 0))	//The charger is plugged in and no overvoltage occurs. No charging overcurrent occurs. [充电器插入并且没有发生过压 没有发生充电过流]
			{
				if((Flag.Lowtemperature == 0))	//No hypothermia occurred [没有发生低温]
				{
					Flag.Charger_ON = 0;
				}
			}
		}
	}
}

/**************************************************
 * @brie  :BMS_Low_Temperature_Protection()
 * @note  :Low temperature protection [低温保护]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void BMS_Low_Temperature_Protection(void)
{
	static uint8_t lock = 0;
	
	if(lock == 0)	//No hypothermia occurred [没发生低温]
	{
		if(CHARGER == 1)
		{
			if( (DVC_1124.GP1_Temp < -3.0f) ||
				(DVC_1124.GP4_Temp < -3.0f)		
				)
			{
				Flag.Lowtemperature = 1;
				CHARG_OFF;					//Turn off charger [关闭充电器]
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 9900;	//Error code [错误代码]
				lock = 1;
			}
		}
		else
		{
			if( (DVC_1124.GP1_Temp < -20.0f) ||
				(DVC_1124.GP4_Temp < -20.0f)		
				)
			{
				Flag.Lowtemperature = 1;
				Flag.Cock_Head = 1;			//Head tilted [翘头]
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 9900;	//Error code [错误代码]
				lock = 1;
			}
		}
	}
	else //Low temperature has occurred [已经发生低温]
	{
		if(CHARGER == 1)
		{
			if( (DVC_1124.GP1_Temp > -5.0f) ||
				(DVC_1124.GP4_Temp > -5.0f)		
				)
			{
				if((CHARGER == 1) && (Flag.Overvoltage == 0) && (Flag.Charging_Overcurrent == 0))	//The charger is plugged in and no overvoltage occurs. No charging overcurrent occurs. [充电器插入并且没有发生过压 没有发生充电过流]
				{
					if((Flag.Overtemperature == 0))	//No hypothermia occurred [没有发生低温]
					{
						Flag.Charger_ON = 0;
					}
				}
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 0;	//Error code [错误代码]
				Flag.Lowtemperature = 0;
				lock = 0;
			}
		}
		else
		{
			if( (DVC_1124.GP1_Temp > -15.0f) ||
				(DVC_1124.GP4_Temp > -15.0f)		
				)
			{
				if((Flag.Undervoltage == 0) && (Flag.Electric_Discharge_Overcurrent == 0))	//No undervoltage occurs. No discharge overcurrent occurs. [没有发生欠压 没有发生放电过流]
				{
					if(Flag.Overtemperature == 1)
					{
						if(CHARGER == 1)	//Low temperature protection but charging [低温保护但是正在充电]
						{
							Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
						}
					}
					else
					{
						Flag.Cock_Head = 0;		//Don't tilt your head [不翘头]
					}		
				}
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 0;	//Error code [错误代码]
				Flag.Lowtemperature = 0;
				lock = 0;
			}
		}
	}
}

//#define K1 -0.05f
//#define B1 1500
/**************************************************
 * @brie  :VESC_Cock_Head()
 * @note  :VESC Head tilted [VESC翘头]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void VESC_Cock_Head(void)
{
	static uint8_t lock = 0;
	if(lock == 0)
	{
		if(Flag.Cock_Head == 1)	//Need to raise your head [需要翘头]
		{
			if(VESC_CAN_RX_DATA.pSTATUS->Rpm > 0)
			{
				Set_PPM(1000);
			}
			else
			{
				Set_PPM(2000);
			}
			lock = 1;
			Software_Counter_1ms.Cock_Head = 0;
		}
	}
	else 
	{
		if(Flag.Cock_Head == 0)
		{
			lock = 0;
			Set_PPM(1500);
		}
	}
}
	
/**************************************************
 * @brie  :DVC1124_Abnormal()
 * @note  :DVC1124 Exception Handling [DVC1124异常处理]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void BMS_Protection_Task(void)
{
	BMS_Overvoltage_Protection();			//T5  Overvoltage protection 			[过压保护		T5]	
	BMS_Undervoltage_Protection();			//T6  Under voltage protection			[欠压保护		T6]
	BMS_Discharge_Overcurrent_Protection();	//T7  Discharge overcurrent protection	[放电过流保护	T7]
	BMS_Charge_Overcurrent_Protection();	//T8  Charging overcurrent protection	[充电过流保护	T8]
	BMS_Short_Circuit_Protection();			//    Short circuit protection			[短路保护		  ]
	BMS_Overtemperature_Protection();		//T9  Over temperature protection		[过温保护		T9]
	BMS_Low_Temperature_Protection();		//T10 Low temperature protection		[低温保护		T10]
	VESC_Cock_Head();
}




#include "DVC1124_app.h"

DVC1124_Type	DVC_1124;

#define  CurrentSenseResistance_mR      1            //电流采样电阻值（单位mR)

/**************************************************
 * @brie  :DVC1124_Voltage()
 * @note  :DVC1124计算电压
 * @param :无
 * @retval:无
 **************************************************/
void DVC1124_Voltage(void)
{
	//计算总电压
	DVC_1124.Voltage = (float)(DVC11XX_Calc_VBAT()/1000.0f);
	//VESC_CAN_DATA.pBMS_V_TOT->Total_Voltage.f = DVC_1124.Voltage;
	
	VESC_CAN_DATA.pBMS_V_TOT->Total_Voltage.f = 0;
	//计算单节电池电压
	for(uint8_t i = 0; i < 20; i++)
	{
		DVC_1124.Single_Voltage[i] = (uint16_t)DVC11XX_Calc_VCell(i);
		VESC_CAN_DATA.pBMS_V_CELL->BMS_Single_Voltage[i] = DVC_1124.Single_Voltage[i];
		VESC_CAN_DATA.pBMS_V_TOT->Total_Voltage.f += (float)(DVC_1124.Single_Voltage[i]/1000.0);
	}
	
	//芯片温度
	DVC_1124.IC_Temp = DVC11XX_Calc_ChipTemp();
	VESC_CAN_DATA.pBMS_HUM->Temp_IC = (int16_t)(DVC_1124.IC_Temp*100);
	//GP1温度
	DVC_1124.GP1_Temp = DVC11XX_Calc_BatTemp(GP1);
	VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[1] = (int16_t)(DVC_1124.GP1_Temp*100);
	//GP3温度
	DVC_1124.GP3_Temp = DVC11XX_Calc_BatTemp(GP3);
	VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[0] = (int16_t)(DVC_1124.GP3_Temp*100);
	//GP4温度
	DVC_1124.GP4_Temp = DVC11XX_Calc_BatTemp(GP4);
	VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[2] = (int16_t)(DVC_1124.GP4_Temp*100);
}

/**************************************************
 * @brie  :DVC1124_Task()
 * @note  :DVC1124任务
 * @param :无
 * @retval:无
 **************************************************/
void DVC1124_Task(void)
{	
	static float current_cc2_last = 0;
	
	if(Software_Counter_1ms.DVC_1124 < 20)
	{
		return;
	}
	
	Software_Counter_1ms.DVC_1124 = 0;
	
	if(DVC11XX_ReadRegs(AFE_ADDR_R(0), 2))
	{
		if(g_AfeRegs.R1.VADF)	//VADC已完成转换
		{			
			if(DVC11XX_ReadRegs(AFE_ADDR_R(7), 0x45))	//读电压
			{
				DVC1124_Voltage();
				if(DVC11XX_ReadRegs(AFE_ADDR_R(103), 3))
				{
					//CalcuVolMaxMin();	//电压最大最小值计算
					BalanceProcess();	//自动均衡处理
				}
				
			}
		}
		if(g_AfeRegs.R1.CC1F)	//CADC CC1已完成转换
		{
			if(DVC11XX_ReadRegs(AFE_ADDR_R(2), 2))	//读CC1
			{
				DVC_1124.Current_CC1 = DVC11XX_Calc_CurrentWithCC1(CurrentSenseResistance_mR);
			}
		}
		if(g_AfeRegs.R1.CC2F)	//CADC CC2已完成转换
		{
			if(DVC11XX_ReadRegs(AFE_ADDR_R(4), 3))	//读读CC2
			{
				DVC_1124.Current_CC2 = DVC11XX_Calc_CurrentWithCC2(CurrentSenseResistance_mR);
				VESC_CAN_DATA.pBMS_I->Input_Current_BMS_IC.f = DVC_1124.Current_CC2;
			}
		}
		
		if(DVC_1124.Current_CC2 != current_cc2_last)	//本次电流不等于上一次电流
		{	
			Software_Counter_1ms.DVC_1124_Res = 0;
			current_cc2_last = DVC_1124.Current_CC2;
		}
		else if(Software_Counter_1ms.DVC_1124_Res > 60000)	//本次电流等于上次电流并且维持了60S
		{
			Software_Counter_1ms.DVC_1124_Res = 0;
			DVC1124_Init();
		}
		
	}
}
	


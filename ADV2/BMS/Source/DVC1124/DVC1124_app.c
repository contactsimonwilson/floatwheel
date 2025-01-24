#include "DVC1124_app.h"

DVC1124_Type	DVC_1124;

#define  CurrentSenseResistance_mR      1            //������������ֵ����λmR)

/**************************************************
 * @brie  :DVC1124_Voltage()
 * @note  :DVC1124�����ѹ
 * @param :��
 * @retval:��
 **************************************************/
void DVC1124_Voltage(void)
{
	//�����ܵ�ѹ
	DVC_1124.Voltage = (float)(DVC11XX_Calc_VBAT()/1000.0f);
	//VESC_CAN_DATA.pBMS_V_TOT->Total_Voltage.f = DVC_1124.Voltage;
	
	VESC_CAN_DATA.pBMS_V_TOT->Total_Voltage.f = 0;
	//���㵥�ڵ�ص�ѹ
	for(uint8_t i = 0; i < 20; i++)
	{
		DVC_1124.Single_Voltage[i] = (uint16_t)DVC11XX_Calc_VCell(i);
		VESC_CAN_DATA.pBMS_V_CELL->BMS_Single_Voltage[i] = DVC_1124.Single_Voltage[i];
		VESC_CAN_DATA.pBMS_V_TOT->Total_Voltage.f += (float)(DVC_1124.Single_Voltage[i]/1000.0);
	}
	
	//оƬ�¶�
	DVC_1124.IC_Temp = DVC11XX_Calc_ChipTemp();
	VESC_CAN_DATA.pBMS_HUM->Temp_IC = (int16_t)(DVC_1124.IC_Temp*100);
	//GP1�¶�
	DVC_1124.GP1_Temp = DVC11XX_Calc_BatTemp(GP1);
	VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[1] = (int16_t)(DVC_1124.GP1_Temp*100);
	//GP3�¶�
	DVC_1124.GP3_Temp = DVC11XX_Calc_BatTemp(GP3);
	VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[0] = (int16_t)(DVC_1124.GP3_Temp*100);
	//GP4�¶�
	DVC_1124.GP4_Temp = DVC11XX_Calc_BatTemp(GP4);
	VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[2] = (int16_t)(DVC_1124.GP4_Temp*100);
}

/**************************************************
 * @brie  :DVC1124_Task()
 * @note  :DVC1124����
 * @param :��
 * @retval:��
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
		if(g_AfeRegs.R1.VADF)	//VADC�����ת��
		{			
			if(DVC11XX_ReadRegs(AFE_ADDR_R(7), 0x45))	//����ѹ
			{
				DVC1124_Voltage();
				if(DVC11XX_ReadRegs(AFE_ADDR_R(103), 3))
				{
					//CalcuVolMaxMin();	//��ѹ�����Сֵ����
					BalanceProcess();	//�Զ����⴦��
				}
				
			}
		}
		if(g_AfeRegs.R1.CC1F)	//CADC CC1�����ת��
		{
			if(DVC11XX_ReadRegs(AFE_ADDR_R(2), 2))	//��CC1
			{
				DVC_1124.Current_CC1 = DVC11XX_Calc_CurrentWithCC1(CurrentSenseResistance_mR);
			}
		}
		if(g_AfeRegs.R1.CC2F)	//CADC CC2�����ת��
		{
			if(DVC11XX_ReadRegs(AFE_ADDR_R(4), 3))	//����CC2
			{
				DVC_1124.Current_CC2 = DVC11XX_Calc_CurrentWithCC2(CurrentSenseResistance_mR);
				VESC_CAN_DATA.pBMS_I->Input_Current_BMS_IC.f = DVC_1124.Current_CC2;
			}
		}
		
		if(DVC_1124.Current_CC2 != current_cc2_last)	//���ε�����������һ�ε���
		{	
			Software_Counter_1ms.DVC_1124_Res = 0;
			current_cc2_last = DVC_1124.Current_CC2;
		}
		else if(Software_Counter_1ms.DVC_1124_Res > 60000)	//���ε��������ϴε�������ά����60S
		{
			Software_Counter_1ms.DVC_1124_Res = 0;
			DVC1124_Init();
		}
		
	}
}
	


#include "vesc_can.h"
	
CAN_BMS_V_TOT 	BMS_V_TOT = 
{
	.Total_Voltage = 0,				//�ܵ�ѹ
	.Charge_Input_Voltage = 0,		//�������ѹ
};

CAN_BMS_I		BMS_I = 
{
	.Input_Current = 0,				//�������
	.Input_Current_BMS_IC = 0,		//BMS_IC����
};


CAN_BMS_AH_WH	BMS_AH_WH = 
{
	.Ah_Counter = 0,				//��غ���ʱ
	.Wh_Counter = 0,				//���Wʱ 
};

CAN_BMS_V_CELL	BMS_V_CELL = 		
{
	.Group = 0,						//�ڼ���
	.BMS_String = 20,				//BMS����
	.BMS_Single_Voltage[0] = 0,		//���ڵ�ص�ѹ
	.BMS_Single_Voltage[1] = 0,		//���ڵ�ص�ѹ
	.BMS_Single_Voltage[2] = 0,		//���ڵ�ص�ѹ
	.BMS_Single_Voltage[3] = 0,		//���ڵ�ص�ѹ	
	.BMS_Single_Voltage[4] = 0,		//���ڵ�ص�ѹ
	.BMS_Single_Voltage[5] = 0,		//���ڵ�ص�ѹ
	.BMS_Single_Voltage[6] = 0,		//���ڵ�ص�ѹ
	.BMS_Single_Voltage[7] = 0,		//���ڵ�ص�ѹ	
	.BMS_Single_Voltage[8] = 0,		//���ڵ�ص�ѹ
	.BMS_Single_Voltage[9] = 0,		//���ڵ�ص�ѹ
	.BMS_Single_Voltage[10] = 0,	//���ڵ�ص�ѹ
	.BMS_Single_Voltage[11] = 0,	//���ڵ�ص�ѹ	
	.BMS_Single_Voltage[12] = 0,	//���ڵ�ص�ѹ
	.BMS_Single_Voltage[13] = 0,	//���ڵ�ص�ѹ
	.BMS_Single_Voltage[14] = 0,	//���ڵ�ص�ѹ
	.BMS_Single_Voltage[15] = 0,	//���ڵ�ص�ѹ	
	.BMS_Single_Voltage[16] = 0,	//���ڵ�ص�ѹ
	.BMS_Single_Voltage[17] = 0,	//���ڵ�ص�ѹ	
	.BMS_Single_Voltage[18] = 0,	//���ڵ�ص�ѹ
	.BMS_Single_Voltage[19] = 0,	//���ڵ�ص�ѹ
};

CAN_BMS_BAL		BMS_BAL = 
{
	.BMS_String = 20,				//BMS����
	.BMS_BAT.i = 0,					//���ڵ��״̬
};

CAN_BMS_TEMPS	BMS_TEMPS =
{
	.Group = 0,						//�ڼ���
	.BMS_Single_Temp[0] = 0,		//���ڵ���¶�
	.BMS_Single_Temp[1] = 0,		//���ڵ���¶�
	.BMS_Single_Temp[2] = 0,		//���ڵ���¶�
	.BMS_Single_Temp[3] = 0,		//���ڵ���¶�
	.BMS_Single_Temp[4] = 0,		//���ڵ���¶�
	.BMS_Single_Temp[5] = 0,		//���ڵ���¶�
	.BMS_Single_Temp[6] = 0,		//���ڵ���¶�
	.BMS_Single_Temp[7] = 0,		//���ڵ���¶�
	.BMS_Single_Temp[8] = 0,		//���ڵ���¶�
	.BMS_Single_Temp[9] = 0,		//���ڵ���¶�
};

CAN_BMS_HUM		BMS_HUM = 
{
	.Humidity = 0,					//ʪ��	0-10000(0%-100%);
	.Temp_Hum_Sensor = 0,			//�¶�	-10000-10000(-100��-100��)
	.Temp_IC = 0,					//IC�¶�
};

CAN_BMS_SOC_SOH_TEMP_STAT	BMS_SOC_SOH_TEMP_STAT = 
{
	.V_Cell_Min = 0,				//���ڵ����͵�ѹ ����1000������
	.V_Cell_Max = 0,				//���ڵ����ߵ�ѹ ����1000������
	.Soc = 0,						//0-255(0%-100%)
	.Soh = 0,						//0-255(0%-100%)
	.T_Cell_Max = 0,				//���ڵ������¶�
	.Stat = 0,						//
};

CAN_BMS_AH_WH_CHG_TOTAL		BMS_AH_WH_CHG_TOTAL =
{
	.Ah_Charge_Total = 0,			//��ʱ
	.Wh_Charge_Total = 0,			//��ʱ
};

CAN_BMS_AH_WH_DIS_TOTAL		BMS_AH_WH_DIS_TOTAL =
{
	.Ah_Discharge_Total = 0,		//��ʱ
	.Wh_Discharge_Total = 0,		//��ʱ
};	

VESC_CAN_TYPE VESC_CAN_DATA = 
{
	.pBMS_V_TOT 	= &BMS_V_TOT,
	.pBMS_I 		= &BMS_I,
	.pBMS_AH_WH		= &BMS_AH_WH,
	.pBMS_V_CELL	= &BMS_V_CELL,
	.pBMS_BAL		= &BMS_BAL,
	.pBMS_TEMPS     = &BMS_TEMPS,
	.pBMS_HUM		= &BMS_HUM,
	.pBMS_SOC_SOH_TEMP_STAT	= &BMS_SOC_SOH_TEMP_STAT,
	.pBMS_AH_WH_CHG_TOTAL 	= &BMS_AH_WH_CHG_TOTAL,
	.pBMS_AH_WH_DIS_TOTAL	= &BMS_AH_WH_DIS_TOTAL,
};

/**************************************************
 * @brie  :VESC_Set_BMS_V_TOT()
 * @note  :�����ܵ�ѹ 	�������ѹ
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_V_TOT(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_V_TOT;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 8;
	can_tx_struct->Data[0] = vesc_can_data->pBMS_V_TOT->Total_Voltage.i[3];
	can_tx_struct->Data[1] = vesc_can_data->pBMS_V_TOT->Total_Voltage.i[2];
	can_tx_struct->Data[2] = vesc_can_data->pBMS_V_TOT->Total_Voltage.i[1];
	can_tx_struct->Data[3] = vesc_can_data->pBMS_V_TOT->Total_Voltage.i[0];
	can_tx_struct->Data[4] = vesc_can_data->pBMS_V_TOT->Charge_Input_Voltage.i[3];
	can_tx_struct->Data[5] = vesc_can_data->pBMS_V_TOT->Charge_Input_Voltage.i[2];
	can_tx_struct->Data[6] = vesc_can_data->pBMS_V_TOT->Charge_Input_Voltage.i[1];
	can_tx_struct->Data[7] = vesc_can_data->pBMS_V_TOT->Charge_Input_Voltage.i[0];
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}
	
/**************************************************
 * @brie  :VESC_Set_BMS_I()
 * @note  :����������� 	BMS_IC����
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_I(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_I;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 8;
	can_tx_struct->Data[0] = vesc_can_data->pBMS_I->Input_Current.i[3];
	can_tx_struct->Data[1] = vesc_can_data->pBMS_I->Input_Current.i[2];
	can_tx_struct->Data[2] = vesc_can_data->pBMS_I->Input_Current.i[1];
	can_tx_struct->Data[3] = vesc_can_data->pBMS_I->Input_Current.i[0];
	can_tx_struct->Data[4] = vesc_can_data->pBMS_I->Input_Current_BMS_IC.i[3];
	can_tx_struct->Data[5] = vesc_can_data->pBMS_I->Input_Current_BMS_IC.i[2];
	can_tx_struct->Data[6] = vesc_can_data->pBMS_I->Input_Current_BMS_IC.i[1];
	can_tx_struct->Data[7] = vesc_can_data->pBMS_I->Input_Current_BMS_IC.i[0];
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}

/**************************************************
 * @brie  :VESC_Set_BMS_AH_WH()
 * @note  :���õ�غ���ʱ 	���Wʱ 
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_AH_WH(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_AH_WH;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 8;
	can_tx_struct->Data[0] = vesc_can_data->pBMS_AH_WH->Ah_Counter.i[3];
	can_tx_struct->Data[1] = vesc_can_data->pBMS_AH_WH->Ah_Counter.i[2];
	can_tx_struct->Data[2] = vesc_can_data->pBMS_AH_WH->Ah_Counter.i[1];
	can_tx_struct->Data[3] = vesc_can_data->pBMS_AH_WH->Ah_Counter.i[0];
	can_tx_struct->Data[4] = vesc_can_data->pBMS_AH_WH->Wh_Counter.i[3];
	can_tx_struct->Data[5] = vesc_can_data->pBMS_AH_WH->Wh_Counter.i[2];
	can_tx_struct->Data[6] = vesc_can_data->pBMS_AH_WH->Wh_Counter.i[1];
	can_tx_struct->Data[7] = vesc_can_data->pBMS_AH_WH->Wh_Counter.i[0];
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}

/**************************************************
 * @brie  :VESC_Set_BMS_V_CELL()
 * @note  :���õ��ڵ�ص�ѹ 
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_V_CELL(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_V_CELL;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 8;
	can_tx_struct->Data[0] = vesc_can_data->pBMS_V_CELL->Group;
	can_tx_struct->Data[1] = vesc_can_data->pBMS_V_CELL->BMS_String;
	can_tx_struct->Data[2] = (vesc_can_data->pBMS_V_CELL->BMS_Single_Voltage[vesc_can_data->pBMS_V_CELL->Group])>>8;
	can_tx_struct->Data[3] =  vesc_can_data->pBMS_V_CELL->BMS_Single_Voltage[vesc_can_data->pBMS_V_CELL->Group];
	can_tx_struct->Data[4] = (vesc_can_data->pBMS_V_CELL->BMS_Single_Voltage[vesc_can_data->pBMS_V_CELL->Group+1])>>8;
	can_tx_struct->Data[5] =  vesc_can_data->pBMS_V_CELL->BMS_Single_Voltage[vesc_can_data->pBMS_V_CELL->Group+1];
	if(vesc_can_data->pBMS_V_CELL->Group < 18)
	{
		can_tx_struct->Data[6] = (vesc_can_data->pBMS_V_CELL->BMS_Single_Voltage[vesc_can_data->pBMS_V_CELL->Group+2])>>8;
		can_tx_struct->Data[7] =  vesc_can_data->pBMS_V_CELL->BMS_Single_Voltage[vesc_can_data->pBMS_V_CELL->Group+2];
	}
	else
	{
		can_tx_struct->Data[6] = 0;
		can_tx_struct->Data[7] = 0;
	}
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}

/**************************************************
 * @brie  :VESC_Set_BMS_BAL()
 * @note  :���õ��ڵ��״̬ 
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_BAL(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_BAL;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 8;
	can_tx_struct->Data[0] = vesc_can_data->pBMS_BAL->BMS_String;
	can_tx_struct->Data[1] = 0;
	can_tx_struct->Data[2] = 0;
	can_tx_struct->Data[3] = 0;
	can_tx_struct->Data[4] = (vesc_can_data->pBMS_BAL->BMS_BAT.i)>>24;
	can_tx_struct->Data[5] = (vesc_can_data->pBMS_BAL->BMS_BAT.i)>>16;
	can_tx_struct->Data[6] = (vesc_can_data->pBMS_BAL->BMS_BAT.i)>>8;
	can_tx_struct->Data[7] =  vesc_can_data->pBMS_BAL->BMS_BAT.i;
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}

/**************************************************
 * @brie  :VESC_Set_BMS_TEMPS()
 * @note  :�����¶� 
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_TEMPS(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_TEMPS;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 8;
	can_tx_struct->Data[0] = vesc_can_data->pBMS_TEMPS->Group;
	can_tx_struct->Data[1] = 24;
	can_tx_struct->Data[2] = (vesc_can_data->pBMS_TEMPS->BMS_Single_Temp[vesc_can_data->pBMS_TEMPS->Group])>>8;
	can_tx_struct->Data[3] =  vesc_can_data->pBMS_TEMPS->BMS_Single_Temp[vesc_can_data->pBMS_TEMPS->Group];
	if(vesc_can_data->pBMS_TEMPS->Group < 9)
	{
		can_tx_struct->Data[4] = (vesc_can_data->pBMS_TEMPS->BMS_Single_Temp[vesc_can_data->pBMS_TEMPS->Group+1])>>8;
		can_tx_struct->Data[5] =  vesc_can_data->pBMS_TEMPS->BMS_Single_Temp[vesc_can_data->pBMS_TEMPS->Group+1];
		can_tx_struct->Data[6] = (vesc_can_data->pBMS_TEMPS->BMS_Single_Temp[vesc_can_data->pBMS_TEMPS->Group+2])>>8;
		can_tx_struct->Data[7] =  vesc_can_data->pBMS_TEMPS->BMS_Single_Temp[vesc_can_data->pBMS_TEMPS->Group+2];
	}
	else
	{
		can_tx_struct->Data[4] = 0;
		can_tx_struct->Data[5] = 0;
		can_tx_struct->Data[6] = 0;
		can_tx_struct->Data[7] = 0;
	}
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}

/**************************************************
 * @brie  :VESC_Set_BMS_HUM()
 * @note  :����ʪ�� �¶� IC�¶�  
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_HUM(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_HUM;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 6;
	can_tx_struct->Data[0] = (vesc_can_data->pBMS_HUM->Temp_Hum_Sensor)>>8;
	can_tx_struct->Data[1] =  vesc_can_data->pBMS_HUM->Temp_Hum_Sensor;
	can_tx_struct->Data[2] = (vesc_can_data->pBMS_HUM->Humidity)>>8;
	can_tx_struct->Data[3] =  vesc_can_data->pBMS_HUM->Humidity;
	can_tx_struct->Data[4] = (vesc_can_data->pBMS_HUM->Temp_IC)>>8;;
	can_tx_struct->Data[5] =  vesc_can_data->pBMS_HUM->Temp_IC;;
	can_tx_struct->Data[6] = 0x00;
	can_tx_struct->Data[7] = 0x00;
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}

/**************************************************
 * @brie  :VESC_Set_BMS_SOC_SOH_TEMP_STAT()
 * @note  :���õ��ڵ����͵�ѹ
 *			   ���ڵ����ߵ�ѹ
 *			    Soc
 *				Soh
 *			   ���ڵ������¶�
 *			   ״̬
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_SOC_SOH_TEMP_STAT(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_SOC_SOH_TEMP_STAT;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 8;
	can_tx_struct->Data[0] = (vesc_can_data->pBMS_SOC_SOH_TEMP_STAT->V_Cell_Min)>>8;
	can_tx_struct->Data[1] =  vesc_can_data->pBMS_SOC_SOH_TEMP_STAT->V_Cell_Min;
	can_tx_struct->Data[2] = (vesc_can_data->pBMS_SOC_SOH_TEMP_STAT->V_Cell_Max)>>8;
	can_tx_struct->Data[3] =  vesc_can_data->pBMS_SOC_SOH_TEMP_STAT->V_Cell_Max;
	can_tx_struct->Data[4] =  vesc_can_data->pBMS_SOC_SOH_TEMP_STAT->Soc;
	can_tx_struct->Data[5] =  vesc_can_data->pBMS_SOC_SOH_TEMP_STAT->Soh;
	can_tx_struct->Data[6] =  vesc_can_data->pBMS_SOC_SOH_TEMP_STAT->T_Cell_Max;
	can_tx_struct->Data[7] =  vesc_can_data->pBMS_SOC_SOH_TEMP_STAT->Stat;
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}

/**************************************************
 * @brie  :VESC_Set_BMS_AH_WH_CHG_TOTAL()
 * @note  :���ó�簲ʱ 	�����ʱ
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_AH_WH_CHG_TOTAL(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_AH_WH_CHG_TOTAL;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 8;
	can_tx_struct->Data[0] = vesc_can_data->pBMS_AH_WH_CHG_TOTAL->Ah_Charge_Total.i[3];
	can_tx_struct->Data[1] = vesc_can_data->pBMS_AH_WH_CHG_TOTAL->Ah_Charge_Total.i[2];
	can_tx_struct->Data[2] = vesc_can_data->pBMS_AH_WH_CHG_TOTAL->Ah_Charge_Total.i[1];
	can_tx_struct->Data[3] = vesc_can_data->pBMS_AH_WH_CHG_TOTAL->Ah_Charge_Total.i[0];
	can_tx_struct->Data[4] = vesc_can_data->pBMS_AH_WH_CHG_TOTAL->Wh_Charge_Total.i[3];
	can_tx_struct->Data[5] = vesc_can_data->pBMS_AH_WH_CHG_TOTAL->Wh_Charge_Total.i[2];
	can_tx_struct->Data[6] = vesc_can_data->pBMS_AH_WH_CHG_TOTAL->Wh_Charge_Total.i[1];
	can_tx_struct->Data[7] = vesc_can_data->pBMS_AH_WH_CHG_TOTAL->Wh_Charge_Total.i[0];
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}

/**************************************************
 * @brie  :VESC_Set_BMS_AH_WH_DIS_TOTAL()
 * @note  :���ð�ʱ ��ʱ
 * @param :can_tx_struct	CAN���ͽṹ��
 *		   vesc_can_data	VESC_CAN_TYPE
 * @retval:��
 **************************************************/
void VESC_Set_BMS_AH_WH_DIS_TOTAL(CanTxMessage *can_tx_struct,VESC_CAN_TYPE *vesc_can_data)
{
	uint32_t can_id;
	
	vesc_can_data->VESC_CAN_CMD = CAN_PACKET_BMS_AH_WH_DIS_TOTAL;
	
	can_id = (0x000000FF |(vesc_can_data->VESC_CAN_CMD<<8));
	
	can_tx_struct->StdId = 0;
	can_tx_struct->ExtId = can_id;
	can_tx_struct->IDE = CAN_ID_EXT;
	can_tx_struct->RTR = CAN_RTRQ_DATA;
	can_tx_struct->DLC = 8;
	can_tx_struct->Data[0] = vesc_can_data->pBMS_AH_WH_DIS_TOTAL->Ah_Discharge_Total.i[3];
	can_tx_struct->Data[1] = vesc_can_data->pBMS_AH_WH_DIS_TOTAL->Ah_Discharge_Total.i[2];
	can_tx_struct->Data[2] = vesc_can_data->pBMS_AH_WH_DIS_TOTAL->Ah_Discharge_Total.i[1];
	can_tx_struct->Data[3] = vesc_can_data->pBMS_AH_WH_DIS_TOTAL->Ah_Discharge_Total.i[0];
	can_tx_struct->Data[4] = vesc_can_data->pBMS_AH_WH_DIS_TOTAL->Wh_Discharge_Total.i[3];
	can_tx_struct->Data[5] = vesc_can_data->pBMS_AH_WH_DIS_TOTAL->Wh_Discharge_Total.i[2];
	can_tx_struct->Data[6] = vesc_can_data->pBMS_AH_WH_DIS_TOTAL->Wh_Discharge_Total.i[1];
	can_tx_struct->Data[7] = vesc_can_data->pBMS_AH_WH_DIS_TOTAL->Wh_Discharge_Total.i[0];
	
	CAN_TransmitMessage(CAN,can_tx_struct);
}

CAN_STATUS STATUS = 
{
	.Rpm = 0,			//ת��
	.Duty_Cycle = 0,	//ռ�ձ�
	.Total_Current = 0,	//�ܵ���
};

CAN_STATUS_2 STATUS_2 = 
{
	.Amp_Hours_Charged = 0,	//���İ�ʱ
	.Amp_Hours = 0,			//���ĵİ�ʱ
};

CAN_STATUS_3 STATUS_3 = 
{
	.Watt_Hours_Charged = 0,	//������ʱ
	.Watt_Hours = 0,			//���ĵ���ʱ
};

CAN_STATUS_4 STATUS_4 = 
{
	.PID_Pos = 0,				//�������������
	.Total_Input_Current = 0,	//�����ܵ���
	.Motor_Temp = 0,			//����¶�
	.MOSFET_Temp = 0,			//MOS���¶�
};

CAN_STATUS_5 STATUS_5 = 
{
	.Input_Voltage = 0,		//�����ѹ
	.Tachometer_Value = 0,	//ת�ٱ�?��ȷ��
};

VESC_CAN_RX_TYPE VESC_CAN_RX_DATA = 
{
	.pSTATUS = &STATUS,
	.pSTATUS_2 = &STATUS_2,
	.pSTATUS_3 = &STATUS_3,
	.pSTATUS_4 = &STATUS_4,
	.pSTATUS_5 = &STATUS_5,
};

void VESC_CAN_RX_Inte(CanRxMessage *can_rx_struct,VESC_CAN_RX_TYPE *vesc_can_rx_data)
{
	uint16_t vesc_can_cmd;
	uint8_t  *pdata =  can_rx_struct->Data;
	
	vesc_can_cmd = can_rx_struct->ExtId>>8;
	
	switch(vesc_can_cmd)
	{
		case CAN_PACKET_STATUS:
			vesc_can_rx_data->pSTATUS->Duty_Cycle 		= (float)((int16_t)(pdata[7]|(pdata[6]<<8)))/1000;
			vesc_can_rx_data->pSTATUS->Total_Current 	= (float)((int16_t)(pdata[5]|(pdata[4]<<8)))/10;
			vesc_can_rx_data->pSTATUS->Rpm 				= (int32_t)(pdata[3]|(pdata[2]<<8)|(pdata[1]<<16)|(pdata[0]<<24));
		break;
		
		case CAN_PACKET_STATUS_2:
			vesc_can_rx_data->pSTATUS_2->Amp_Hours_Charged	= (float)((int32_t)(pdata[7]|(pdata[6]<<8)|(pdata[5]<<16)|(pdata[4]<<24)))/10000;
			vesc_can_rx_data->pSTATUS_2->Amp_Hours 			= (float)((int32_t)(pdata[3]|(pdata[2]<<8)|(pdata[1]<<16)|(pdata[0]<<24)))/10000;
		break;
		
		case CAN_PACKET_STATUS_3:
			vesc_can_rx_data->pSTATUS_3->Watt_Hours_Charged = (float)((int32_t)(pdata[7]|(pdata[6]<<8)|(pdata[5]<<16)|(pdata[4]<<24)))/10000;
			vesc_can_rx_data->pSTATUS_3->Watt_Hours 		= (float)((int32_t)(pdata[3]|(pdata[2]<<8)|(pdata[1]<<16)|(pdata[0]<<24)))/10000;
		break;
		
		case CAN_PACKET_STATUS_4:
			vesc_can_rx_data->pSTATUS_4->PID_Pos 				= (float)((int16_t)(pdata[7]|(pdata[6]<<8)))/50;
			vesc_can_rx_data->pSTATUS_4->Total_Input_Current 	= (float)((int16_t)(pdata[5]|(pdata[4]<<8)))/10;
			vesc_can_rx_data->pSTATUS_4->Motor_Temp 			= (float)((int16_t)(pdata[3]|(pdata[2]<<8)))/10;
			vesc_can_rx_data->pSTATUS_4->MOSFET_Temp 			= (float)((int16_t)(pdata[1]|(pdata[0]<<8)))/10;
		break;
		
		case CAN_PACKET_STATUS_5:
			vesc_can_rx_data->pSTATUS_5->Input_Voltage 		= (float)((int16_t)(pdata[5]|(pdata[4]<<8)))/10;
			vesc_can_rx_data->pSTATUS_5->Tachometer_Value 	= (int32_t)(pdata[3]|(pdata[2]<<8)|(pdata[1]<<16)|(pdata[0]<<24));
		break;
		
		default:
			
		break;
		
	}
}

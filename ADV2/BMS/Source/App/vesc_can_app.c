#include "vesc_can_app.h"

/*
	CAN_TX_Config.StdId 	//Standard frame ID [标准帧ID]
	CAN_TX_Config.ExtId		//Extended frame ID [扩展帧ID]
	CAN_TX_Config.IDE		//Extended frame or standard frame [扩展帧还是标准帧]
	CAN_TX_Config.RTR		//Remote frame or data frame [远程帧还是数据帧]
	CAN_TX_Config.DLC		//Data length 0-8 [数据长度0-8]
	CAN_TX_Config.Data[8]	//Data sent: A maximum of 8 bytes can be sent in one frame of the CAN bus. [发送的数据 CAN总线一帧报文最多发8个字节]
*/
CanTxMessage CAN_TX_Config;

/**************************************************
 * @brie  :VESC_CAN_Task()
 * @note  :VESC_CAN Task [VESC_CAN任务]
 * @param :none [无]
 * @retval:none [无]
 **************************************************/
void VESC_CAN_Task(void)
{
	static uint8_t vesc_can_send_step = 0;
		
	if((Software_Counter_1ms.VESC_CAN < 50) || (Flag.Power != 2))
	{
		return;
	}
	Software_Counter_1ms.VESC_CAN = 0;
	//VESC_CAN_DATA.pBMS_I->Input_Current.f += 0.001f;
	switch(vesc_can_send_step)
	{
		case 0:	//Send total voltage [发送总电压]
			VESC_Set_BMS_V_TOT(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
			
		case 1:	//Send battery voltage 1-2-3 [发送电池电压 1-2-3]
			VESC_CAN_DATA.pBMS_V_CELL->Group = 0;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 2:	//Send battery voltage 4-5-6 [发送电池电压 4-5-6]
			VESC_CAN_DATA.pBMS_V_CELL->Group = 3;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 3: //Send battery voltage 7-8-9 [发送电池电压 7-8-9]
			VESC_CAN_DATA.pBMS_V_CELL->Group = 6;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 4: //Send battery voltage 10-11-12 [发送电池电压 10-11-12]
			VESC_CAN_DATA.pBMS_V_CELL->Group = 9;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 5: //Send battery voltage 13-14-15 [发送电池电压 13-14-15]
			VESC_CAN_DATA.pBMS_V_CELL->Group = 12;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 6: //Send battery voltage 16-17-18 [发送电池电压 16-17-18]
			VESC_CAN_DATA.pBMS_V_CELL->Group = 15;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 7: //Send battery voltage 19-20 [发送电池电压 19-20]
			VESC_CAN_DATA.pBMS_V_CELL->Group = 18;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 8: //Send battery voltage status [发送电池电压状态]
			VESC_Set_BMS_BAL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 9: //Send battery current [发送电池电流]
			VESC_Set_BMS_I(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 10: //Send IC temperature [发送IC温度]
			VESC_Set_BMS_HUM(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 11: //Send NTC temperature [发送NTC温度]
			VESC_CAN_DATA.pBMS_TEMPS->Group = 0;
			VESC_Set_BMS_TEMPS(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 12: //Send current [发送电流]
			VESC_Set_BMS_I(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 13: //Send error code [发送错误代码]
			VESC_CAN_DATA.pBMS_TEMPS->Group = 3;
			VESC_Set_BMS_TEMPS(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 14: //Send error code [发送错误代码]
			VESC_CAN_DATA.pBMS_TEMPS->Group = 6;
			VESC_Set_BMS_TEMPS(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step = 0;
		break;
		
		default:
			vesc_can_send_step = 0;
		break;
		
	}
	
}


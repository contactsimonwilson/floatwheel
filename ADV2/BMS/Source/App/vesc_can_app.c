#include "vesc_can_app.h"

/*
	CAN_TX_Config.StdId 	//��׼֡ID
	CAN_TX_Config.ExtId		//��չ֡ID
	CAN_TX_Config.IDE		//��չ֡���Ǳ�׼֡
	CAN_TX_Config.RTR		//Զ��֡��������֡
	CAN_TX_Config.DLC		//���ݳ���0-8
	CAN_TX_Config.Data[8]	//���͵����� CAN����һ֡������෢8���ֽ�
*/
CanTxMessage CAN_TX_Config;

/**************************************************
 * @brie  :VESC_CAN_Task()
 * @note  :VESC_CAN����
 * @param :��
 * @retval:��
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
		case 0:	//�����ܵ�ѹ
			VESC_Set_BMS_V_TOT(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
			
		case 1:	//���͵�ص�ѹ 1-2-3
			VESC_CAN_DATA.pBMS_V_CELL->Group = 0;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 2:	//���͵�ص�ѹ 4-5-6
			VESC_CAN_DATA.pBMS_V_CELL->Group = 3;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 3: //���͵�ص�ѹ 7-8-9
			VESC_CAN_DATA.pBMS_V_CELL->Group = 6;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 4://���͵�ص�ѹ 10-11-12
			VESC_CAN_DATA.pBMS_V_CELL->Group = 9;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 5://���͵�ص�ѹ 13-14-15
			VESC_CAN_DATA.pBMS_V_CELL->Group = 12;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 6://���͵�ص�ѹ 16-17-18
			VESC_CAN_DATA.pBMS_V_CELL->Group = 15;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 7://���͵�ص�ѹ 19-20
			VESC_CAN_DATA.pBMS_V_CELL->Group = 18;
			VESC_Set_BMS_V_CELL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 8://���͵�ص�ѹ״̬
			VESC_Set_BMS_BAL(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 9://���͵�ص���
			VESC_Set_BMS_I(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 10://����IC�¶�
			VESC_Set_BMS_HUM(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 11://����NTC�¶�
			VESC_CAN_DATA.pBMS_TEMPS->Group = 0;
			VESC_Set_BMS_TEMPS(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 12://���͵���
			VESC_Set_BMS_I(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 13://���ʹ������
			VESC_CAN_DATA.pBMS_TEMPS->Group = 3;
			VESC_Set_BMS_TEMPS(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step++;
		break;
		
		case 14://���ʹ������
			VESC_CAN_DATA.pBMS_TEMPS->Group = 6;
			VESC_Set_BMS_TEMPS(&CAN_TX_Config,&VESC_CAN_DATA);
			vesc_can_send_step = 0;
		break;
		
		default:
			vesc_can_send_step = 0;
		break;
		
	}
	
}


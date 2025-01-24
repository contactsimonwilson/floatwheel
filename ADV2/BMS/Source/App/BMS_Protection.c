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
 * @note  :��ѹ����
 * @param :��
 * @retval:��
 **************************************************/
void BMS_Overvoltage_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0;
	
	if(g_AfeRegs.R0.bitmap.COV)		//������ع�ѹ
	{
		CHARG_OFF;					//�رճ����
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[3] = 9900;	//�������
		Flag.Overvoltage = 1;
		
		if(newBals == 0)	//��ѹ�������
		{
			Flag.Overvoltage = 0;
			if((CHARGER == 1) && (Flag.Charging_Overcurrent == 0)) //��ѹ�����������û�з���������
			{
				if((Flag.Overtemperature == 0) && (Flag.Lowtemperature == 0))	//û�з������º͵���
				{
					Flag.Charger_ON = 0;
				}
				
			}
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[3] = 0;	//�������
			
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
 * @note  :Ƿѹ����
 * @param :��
 * @retval:��
 **************************************************/
void BMS_Undervoltage_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0,val = 0;
	
	if(g_AfeRegs.R0.bitmap.CUV)		//�������Ƿѹ
	{
		Flag.Undervoltage = 1;
		Flag.Cock_Head = 1;//��ͷ
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[4] = 9900;	//�������
		
		for(i=0;i<AFE_MAX_CELL_CNT;i++)
		{
			if(DVC_1124.Single_Voltage[i] < 3500)
			{
				val++;
			}
		}
		
		if(val == 0)	//���е�ص�ѹ������3.5V
		{
			i = 0;
			
			if(Flag.Electric_Discharge_Overcurrent == 0)	//û�з����ŵ����
			{
				if(Flag.Lowtemperature == 1)
				{
					if(CHARGER == 1)	//���±����������ڳ��
					{
						Flag.Cock_Head = 0;//����ͷ
					}
				}
				else
				{
					if(Flag.Overtemperature == 1)	
					{
						if(CHARGER == 1)	//���±����������ڳ��
						{
							Flag.Cock_Head = 0;//����ͷ
						}
					}
					else
					{
						Flag.Cock_Head = 0;//����ͷ
					}
				}				
			}
			
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[4] = 0;	//�������
			
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
 * @note  :�ŵ��������
 * @param :��
 * @retval:��
 **************************************************/
void BMS_Discharge_Overcurrent_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0;
	static uint8_t lock = 0;
	
	//if(g_AfeRegs.R0.bitmap.OCD2)	//����2���ŵ����
	
	if(DVC_1124.Current_CC2 > 115)	//115A����
	{
		Flag.Electric_Discharge_Overcurrent = 1;
		Flag.Cock_Head = 1;//��ͷ
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[5] = 9900;	//�������
		
		if(lock == 0)	//����������һ�ν���
		{
			if((VESC_CAN_RX_DATA.pSTATUS->Rpm > 100) || (VESC_CAN_RX_DATA.pSTATUS->Rpm < -100))	//�ٶȴ��ڡ�100
			{
				Software_Counter_1ms.Discharge_Overcurrent_Delay = 0;
			}
			else //�ٶ��ڡ�100����
			{
				Software_Counter_1ms.Discharge_Overcurrent_Delay = 0;
				lock = 1;
			}
		}
	
		if((Software_Counter_1ms.Discharge_Overcurrent_Delay >= 2000) && (lock == 1)) //�ٶ��ڡ�100��������2S
		{
			lock = 0;
			
			if(Flag.Undervoltage == 0)	//û�з���Ƿѹ
			{
				if(Flag.Lowtemperature == 1)
				{
					if(CHARGER == 1)	//���±����������ڳ��
					{
						Flag.Cock_Head = 0;//����ͷ
					}
				}
				else
				{
					if(Flag.Overtemperature == 1)	
					{
						if(CHARGER == 1)	//���±����������ڳ��
						{
							Flag.Cock_Head = 0;//����ͷ
						}
					}
					else
					{
						Flag.Cock_Head = 0;//����ͷ
					}
				}		
			}
			
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[5] = 0;	//�������
			
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
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[5] = 0;	//�������
		if(Flag.Undervoltage == 0)	//û�з���Ƿѹ
		{
			if(Flag.Lowtemperature == 1)
			{
				if(CHARGER == 1)	//���±����������ڳ��
				{
					Flag.Cock_Head = 0;//����ͷ
				}
			}
			else
			{
				if(Flag.Overtemperature == 1)	
				{
					if(CHARGER == 1)	//���±����������ڳ��
					{
						Flag.Cock_Head = 0;//����ͷ
					}
				}
				else
				{
					Flag.Cock_Head = 0;//����ͷ
				}
			}		
		}
	}
}

/**************************************************
 * @brie  :BMS_Charge_Overcurrent_Protection()
 * @note  :����������
 * @param :��
 * @retval:��
 **************************************************/
void BMS_Charge_Overcurrent_Protection(void)
{
	uint8_t clean_flag = 0xFF,r0;
	uint8_t i = 0;
	static uint8_t lock = 0;
	
	//if(g_AfeRegs.R0.bitmap.OCC2)	//����2��������
	
	if(DVC_1124.Current_CC2 < -20)	//20A����
	{
		Flag.Charging_Overcurrent = 1;
		CHARG_OFF;					//�رճ����
		VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[6] = 9900;	//�������
		lock = 1;
		Software_Counter_1ms.Charge_Overcurrent_Delay = 0;
	}
	else if(DVC_1124.Current_CC2 > -1) //1A
	{
		if(lock == 1)
		{
			if(Software_Counter_1ms.Charge_Overcurrent_Delay > 10000)
			{
				lock = 0;
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[6] = 0;	//�������
				
				if((CHARGER == 1) && (Flag.Overvoltage == 0))	//��������벢��û�з�����ѹ
				{
					if((Flag.Overtemperature == 0) && (Flag.Lowtemperature == 0))	//û�з������º͵���
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
 * @note  :��·����
 * @param :��
 * @retval:��
 **************************************************/
void BMS_Short_Circuit_Protection(void)
{
	if(g_AfeRegs.R0.bitmap.SCD)		//�����ŵ��·
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
 * @note  :���±���
 * @param :��
 * @retval:��
 **************************************************/
void BMS_Overtemperature_Protection(void)
{
	static uint8_t lock = 0;
	
	if(lock == 0)	//û��������
	{
		if( (DVC_1124.IC_Temp > 80.0f) ||
			(DVC_1124.GP3_Temp > 85.0f) ||
			(DVC_1124.GP1_Temp > 70.0f) ||
			(DVC_1124.GP4_Temp > 70.0f)
			) 
		{
			Flag.Overtemperature = 1;
			CHARG_OFF;					//�رճ����
			Flag.Cock_Head = 1;			//��ͷ
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[7] = 9900;	//�������
			lock = 1;
		}
	}
	else	//�Ѿ���������
	{
		if( (DVC_1124.IC_Temp < 75.0f) &&
			(DVC_1124.GP3_Temp < 80.0f) &&
			(DVC_1124.GP1_Temp < 65.0f) &&
			(DVC_1124.GP4_Temp < 65.0f)
			) 
		{
			Flag.Overtemperature = 0;
			lock = 0;
			VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[7] = 0;	//������� T9
			
			if((Flag.Undervoltage == 0) && (Flag.Electric_Discharge_Overcurrent == 0))	//û�з���Ƿѹ û�з����ŵ����
			{
				if(Flag.Lowtemperature == 1)
				{
					if(CHARGER == 1)	//���±����������ڳ��
					{
						Flag.Cock_Head = 0;//����ͷ
					}
				}
				else
				{
					Flag.Cock_Head = 0;//����ͷ
				}		
			}
			
			if((CHARGER == 1) && (Flag.Overvoltage == 0) && (Flag.Charging_Overcurrent == 0))	//��������벢��û�з�����ѹ û�з���������
			{
				if((Flag.Lowtemperature == 0))	//û�з�������
				{
					Flag.Charger_ON = 0;
				}
			}
		}
	}
}

/**************************************************
 * @brie  :BMS_Low_Temperature_Protection()
 * @note  :���±���
 * @param :��
 * @retval:��
 **************************************************/
void BMS_Low_Temperature_Protection(void)
{
	static uint8_t lock = 0;
	
	if(lock == 0)	//û��������
	{
		if(CHARGER == 1)
		{
			if( (DVC_1124.GP1_Temp < -3.0f) ||
				(DVC_1124.GP4_Temp < -3.0f)		
				)
			{
				Flag.Lowtemperature = 1;
				CHARG_OFF;					//�رճ����
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 9900;	//�������
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
				Flag.Cock_Head = 1;			//��ͷ
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 9900;	//�������
				lock = 1;
			}
		}
	}
	else //�Ѿ���������
	{
		if(CHARGER == 1)
		{
			if( (DVC_1124.GP1_Temp > -5.0f) ||
				(DVC_1124.GP4_Temp > -5.0f)		
				)
			{
				if((CHARGER == 1) && (Flag.Overvoltage == 0) && (Flag.Charging_Overcurrent == 0))	//��������벢��û�з�����ѹ û�з���������
				{
					if((Flag.Overtemperature == 0))	//û�з�������
					{
						Flag.Charger_ON = 0;
					}
				}
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 0;	//�������
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
				if((Flag.Undervoltage == 0) && (Flag.Electric_Discharge_Overcurrent == 0))	//û�з���Ƿѹ û�з����ŵ����
				{
					if(Flag.Overtemperature == 1)
					{
						if(CHARGER == 1)	//���±����������ڳ��
						{
							Flag.Cock_Head = 0;//����ͷ
						}
					}
					else
					{
						Flag.Cock_Head = 0;//����ͷ
					}		
				}
				VESC_CAN_DATA.pBMS_TEMPS->BMS_Single_Temp[8] = 0;	//�������
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
 * @note  :VESC��ͷ
 * @param :��
 * @retval:��
 **************************************************/
void VESC_Cock_Head(void)
{
	static uint8_t lock = 0;
	if(lock == 0)
	{
		if(Flag.Cock_Head == 1)	//��Ҫ��ͷ
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
 * @note  :DVC1124�쳣����
 * @param :��
 * @retval:��
 **************************************************/
void BMS_Protection_Task(void)
{
	BMS_Overvoltage_Protection();			//��ѹ����		T5
	BMS_Undervoltage_Protection();			//Ƿѹ����		T6
	BMS_Discharge_Overcurrent_Protection();	//�ŵ��������	T7
	BMS_Charge_Overcurrent_Protection();	//����������	T8
	BMS_Short_Circuit_Protection();			//��·����		
	BMS_Overtemperature_Protection();		//���±���		T9
	BMS_Low_Temperature_Protection();		//���±���		T10
	VESC_Cock_Head();
}




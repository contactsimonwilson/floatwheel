/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.03.16
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			    						 		�Զ����⴦��
**************************************************************************************/
#include "CellBalance.h"
#include "DVC1124_app.h"

u8 bOTC;//���±�־λ
int uiCellVmin,uiCellVmax;
int	uiCellvotage[AFE_MAX_CELL_CNT];
u32	uiBalMaskFlags=0,uiBalMaskFlags_Prepared=0;
u32 newBals = 0;
u32 newBals_max = 0;

/**
	* @˵��	оƬ���±���
	* @����	������ֵ u8 temp
	* @����ֵ	
	* @ע	
*/
void OverTempProtect(u8 temp){
float t;
	t=DVC11XX_Calc_ChipTemp();//��ȡоƬ�¶�
	
	if(t>=temp)
	bOTC=1;		//������λ
	else
	bOTC=0;
}

/**
	* @˵��	��о�����С��ѹ����
	* @����	
	* @����ֵ	
	* @ע	
*/
void CalcuVolMaxMin(void){
	s8 cellIndex;
	u8 i;
	int cellVoltage;

	for(i=0;i<AFE_MAX_CELL_CNT;i++)
	{
		uiCellvotage[i]=DVC11XX_Calc_VCell(i);//������ѹʵ��ֵ��ԭ
	}

	uiCellVmin = uiCellVmax = uiCellvotage[0];//��ʼ��

	for(cellIndex=AFE_MAX_CELL_CNT-1;cellIndex>=0;cellIndex--)
	{
		cellVoltage=uiCellvotage[cellIndex];
		if( cellVoltage>uiCellVmax)
		{
			uiCellVmax = cellVoltage;
			if(uiCellVmin==0)
			{
				uiCellVmin=uiCellVmax;
			}
		}
		else if(cellVoltage<uiCellVmin && cellVoltage>0)
		{//��0
			uiCellVmin = cellVoltage;
		}
	}
}

/**
	* @˵��	�Զ����⴦��
	* @����	
	* @����ֵ	
	* @ע	
*/
void BalanceProcess(void)
{
	u8 i;
	
	newBals = 0;
	
	uiBalMaskFlags=(g_AfeRegs.R103_R105.CB[0]<<16)+(g_AfeRegs.R103_R105.CB[1]<<8)+g_AfeRegs.R103_R105.CB[2];//ˢ�µ�ǰ����λ
	
	for(i=0;i<AFE_MAX_CELL_CNT;i++)
	{
		if(DVC_1124.Single_Voltage[i] > uiBalanceVol_max)
		{
			newBals |= (1<<i);	//�������о����ѹ��Ҫ��������ĸ���λ
		}
	}
	if(newBals != uiBalMaskFlags)
	{
		Balance_Contrl(newBals);
	}
	
//	for(i=0;i<AFE_MAX_CELL_CNT;i++)
//	{
//		if(uiCellvotage[i] > uiBalanceVol_max)
//		{
//			newBals_max |= (1<<i);	//�������о����ѹ��Ҫ��������ĸ���λ
//		}
//	}
//	
//	if(((uiCellVmin>uiBalanceVol)&&(uiCellVmax-uiCellVmin)>=uiBalanceVolDiff) || (newBals_max != 0))
//	{//δ���¡���͵�ѹ���ھ��⿪����С��ѹ��ѹ����ھ��⿪����ֵ
//		
//		int cellVoltage=0;
//		for(i=0;i<AFE_MAX_CELL_CNT;i++)
//		{
//			cellVoltage=uiCellvotage[i];
//			if( (cellVoltage-uiCellVmin)>=uiBalanceVolDiff)
//			{
//				newBals |= (1<<i);	//�������Ҫ��������ĸ���λ
//			}
//		}
//		newBals |= newBals_max;
//	}
//	if(newBals!=uiBalMaskFlags)
//	{ //����λ�仯
//		if(newBals==uiBalMaskFlags_Prepared)
//		{
//			
//			uiBalMaskFlags=uiBalMaskFlags_Prepared;

//			Balance_Contrl(uiBalMaskFlags);
//			
//		}	
//		else
//		uiBalMaskFlags_Prepared=newBals; 
//	}
//	else 
//	{
//		uiBalMaskFlags_Prepared=uiBalMaskFlags;
//	}
		  
}

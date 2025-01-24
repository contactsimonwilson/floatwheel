/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.03.16
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			    						 		自动均衡处理
**************************************************************************************/
#include "CellBalance.h"
#include "DVC1124_app.h"

u8 bOTC;//过温标志位
int uiCellVmin,uiCellVmax;
int	uiCellvotage[AFE_MAX_CELL_CNT];
u32	uiBalMaskFlags=0,uiBalMaskFlags_Prepared=0;
u32 newBals = 0;
u32 newBals_max = 0;

/**
	* @说明	芯片过温保护
	* @参数	过温阈值 u8 temp
	* @返回值	
	* @注	
*/
void OverTempProtect(u8 temp){
float t;
	t=DVC11XX_Calc_ChipTemp();//获取芯片温度
	
	if(t>=temp)
	bOTC=1;		//过温置位
	else
	bOTC=0;
}

/**
	* @说明	电芯最大最小电压计算
	* @参数	
	* @返回值	
	* @注	
*/
void CalcuVolMaxMin(void){
	s8 cellIndex;
	u8 i;
	int cellVoltage;

	for(i=0;i<AFE_MAX_CELL_CNT;i++)
	{
		uiCellvotage[i]=DVC11XX_Calc_VCell(i);//各串电压实际值还原
	}

	uiCellVmin = uiCellVmax = uiCellvotage[0];//初始化

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
		{//防0
			uiCellVmin = cellVoltage;
		}
	}
}

/**
	* @说明	自动均衡处理
	* @参数	
	* @返回值	
	* @注	
*/
void BalanceProcess(void)
{
	u8 i;
	
	newBals = 0;
	
	uiBalMaskFlags=(g_AfeRegs.R103_R105.CB[0]<<16)+(g_AfeRegs.R103_R105.CB[1]<<8)+g_AfeRegs.R103_R105.CB[2];//刷新当前均衡位
	
	for(i=0;i<AFE_MAX_CELL_CNT;i++)
	{
		if(DVC_1124.Single_Voltage[i] > uiBalanceVol_max)
		{
			newBals |= (1<<i);	//计算出电芯最大电压需要开启均衡的各个位
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
//			newBals_max |= (1<<i);	//计算出电芯最大电压需要开启均衡的各个位
//		}
//	}
//	
//	if(((uiCellVmin>uiBalanceVol)&&(uiCellVmax-uiCellVmin)>=uiBalanceVolDiff) || (newBals_max != 0))
//	{//未过温、最低电压高于均衡开启最小电压、压差高于均衡开启阈值
//		
//		int cellVoltage=0;
//		for(i=0;i<AFE_MAX_CELL_CNT;i++)
//		{
//			cellVoltage=uiCellvotage[i];
//			if( (cellVoltage-uiCellVmin)>=uiBalanceVolDiff)
//			{
//				newBals |= (1<<i);	//计算出需要开启均衡的各个位
//			}
//		}
//		newBals |= newBals_max;
//	}
//	if(newBals!=uiBalMaskFlags)
//	{ //均衡位变化
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

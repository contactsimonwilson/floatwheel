/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.01.20
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			          AFE电压计算处理                              		
******************************************************************************/
#include "Voltage.h"
/////////////////////////////////////////////////////////////////////////////

static float s_SecondCALI_p1=0.35f/1000000,s_SecondCALI_p2=-0.12f/ 1000000,s_SecondCALI_preVcm=0,s_SecondCALI_preVcell_2nd=0;
u32 Sigma_SecondCALI=0;

/**
	* @说明	电压二次校准
	* @参数	电压采样值、电池串号
	* @返回值	float 电压值
	* @注	单位mV
*/
static float CellVolSecondaryCalibrate(float value,int cellno){
	
  if (cellno == 0) {
		s_SecondCALI_preVcm = 0;
		s_SecondCALI_preVcell_2nd = value;
	}
  else {
	s_SecondCALI_preVcm += s_SecondCALI_preVcell_2nd;
	s_SecondCALI_preVcell_2nd = value / (1 + s_SecondCALI_p1 * s_SecondCALI_preVcm + s_SecondCALI_p2 * s_SecondCALI_preVcm*s_SecondCALI_preVcm);
	}
  return s_SecondCALI_preVcell_2nd;
}
/**
	* @说明	计算电池组的各个电芯电压
	* @参数	寄存器R29~R76、R109
	* @返回值	u16 电压值
	* @注	单位mV
*/
float DVC11XX_Calc_VCell(u8 cellIndex){
	float fValue;
	u16 uwValue;
#ifndef	 DVC1124
	u8 cellMask=CellMask[cellIndex];
#else
	u8 cellMask=cellIndex;
#endif
		if(cellIndex>AFE_MAX_CELL_CNT-1)
			return ERROR;

	uwValue=(g_AfeRegs.R29_76.VCELLS[cellMask].VCELL_H<<8)|g_AfeRegs.R29_76.VCELLS[cellMask].VCELL_L;

	if(g_AfeRegs.R109.CVS){ //电池电压以有符号数显示，LSB=200μV
		fValue=_lsbVCELL_signed  * (s16)uwValue;
	}
  else{//电池电压以无符号数显示，LSB=100μV;
    fValue=_lsbVCELL * (u16)uwValue;
  }		
 
		fValue=CellVolSecondaryCalibrate(fValue,cellIndex); //电池二次校准

	return 	fValue*1000+0.5f;//四舍五入取整（单位mV）
}	

/**
	* @说明	计算电池组总电压
	* @参数	寄存器R7、R8
	* @返回值	u16 电压值
	* @注	单位mV
*/
u32 DVC11XX_Calc_VBAT(void){
	u16 uwValue = (g_AfeRegs.R7_8.VBAT_H<<8)|g_AfeRegs.R7_8.VBAT_L;
	float fValue= _lsbVCELL * 10000 * uwValue*12.8f;
  return 	(u32)(fValue+0.5f);//四舍五入取整
}

/**
	* @说明	计算PACK管脚电压值
	* @参数	寄存器R9、R10
	* @返回值	u16 电压值
	* @注 单位mV
*/
u32 DVC11XX_Calc_VPACK(void){
	u16 uwValue = (g_AfeRegs.R9_10.VPK_H<<8)|g_AfeRegs.R9_10.VPK_L;
	float fValue = _lsbVCELL * 10000 * uwValue*12.8f;
  return 	(u32)(fValue+0.5f);//四舍五入取整
}

/**
	* @说明	计算LOAD管脚电压值
	* @参数	寄存器R11、R12
	* @返回值	u16 电压值
	* @注 单位mV
*/
u32 DVC11XX_Calc_VLOAD(void){
	u16 uwValue = (g_AfeRegs.R11_12.VLD_H<<8)|g_AfeRegs.R11_12.VLD_L;
	float fValue = _lsbVCELL * 10000 * uwValue*12.8f;
  return 	(u32)(fValue+0.5f);//四舍五入取整
}
/**
	* @说明	计算V1P8管脚电压值
	* @参数	寄存器R15、R16
	* @返回值	u16 电压值
	* @注 单位mV
*/
u16 DVC11XX_Calc_V1P8(void){
	u16 uwValue=(g_AfeRegs.R15_16.V1P8_H<<8)|g_AfeRegs.R15_16.V1P8_L;
	float fValue = _lsbVCELL * 1000 * uwValue;
  return 	(u16)(fValue+0.5f);//四舍五入取整
}
/**
	* @说明	电芯屏蔽
	* @参数	屏蔽电芯各串号
	* @返回值	
	* @注 
*/
void CellTestClose(u32 cellnumber){

	if(cellnumber<=0xfffff)//u20
	{
		g_AfeRegs.R106.CM_H=cellnumber>>12;
		g_AfeRegs.R107.CM_M=((u16)cellnumber&0x0ff0)>>4;
		g_AfeRegs.R108.CM_L=(u8)cellnumber&0x0f;
		while(!DVC11XX_WriteRegs(AFE_ADDR_R(106),3));

	}

}

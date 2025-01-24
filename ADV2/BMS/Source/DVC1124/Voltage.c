/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.01.20
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			          AFE��ѹ���㴦��                              		
******************************************************************************/
#include "Voltage.h"
/////////////////////////////////////////////////////////////////////////////

static float s_SecondCALI_p1=0.35f/1000000,s_SecondCALI_p2=-0.12f/ 1000000,s_SecondCALI_preVcm=0,s_SecondCALI_preVcell_2nd=0;
u32 Sigma_SecondCALI=0;

/**
	* @˵��	��ѹ����У׼
	* @����	��ѹ����ֵ����ش���
	* @����ֵ	float ��ѹֵ
	* @ע	��λmV
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
	* @˵��	��������ĸ�����о��ѹ
	* @����	�Ĵ���R29~R76��R109
	* @����ֵ	u16 ��ѹֵ
	* @ע	��λmV
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

	if(g_AfeRegs.R109.CVS){ //��ص�ѹ���з�������ʾ��LSB=200��V
		fValue=_lsbVCELL_signed  * (s16)uwValue;
	}
  else{//��ص�ѹ���޷�������ʾ��LSB=100��V;
    fValue=_lsbVCELL * (u16)uwValue;
  }		
 
		fValue=CellVolSecondaryCalibrate(fValue,cellIndex); //��ض���У׼

	return 	fValue*1000+0.5f;//��������ȡ������λmV��
}	

/**
	* @˵��	���������ܵ�ѹ
	* @����	�Ĵ���R7��R8
	* @����ֵ	u16 ��ѹֵ
	* @ע	��λmV
*/
u32 DVC11XX_Calc_VBAT(void){
	u16 uwValue = (g_AfeRegs.R7_8.VBAT_H<<8)|g_AfeRegs.R7_8.VBAT_L;
	float fValue= _lsbVCELL * 10000 * uwValue*12.8f;
  return 	(u32)(fValue+0.5f);//��������ȡ��
}

/**
	* @˵��	����PACK�ܽŵ�ѹֵ
	* @����	�Ĵ���R9��R10
	* @����ֵ	u16 ��ѹֵ
	* @ע ��λmV
*/
u32 DVC11XX_Calc_VPACK(void){
	u16 uwValue = (g_AfeRegs.R9_10.VPK_H<<8)|g_AfeRegs.R9_10.VPK_L;
	float fValue = _lsbVCELL * 10000 * uwValue*12.8f;
  return 	(u32)(fValue+0.5f);//��������ȡ��
}

/**
	* @˵��	����LOAD�ܽŵ�ѹֵ
	* @����	�Ĵ���R11��R12
	* @����ֵ	u16 ��ѹֵ
	* @ע ��λmV
*/
u32 DVC11XX_Calc_VLOAD(void){
	u16 uwValue = (g_AfeRegs.R11_12.VLD_H<<8)|g_AfeRegs.R11_12.VLD_L;
	float fValue = _lsbVCELL * 10000 * uwValue*12.8f;
  return 	(u32)(fValue+0.5f);//��������ȡ��
}
/**
	* @˵��	����V1P8�ܽŵ�ѹֵ
	* @����	�Ĵ���R15��R16
	* @����ֵ	u16 ��ѹֵ
	* @ע ��λmV
*/
u16 DVC11XX_Calc_V1P8(void){
	u16 uwValue=(g_AfeRegs.R15_16.V1P8_H<<8)|g_AfeRegs.R15_16.V1P8_L;
	float fValue = _lsbVCELL * 1000 * uwValue;
  return 	(u16)(fValue+0.5f);//��������ȡ��
}
/**
	* @˵��	��о����
	* @����	���ε�о������
	* @����ֵ	
	* @ע 
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

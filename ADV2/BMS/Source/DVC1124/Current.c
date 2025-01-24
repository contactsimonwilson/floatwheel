/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.01.20
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			          AFE�������㴦��                              		
******************************************************************************/
#include "Current.h"
/////////////////////////////////////////////////////////////////////////////


//ͨ��������CC1�Ĳ���ֵ��������� 
//��ؼĴ��� R2~R3
float DVC11XX_Calc_CurrentWithCC1(float senseResistance_mR){
	s16 swValue=(g_AfeRegs.R2_3.CC1_H<<8)|g_AfeRegs.R2_3.CC1_L;
	return swValue*_lsbCC1*1000.0f/senseResistance_mR; //���ص���ֵ����λA��
}	


//ͨ��������CC2�Ĳ���ֵ��������� 
//��ؼĴ��� R4~R6
float DVC11XX_Calc_CurrentWithCC2(float senseResistance_mR){
	s32 iValue=((g_AfeRegs.R4_6.CC2_H<<12)|(g_AfeRegs.R4_6.CC2_M<<4)|g_AfeRegs.R4_6.CC2_L);
  if(iValue&0x80000) iValue|=0xFFF00000; //��Ϊ��������32λ����	
	return iValue*_lsbCC2*1000.0f/senseResistance_mR; //���ص���ֵ����λA��
}

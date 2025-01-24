/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.01.20
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			          AFE电流计算处理                              		
******************************************************************************/
#include "Current.h"
/////////////////////////////////////////////////////////////////////////////


//通过过滤器CC1的采样值来计算电流 
//相关寄存器 R2~R3
float DVC11XX_Calc_CurrentWithCC1(float senseResistance_mR){
	s16 swValue=(g_AfeRegs.R2_3.CC1_H<<8)|g_AfeRegs.R2_3.CC1_L;
	return swValue*_lsbCC1*1000.0f/senseResistance_mR; //返回电流值（单位A）
}	


//通过过滤器CC2的采样值来计算电流 
//相关寄存器 R4~R6
float DVC11XX_Calc_CurrentWithCC2(float senseResistance_mR){
	s32 iValue=((g_AfeRegs.R4_6.CC2_H<<12)|(g_AfeRegs.R4_6.CC2_M<<4)|g_AfeRegs.R4_6.CC2_L);
  if(iValue&0x80000) iValue|=0xFFF00000; //若为负数则补足32位补码	
	return iValue*_lsbCC2*1000.0f/senseResistance_mR; //返回电流值（单位A）
}

/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.03.16
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			    						 		��������
**************************************************************************************/
#include "CellBalance.h"
/**
	* @˵��	�������
	* @����	u32 vlaue ����λ
	* @����ֵ	
	* @ע 
*/
void Balance_Contrl(u32 vlaue){
	if(vlaue<0xffffff)
	{
		g_AfeRegs.R103_R105.CB[0]=vlaue>>16;
		g_AfeRegs.R103_R105.CB[1]=vlaue>>8;
		g_AfeRegs.R103_R105.CB[2]=vlaue&0xff;
		
		DVC11XX_WriteRegs(AFE_ADDR_R(103),3);//�򿪶�Ӧ����λ
	}
}



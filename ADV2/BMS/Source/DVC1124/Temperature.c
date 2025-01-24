/******************************************************************************
;  *   	@MCU				 STM32F103C8T6
;  *   	@Create Date         2023.09.20
;  *    @Official website		 http://www.devechip.com/
;  *----------------------Abstract Description---------------------------------
;  *			         					 AFE温度计算处理                              		
******************************************************************************/
#include "Temperature.h"
/////////////////////////////////////////////////////////////////////////////


u16 Rpu=0;

const int NCP18XH103_Temp[34]={//℃
-40,-35,-30,-25,-20,-15,-10,-5,
0,5,10,15,20,25,30,35,
40,45,50,55,60,65,70,75,
80,85,90,95,100,105,110,115,
120,125};
const float NCP18XH103_Res[34]={//kohm
195.652,148.171,113.347,87.559,68.237,53.65,42.406,33.892,
27.219,22.021,17.926,14.674,12.081,10,8.315,6.948,
5.834,4.917,4.161,3.535,3.014,2.586,2.228,1.925,
1.669,1.452,1.268,1.11,0.974,0.858,0.758,0.672,
0.596,0.531};

/**
	* @说明	读取NFRT计算上拉电阻
	* @参数	
	* @返回值	
	* @注	
*/
void Read_NFRT (void)
{
	DVC11XX_ReadRegs(AFE_ADDR_R(126),1);
	Rpu=g_AfeRegs.R126.F1RT*25+6800;//欧姆
}

/**
	* @说明	芯片温度计算
	* @参数	
	* @返回值	float Tp_Value 温度值
	* @注	
*/
float DVC11XX_Calc_ChipTemp(void)
{
	float Tp_Value;
	u16 VCT=(g_AfeRegs.R13_14.VCT_H<<8)|g_AfeRegs.R13_14.VCT_L;
	Tp_Value=VCT*0.24467f-271.3f;
	return Tp_Value;
}

/**
	* @说明	温敏电阻采样温度计算
	* @参数	u8 GP 复用管脚
	* @返回值	float Tp_Value 温度值
	* @注	
*/
float DVC11XX_Calc_BatTemp(u8 GP)
{
	float V1P8t,VGPt,Tp_Value,GP_res;
	u8 i,t=34;
	u16 V1P8=(g_AfeRegs.R15_16.V1P8_H<<8)|g_AfeRegs.R15_16.V1P8_L;
	u16 GPn_T=(g_AfeRegs.R17_28.VGP[GP].VGP_H<<8)|g_AfeRegs.R17_28.VGP[GP].VGP_L;

	V1P8t=V1P8*0.1f;//V1P8 * _lsbVCELL *1000 单位mv

	VGPt=GPn_T*0.1f;//VGP1 * _lsbVCELL *1000 单位mv

	GP_res=(VGPt/V1P8t*Rpu)/(1-VGPt/V1P8t)/1000.0f;//GP1温敏电阻计算值 

	for(i=0;i<t;)//查表
	{
		if(GP_res<=NCP18XH103_Res[i])
		i++;
		else 
		t=i;
	}
	Tp_Value=NCP18XH103_Temp[t]-//平滑处理
	(NCP18XH103_Res[t]-GP_res)/(NCP18XH103_Res[t]-NCP18XH103_Res[t-1])*5;

	return Tp_Value;
}
